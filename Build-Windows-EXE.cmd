@echo off
setlocal
cd /d "%~dp0"
"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -ExecutionPolicy Bypass -File "%~dp0scripts\build-windows.ps1"
set "build_result=%errorlevel%"
if "%build_result%"=="0" (
  echo.
  echo Ready: release\Rhine Music.exe
) else (
  echo.
  echo Build failed. Read the error above before retrying.
)
pause
exit /b %build_result%
