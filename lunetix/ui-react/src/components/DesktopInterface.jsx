import React, { useState, useEffect } from 'react';
import { motion } from 'framer-motion';
import DesktopToolbar from './DesktopToolbar';
import TabSwitcher from './TabSwitcher';
import TabManager from './TabManager';
import AddressBar from './AddressBar';
import BookmarkManager from './BookmarkManager';
// import DownloadManager from './DownloadManager';
import browserAPI from '../services/BrowserAPI';
import { useBrowserBridge } from '../utils/browserBridge';
import { 
  Search, 
  Star, 
  Download, 
  Shield, 
  Settings,
  Globe,
  Github,
  Youtube,
  Twitter
} from 'lucide-react';

const DesktopInterface = () => {
  const [tabs, setTabs] = useState([
    { 
      id: 1, 
      title: 'Lunetix Start Page', 
      url: 'lunetix://start', 
      favicon: null,
      isLoading: false 
    }
  ]);
  const [activeTabId, setActiveTabId] = useState(1);
  const [isTabSwitcherOpen, setIsTabSwitcherOpen] = useState(false);
  const [showBookmarks, setShowBookmarks] = useState(false);
  const [showDownloads, setShowDownloads] = useState(false);
  const [currentUrl, setCurrentUrl] = useState('lunetix://start');
  const [canGoBack, setCanGoBack] = useState(false);
  const [canGoForward, setCanGoForward] = useState(false);
  const [isLoading, setIsLoading] = useState(false);
  const [currentTime, setCurrentTime] = useState(new Date());

  const bridge = useBrowserBridge();

  useEffect(() => {
    // Initialize browser API
    browserAPI.onTabCreated((tabData) => {
      setTabs(prev => [...prev, tabData]);
    });

    browserAPI.onTabUpdated((tabData) => {
      setTabs(prev => prev.map(tab => 
        tab.id === tabData.id ? { ...tab, ...tabData } : tab
      ));
    });

    browserAPI.onTabClosed((tabData) => {
      setTabs(prev => prev.filter(tab => tab.id !== tabData.id));
    });

    browserAPI.onTabActivated((tabData) => {
      setActiveTabId(tabData.id);
    });

    // Update time every second
    const timer = setInterval(() => {
      setCurrentTime(new Date());
    }, 1000);

    // Listen for navigation updates from backend
    const unsubscribeNav = bridge.on('navigation-state', (data) => {
      setCanGoBack(data.canGoBack);
      setCanGoForward(data.canGoForward);
      setCurrentUrl(data.url);
    });

    const unsubscribeLoading = bridge.on('loading-state', (data) => {
      setIsLoading(data.isLoading);
    });

    return () => {
      clearInterval(timer);
      unsubscribeNav();
      unsubscribeLoading();
    };
  }, [bridge]);

  const handleNavigate = (url) => {
    const activeTab = tabs.find(tab => tab.id === activeTabId);
    if (activeTab) {
      browserAPI.navigate(activeTabId, url);
    }
    bridge.navigate(url);
    setCurrentUrl(url);
  };

  const handleNewTab = async () => {
    try {
      await browserAPI.createTab();
    } catch (error) {
      // Fallback to local state
      const newTab = {
        id: Date.now(),
        title: 'New Tab',
        url: 'lunetix://newtab',
        favicon: null,
        isLoading: false
      };
      setTabs(prev => [...prev, newTab]);
      setActiveTabId(newTab.id);
    }
    bridge.createTab();
  };

  const handleCloseTab = async (tabId) => {
    try {
      await browserAPI.closeTab(tabId);
    } catch (error) {
      // Fallback to local state
      setTabs(prev => prev.filter(tab => tab.id !== tabId));
      if (activeTabId === tabId && tabs.length > 1) {
        const remainingTabs = tabs.filter(tab => tab.id !== tabId);
        setActiveTabId(remainingTabs[0]?.id);
      }
    }
    bridge.closeTab(tabId);
  };

  const handleTabChange = async (tabId) => {
    try {
      await browserAPI.switchTab(tabId);
      setActiveTabId(tabId);
      const tab = tabs.find(t => t.id === tabId);
      if (tab) {
        setCurrentUrl(tab.url);
      }
    } catch (error) {
      // Fallback to local state
      setActiveTabId(tabId);
      const tab = tabs.find(t => t.id === tabId);
      if (tab) {
        setCurrentUrl(tab.url);
      }
    }
    bridge.switchTab(tabId);
  };

  const FavoriteItem = ({ icon: Icon, title, url, gradient, onClick }) => (
    <motion.button
      whileHover={{ scale: 1.02, y: -2 }}
      whileTap={{ scale: 0.98 }}
      onClick={onClick || (() => handleNavigate(url))}
      className="group flex flex-col items-center p-6 bg-white/60 backdrop-blur-sm border border-white/30 rounded-squircle-lg hover:bg-white/80 transition-all duration-300 shadow-apple hover:shadow-apple-lg"
    >
      <div className={`w-12 h-12 ${gradient} rounded-squircle mb-3 flex items-center justify-center group-hover:scale-110 transition-transform duration-200`}>
        <Icon size={24} className="text-white" />
      </div>
      <span className="text-sm font-medium text-apple-gray-700 group-hover:text-apple-gray-900 transition-colors">
        {title}
      </span>
    </motion.button>
  );

  const QuickLink = ({ title, url, description }) => (
    <motion.button
      whileHover={{ x: 4 }}
      onClick={() => handleNavigate(url)}
      className="flex items-center w-full p-3 rounded-lg hover:bg-white/50 transition-all duration-200 group"
    >
      <div className="w-8 h-8 bg-apple-gray-300 rounded-lg mr-3 flex items-center justify-center">
        <Globe size={16} className="text-apple-gray-600" />
      </div>
      <div className="text-left">
        <div className="text-sm font-medium text-apple-gray-700 group-hover:text-apple-gray-900">
          {title}
        </div>
        <div className="text-xs text-apple-gray-500">{description}</div>
      </div>
    </motion.button>
  );

  return (
    <div className="h-screen bg-gradient-to-br from-apple-gray-50 via-white to-apple-gray-100 flex flex-col">
      {/* Tab Manager */}
      <TabManager className="border-b border-gray-200/50" />

      {/* Address Bar */}
      <div className="px-4 py-2 bg-white/80 backdrop-blur-xl border-b border-gray-200/50">
        <AddressBar 
          activeTab={tabs.find(tab => tab.id === activeTabId)}
          className="w-full"
        />
      </div>

      {/* Main Content Area */}
      <div className="flex-1 overflow-hidden">
        <div className="h-full flex flex-col items-center justify-center p-12">
          {/* Welcome Section */}
          <motion.div
            initial={{ opacity: 0, y: 30 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.8, ease: 'easeOut' }}
            className="text-center mb-12"
          >
            <h1 className="text-6xl font-thin text-apple-gray-700 mb-4">
              Lunetix
            </h1>
            <p className="text-xl text-apple-gray-500 font-light">
              Fast, Secure, and Private Web Browser
            </p>
          </motion.div>

          {/* Search Bar */}
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6, delay: 0.2 }}
            className="w-full max-w-2xl mb-16"
          >
            <div className="relative">
              <input
                type="text"
                placeholder="Search Google or enter address"
                className="w-full px-6 py-4 bg-white/80 backdrop-blur-sm border border-apple-gray-200 rounded-2xl text-apple-gray-700 placeholder-apple-gray-400 text-lg outline-none focus:bg-white focus:border-apple-blue focus:ring-2 focus:ring-apple-blue/20 transition-all duration-200 shadow-apple"
                onKeyPress={(e) => {
                  if (e.key === 'Enter' && e.target.value.trim()) {
                    handleNavigate(e.target.value.trim());
                  }
                }}
              />
              <Search className="absolute right-6 top-1/2 transform -translate-y-1/2 text-apple-gray-400" size={20} />
            </div>
          </motion.div>

          {/* Favorites Grid */}
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6, delay: 0.4 }}
            className="grid grid-cols-2 md:grid-cols-4 lg:grid-cols-6 gap-6 mb-12 w-full max-w-4xl"
          >
            <FavoriteItem
              icon={Search}
              title="Google"
              url="https://google.com"
              gradient="bg-gradient-to-br from-blue-500 to-blue-600"
            />
            <FavoriteItem
              icon={Youtube}
              title="YouTube"
              url="https://youtube.com"
              gradient="bg-gradient-to-br from-red-500 to-red-600"
            />
            <FavoriteItem
              icon={Github}
              title="GitHub"
              url="https://github.com"
              gradient="bg-gradient-to-br from-gray-700 to-gray-800"
            />
            <FavoriteItem
              icon={Twitter}
              title="Twitter"
              url="https://twitter.com"
              gradient="bg-gradient-to-br from-sky-400 to-sky-500"
            />
            <FavoriteItem
              icon={Star}
              title="Bookmarks"
              url="#"
              gradient="bg-gradient-to-br from-yellow-400 to-yellow-500"
              onClick={() => setShowBookmarks(true)}
            />
            <FavoriteItem
              icon={Download}
              title="Downloads"
              url="#"
              gradient="bg-gradient-to-br from-purple-500 to-purple-600"
              onClick={() => setShowDownloads(true)}
            />
          </motion.div>

          {/* Quick Links & Info */}
          <div className="grid grid-cols-1 md:grid-cols-2 gap-8 w-full max-w-4xl">
            {/* Recent Sites */}
            <motion.div
              initial={{ opacity: 0, x: -20 }}
              animate={{ opacity: 1, x: 0 }}
              transition={{ duration: 0.6, delay: 0.6 }}
              className="bg-white/60 backdrop-blur-sm border border-white/30 rounded-squircle-lg p-6 shadow-apple"
            >
              <h3 className="text-lg font-semibold text-apple-gray-700 mb-4">
                Recent Sites
              </h3>
              <div className="space-y-2">
                <QuickLink
                  title="Wikipedia"
                  url="https://wikipedia.org"
                  description="Free encyclopedia"
                />
                <QuickLink
                  title="Reddit"
                  url="https://reddit.com"
                  description="Front page of the internet"
                />
                <QuickLink
                  title="Stack Overflow"
                  url="https://stackoverflow.com"
                  description="Developer community"
                />
              </div>
            </motion.div>

            {/* Browser Info */}
            <motion.div
              initial={{ opacity: 0, x: 20 }}
              animate={{ opacity: 1, x: 0 }}
              transition={{ duration: 0.6, delay: 0.8 }}
              className="bg-white/60 backdrop-blur-sm border border-white/30 rounded-squircle-lg p-6 shadow-apple"
            >
              <h3 className="text-lg font-semibold text-apple-gray-700 mb-4">
                Browser Status
              </h3>
              <div className="space-y-3">
                <div className="flex items-center justify-between">
                  <span className="text-sm text-apple-gray-600">Privacy Shield</span>
                  <div className="flex items-center">
                    <div className="w-2 h-2 bg-green-500 rounded-full mr-2"></div>
                    <span className="text-sm font-medium text-green-600">Active</span>
                  </div>
                </div>
                <div className="flex items-center justify-between">
                  <span className="text-sm text-apple-gray-600">Tabs Open</span>
                  <span className="text-sm font-medium text-apple-gray-700">{tabs.length}</span>
                </div>
                <div className="flex items-center justify-between">
                  <span className="text-sm text-apple-gray-600">Time</span>
                  <span className="text-sm font-medium text-apple-gray-700">
                    {currentTime.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })}
                  </span>
                </div>
              </div>
            </motion.div>
          </div>
        </div>
      </div>

      {/* Tab Switcher */}
      <TabSwitcher
        isOpen={isTabSwitcherOpen}
        onClose={() => setIsTabSwitcherOpen(false)}
        tabs={tabs}
        activeTabId={activeTabId}
        onTabSelect={handleTabChange}
        onTabClose={handleCloseTab}
        onNewTab={handleNewTab}
      />

      {/* Bookmark Manager */}
      <BookmarkManager
        isOpen={showBookmarks}
        onClose={() => setShowBookmarks(false)}
      />

      {/* Download Manager */}
      {/* <DownloadManager
        isOpen={showDownloads}
        onClose={() => setShowDownloads(false)}
      /> */}
    </div>
  );
};

export default DesktopInterface;