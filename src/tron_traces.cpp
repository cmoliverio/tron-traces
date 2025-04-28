// TronGridRenderer.cpp
#include "tron_traces.hpp"
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
    }
    
    ~TronRendererObject() {
        delete m_renderer;
    }
    
    void render() override {
        // Clear the framebuffer
        QOpenGLFramebufferObject *fbo = framebufferObject();
        m_renderer->render(fbo);
    }
    
    void synchronize(QQuickFramebufferObject *item) override {
        // Update animation state
        m_renderer->update(m_deltaTime);
    }
    
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        return new QOpenGLFramebufferObject(size, format);
    }
    
private:
    TronGridRenderer *m_renderer;
    qreal m_deltaTime = 0.016; // ~60fps
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

void TronGridRenderer::render(QOpenGLFramebufferObject *fbo) {
    // Make sure we're rendering to the correct framebuffer
    fbo->bind();
    
    // Set up OpenGL state
    glClearColor(0.7f, 0.7f, 0.0f, 1.0f); // Dark blue background - TRON-like
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Enable blending for the glow effect
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw a simple grid
    glBegin(GL_LINES);
    
    // Set color for grid lines - TRON cyan color
    glColor4f(0.0f, 0.7f, 0.f, 0.1f);
    
    // Draw horizontal grid lines
    float gridSize = 1.0f;
    int gridCount = 20;
    for (int i = -gridCount; i <= gridCount; i++) {
        glVertex3f(-gridCount * gridSize, 0.0f, i * gridSize);
        glVertex3f(gridCount * gridSize, 0.0f, i * gridSize);
    }
    
    // Draw vertical grid lines
    for (int i = -gridCount; i <= gridCount; i++) {
        glVertex3f(i * gridSize, 0.0f, -gridCount * gridSize);
        glVertex3f(i * gridSize, 0.0f, gridCount * gridSize);
    }
    
    glEnd();

    qDebug() << "Drawing grid...";
    
    // Disable blending
    glDisable(GL_BLEND);
    
    fbo->release();
}

void TronGridRenderer::update(qreal deltaTime) {
    // Update animation state
    // In a full implementation:
    // 1. Update line positions
    // 2. Update any other animated elements
}