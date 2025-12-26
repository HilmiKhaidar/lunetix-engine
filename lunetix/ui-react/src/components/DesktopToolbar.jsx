import React, { useState, useRef, useEffect } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { 
  ArrowLeft, 
  ArrowRight, 
  RotateCcw, 
  Search,
  Star,
  Download,
  Shield,
  Settings,
  Plus,
  X,
  Minus,
  Square
} from 'lucide-react';

const DesktopToolbar = ({ 
  tabs = [],
  activeTabId,
  onTabChange,
  onTabClose,
  onNewTab,
  url = "",
  onNavigate,
  onReload,
  onBack,
  onForward,
  canGoBack = false,
  canGoForward = false,
  isLoading = false 
}) => {
  const [hoveredTab, setHoveredTab] = useState(null);
  const [inputValue, setInputValue] = useState(url);
  const [isAddressBarFocused, setIsAddressBarFocused] = useState(false);
  const addressBarRef = useRef(null);

  useEffect(() => {
    setInputValue(url);
  }, [url]);

  const handleAddressSubmit = (e) => {
    e.preventDefault();
    if (inputValue.trim()) {
      onNavigate?.(inputValue.trim());
      addressBarRef.current?.blur();
    }
  };

  const TrafficLights = () => (
    <div className="flex items-center space-x-2 pl-5 pr-4">
      <motion.button
        whileHover={{ scale: 1.1 }}
        whileTap={{ scale: 0.95 }}
        className="w-3 h-3 rounded-full bg-red-500 hover:bg-red-600 flex items-center justify-center group"
      >
        <X size={8} className="opacity-0 group-hover:opacity-100 text-red-900 transition-opacity" />
      </motion.button>
      <motion.button
        whileHover={{ scale: 1.1 }}
        whileTap={{ scale: 0.95 }}
        className="w-3 h-3 rounded-full bg-yellow-500 hover:bg-yellow-600 flex items-center justify-center group"
      >
        <Minus size={8} className="opacity-0 group-hover:opacity-100 text-yellow-900 transition-opacity" />
      </motion.button>
      <motion.button
        whileHover={{ scale: 1.1 }}
        whileTap={{ scale: 0.95 }}
        className="w-3 h-3 rounded-full bg-green-500 hover:bg-green-600 flex items-center justify-center group"
      >
        <Square size={6} className="opacity-0 group-hover:opacity-100 text-green-900 transition-opacity" />
      </motion.button>
    </div>
  );

  const Tab = ({ tab, isActive, isHovered, onHover, onLeave }) => (
    <motion.div
      layout
      initial={{ opacity: 0, scale: 0.8 }}
      animate={{ opacity: 1, scale: 1 }}
      exit={{ opacity: 0, scale: 0.8 }}
      transition={{ type: "spring", stiffness: 300, damping: 30 }}
      onMouseEnter={() => onHover(tab.id)}
      onMouseLeave={onLeave}
      className={`
        relative group cursor-pointer
        ${isActive ? 'z-10' : 'z-0'}
      `}
    >
      <div
        className={`
          flex items-center px-4 py-2 mx-0.5
          transition-all duration-200 ease-apple
          ${isActive 
            ? 'bg-safari-tab-active rounded-t-lg shadow-safari-tab' 
            : isHovered 
              ? 'bg-safari-tab-hover rounded-t-lg' 
              : 'bg-safari-tab rounded-t-lg'
          }
          ${!isActive ? 'transform scale-95' : ''}
        `}
        onClick={() => onTabChange(tab.id)}
      >
        {/* Favicon */}
        <div className="w-4 h-4 mr-2 flex-shrink-0">
          {tab.favicon ? (
            <img src={tab.favicon} alt="" className="w-full h-full rounded-sm" />
          ) : (
            <div className="w-full h-full bg-apple-gray-300 rounded-sm flex items-center justify-center">
              <div className="w-2 h-2 bg-apple-gray-500 rounded-full" />
            </div>
          )}
        </div>

        {/* Title */}
        <span className={`
          flex-1 text-sm font-medium truncate
          ${isActive ? 'text-apple-gray-700' : 'text-apple-gray-600'}
          transition-colors duration-200
        `}>
          {tab.title || 'New Tab'}
        </span>

        {/* Close Button */}
        <motion.button
          whileHover={{ scale: 1.1 }}
          whileTap={{ scale: 0.9 }}
          onClick={(e) => {
            e.stopPropagation();
            onTabClose(tab.id);
          }}
          className={`
            ml-2 p-1 rounded-full transition-all duration-200
            ${isActive || isHovered 
              ? 'opacity-100 hover:bg-apple-gray-200' 
              : 'opacity-0 group-hover:opacity-100'
            }
          `}
        >
          <X size={12} className="text-apple-gray-500" />
        </motion.button>

        {/* Loading Indicator */}
        {tab.isLoading && (
          <motion.div
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            className="absolute bottom-0 left-0 right-0 h-0.5 bg-apple-blue"
          >
            <motion.div
              className="h-full bg-apple-blue-light"
              animate={{ x: ['-100%', '100%'] }}
              transition={{ repeat: Infinity, duration: 1, ease: 'linear' }}
            />
          </motion.div>
        )}
      </div>
    </motion.div>
  );

  return (
    <div className="bg-safari-toolbar/80 backdrop-blur-xl border-b border-apple-gray-200/50">
      {/* Window Controls & Tabs */}
      <div className="flex items-end h-12">
        <TrafficLights />
        
        {/* Tabs Container */}
        <div className="flex-1 flex items-end overflow-hidden">
          <div className="flex items-end space-x-0">
            <AnimatePresence mode="popLayout">
              {tabs.map((tab) => (
                <Tab
                  key={tab.id}
                  tab={tab}
                  isActive={tab.id === activeTabId}
                  isHovered={hoveredTab === tab.id}
                  onHover={setHoveredTab}
                  onLeave={() => setHoveredTab(null)}
                />
              ))}
            </AnimatePresence>
          </div>
          
          {/* New Tab Button */}
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            onClick={onNewTab}
            className="ml-2 p-2 rounded-full hover:bg-apple-gray-200/50 transition-colors duration-200"
          >
            <Plus size={14} className="text-apple-gray-600" />
          </motion.button>
        </div>
      </div>

      {/* Navigation & Address Bar */}
      <div className="flex items-center px-5 py-2 space-x-3">
        {/* Navigation Buttons */}
        <div className="flex items-center space-x-1">
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            onClick={onBack}
            disabled={!canGoBack}
            className={`
              p-2 rounded-lg transition-all duration-200
              ${canGoBack 
                ? 'text-apple-gray-700 hover:bg-apple-gray-200/50' 
                : 'text-apple-gray-400 cursor-not-allowed'
              }
            `}
          >
            <ArrowLeft size={16} />
          </motion.button>
          
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            onClick={onForward}
            disabled={!canGoForward}
            className={`
              p-2 rounded-lg transition-all duration-200
              ${canGoForward 
                ? 'text-apple-gray-700 hover:bg-apple-gray-200/50' 
                : 'text-apple-gray-400 cursor-not-allowed'
              }
            `}
          >
            <ArrowRight size={16} />
          </motion.button>
          
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            onClick={onReload}
            className={`
              p-2 rounded-lg transition-all duration-200
              ${isLoading 
                ? 'text-apple-blue animate-spin' 
                : 'text-apple-gray-700 hover:bg-apple-gray-200/50'
              }
            `}
          >
            <RotateCcw size={16} />
          </motion.button>
        </div>

        {/* Address Bar */}
        <motion.form
          onSubmit={handleAddressSubmit}
          className="flex-1 max-w-2xl mx-auto"
          layout
        >
          <div className={`
            relative flex items-center
            bg-white/60 backdrop-blur-sm
            border border-apple-gray-200/50
            rounded-lg px-4 py-2
            transition-all duration-200 ease-apple
            ${isAddressBarFocused 
              ? 'bg-white/80 border-apple-blue shadow-apple ring-2 ring-apple-blue/20' 
              : 'hover:bg-white/70'
            }
          `}>
            <Search size={16} className="text-apple-gray-400 mr-3" />
            
            <input
              ref={addressBarRef}
              type="text"
              value={inputValue}
              onChange={(e) => setInputValue(e.target.value)}
              onFocus={() => setIsAddressBarFocused(true)}
              onBlur={() => setIsAddressBarFocused(false)}
              placeholder="Search Google or enter address"
              className="flex-1 bg-transparent outline-none font-sf text-sm text-apple-gray-700 placeholder-apple-gray-400"
            />
            
            {inputValue && isAddressBarFocused && (
              <motion.button
                type="button"
                initial={{ opacity: 0, scale: 0.8 }}
                animate={{ opacity: 1, scale: 1 }}
                onClick={() => setInputValue('')}
                className="ml-2 p-1 rounded-full hover:bg-apple-gray-200 transition-colors"
              >
                <X size={12} className="text-apple-gray-500" />
              </motion.button>
            )}
          </div>
        </motion.form>

        {/* Action Buttons */}
        <div className="flex items-center space-x-1">
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            className="p-2 rounded-lg text-apple-gray-700 hover:bg-apple-gray-200/50 transition-colors duration-200"
            title="Privacy Shield"
          >
            <Shield size={16} />
          </motion.button>
          
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            className="p-2 rounded-lg text-apple-gray-700 hover:bg-apple-gray-200/50 transition-colors duration-200"
            title="Bookmarks"
          >
            <Star size={16} />
          </motion.button>
          
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            className="p-2 rounded-lg text-apple-gray-700 hover:bg-apple-gray-200/50 transition-colors duration-200"
            title="Downloads"
          >
            <Download size={16} />
          </motion.button>
          
          <motion.button
            whileHover={{ scale: 1.05 }}
            whileTap={{ scale: 0.95 }}
            className="p-2 rounded-lg text-apple-gray-700 hover:bg-apple-gray-200/50 transition-colors duration-200"
            title="Settings"
          >
            <Settings size={16} />
          </motion.button>
        </div>
      </div>
    </div>
  );
};

export default DesktopToolbar;