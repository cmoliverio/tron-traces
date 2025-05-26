#include "the_grid.hpp"

#include <QMatrix4x4>
#include <QVector3D>

TheGrid::TheGrid(QWidget *parent) : QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer) {}

TheGrid::~TheGrid() {}

float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f
 };

void TheGrid::initializeGL()
{
    initializeOpenGLFunctions();

    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Top vertex
        -0.5f, -0.5f, 0.0f, // Bottom left vertex
        0.5f, -0.5f, 0.0f  // Bottom right vertex
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                        "#version 330 core\n"
                                        "layout(location = 0) in vec3 position;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    gl_Position = vec4(position, 1.0);\n"
                                        "}\n"
                                        );
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        "#version 330 core\n"
                                        "out vec4 fragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    fragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                        "}\n"
                                        );
    shaderProgram->link();
    shaderProgram->bind();
}

void TheGrid::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TheGrid::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram->bind();
    vbo.bind();

    int posLocation = shaderProgram->attributeLocation("position");
    shaderProgram->enableAttributeArray(posLocation);
    shaderProgram->setAttributeBuffer(posLocation, GL_FLOAT, 0, 3);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    shaderProgram->disableAttributeArray(posLocation);
    vbo.release();
    shaderProgram->release();
}