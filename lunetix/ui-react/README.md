# Lunetix Browser - React + Tailwind UI

Modern React-based user interface for the Lunetix browser with Apple-inspired design system.

## 🚀 Features

- **React 18** with modern hooks and functional components
- **Tailwind CSS** with custom Apple design system
- **Framer Motion** for smooth animations and transitions
- **Vite** for fast development and optimized builds
- **Apple Design Language** - iOS 17 & macOS Sonoma inspired
- **Responsive Design** - Mobile-first with desktop adaptations
- **Component Architecture** - Modular and reusable components

## 📁 Project Structure

```
lunetix/ui-react/
├── src/
│   ├── components/
│   │   ├── MobileInterface.jsx      # iOS-style mobile interface
│   │   ├── DesktopInterface.jsx     # macOS-style desktop interface
│   │   ├── MobileAddressBar.jsx     # Bottom-floating address bar
│   │   ├── DesktopToolbar.jsx       # Safari-style toolbar
│   │   ├── TabSwitcher.jsx          # Animated tab switcher
│   │   └── EcosystemDemo.jsx        # Interactive demo showcase
│   ├── utils/
│   │   └── browserBridge.js         # C++ backend communication
│   ├── main.jsx                     # React app entry point
│   └── index.css                    # Global styles + Tailwind
├── public/                          # Static assets
├── index.html                       # Main entry (auto-detect device)
├── mobile.html                      # Mobile-specific entry
├── desktop.html                     # Desktop-specific entry
├── ecosystem.html                   # Demo showcase entry
├── package.json                     # Dependencies and scripts
├── vite.config.js                   # Vite build configuration
└── tailwind.config.js               # Tailwind + Apple design system
```

## 🎨 Design System

### Colors
- **Apple Blue**: `#007AFF` (Primary brand color)
- **Apple Gray Scale**: From `#FAFAFA` to `#1D1D1F`
- **Semantic Colors**: Red, Orange, Yellow, Green, Purple, etc.

### Typography
- **Font Family**: SF Pro Display, SF Pro Text, system fonts
- **Font Sizes**: Responsive scale from 11px to 32px
- **Font Weights**: Thin (100) to Bold (700)

### Border Radius
- **Squircle**: `18px` (iOS-style rounded corners)
- **Capsule**: `50px` (Perfect pill shape)
- **Variants**: Small (12px), Large (24px)

### Animations
- **Spring**: Smooth, bouncy transitions
- **Apple Easing**: `cubic-bezier(0.25, 0.46, 0.45, 0.94)`
- **Framer Motion**: Advanced gesture and layout animations

## 🛠️ Development

### Prerequisites
- Node.js 18+ with npm
- Modern browser with ES2023+ support

### Setup
```bash
# Install dependencies
npm install

# Start development server
npm run dev

# Build for production
npm run build

# Preview production build
npm run preview
```

### Build Scripts
- `build_lunetix_react.bat` - Complete build process
- `start_lunetix_react.bat` - Launch browser with React UI

## 📱 Interfaces

### Mobile Interface
- **Design**: iOS 17 inspired
- **Layout**: Bottom-floating address bar
- **Features**: Touch-optimized, gesture support
- **Entry**: `mobile.html`

### Desktop Interface  
- **Design**: macOS Sonoma inspired
- **Layout**: Safari-style toolbar and tabs
- **Features**: Keyboard shortcuts, window controls
- **Entry**: `desktop.html`

### Ecosystem Demo
- **Purpose**: Interactive showcase
- **Features**: Device switching, feature highlights
- **Entry**: `ecosystem.html`

## 🔗 Browser Integration

### Browser Bridge (`browserBridge.js`)
Handles communication between React UI and C++ Chromium backend:

```javascript
import { useBrowserBridge } from './utils/browserBridge';

const bridge = useBrowserBridge();

// Navigation
bridge.navigate('https://example.com');
bridge.goBack();
bridge.goForward();
bridge.reload();

// Tab Management
bridge.createTab();
bridge.closeTab(tabId);
bridge.switchTab(tabId);

// Event Listeners
bridge.on('navigation-state', (data) => {
  // Handle navigation updates
});
```

## 🎯 Component Architecture

### Core Components
- **MobileInterface**: Main mobile app container
- **DesktopInterface**: Main desktop app container
- **MobileAddressBar**: iOS-style bottom address bar
- **DesktopToolbar**: macOS-style top toolbar
- **TabSwitcher**: Animated tab overview

### Shared Features
- State management with React hooks
- Responsive design with Tailwind
- Smooth animations with Framer Motion
- Apple design system compliance
- Accessibility support

## 🚀 Deployment

### Production Build
```bash
npm run build
```

Generates optimized files in `../browser/ui/dist/`:
- `index.html` - Main entry with device detection
- `mobile.html` - Mobile-specific build
- `desktop.html` - Desktop-specific build  
- `ecosystem.html` - Demo showcase build
- `assets/` - Optimized JS, CSS, and static files

### Browser Integration
Built files are served by the Chromium backend and loaded as app windows:

```bash
# Mobile interface
chrome.exe --app="file:///path/to/mobile.html" --window-size=400,900

# Desktop interface  
chrome.exe --app="file:///path/to/desktop.html" --window-size=1200,800
```

## 🎨 Customization

### Tailwind Configuration
Modify `tailwind.config.js` to customize:
- Color palette
- Typography scale
- Spacing system
- Animation timings
- Component variants

### Component Styling
Components use Tailwind utility classes with custom design tokens:
```jsx
<div className="bg-apple-gray-100 rounded-squircle shadow-apple">
  <span className="font-sf text-apple-gray-700">Content</span>
</div>
```

## 📚 Dependencies

### Core
- `react` - UI library
- `react-dom` - DOM rendering
- `react-router-dom` - Client-side routing

### Styling
- `tailwindcss` - Utility-first CSS
- `autoprefixer` - CSS vendor prefixes
- `postcss` - CSS processing

### Animation
- `framer-motion` - Advanced animations
- `lucide-react` - Modern icon library

### Development
- `vite` - Fast build tool
- `@vitejs/plugin-react` - React support
- `eslint` - Code linting

## 🔧 Browser Bridge API

Complete API for C++ backend communication:

### Navigation
- `navigate(url)` - Navigate to URL
- `goBack()` - Go back in history
- `goForward()` - Go forward in history
- `reload()` - Reload current page

### Tab Management
- `createTab(url?)` - Create new tab
- `closeTab(tabId)` - Close specific tab
- `switchTab(tabId)` - Switch to tab
- `updateTab(tabId, props)` - Update tab properties

### Window Management
- `createWindow(options)` - Create new window
- `closeWindow(windowId)` - Close window
- `minimizeWindow()` - Minimize window
- `maximizeWindow()` - Maximize window

### Data Management
- `addBookmark(url, title)` - Add bookmark
- `getHistory(options)` - Get browsing history
- `clearBrowsingData(options)` - Clear browser data

## 🎉 Getting Started

1. **Build the React UI**:
   ```bash
   build_lunetix_react.bat
   ```

2. **Launch the browser**:
   ```bash
   start_lunetix_react.bat
   ```

3. **Choose your interface**:
   - Mobile (iOS 17 style)
   - Desktop (macOS Sonoma style)
   - Ecosystem Demo

4. **Start developing**:
   - Modify components in `src/components/`
   - Update styles in `tailwind.config.js`
   - Test with `npm run dev`

## 🌟 Features Showcase

- **Glassmorphism Effects**: Translucent backgrounds with blur
- **Spring Animations**: Natural, bouncy transitions
- **Responsive Design**: Mobile-first with desktop enhancements
- **Touch Gestures**: Swipe, pinch, and tap interactions
- **Keyboard Shortcuts**: Desktop productivity features
- **Dark Mode Support**: Automatic system preference detection
- **Accessibility**: WCAG compliant with screen reader support

---

Built with ❤️ using React, Tailwind CSS, and Apple's design principles.