/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./mobile.html", 
    "./desktop.html",
    "./ecosystem.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      fontFamily: {
        'sf': ['-apple-system', 'BlinkMacSystemFont', 'SF Pro Display', 'SF Pro Text', 'system-ui', 'sans-serif'],
        'sf-mono': ['SF Mono', 'Monaco', 'Inconsolata', 'Roboto Mono', 'monospace'],
      },
      colors: {
        apple: {
          // Apple System Colors (iOS 17 & macOS Sonoma)
          blue: '#007AFF',
          'blue-light': '#5AC8FA',
          'blue-dark': '#0051D5',
          'blue-pastel': '#B3D9FF',
          
          // Apple Gray Scale
          gray: {
            50: '#FAFAFA',
            100: '#F5F5F7',  // Apple Light Gray
            150: '#F0F0F2',
            200: '#E5E5E7',
            250: '#DADADC',
            300: '#D2D2D7',
            350: '#C7C7CC',
            400: '#86868B',  // Apple Medium Gray
            500: '#6E6E73',
            600: '#515154',
            700: '#1D1D1F',  // Apple Dark Gray
            800: '#161618',
            900: '#0D0D0F',
          },
          
          // Apple Semantic Colors
          red: '#FF3B30',
          orange: '#FF9500',
          yellow: '#FFCC00',
          green: '#34C759',
          mint: '#00C7BE',
          teal: '#30B0C7',
          cyan: '#32D2FF',
          indigo: '#5856D6',
          purple: '#AF52DE',
          pink: '#FF2D92',
          brown: '#A2845E',
        },
        
        // Safari-specific colors
        safari: {
          toolbar: 'rgba(246, 246, 246, 0.8)',
          'toolbar-dark': 'rgba(40, 40, 40, 0.8)',
          tab: 'rgba(255, 255, 255, 0.7)',
          'tab-active': 'rgba(255, 255, 255, 0.95)',
          'tab-hover': 'rgba(255, 255, 255, 0.85)',
        }
      },
      
      spacing: {
        '4.5': '1.125rem',
        '18': '4.5rem',
        '88': '22rem',
        '92': '23rem',
        '100': '25rem',
      },
      
      borderRadius: {
        'squircle': '18px',        // iOS Squircle
        'squircle-sm': '12px',     // Small Squircle
        'squircle-lg': '24px',     // Large Squircle
        'capsule': '50px',         // Perfect capsule
        '4xl': '2rem',
        '5xl': '2.5rem',
      },
      
      backdropBlur: {
        'xs': '2px',
        '4xl': '72px',
      },
      
      fontSize: {
        'xs': ['11px', { lineHeight: '16px', letterSpacing: '0.06em' }],
        'sm': ['13px', { lineHeight: '18px', letterSpacing: '0.01em' }],
        'base': ['15px', { lineHeight: '22px', letterSpacing: '0em' }],
        'lg': ['17px', { lineHeight: '24px', letterSpacing: '-0.01em' }],
        'xl': ['20px', { lineHeight: '28px', letterSpacing: '-0.02em' }],
        '2xl': ['24px', { lineHeight: '32px', letterSpacing: '-0.02em' }],
        '3xl': ['32px', { lineHeight: '40px', letterSpacing: '-0.03em' }],
      },
      
      animation: {
        'spring-in': 'springIn 0.4s cubic-bezier(0.175, 0.885, 0.32, 1.275)',
        'spring-out': 'springOut 0.3s cubic-bezier(0.55, 0.055, 0.675, 0.19)',
        'fade-in-up': 'fadeInUp 0.6s cubic-bezier(0.25, 0.46, 0.45, 0.94)',
        'slide-in-bottom': 'slideInBottom 0.4s cubic-bezier(0.25, 0.46, 0.45, 0.94)',
        'scale-in': 'scaleIn 0.3s cubic-bezier(0.25, 0.46, 0.45, 0.94)',
        'bounce-gentle': 'bounceGentle 0.6s ease-out',
        'pulse-subtle': 'pulseSubtle 2s ease-in-out infinite',
      },
      
      keyframes: {
        springIn: {
          '0%': {
            opacity: '0',
            transform: 'scale(0.8) translateY(20px)',
          },
          '100%': {
            opacity: '1',
            transform: 'scale(1) translateY(0)',
          },
        },
        springOut: {
          '0%': {
            opacity: '1',
            transform: 'scale(1) translateY(0)',
          },
          '100%': {
            opacity: '0',
            transform: 'scale(0.8) translateY(20px)',
          },
        },
        fadeInUp: {
          '0%': {
            opacity: '0',
            transform: 'translateY(30px)',
          },
          '100%': {
            opacity: '1',
            transform: 'translateY(0)',
          },
        },
        slideInBottom: {
          '0%': {
            opacity: '0',
            transform: 'translateY(100%)',
          },
          '100%': {
            opacity: '1',
            transform: 'translateY(0)',
          },
        },
        scaleIn: {
          '0%': {
            opacity: '0',
            transform: 'scale(0.9)',
          },
          '100%': {
            opacity: '1',
            transform: 'scale(1)',
          },
        },
        bounceGentle: {
          '0%, 20%, 53%, 80%, 100%': {
            transform: 'translate3d(0,0,0)',
          },
          '40%, 43%': {
            transform: 'translate3d(0, -8px, 0)',
          },
          '70%': {
            transform: 'translate3d(0, -4px, 0)',
          },
          '90%': {
            transform: 'translate3d(0, -2px, 0)',
          },
        },
        pulseSubtle: {
          '0%, 100%': {
            opacity: '1',
          },
          '50%': {
            opacity: '0.8',
          },
        },
      },
      
      boxShadow: {
        'glass': '0 8px 32px rgba(0, 0, 0, 0.1)',
        'glass-lg': '0 20px 40px rgba(0, 0, 0, 0.12)',
        'apple': '0 1px 3px rgba(0, 0, 0, 0.12), 0 1px 2px rgba(0, 0, 0, 0.24)',
        'apple-lg': '0 4px 6px rgba(0, 0, 0, 0.07), 0 10px 20px rgba(0, 0, 0, 0.1)',
        'safari-tab': '0 1px 3px rgba(0, 0, 0, 0.1)',
        'safari-toolbar': '0 1px 0 rgba(0, 0, 0, 0.1)',
      },
      
      transitionTimingFunction: {
        'apple': 'cubic-bezier(0.25, 0.46, 0.45, 0.94)',
        'spring': 'cubic-bezier(0.175, 0.885, 0.32, 1.275)',
        'bounce-out': 'cubic-bezier(0.55, 0.055, 0.675, 0.19)',
      },
    },
  },
  plugins: [],
}