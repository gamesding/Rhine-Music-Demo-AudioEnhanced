[CmdletBinding()]
param([switch]$PrepareOnly)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
$projectRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))
$buildRoot = [IO.Path]::GetFullPath((Join-Path $projectRoot '.tools\windows-build'))
if (-not [Environment]::Is64BitOperatingSystem) { throw 'The standalone build requires 64-bit Windows.' }
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12
Add-Type -AssemblyName System.IO.Compression.FileSystem
$manifest = Get-Content -LiteralPath (Join-Path $PSScriptRoot 'windows-build-tools.json') -Raw -Encoding UTF8 | ConvertFrom-Json

function Assert-BuildPath([string]$Target) {
    $absolute = [IO.Path]::GetFullPath($Target)
    if (-not $absolute.StartsWith($buildRoot + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
        throw "Refusing to modify a path outside the local build cache: $absolute"
    }
    return $absolute
}
function Prepare-Tool([string]$Name, $Spec) {
    $toolRoot = Assert-BuildPath (Join-Path $buildRoot $Name)
    $executable = Join-Path (Join-Path $toolRoot $Spec.folder) $Spec.executable
    $marker = Join-Path $toolRoot '.archive-sha256'
    if ((Test-Path -LiteralPath $executable -PathType Leaf) -and (Test-Path -LiteralPath $marker -PathType Leaf)) {
        if ((Get-Content -LiteralPath $marker -Raw).Trim() -eq $Spec.sha256) { return $executable }
    }
    New-Item -ItemType Directory -Path $buildRoot -Force | Out-Null
    $archive = Assert-BuildPath (Join-Path $buildRoot ($Name + '-' + $Spec.version + '.zip'))
    $validArchive = (Test-Path -LiteralPath $archive -PathType Leaf) -and ((Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash.ToLowerInvariant() -eq $Spec.sha256)
    if (-not $validArchive) {
        $partial = Assert-BuildPath ($archive + '.partial')
        Write-Host "Downloading official $Name $($Spec.version)..."
        Invoke-WebRequest -Uri $Spec.url -OutFile $partial -UseBasicParsing
        if ((Get-FileHash -LiteralPath $partial -Algorithm SHA256).Hash.ToLowerInvariant() -ne $Spec.sha256) {
            Remove-Item -LiteralPath $partial -Force
            throw "$Name download failed SHA-256 verification."
        }
        Move-Item -LiteralPath $partial -Destination $archive -Force
    }
    $staging = Assert-BuildPath ($toolRoot + '.part-' + [Guid]::NewGuid().ToString('N').Substring(0,8))
    try {
        [IO.Compression.ZipFile]::ExtractToDirectory($archive, $staging)
        if (-not (Test-Path -LiteralPath (Join-Path (Join-Path $staging $Spec.folder) $Spec.executable) -PathType Leaf)) { throw "$Name archive has no expected executable." }
        # Both resolved paths were checked against the owned build cache.
        $toolRoot = Assert-BuildPath $toolRoot
        if (Test-Path -LiteralPath $toolRoot) { Remove-Item -LiteralPath $toolRoot -Recurse -Force }
        Move-Item -LiteralPath $staging -Destination $toolRoot
        [IO.File]::WriteAllText($marker, $Spec.sha256, [Text.UTF8Encoding]::new($false))
    } finally {
        $staging = Assert-BuildPath $staging
        if (Test-Path -LiteralPath $staging) { Remove-Item -LiteralPath $staging -Recurse -Force }
    }
    return $executable
}
function Invoke-Node([string[]]$NodeArguments) {
    & $script:buildNode @NodeArguments
    if ($LASTEXITCODE -ne 0) { throw "Node command failed (exit $LASTEXITCODE): $($NodeArguments -join ' ')" }
}
function Invoke-Npm([string[]]$PackageArguments) {
    Invoke-Node (@($script:npmCli) + $PackageArguments)
}

$previousPath = $env:PATH
$previousCompiler = $env:RHINE_CXX
Push-Location -LiteralPath $projectRoot
try {
    $script:buildNode = Prepare-Tool 'node' $manifest.node
    $buildZig = Prepare-Tool 'zig' $manifest.zig
    $script:npmCli = Join-Path (Split-Path -Parent $script:buildNode) 'node_modules\npm\bin\npm-cli.js'
    $env:PATH = (Split-Path -Parent $script:buildNode) + ';' + $previousPath
    $env:RHINE_CXX = $buildZig
    Write-Host "Node: $script:buildNode"
    Write-Host "Zig:  $buildZig"
    if ($PrepareOnly) { Write-Host 'Portable build tools are ready.'; exit 0 }
    Invoke-Npm -PackageArguments @('ci')
    Invoke-Npm -PackageArguments @('run', 'build:native')
    Invoke-Npm -PackageArguments @('run', 'build:sony')
    Invoke-Npm -PackageArguments @('run', 'check:sony')
    Invoke-Npm -PackageArguments @('run', 'check:native')
    Invoke-Npm -PackageArguments @('run', 'check:audio')
    Invoke-Npm -PackageArguments @('run', 'check:hires')
    Invoke-Npm -PackageArguments @('run', 'check:music')
    Invoke-Npm -PackageArguments @('run', 'check:content')
    Invoke-Npm -PackageArguments @('run', 'check:viewport')
    Invoke-Npm -PackageArguments @('run', 'build')
    Invoke-Npm -PackageArguments @('run', 'package:windows', '--', '--skip-build')
    Invoke-Node -NodeArguments @('scripts/check-windows-package.mjs')
    Write-Host ''
    Write-Host 'Build and isolated executable verification passed.' -ForegroundColor Green
    Write-Host (Join-Path $projectRoot 'release\Rhine Music.exe')
} catch {
    Write-Host $_.Exception.Message -ForegroundColor Red
    exit 1
} finally {
    $env:PATH = $previousPath
    $env:RHINE_CXX = $previousCompiler
    Pop-Location
}
