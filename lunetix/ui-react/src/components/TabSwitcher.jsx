import React, { useState } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { X, Plus, Grid3X3 } from 'lucide-react';

const TabSwitcher = ({ 
  isOpen, 
  onClose, 
  tabs = [], 
  activeTabId, 
  onTabSelect, 
  onTabClose, 
  onNewTab 
}) => {
  const [hoveredTab, setHoveredTab] = useState(null);

  const overlayVariants = {
    hidden: { opacity: 0 },
    visible: { 
      opacity: 1,
      transition: { duration: 0.2 }
    },
    exit: { 
      opacity: 0,
      transition: { duration: 0.2 }
    }
  };

  const containerVariants = {
    hidden: { 
      opacity: 0,
      scale: 0.9,
      y: 50
    },
    visible: { 
      opacity: 1,
      scale: 1,
      y: 0,
      transition: {
        type: "spring",
        stiffness: 300,
        damping: 30,
        staggerChildren: 0.05
      }
    },
    exit: { 
      opacity: 0,
      scale: 0.9,
      y: 50,
      transition: {
        duration: 0.2,
        staggerChildren: 0.02,
        staggerDirection: -1
      }
    }
  };

  const tabVariants = {
    hidden: { 
      opacity: 0,
      y: 20,
      scale: 0.9
    },
    visible: { 
      opacity: 1,
      y: 0,
      scale: 1,
      transition: {
        type: "spring",
        stiffness: 400,
        damping: 25
      }
    },
    exit: { 
      opacity: 0,
      y: -20,
      scale: 0.9,
      transition: { duration: 0.15 }
    }
  };

  const TabCard = ({ tab, index }) => {
    const isActive = tab.id === activeTabId;
    const isHovered = hoveredTab === tab.id;

    return (
      <motion.div
        variants={tabVariants}
        layout
        layoutId={`tab-${tab.id}`}
        onMouseEnter={() => setHoveredTab(tab.id)}
        onMouseLeave={() => setHoveredTab(null)}
        onClick={() => {
          onTabSelect(tab.id);
          onClose();
        }}
        className={`
          relative cursor-pointer group
          bg-white/80 backdrop-blur-xl
          border border-white/30
          rounded-squircle-lg overflow-hidden
          transition-all duration-300 ease-spring
          ${isActive ? 'ring-2 ring-apple-blue/50 shadow-apple-lg' : 'shadow-apple'}
          ${isHovered ? 'transform scale-105 shadow-apple-lg' : ''}
        `}
        whileHover={{ 
          scale: 1.02,
          transition: { type: "spring", stiffness: 400, damping: 25 }
        }}
        whileTap={{ 
          scale: 0.98,
          transition: { duration: 0.1 }
        }}
      >
        {/* Tab Preview */}
        <div className="aspect-[4/3] bg-gradient-to-br from-apple-gray-50 to-apple-gray-100 relative overflow-hidden">
          {/* Simulated Website Content */}
          <div className="absolute inset-0 p-3">
            <div className="w-full h-2 bg-apple-gray-200 rounded-full mb-2" />
            <div className="w-3/4 h-2 bg-apple-gray-200 rounded-full mb-2" />
            <div className="w-1/2 h-2 bg-apple-gray-200 rounded-full mb-4" />
            
            <div className="grid grid-cols-2 gap-2">
              <div className="h-8 bg-apple-gray-200 rounded" />
              <div className="h-8 bg-apple-gray-200 rounded" />
            </div>
          </div>

          {/* Loading Indicator */}
          {tab.isLoading && (
            <motion.div
              initial={{ width: 0 }}
              animate={{ width: '100%' }}
              className="absolute top-0 left-0 h-1 bg-apple-blue"
            />
          )}

          {/* Active Indicator */}
          {isActive && (
            <motion.div
              layoutId="activeTabIndicator"
              className="absolute top-2 right-2 w-3 h-3 bg-apple-blue rounded-full shadow-lg"
              transition={{ type: "spring", stiffness: 500, damping: 30 }}
            />
          )}
        </div>

        {/* Tab Info */}
        <div className="p-3 border-t border-white/20">
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-2 flex-1 min-w-0">
              {/* Favicon */}
              <div className="w-4 h-4 flex-shrink-0">
                {tab.favicon ? (
                  <img src={tab.favicon} alt="" className="w-full h-full rounded-sm" />
                ) : (
                  <div className="w-full h-full bg-apple-gray-300 rounded-sm flex items-center justify-center">
                    <div className="w-2 h-2 bg-apple-gray-500 rounded-full" />
                  </div>
                )}
              </div>

              {/* Title */}
              <span className="text-sm font-medium text-apple-gray-700 truncate">
                {tab.title || 'New Tab'}
              </span>
            </div>

            {/* Close Button */}
            <motion.button
              onClick={(e) => {
                e.stopPropagation();
                onTabClose(tab.id);
              }}
              whileHover={{ scale: 1.1 }}
              whileTap={{ scale: 0.9 }}
              className={`
                p-1.5 rounded-full transition-all duration-200
                ${isHovered || isActive 
                  ? 'opacity-100 bg-apple-gray-200/50 hover:bg-red-100 hover:text-red-600' 
                  : 'opacity-0 group-hover:opacity-100'
                }
              `}
            >
              <X size={12} />
            </motion.button>
          </div>

          {/* URL */}
          <div className="mt-1">
            <span className="text-xs text-apple-gray-500 truncate block">
              {tab.url || 'lunetix://newtab'}
            </span>
          </div>
        </div>
      </motion.div>
    );
  };

  return (
    <AnimatePresence>
      {isOpen && (
        <motion.div
          variants={overlayVariants}
          initial="hidden"
          animate="visible"
          exit="exit"
          className="fixed inset-0 z-50 bg-black/20 backdrop-blur-sm"
          onClick={onClose}
        >
          <motion.div
            variants={containerVariants}
            onClick={(e) => e.stopPropagation()}
            className="absolute inset-4 md:inset-8 lg:inset-16 bg-white/10 backdrop-blur-2xl rounded-squircle-lg border border-white/20 shadow-glass-lg overflow-hidden"
          >
            {/* Header */}
            <div className="flex items-center justify-between p-6 border-b border-white/20">
              <div className="flex items-center space-x-3">
                <Grid3X3 size={24} className="text-apple-gray-700" />
                <h2 className="text-xl font-semibold text-apple-gray-700">
                  {tabs.length} {tabs.length === 1 ? 'Tab' : 'Tabs'}
                </h2>
              </div>

              <div className="flex items-center space-x-2">
                {/* New Tab Button */}
                <motion.button
                  onClick={() => {
                    onNewTab();
                    onClose();
                  }}
                  whileHover={{ scale: 1.05 }}
                  whileTap={{ scale: 0.95 }}
                  className="flex items-center space-x-2 px-4 py-2 bg-apple-blue text-white rounded-lg font-medium transition-colors hover:bg-apple-blue-dark"
                >
                  <Plus size={16} />
                  <span>New Tab</span>
                </motion.button>

                {/* Close Button */}
                <motion.button
                  onClick={onClose}
                  whileHover={{ scale: 1.05 }}
                  whileTap={{ scale: 0.95 }}
                  className="p-2 rounded-lg text-apple-gray-600 hover:bg-apple-gray-200/50 transition-colors"
                >
                  <X size={20} />
                </motion.button>
              </div>
            </div>

            {/* Tabs Grid */}
            <div className="flex-1 overflow-auto p-6">
              {tabs.length > 0 ? (
                <motion.div 
                  className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4"
                  variants={containerVariants}
                >
                  <AnimatePresence mode="popLayout">
                    {tabs.map((tab, index) => (
                      <TabCard key={tab.id} tab={tab} index={index} />
                    ))}
                  </AnimatePresence>
                </motion.div>
              ) : (
                <motion.div
                  variants={tabVariants}
                  className="flex flex-col items-center justify-center h-full text-center"
                >
                  <div className="w-16 h-16 bg-apple-gray-200 rounded-full flex items-center justify-center mb-4">
                    <Grid3X3 size={32} className="text-apple-gray-500" />
                  </div>
                  <h3 className="text-lg font-semibold text-apple-gray-700 mb-2">
                    No tabs open
                  </h3>
                  <p className="text-apple-gray-500 mb-6">
                    Create a new tab to get started
                  </p>
                  <motion.button
                    onClick={() => {
                      onNewTab();
                      onClose();
                    }}
                    whileHover={{ scale: 1.05 }}
                    whileTap={{ scale: 0.95 }}
                    className="flex items-center space-x-2 px-6 py-3 bg-apple-blue text-white rounded-lg font-medium transition-colors hover:bg-apple-blue-dark"
                  >
                    <Plus size={16} />
                    <span>New Tab</span>
                  </motion.button>
                </motion.div>
              )}
            </div>
          </motion.div>
        </motion.div>
      )}
    </AnimatePresence>
  );
};

export default TabSwitcher;