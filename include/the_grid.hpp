#ifndef THE_GRID_H
#define THE_GRID_H

// #include <GL/glew.h>
// #include <GL/gl.h>

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class TheGrid : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT
public:
    TheGrid(QWidget *parent = nullptr);
    ~TheGrid();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    
private:
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *shaderProgram;
};

#endif // THE_GRID_H