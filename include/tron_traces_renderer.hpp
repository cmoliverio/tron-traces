#ifndef TRON_TRACES_RENDERER_H
#define TRON_TRACES_RENDERER_H

#include <chrono>
#include <thread>
#include <QQuickFramebufferObject>

class TronTracesRenderer : public QQuickFramebufferObject::Renderer {
    public:
        TronTracesRenderer();
        ~TronTracesRenderer();
        
        void render() override;
    
    // private:
        // TronGridRenderer *m_renderer;
        // QElapsedTimer m_timer;
        // QTimer *m_frameTimer;
    };

#endif // TRON_TRACES_RENDERER_H