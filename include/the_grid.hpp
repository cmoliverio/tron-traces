#ifndef THE_GRID_H
#define THE_GRID_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>

class TheGrid : public QObject, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit TheGrid(QObject *parent = nullptr);
    void initialize();
    void render(QOpenGLFramebufferObject *fbo);
    
private:
    GLuint gridVAO, gridVBO;
};

#endif // THE_GRID_H