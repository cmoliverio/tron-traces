#ifndef TRON_TRACES_RENDERER_H
#define TRON_TRACES_RENDERER_H

#include <QtGlobal>
#include <QTimer>
#include <QElapsedTimer>
#include <QQuickFramebufferObject>

class TronTracesRenderer : public QQuickFramebufferObject::Renderer {
private:
    QTimer *m_frameTimer;
    QElapsedTimer m_timer;
    QElapsedTimer m_renderTimer;
    qint64 m_lastRenderTime = 0;
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