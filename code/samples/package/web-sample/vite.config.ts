import { defineConfig } from 'vitest/config'
import { fileURLToPath } from 'url'
import { resolve } from 'path'

const __dirname = fileURLToPath(new URL('.', import.meta.url))

export default defineConfig({
  server: {
    headers: {
      // Required for SharedArrayBuffer (if using threads)
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    },
    fs: {
      // TODO (stouff) ask web people if this is undesirable for a test app
      // Allow serving files from the mapitron package outside the project root
      allow: [resolve(__dirname, '../..')]
    }
  },
  plugins: [
    {
      name: 'wasm-reload',
      configureServer(server) {
        // Vite only watches inside the project root by default; explicitly add
        // the mapitron package output dir so handleHotUpdate fires when cmake rebuilds
        server.watcher.add(resolve(__dirname, '../../packages/web/mapitron/src'))
      },
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
