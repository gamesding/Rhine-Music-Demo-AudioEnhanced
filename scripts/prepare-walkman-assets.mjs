import path from 'node:path'
import { promises as fs } from 'node:fs'
import { createHash } from 'node:crypto'
import { fileURLToPath } from 'node:url'
import manifest from './sony-walkman/assets.json' with { type: 'json' }

const project = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '..')
export async function installWalkmanAssets(source, destination = process.env.SONY_WALKMAN_ASSETS ?? path.join(project,'vendor/sony-walkman')) {
  const from = path.resolve(source), to = path.resolve(destination)
  // Verify the whole pack before replacing any local runtime file.
  const files = []
  for (const [name, expected] of Object.entries(manifest.files)) {
    const bytes = await fs.readFile(path.join(from,name))
    if (createHash('sha256').update(bytes).digest('hex') !== expected) throw new Error(`Sony original hash mismatch: ${name}`)
    files.push([name,bytes])
  }
  await fs.mkdir(to,{ recursive:true })
  if (from !== to) for (const [name,bytes] of files) {
    const target = path.join(to,name)
    await fs.writeFile(`${target}.tmp`,bytes,{ mode:0o600 })
    await fs.rename(`${target}.tmp`,target)
  }
  return { revision:manifest.revision, verifiedFiles:files.length }
}
if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) {
  const index = process.argv.indexOf('--from')
  if (index < 0 || !process.argv[index+1]) {
    console.error('Usage: node scripts/prepare-walkman-assets.mjs --from <private extracted runtime-assets directory>')
    process.exitCode = 1
  } else {
    try { console.log(JSON.stringify(await installWalkmanAssets(process.argv[index+1]))) }
    catch (error) { console.error(error.message); process.exitCode = 1 }
  }
}
