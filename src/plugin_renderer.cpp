#include "plugin_renderer.hpp"

PluginRenderer::PluginRenderer() {
    qDebug() << "I'm initializing!";

    the_grid = new TheGrid();
    the_grid->initialize();
    
    // starts the timer
    m_timer.start();
    
    // timer to trigger redraws
    m_frameTimer = new QTimer();
    m_frameTimer->setInterval(100); // in milliseconds
    
    // Connect the timer to trigger updates
    QObject::connect(m_frameTimer, &QTimer::timeout, [this]() {
        update(); // requests the render() function to be called
    });
    
    // Start the timer
    m_frameTimer->start();
}

PluginRenderer::~PluginRenderer() {
    // destroy
    qDebug() << "DYing";
}

void PluginRenderer::render() {
    // Calculate time since last render
    qint64 currentTime = m_renderTimer.elapsed();
    qint64 timeSinceLastRender = currentTime - m_lastRenderTime;

    qDebug() << "Time since last render:" << timeSinceLastRender << "ms";
    qDebug() << "Holy crap I'm RENdering";

    QOpenGLFramebufferObject *fbo = framebufferObject();
    the_grid->render(fbo);

    // Update last render time
    m_lastRenderTime = currentTime;
}