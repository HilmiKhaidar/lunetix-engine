import React, { useState, useEffect } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { 
  Monitor, 
  Smartphone, 
  Tablet,
  ArrowRight,
  Zap,
  Shield,
  Globe,
  Star,
  Download
} from 'lucide-react';

const EcosystemDemo = () => {
  const [activeDevice, setActiveDevice] = useState('desktop');
  const [currentTime, setCurrentTime] = useState(new Date());

  useEffect(() => {
    const timer = setInterval(() => {
      setCurrentTime(new Date());
    }, 1000);
    return () => clearInterval(timer);
  }, []);

  const devices = [
    {
      id: 'desktop',
      name: 'Desktop',
      icon: Monitor,
      description: 'Full-featured browsing experience',
      color: 'from-blue-500 to-blue-600'
    },
    {
      id: 'mobile',
      name: 'Mobile',
      icon: Smartphone,
      description: 'Touch-optimized interface',
      color: 'from-green-500 to-green-600'
    },
    {
      id: 'tablet',
      name: 'Tablet',
      icon: Tablet,
      description: 'Adaptive layout design',
      color: 'from-purple-500 to-purple-600'
    }
  ];

  const features = [
    {
      icon: Zap,
      title: 'Lightning Fast',
      description: 'Optimized Chromium engine with enhanced performance',
      color: 'text-yellow-500'
    },
    {
      icon: Shield,
      title: 'Privacy First',
      description: 'Built-in tracking protection and secure browsing',
      color: 'text-green-500'
    },
    {
      icon: Globe,
      title: 'Universal Design',
      description: 'Consistent experience across all Apple devices',
      color: 'text-blue-500'
    }
  ];

  const DevicePreview = ({ device }) => {
    const baseClasses = "relative overflow-hidden bg-gradient-to-br from-apple-gray-50 to-white rounded-squircle-lg shadow-apple-lg";
    
    switch (device) {
      case 'desktop':
        return (
          <div className={`${baseClasses} aspect-[16/10] p-4`}>
            {/* Desktop Window */}
            <div className="w-full h-full bg-white rounded-lg shadow-inner overflow-hidden">
              {/* Title Bar */}
              <div className="flex items-center justify-between px-4 py-2 bg-apple-gray-100 border-b border-apple-gray-200">
                <div className="flex items-center space-x-2">
                  <div className="flex space-x-1">
                    <div className="w-2 h-2 bg-red-500 rounded-full"></div>
                    <div className="w-2 h-2 bg-yellow-500 rounded-full"></div>
                    <div className="w-2 h-2 bg-green-500 rounded-full"></div>
                  </div>
                  <span className="text-xs font-medium text-apple-gray-600">Lunetix</span>
                </div>
              </div>
              
              {/* Content */}
              <div className="p-4 space-y-3">
                <div className="w-full h-2 bg-apple-gray-200 rounded"></div>
                <div className="w-3/4 h-2 bg-apple-gray-200 rounded"></div>
                <div className="grid grid-cols-3 gap-2 mt-4">
                  <div className="h-8 bg-apple-blue/20 rounded"></div>
                  <div className="h-8 bg-apple-green/20 rounded"></div>
                  <div className="h-8 bg-apple-purple/20 rounded"></div>
                </div>
              </div>
            </div>
          </div>
        );
        
      case 'mobile':
        return (
          <div className={`${baseClasses} aspect-[9/19] p-2`}>
            {/* Mobile Frame */}
            <div className="w-full h-full bg-black rounded-squircle overflow-hidden">
              {/* Screen */}
              <div className="w-full h-full bg-gradient-to-br from-apple-blue via-apple-blue-light to-apple-blue-dark p-3">
                {/* Status Bar */}
                <div className="flex justify-between items-center text-white text-xs mb-4">
                  <span>9:41</span>
                  <div className="flex space-x-1">
                    <span>📶</span>
                    <span>🔋</span>
                  </div>
                </div>
                
                {/* Content */}
                <div className="text-center text-white space-y-4">
                  <h3 className="text-lg font-light">Lunetix</h3>
                  <div className="w-full h-8 bg-white/20 rounded-squircle"></div>
                  <div className="grid grid-cols-2 gap-2">
                    <div className="h-12 bg-white/20 rounded-squircle"></div>
                    <div className="h-12 bg-white/20 rounded-squircle"></div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        );
        
      case 'tablet':
        return (
          <div className={`${baseClasses} aspect-[4/3] p-3`}>
            {/* Tablet Frame */}
            <div className="w-full h-full bg-apple-gray-800 rounded-squircle overflow-hidden">
              {/* Screen */}
              <div className="w-full h-full bg-gradient-to-br from-apple-gray-50 to-white p-4">
                {/* Header */}
                <div className="flex items-center justify-between mb-4">
                  <h3 className="text-sm font-semibold text-apple-gray-700">Lunetix</h3>
                  <div className="text-xs text-apple-gray-500">
                    {currentTime.toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })}
                  </div>
                </div>
                
                {/* Content Grid */}
                <div className="grid grid-cols-4 gap-2">
                  {[...Array(8)].map((_, i) => (
                    <div key={i} className="aspect-square bg-apple-gray-200 rounded-lg"></div>
                  ))}
                </div>
              </div>
            </div>
          </div>
        );
        
      default:
        return null;
    }
  };

  return (
    <div className="min-h-screen bg-gradient-to-br from-apple-gray-50 via-white to-apple-gray-100">
      {/* Header */}
      <div className="relative overflow-hidden">
        <div className="absolute inset-0 bg-gradient-to-r from-apple-blue/10 to-apple-purple/10"></div>
        <div className="relative max-w-7xl mx-auto px-6 py-16">
          <motion.div
            initial={{ opacity: 0, y: 30 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.8 }}
            className="text-center"
          >
            <h1 className="text-6xl font-thin text-apple-gray-700 mb-6">
              Lunetix Ecosystem
            </h1>
            <p className="text-xl text-apple-gray-500 font-light max-w-3xl mx-auto">
              Experience the future of web browsing with our unified design system 
              that seamlessly adapts to every Apple device in your ecosystem.
            </p>
          </motion.div>
        </div>
      </div>

      {/* Device Showcase */}
      <div className="max-w-7xl mx-auto px-6 py-16">
        <div className="grid lg:grid-cols-2 gap-16 items-center">
          {/* Device Selection */}
          <div className="space-y-8">
            <motion.h2
              initial={{ opacity: 0, x: -30 }}
              animate={{ opacity: 1, x: 0 }}
              transition={{ duration: 0.6 }}
              className="text-3xl font-semibold text-apple-gray-700"
            >
              Choose Your Experience
            </motion.h2>
            
            <div className="space-y-4">
              {devices.map((device, index) => (
                <motion.button
                  key={device.id}
                  initial={{ opacity: 0, x: -30 }}
                  animate={{ opacity: 1, x: 0 }}
                  transition={{ duration: 0.6, delay: index * 0.1 }}
                  onClick={() => setActiveDevice(device.id)}
                  className={`
                    w-full flex items-center p-6 rounded-squircle-lg transition-all duration-300
                    ${activeDevice === device.id 
                      ? 'bg-white shadow-apple-lg ring-2 ring-apple-blue/30' 
                      : 'bg-white/60 hover:bg-white/80 shadow-apple'
                    }
                  `}
                >
                  <div className={`
                    w-12 h-12 rounded-squircle flex items-center justify-center mr-4
                    bg-gradient-to-br ${device.color}
                  `}>
                    <device.icon size={24} className="text-white" />
                  </div>
                  
                  <div className="flex-1 text-left">
                    <h3 className="text-lg font-semibold text-apple-gray-700">
                      {device.name}
                    </h3>
                    <p className="text-sm text-apple-gray-500">
                      {device.description}
                    </p>
                  </div>
                  
                  <ArrowRight 
                    size={20} 
                    className={`
                      transition-all duration-300
                      ${activeDevice === device.id 
                        ? 'text-apple-blue transform translate-x-1' 
                        : 'text-apple-gray-400'
                      }
                    `} 
                  />
                </motion.button>
              ))}
            </div>
          </div>

          {/* Device Preview */}
          <motion.div
            key={activeDevice}
            initial={{ opacity: 0, scale: 0.9 }}
            animate={{ opacity: 1, scale: 1 }}
            transition={{ type: "spring", stiffness: 300, damping: 30 }}
            className="flex justify-center"
          >
            <DevicePreview device={activeDevice} />
          </motion.div>
        </div>
      </div>

      {/* Features Section */}
      <div className="bg-white/50 backdrop-blur-sm">
        <div className="max-w-7xl mx-auto px-6 py-16">
          <motion.div
            initial={{ opacity: 0, y: 30 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.8 }}
            className="text-center mb-12"
          >
            <h2 className="text-4xl font-semibold text-apple-gray-700 mb-4">
              Built for Excellence
            </h2>
            <p className="text-lg text-apple-gray-500 max-w-2xl mx-auto">
              Every feature is crafted with Apple's design principles in mind, 
              delivering an experience that feels native to your device.
            </p>
          </motion.div>

          <div className="grid md:grid-cols-3 gap-8">
            {features.map((feature, index) => (
              <motion.div
                key={feature.title}
                initial={{ opacity: 0, y: 30 }}
                animate={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.6, delay: index * 0.2 }}
                className="text-center p-8 bg-white/60 backdrop-blur-sm rounded-squircle-lg shadow-apple hover:shadow-apple-lg transition-all duration-300"
              >
                <div className="w-16 h-16 mx-auto mb-6 bg-apple-gray-100 rounded-squircle flex items-center justify-center">
                  <feature.icon size={32} className={feature.color} />
                </div>
                <h3 className="text-xl font-semibold text-apple-gray-700 mb-3">
                  {feature.title}
                </h3>
                <p className="text-apple-gray-500">
                  {feature.description}
                </p>
              </motion.div>
            ))}
          </div>
        </div>
      </div>

      {/* CTA Section */}
      <div className="max-w-7xl mx-auto px-6 py-16">
        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.8 }}
          className="text-center bg-gradient-to-r from-apple-blue to-apple-purple rounded-squircle-lg p-12 text-white"
        >
          <h2 className="text-4xl font-semibold mb-4">
            Ready to Experience Lunetix?
          </h2>
          <p className="text-xl opacity-90 mb-8 max-w-2xl mx-auto">
            Join thousands of users who have made the switch to a better, 
            more private browsing experience.
          </p>
          
          <div className="flex flex-col sm:flex-row gap-4 justify-center">
            <motion.button
              whileHover={{ scale: 1.05 }}
              whileTap={{ scale: 0.95 }}
              onClick={() => window.location.href = '/desktop'}
              className="flex items-center justify-center px-8 py-4 bg-white text-apple-blue rounded-squircle font-semibold hover:bg-apple-gray-50 transition-colors"
            >
              <Monitor size={20} className="mr-2" />
              Try Desktop Version
            </motion.button>
            
            <motion.button
              whileHover={{ scale: 1.05 }}
              whileTap={{ scale: 0.95 }}
              onClick={() => window.location.href = '/mobile'}
              className="flex items-center justify-center px-8 py-4 bg-white/20 text-white rounded-squircle font-semibold hover:bg-white/30 transition-colors border border-white/30"
            >
              <Smartphone size={20} className="mr-2" />
              Try Mobile Version
            </motion.button>
          </div>
        </motion.div>
      </div>
    </div>
  );
};

export default EcosystemDemo;