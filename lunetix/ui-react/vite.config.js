import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { resolve } from 'path'

export default defineConfig({
  plugins: [react()],
  resolve: {
    alias: {
      '@': resolve(__dirname, './src'),
    },
  },
  build: {
    outDir: '../browser/ui/dist',
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        mobile: resolve(__dirname, 'mobile.html'),
        desktop: resolve(__dirname, 'desktop.html'),
        ecosystem: resolve(__dirname, 'ecosystem.html'),
      },
    },
  },
  server: {
    port: 3000,
    host: true,
  },
})