import React, { useState, useEffect } from 'react';
import { motion } from 'framer-motion';
import MobileAddressBar from './MobileAddressBar';
import TabSwitcher from './TabSwitcher';
import { useBrowserBridge } from '../utils/browserBridge';
import { Grid3X3, Search, Clock, Star, Shield } from 'lucide-react';

const MobileInterface = () => {
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
  const [currentUrl, setCurrentUrl] = useState('lunetix://start');
  const [canGoBack, setCanGoBack] = useState(false);
  const [canGoForward, setCanGoForward] = useState(false);
  const [isLoading, setIsLoading] = useState(false);

  const bridge = useBrowserBridge();

  useEffect(() => {
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
      unsubscribeNav();
      unsubscribeLoading();
    };
  }, [bridge]);

  const handleNavigate = (url) => {
    bridge.navigate(url);
    setCurrentUrl(url);
  };

  const handleNewTab = () => {
    const newTab = {
      id: Date.now(),
      title: 'New Tab',
      url: 'lunetix://newtab',
      favicon: null,
      isLoading: false
    };
    setTabs(prev => [...prev, newTab]);
    setActiveTabId(newTab.id);
    bridge.createTab();
  };

  const handleCloseTab = (tabId) => {
    setTabs(prev => prev.filter(tab => tab.id !== tabId));
    if (activeTabId === tabId && tabs.length > 1) {
      const remainingTabs = tabs.filter(tab => tab.id !== tabId);
      setActiveTabId(remainingTabs[0]?.id);
    }
    bridge.closeTab(tabId);
  };

  const handleTabSelect = (tabId) => {
    setActiveTabId(tabId);
    const tab = tabs.find(t => t.id === tabId);
    if (tab) {
      setCurrentUrl(tab.url);
      bridge.switchTab(tabId);
    }
  };

  const QuickAction = ({ icon: Icon, label, color, onClick }) => (
    <motion.button
      whileHover={{ scale: 1.05 }}
      whileTap={{ scale: 0.95 }}
      onClick={onClick}
      className={`
        flex flex-col items-center p-4 rounded-squircle-lg
        bg-white/20 backdrop-blur-sm border border-white/30
        transition-all duration-200 hover:bg-white/30
      `}
    >
      <Icon size={24} className={`${color} mb-2`} />
      <span className="text-xs font-medium text-white">{label}</span>
    </motion.button>
  );

  return (
    <div className="h-screen bg-gradient-to-br from-apple-blue via-apple-blue-light to-apple-blue-dark overflow-hidden">
      {/* Status Bar */}
      <div className="flex justify-between items-center px-6 py-3 text-white">
        <div className="flex items-center space-x-1">
          <div className="flex space-x-1">
            <div className="w-1 h-1 bg-white rounded-full"></div>
            <div className="w-1 h-1 bg-white rounded-full"></div>
            <div className="w-1 h-1 bg-white rounded-full"></div>
          </div>
          <span className="ml-2 text-sm font-medium">Lunetix</span>
        </div>
        <div className="text-sm font-medium">9:41</div>
        <div className="flex items-center space-x-1">
          <div className="text-sm">📶</div>
          <div className="text-sm">🔋</div>
        </div>
      </div>

      {/* Main Content */}
      <div className="flex-1 px-6 py-8">
        {/* Logo */}
        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6, ease: 'easeOut' }}
          className="text-center mb-12"
        >
          <h1 className="text-5xl font-thin text-white mb-4">Lunetix</h1>
          <p className="text-white/80 text-lg font-light">
            Fast, Secure, and Private
          </p>
        </motion.div>

        {/* Search Box */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6, delay: 0.2 }}
          className="mb-12"
        >
          <div className="relative">
            <input
              type="text"
              placeholder="Search or enter website name"
              className="w-full px-6 py-4 bg-white/20 backdrop-blur-xl border border-white/30 rounded-squircle text-white placeholder-white/70 text-lg outline-none focus:bg-white/30 focus:border-white/50 transition-all duration-200"
              onKeyPress={(e) => {
                if (e.key === 'Enter' && e.target.value.trim()) {
                  handleNavigate(e.target.value.trim());
                }
              }}
            />
            <Search className="absolute right-4 top-1/2 transform -translate-y-1/2 text-white/70" size={20} />
          </div>
        </motion.div>

        {/* Quick Actions */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6, delay: 0.4 }}
          className="grid grid-cols-2 gap-4 mb-8"
        >
          <QuickAction
            icon={Grid3X3}
            label="Tabs"
            color="text-white"
            onClick={() => setIsTabSwitcherOpen(true)}
          />
          <QuickAction
            icon={Star}
            label="Bookmarks"
            color="text-white"
            onClick={() => console.log('Bookmarks')}
          />
          <QuickAction
            icon={Clock}
            label="History"
            color="text-white"
            onClick={() => console.log('History')}
          />
          <QuickAction
            icon={Shield}
            label="Privacy"
            color="text-white"
            onClick={() => console.log('Privacy')}
          />
        </motion.div>

        {/* Recent Sites */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6, delay: 0.6 }}
        >
          <h3 className="text-white/90 font-medium mb-4">Recent Sites</h3>
          <div className="space-y-3">
            {[
              { name: 'Google', url: 'google.com', color: 'bg-blue-500' },
              { name: 'GitHub', url: 'github.com', color: 'bg-gray-800' },
              { name: 'YouTube', url: 'youtube.com', color: 'bg-red-500' },
            ].map((site, index) => (
              <motion.button
                key={site.name}
                initial={{ opacity: 0, x: -20 }}
                animate={{ opacity: 1, x: 0 }}
                transition={{ duration: 0.4, delay: 0.7 + index * 0.1 }}
                onClick={() => handleNavigate(`https://${site.url}`)}
                className="flex items-center w-full p-3 bg-white/10 backdrop-blur-sm border border-white/20 rounded-squircle hover:bg-white/20 transition-all duration-200"
              >
                <div className={`w-8 h-8 ${site.color} rounded-lg mr-3 flex items-center justify-center`}>
                  <span className="text-white text-sm font-bold">
                    {site.name[0]}
                  </span>
                </div>
                <div className="text-left">
                  <div className="text-white font-medium">{site.name}</div>
                  <div className="text-white/70 text-sm">{site.url}</div>
                </div>
              </motion.button>
            ))}
          </div>
        </motion.div>
      </div>

      {/* Mobile Address Bar */}
      <MobileAddressBar
        url={currentUrl}
        onNavigate={handleNavigate}
        onReload={() => bridge.reload()}
        onBack={() => bridge.goBack()}
        onForward={() => bridge.goForward()}
        canGoBack={canGoBack}
        canGoForward={canGoForward}
        isLoading={isLoading}
      />

      {/* Tab Switcher */}
      <TabSwitcher
        isOpen={isTabSwitcherOpen}
        onClose={() => setIsTabSwitcherOpen(false)}
        tabs={tabs}
        activeTabId={activeTabId}
        onTabSelect={handleTabSelect}
        onTabClose={handleCloseTab}
        onNewTab={handleNewTab}
      />
    </div>
  );
};

export default MobileInterface;