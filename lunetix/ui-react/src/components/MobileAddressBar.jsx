import React, { useState, useRef, useEffect } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { 
  ArrowLeft, 
  ArrowRight, 
  RotateCcw, 
  Type, 
  Link, 
  Search,
  X,
  Plus
} from 'lucide-react';

const MobileAddressBar = ({ 
  url = "lunetix.com", 
  onNavigate, 
  onReload, 
  onBack, 
  onForward,
  canGoBack = false,
  canGoForward = false,
  isLoading = false 
}) => {
  const [isExpanded, setIsExpanded] = useState(false);
  const [inputValue, setInputValue] = useState(url);
  const [isFocused, setIsFocused] = useState(false);
  const inputRef = useRef(null);

  useEffect(() => {
    setInputValue(url);
  }, [url]);

  const handleSubmit = (e) => {
    e.preventDefault();
    if (inputValue.trim()) {
      onNavigate?.(inputValue.trim());
      setIsExpanded(false);
      setIsFocused(false);
      inputRef.current?.blur();
    }
  };

  const handleFocus = () => {
    setIsFocused(true);
    setIsExpanded(true);
  };

  const handleBlur = () => {
    setIsFocused(false);
    setTimeout(() => {
      if (!isFocused) {
        setIsExpanded(false);
      }
    }, 150);
  };

  const handleClear = () => {
    setInputValue('');
    inputRef.current?.focus();
  };

  return (
    <div className="fixed bottom-6 left-1/2 transform -translate-x-1/2 z-50 w-[92%] max-w-sm">
      <motion.div
        layout
        initial={{ y: 100, opacity: 0 }}
        animate={{ y: 0, opacity: 1 }}
        transition={{ 
          type: "spring", 
          stiffness: 300, 
          damping: 30,
          opacity: { duration: 0.2 }
        }}
        className={`
          relative overflow-hidden
          ${isExpanded ? 'rounded-squircle-lg' : 'rounded-capsule'}
          bg-white/70 backdrop-blur-xl 
          border border-white/20
          shadow-glass-lg
          transition-all duration-300 ease-apple
        `}
      >
        {/* Main Address Bar */}
        <motion.form 
          onSubmit={handleSubmit}
          layout
          className="flex items-center px-4 py-3"
        >
          {/* Navigation Buttons (Expanded State) */}
          <AnimatePresence>
            {isExpanded && (
              <motion.div
                initial={{ opacity: 0, x: -20 }}
                animate={{ opacity: 1, x: 0 }}
                exit={{ opacity: 0, x: -20 }}
                transition={{ duration: 0.2 }}
                className="flex items-center space-x-2 mr-3"
              >
                <button
                  type="button"
                  onClick={onBack}
                  disabled={!canGoBack}
                  className={`
                    p-2 rounded-full transition-all duration-200
                    ${canGoBack 
                      ? 'text-apple-blue hover:bg-apple-blue/10 active:scale-95' 
                      : 'text-apple-gray-400 cursor-not-allowed'
                    }
                  `}
                >
                  <ArrowLeft size={18} />
                </button>
                
                <button
                  type="button"
                  onClick={onForward}
                  disabled={!canGoForward}
                  className={`
                    p-2 rounded-full transition-all duration-200
                    ${canGoForward 
                      ? 'text-apple-blue hover:bg-apple-blue/10 active:scale-95' 
                      : 'text-apple-gray-400 cursor-not-allowed'
                    }
                  `}
                >
                  <ArrowRight size={18} />
                </button>
              </motion.div>
            )}
          </AnimatePresence>

          {/* URL Input */}
          <div className="flex-1 relative">
            <input
              ref={inputRef}
              type="text"
              value={inputValue}
              onChange={(e) => setInputValue(e.target.value)}
              onFocus={handleFocus}
              onBlur={handleBlur}
              placeholder="Search or enter website name"
              className={`
                w-full bg-transparent outline-none
                font-sf text-base text-apple-gray-700
                placeholder-apple-gray-400
                transition-all duration-200
                ${isExpanded ? 'text-left' : 'text-center'}
              `}
            />
            
            {/* Clear Button */}
            <AnimatePresence>
              {isFocused && inputValue && (
                <motion.button
                  type="button"
                  onClick={handleClear}
                  initial={{ opacity: 0, scale: 0.8 }}
                  animate={{ opacity: 1, scale: 1 }}
                  exit={{ opacity: 0, scale: 0.8 }}
                  className="absolute right-0 top-1/2 transform -translate-y-1/2 p-1 rounded-full bg-apple-gray-300 text-white"
                >
                  <X size={12} />
                </motion.button>
              )}
            </AnimatePresence>
          </div>

          {/* Action Buttons */}
          <div className="flex items-center space-x-2 ml-3">
            {/* Format Button (Aa) */}
            <motion.button
              type="button"
              whileTap={{ scale: 0.95 }}
              className="p-2 rounded-full text-apple-gray-600 hover:bg-apple-gray-100/50 transition-colors duration-200"
              title="Text Format"
            >
              <Type size={16} />
            </motion.button>

            {/* Link Button */}
            <motion.button
              type="button"
              whileTap={{ scale: 0.95 }}
              className="p-2 rounded-full text-apple-gray-600 hover:bg-apple-gray-100/50 transition-colors duration-200"
              title="Share Link"
            >
              <Link size={16} />
            </motion.button>

            {/* Reload Button */}
            <motion.button
              type="button"
              onClick={onReload}
              whileTap={{ scale: 0.95 }}
              className={`
                p-2 rounded-full transition-all duration-200
                ${isLoading 
                  ? 'text-apple-blue animate-spin' 
                  : 'text-apple-gray-600 hover:bg-apple-gray-100/50'
                }
              `}
              title="Reload"
            >
              <RotateCcw size={16} />
            </motion.button>
          </div>
        </motion.form>

        {/* Expanded Content */}
        <AnimatePresence>
          {isExpanded && (
            <motion.div
              initial={{ height: 0, opacity: 0 }}
              animate={{ height: 'auto', opacity: 1 }}
              exit={{ height: 0, opacity: 0 }}
              transition={{ duration: 0.3, ease: 'easeInOut' }}
              className="border-t border-white/10"
            >
              {/* Quick Actions */}
              <div className="px-4 py-3">
                <div className="flex items-center justify-between mb-3">
                  <span className="text-xs font-medium text-apple-gray-500 uppercase tracking-wider">
                    Quick Actions
                  </span>
                </div>
                
                <div className="grid grid-cols-4 gap-3">
                  <button className="flex flex-col items-center p-3 rounded-squircle bg-white/30 hover:bg-white/40 transition-colors duration-200">
                    <Search size={20} className="text-apple-blue mb-1" />
                    <span className="text-xs text-apple-gray-700">Search</span>
                  </button>
                  
                  <button className="flex flex-col items-center p-3 rounded-squircle bg-white/30 hover:bg-white/40 transition-colors duration-200">
                    <Plus size={20} className="text-apple-green mb-1" />
                    <span className="text-xs text-apple-gray-700">New Tab</span>
                  </button>
                  
                  <button className="flex flex-col items-center p-3 rounded-squircle bg-white/30 hover:bg-white/40 transition-colors duration-200">
                    <Type size={20} className="text-apple-purple mb-1" />
                    <span className="text-xs text-apple-gray-700">Reader</span>
                  </button>
                  
                  <button className="flex flex-col items-center p-3 rounded-squircle bg-white/30 hover:bg-white/40 transition-colors duration-200">
                    <Link size={20} className="text-apple-orange mb-1" />
                    <span className="text-xs text-apple-gray-700">Share</span>
                  </button>
                </div>
              </div>
            </motion.div>
          )}
        </AnimatePresence>

        {/* Loading Indicator */}
        <AnimatePresence>
          {isLoading && (
            <motion.div
              initial={{ scaleX: 0 }}
              animate={{ scaleX: 1 }}
              exit={{ scaleX: 0 }}
              transition={{ duration: 0.3 }}
              className="absolute bottom-0 left-0 h-0.5 bg-apple-blue origin-left"
              style={{ width: '100%' }}
            />
          )}
        </AnimatePresence>
      </motion.div>
    </div>
  );
};

export default MobileAddressBar;