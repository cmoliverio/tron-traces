#include "the_grid.hpp"

#include <QMatrix4x4>
#include <QVector3D>

TheGrid::TheGrid(QWidget *parent) : QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer) {}

TheGrid::~TheGrid() {}

GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Top vertex
        -0.577f, -0.5f, 0.0f, // Bottom left vertex
        0.577f, -0.5f, 0.0f  // Bottom right vertex
};

void TheGrid::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Top vertex
        -0.577f, -0.5f, 0.0f, // Bottom left vertex
        0.577f, -0.5f, 0.0f  // Bottom right vertex
    };

    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    shaderProgram = new QOpenGLShaderProgram();

    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                        "#version 330 core\n"
                                        "layout(location = 0) in vec3 position;\n"
                                        "uniform mat4 model;\n"
                                        "uniform mat4 view;\n"
                                        "uniform mat4 projection;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    gl_Position = projection * view * model * vec4(position.x, -position.y, position.z, 1.0);\n"
                                        "}\n"
                                        );
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        "#version 330 core\n"
    "out vec4 fragColor;\n"
    "uniform float time;\n"
    "void main()\n"
    "{\n"
    "    float r = (sin(time) + 1.0) * 0.5;\n"
    "    float g = (sin(time + 2.0) + 1.0) * 0.5;\n"
    "    float b = (sin(time + 4.0) + 1.0) * 0.5;\n"
    "    fragColor = vec4(r, g, b, 1.0);\n"
    "}\n"
                                        );
    shaderProgram->link();
    shaderProgram->bind();
}

void TheGrid::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    
    // Calculate aspect ratio and create orthographic projection
    float aspect = float(w) / float(h);
    projectionMatrix.setToIdentity();
    
    // if (aspect > 1.0f) {
    //     // Wider than tall - scale X to maintain square aspect
    //     projectionMatrix.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    // } else {
    //     // Taller than wide - scale Y to maintain square aspect  
    //     projectionMatrix.ortho(-1.0f, 1.0f, -1.0f/aspect, 1.0f/aspect, -1.0f, 1.0f);
    // }

    projectionMatrix.perspective(45.0f, aspect, 0.1f, 100.0f);
}

void TheGrid::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram->bind();

    // Get elapsed time in seconds
    static auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    float time = std::chrono::duration<float>(currentTime - startTime).count();

    // Model matrix: rotate + translate (move back and forth on Z)
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    // Oscillate along Z: between -2.0 and -5.0
    float zPos = -3.5f + std::sin(time) * 1.5f;  
    modelMatrix.translate(0.0f, 0.0f, zPos);

    // Rotate around Y axis
    modelMatrix.rotate(time * 50.0f, 0.0f, 1.0f, 0.0f);  // degrees per second

    // View matrix: place camera back at Z = 0
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    // No translation needed if camera stays at origin

    shaderProgram->setUniformValue("model", modelMatrix);
    shaderProgram->setUniformValue("view", viewMatrix);
    shaderProgram->setUniformValue("projection", projectionMatrix);
    shaderProgram->setUniformValue("time", time);
    
    vbo.bind();
    int posLocation = shaderProgram->attributeLocation("position");
    shaderProgram->enableAttributeArray(posLocation);
    shaderProgram->setAttributeBuffer(posLocation, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    shaderProgram->disableAttributeArray(posLocation);
    vbo.release();
    shaderProgram->release();
}