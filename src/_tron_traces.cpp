// TronGridRenderer.cpp
#include "tron_traces.hpp"
#include <chrono>
#include <random>
#include <thread>
#include <numbers>
#include <QTimer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <QQuickWindow>
#include <QMatrix4x4>
#include <QVector3D>

class TronRendererObject : public QQuickFramebufferObject::Renderer {
public:
    TronRendererObject() {
        m_renderer = new TronGridRenderer();
        m_renderer->initialize();

        m_timer.start();

        m_frameTimer = new QTimer();
        m_frameTimer->setInterval(100); // ~60 FPS
        QObject::connect(m_frameTimer, &QTimer::timeout, [this]() {
            update();  // <--- THIS is the correct way to trigger redraws
        });
        m_frameTimer->start();
    }

    ~TronRendererObject() {
        m_frameTimer->stop();
        delete m_frameTimer;
        delete m_renderer;
    }

    void render() override {
        
        // qreal elapsed = m_timer.elapsed() / 1000.0;
        // m_timer.restart();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        qDebug() << "I am updating now!";
        // QOpenGLFramebufferObject *fbo = framebufferObject();
        // m_renderer->grid_render(fbo);
        // m_renderer->update(0);

        // qDebug() << "I am updating now!\n";

        // QOpenGLFramebufferObject *fbo = framebufferObject();
        // m_renderer->grid_render(fbo);
        // m_renderer->update(0);
        
    }
    // TronRendererObject() {
    //     m_renderer = new TronGridRenderer();
    //     m_renderer->initialize();
    // }
    
    // ~TronRendererObject() {
    //     m_frameTimer->stop();
    //     delete m_frameTimer;
    //     delete m_renderer;
    // }

    // void render() override {
    //     qreal elapsed = m_timer.elapsed() / 1000.0;
    //     m_timer.restart();

    //     QOpenGLFramebufferObject *fbo = framebufferObject();
    //     m_renderer->render(fbo);
    //     m_renderer->update(elapsed);

    //     std::this_thread::sleep_for(std::chrono::milliseconds(16));
    // }
    
private:
    TronGridRenderer *m_renderer;
    QElapsedTimer m_timer;
    QTimer *m_frameTimer;
};

QQuickFramebufferObject::Renderer *TronRendererItem::createRenderer() const {
    return new TronRendererObject();
}

// Implementation of TronGridRenderer
TronGridRenderer::TronGridRenderer(QObject *parent) : QObject(parent) {
}

void TronGridRenderer::initialize() {
    initializeOpenGLFunctions();
    
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Set up viewport and camera
    glViewport(0, 0, 800, 600);

    // Create projection matrix
    QMatrix4x4 projection;
    projection.perspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
    
    // Create view matrix
    QMatrix4x4 view;
    view.lookAt(QVector3D(0.0f, 10.0f, 15.0f),  // Camera position
                QVector3D(0.0f, 0.0f, 0.0f),    // Look at point
                QVector3D(0.0f, 1.0f, 0.0f));   // Up vector
    
    // Load matrices
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.constData());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view.constData());

    qDebug() << "Initialize complete";
}

void TronGridRenderer::grid_render(QOpenGLFramebufferObject *fbo) {

    // Make sure we're rendering to the correct framebuffer
    fbo->bind();
    
    // Set up OpenGL state
    // using namespace std::chrono;
    // auto now = system_clock::now().time_since_epoch() % std::numbers::pi;
    // float seconds = duration_cast<duration<float>>(now).count();
    // qDebug() << "seconds is" << seconds;
    // float blue = 0.5 + (sinf(seconds) / 4);

    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister RNG
    std::uniform_real_distribution<> dist(0.6, 0.8);

    double randomValue = dist(gen);

    qDebug() << "randval is " << randomValue;

    glClearColor(0.0f, 0.3f, 0.6, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Enable blending for the glow effect
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Disable blending
    glDisable(GL_BLEND);
    
    fbo->release();

    qDebug() << "GRID redner";
}

void TronGridRenderer::update(qreal deltaTime) {
    deltaTime += 0;
    qDebug() << "In update func";
}