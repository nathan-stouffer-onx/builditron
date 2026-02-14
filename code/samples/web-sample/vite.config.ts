import { defineConfig } from 'vite'

export default defineConfig({
  server: {
    headers: {
      // Required for SharedArrayBuffer (if using threads)
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    }
  }
})
