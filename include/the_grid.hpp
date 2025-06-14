#ifndef THE_GRID_H
#define THE_GRID_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>

#include "light_trail.hpp"

class TheGrid : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    TheGrid(QWidget *parent = nullptr);
    ~TheGrid();
    void initialize_light_cycles();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    float degrees_rotated = 0.0f;
    
private:
    QOpenGLBuffer vbo;
    QOpenGLBuffer lineVBO;
    QOpenGLShaderProgram *shaderProgram;
    QOpenGLShaderProgram *lineShaderProgram;
    QMatrix4x4 projectionMatrix;

    std::unique_ptr<std::vector<std::unique_ptr<LightTrail>>> trails;
};

#endif // THE_GRID_H