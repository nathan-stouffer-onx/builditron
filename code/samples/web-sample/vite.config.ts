import { defineConfig } from 'vitest/config'
import { fileURLToPath } from 'url'
import { resolve } from 'path'

const buildType = (process.env.BUILD_TYPE ?? 'Debug').toLowerCase()
const __dirname = fileURLToPath(new URL('.', import.meta.url))

export default defineConfig({
  resolve: {
    alias: {
      'mapitron': resolve(__dirname, `../../packages/web/mapitron/src/${buildType}/mapitron.js`)
    }
  },
  server: {
    headers: {
      // Required for SharedArrayBuffer (if using threads)
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    },
    fs: {
      // Allow serving files from the mapitron package outside the project root
      allow: [resolve(__dirname, '../..')]
    },
    watch: {
      // Watch the mapitron package for changes
      ignored: ['!**/packages/web/mapitron/src/**']
    }
  },
  plugins: [
    {
      name: 'wasm-reload',
      handleHotUpdate({ file, server }) {
        // Force full reload when WASM or the mapitron JS module changes
        if (file.endsWith('.wasm') || file.endsWith('mapitron.js')) {
          server.ws.send({
            type: 'full-reload',
            path: '*'
          })
          return []
        }
      }
    }
  ],
  test: {
    environment: 'node'
  }
})
