#ifndef THE_GRID_H
#define THE_GRID_H

// #include <GL/glew.h>
// #include <GL/gl.h>

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>

class TheGrid : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT
public:
    TheGrid(QWidget *parent = nullptr);
    ~TheGrid();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    
private:
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *shaderProgram;
    QMatrix4x4 projectionMatrix;
};

#endif // THE_GRID_H