import { defineConfig } from 'vitest/config'

export default defineConfig({
  server: {
    headers: {
      // Required for SharedArrayBuffer (if using threads)
      'Cross-Origin-Opener-Policy': 'same-origin',
      'Cross-Origin-Embedder-Policy': 'require-corp'
    }
  },
  define: {
    // Make BUILD_TYPE available to the app (defaults to Debug for development)
    'import.meta.env.BUILD_TYPE': JSON.stringify(process.env.BUILD_TYPE || 'Debug')
  },
  test: {
    environment: 'jsdom'
  }
})
