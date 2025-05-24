#ifndef PLUGIN_RENDERER_H
#define PLUGIN_RENDERER_H

#include <QtGlobal>
#include <QTimer>
#include <QElapsedTimer>
#include <QQuickFramebufferObject>

#include "the_grid.hpp"

class PluginRenderer : public QQuickFramebufferObject::Renderer {
private:
    QTimer *m_frameTimer;
    QElapsedTimer m_timer;
    QElapsedTimer m_renderTimer;
    qint64 m_lastRenderTime = 0;
    TheGrid *the_grid;
public:
    PluginRenderer();
    ~PluginRenderer();
    
    void render() override;
};

#endif // PLUGIN_RENDERER_H