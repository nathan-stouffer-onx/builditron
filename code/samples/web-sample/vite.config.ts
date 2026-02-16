import { defineConfig } from 'vitest/config'

export default defineConfig({
  server: {
    headers: {
      // Required for SharedArrayBuffer (if using threads)
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    },
    watch: {
      // Watch WASM files for changes
      ignored: ['!**/src/wasm/**']
    }
  },
  define: {
    // Make BUILD_TYPE available to the app (defaults to Debug for development)
    'import.meta.env.BUILD_TYPE': JSON.stringify(process.env.BUILD_TYPE || 'Debug')
  },
  plugins: [
    {
      name: 'wasm-reload',
      handleHotUpdate({ file, server }) {
        // Force full reload when WASM files change (HMR doesn't work well with WASM)
        if (file.endsWith('.wasm') || (file.includes('/wasm/') && file.endsWith('.js'))) {
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
    environment: 'jsdom'
  }
})
