import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import MobileInterface from './components/MobileInterface';
import DesktopInterface from './components/DesktopInterface';
import EcosystemDemo from './components/EcosystemDemo';
import './index.css';

const App = () => {
  // Detect device type based on URL params or user agent
  const urlParams = new URLSearchParams(window.location.search);
  const forceMode = urlParams.get('mode');
  
  const isMobile = forceMode === 'mobile' || 
    (!forceMode && /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent));

  return (
    <Router>
      <Routes>
        <Route path="/mobile" element={<MobileInterface />} />
        <Route path="/desktop" element={<DesktopInterface />} />
        <Route path="/ecosystem" element={<EcosystemDemo />} />
        <Route path="/" element={isMobile ? <MobileInterface /> : <DesktopInterface />} />
      </Routes>
    </Router>
  );
};

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);