#include <chrono>
#include <thread>
#include "tron_traces_renderer.hpp"


TronTracesRenderer::TronTracesRenderer() {
    // m_renderer = new TronGridRenderer();
    // m_renderer->initialize();
    qDebug() << "I'm initalizing!";

    // m_timer.start();

    // m_frameTimer = new QTimer();
    // m_frameTimer->setInterval(100); // ~60 FPS
    // QObject::connect(m_frameTimer, &QTimer::timeout, [this]() {
    //     update();  // <--- THIS is the correct way to trigger redraws
    // });
    // m_frameTimer->start();
}

TronTracesRenderer::~TronTracesRenderer() {
    // destroy
    qDebug() << "DYing";
}

void TronTracesRenderer::render() {

    qDebug() << "Holy crap im RENdering";
    
    // qreal elapsed = m_timer.elapsed() / 1000.0;
    // m_timer.restart();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // qDebug() << "I am updating now!";
    // QOpenGLFramebufferObject *fbo = framebufferObject();
    // m_renderer->grid_render(fbo);
    // m_renderer->update(0);

    // qDebug() << "I am updating now!\n";

    // QOpenGLFramebufferObject *fbo = framebufferObject();
    // m_renderer->grid_render(fbo);
    // m_renderer->update(0);
    
}