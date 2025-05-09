#include "tron_traces_renderer.hpp"


TronTracesRenderer::TronTracesRenderer() {
    qDebug() << "I'm initializing!";
    
    // starts the timer
    m_timer.start();
    
    // timer to trigger redraws
    m_frameTimer = new QTimer();
    m_frameTimer->setInterval(16); // in milliseconds
    
    // Connect the timer to trigger updates
    QObject::connect(m_frameTimer, &QTimer::timeout, [this]() {
        update(); // requests the render() function to be called
    });
    
    // Start the timer
    m_frameTimer->start();
}

TronTracesRenderer::~TronTracesRenderer() {
    // destroy
    qDebug() << "DYing";
}

void TronTracesRenderer::render() {
    // Calculate time since last render
    qint64 currentTime = m_renderTimer.elapsed();
    qint64 timeSinceLastRender = currentTime - m_lastRenderTime;

    // qDebug() << "Time since last render:" << timeSinceLastRender << "ms";
    // qDebug() << "Holy crap I'm RENdering";

    // Update last render time
    m_lastRenderTime = currentTime;
}