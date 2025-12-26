/**
 * Lunetix Browser Bridge
 * Interface untuk komunikasi antara React UI dan C++ Backend
 */

class LunetixBrowserBridge {
  constructor() {
    this.listeners = new Map();
    this.isReady = false;
    this.init();
  }

  /**
   * Initialize bridge connection
   */
  init() {
    // Check if running in Chromium environment
    if (typeof window !== 'undefined' && window.chrome) {
      this.isReady = true;
      this.setupMessageHandlers();
    }
  }

  /**
   * Setup message handlers for C++ communication
   */
  setupMessageHandlers() {
    // Listen for messages from C++ backend
    window.addEventListener('message', (event) => {
      if (event.source !== window) return;
      
      const { type, data } = event.data;
      if (type && type.startsWith('lunetix:')) {
        this.handleBackendMessage(type, data);
      }
    });
  }

  /**
   * Handle messages from C++ backend
   */
  handleBackendMessage(type, data) {
    const listeners = this.listeners.get(type) || [];
    listeners.forEach(callback => {
      try {
        callback(data);
      } catch (error) {
        console.error('Error in bridge listener:', error);
      }
    });
  }

  /**
   * Send message to C++ backend
   */
  sendToBackend(type, data = {}) {
    if (!this.isReady) {
      console.warn('Bridge not ready, queuing message:', type);
      return;
    }

    const message = {
      type: `lunetix:${type}`,
      data,
      timestamp: Date.now()
    };

    // Send via postMessage for C++ to intercept
    window.postMessage(message, '*');
  }

  /**
   * Register listener for backend messages
   */
  on(type, callback) {
    const fullType = type.startsWith('lunetix:') ? type : `lunetix:${type}`;
    
    if (!this.listeners.has(fullType)) {
      this.listeners.set(fullType, []);
    }
    
    this.listeners.get(fullType).push(callback);
    
    // Return unsubscribe function
    return () => {
      const listeners = this.listeners.get(fullType) || [];
      const index = listeners.indexOf(callback);
      if (index > -1) {
        listeners.splice(index, 1);
      }
    };
  }

  /**
   * Navigation Methods
   */
  navigate(url) {
    this.sendToBackend('navigate', { url });
  }

  goBack() {
    this.sendToBackend('navigation', { action: 'back' });
  }

  goForward() {
    this.sendToBackend('navigation', { action: 'forward' });
  }

  reload() {
    this.sendToBackend('navigation', { action: 'reload' });
  }

  stop() {
    this.sendToBackend('navigation', { action: 'stop' });
  }

  /**
   * Tab Management
   */
  createTab(url = 'lunetix://newtab') {
    this.sendToBackend('tab', { action: 'create', url });
  }

  closeTab(tabId) {
    this.sendToBackend('tab', { action: 'close', tabId });
  }

  switchTab(tabId) {
    this.sendToBackend('tab', { action: 'switch', tabId });
  }

  updateTab(tabId, properties) {
    this.sendToBackend('tab', { action: 'update', tabId, properties });
  }

  /**
   * Window Management
   */
  createWindow(options = {}) {
    this.sendToBackend('window', { action: 'create', options });
  }

  closeWindow(windowId) {
    this.sendToBackend('window', { action: 'close', windowId });
  }

  minimizeWindow() {
    this.sendToBackend('window', { action: 'minimize' });
  }

  maximizeWindow() {
    this.sendToBackend('window', { action: 'maximize' });
  }

  /**
   * Bookmarks
   */
  addBookmark(url, title, folder = '') {
    this.sendToBackend('bookmark', { action: 'add', url, title, folder });
  }

  removeBookmark(bookmarkId) {
    this.sendToBackend('bookmark', { action: 'remove', bookmarkId });
  }

  getBookmarks() {
    this.sendToBackend('bookmark', { action: 'get' });
  }

  /**
   * History
   */
  getHistory(options = {}) {
    this.sendToBackend('history', { action: 'get', options });
  }

  clearHistory(options = {}) {
    this.sendToBackend('history', { action: 'clear', options });
  }

  /**
   * Downloads
   */
  getDownloads() {
    this.sendToBackend('download', { action: 'get' });
  }

  pauseDownload(downloadId) {
    this.sendToBackend('download', { action: 'pause', downloadId });
  }

  resumeDownload(downloadId) {
    this.sendToBackend('download', { action: 'resume', downloadId });
  }

  cancelDownload(downloadId) {
    this.sendToBackend('download', { action: 'cancel', downloadId });
  }

  /**
   * Settings
   */
  getSetting(key) {
    this.sendToBackend('setting', { action: 'get', key });
  }

  setSetting(key, value) {
    this.sendToBackend('setting', { action: 'set', key, value });
  }

  /**
   * Privacy & Security
   */
  clearBrowsingData(options = {}) {
    this.sendToBackend('privacy', { action: 'clearData', options });
  }

  setPrivacyMode(enabled) {
    this.sendToBackend('privacy', { action: 'setMode', enabled });
  }

  /**
   * Extensions
   */
  getExtensions() {
    this.sendToBackend('extension', { action: 'get' });
  }

  enableExtension(extensionId) {
    this.sendToBackend('extension', { action: 'enable', extensionId });
  }

  disableExtension(extensionId) {
    this.sendToBackend('extension', { action: 'disable', extensionId });
  }

  /**
   * Developer Tools
   */
  openDevTools() {
    this.sendToBackend('devtools', { action: 'open' });
  }

  closeDevTools() {
    this.sendToBackend('devtools', { action: 'close' });
  }

  /**
   * Utility Methods
   */
  getSystemInfo() {
    this.sendToBackend('system', { action: 'info' });
  }

  showNotification(title, message, options = {}) {
    this.sendToBackend('notification', { title, message, options });
  }

  /**
   * Event Emitter Methods
   */
  emit(eventName, data) {
    this.sendToBackend('event', { eventName, data });
  }

  /**
   * Cleanup
   */
  destroy() {
    this.listeners.clear();
    this.isReady = false;
  }
}

// Create singleton instance
const browserBridge = new LunetixBrowserBridge();

// React Hook for using the bridge
export const useBrowserBridge = () => {
  return browserBridge;
};

// Export bridge instance
export default browserBridge;

// Export specific methods for convenience
export const {
  navigate,
  goBack,
  goForward,
  reload,
  createTab,
  closeTab,
  switchTab,
  addBookmark,
  getHistory,
  clearBrowsingData
} = browserBridge;