#include "the_grid.hpp"

#include <QMatrix4x4>
#include <QVector3D>

TheGrid::TheGrid(QWidget *parent) : QOpenGLWidget(parent), vbo(QOpenGLBuffer::VertexBuffer), lineVBO(QOpenGLBuffer::VertexBuffer) {}

TheGrid::~TheGrid() {
    if (lineShaderProgram) {
        delete lineShaderProgram;
    }
}

GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Top vertex
        -0.577f, -0.5f, 0.0f, // Bottom left vertex
        0.577f, -0.5f, 0.0f  // Bottom right vertex
};

void TheGrid::initialize_light_cycles()
{
    this->trails = std::make_unique<std::vector<std::unique_ptr<LightTrail>>>();
    
    // Method 1: Using make_unique (recommended)
    this->trails->push_back(
        std::make_unique<LightTrail>(Point{0.0f, 0.1f, 0.5f}, Direction::RIGHT)
    );
    this->trails->back()->move();
}

void TheGrid::move_light_cycles()
{
    for(int i = 0; i < this->trails->size(); i++)
    {
        this->trails->at(i)->move();
    }
}

void TheGrid::initializeGL()
{
    initialize_light_cycles();
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f, // Top vertex
        -0.577f, -0.5f, 0.0f, // Bottom left vertex
        0.577f, -0.5f, 0.0f  // Bottom right vertex
    };

    // Initialize triangle VBO
    vbo.create();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));

    // Initialize line VBO
    lineVBO.create();

    // Create triangle shader program
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

    // Create line shader program
    lineShaderProgram = new QOpenGLShaderProgram();
    lineShaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex,
        "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out float distanceFromCamera;\n"
        "void main()\n"
        "{\n"
        "    vec4 worldPos = model * vec4(position.x, -position.y, position.z, 1.0);\n"
        "    vec4 viewPos = view * worldPos;\n"
        "    gl_Position = projection * viewPos;\n"
        "    \n"
        "    // Calculate distance from camera (in view space, camera is at origin)\n"
        "    distanceFromCamera = length(viewPos.xyz);\n"
        "}\n"
        );
    lineShaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment,
        "#version 330 core\n"
        "in float distanceFromCamera;\n"
        "out vec4 fragColor;\n"
        "uniform vec3 lineColor;\n"
        "uniform float time;\n"
        "void main()\n"
        "{\n"
        "    // Glowing effect for the trail\n"
        "    float intensity = 0.8 + 0.2 * sin(time * 3.0);\n"
        "    \n"
        "    // Distance-based alpha falloff\n"
        "    float alpha = 1.0 / (1.0 + distanceFromCamera * 0.3);\n"
        "    alpha = clamp(alpha, 0.3, 1.0); // Keep minimum visibility\n"
        "    \n"
        "    fragColor = vec4(lineColor * intensity, alpha);\n"
        "}\n"
        );
    lineShaderProgram->link();
}

void TheGrid::updateLineGeometry()
{
    std::vector<GLfloat> lineVertices;
    
    // Collect all trail points from all light cycles
    for (const auto& trail : *trails) {
        if (trail->trail->size() >= 1) {
            // Convert trail points to line segments
            for (size_t i = 0; i < trail->trail->size() - 1; i++) {
                const Point& p1 = trail->trail->at(i);
                const Point& p2 = trail->trail->at(i + 1);
                
                // Add first point
                lineVertices.push_back(p1[0]);
                lineVertices.push_back(p1[1]);
                lineVertices.push_back(p1[2]);
                
                // Add second point
                lineVertices.push_back(p2[0]);
                lineVertices.push_back(p2[1]);
                lineVertices.push_back(p2[2]);
            }
            
            // Add line from last trail point to current moving position
            if (!trail->trail->empty()) {
                const Point& lastTrailPoint = trail->trail->back();
                const Point& currentPoint = trail->current_point;
                
                // Add last trail point
                lineVertices.push_back(lastTrailPoint[0]);
                lineVertices.push_back(lastTrailPoint[1]);
                lineVertices.push_back(lastTrailPoint[2]);
                
                // Add current moving point
                lineVertices.push_back(currentPoint[0]);
                lineVertices.push_back(currentPoint[1]);
                lineVertices.push_back(currentPoint[2]);
            }
        }
    }
    
    // Update line VBO
    if (!lineVertices.empty()) {
        lineVBO.bind();
        lineVBO.allocate(lineVertices.data(), lineVertices.size() * sizeof(GLfloat));
        lineVertexCount = lineVertices.size() / 3;
    } else {
        lineVertexCount = 0;
    }
}

void TheGrid::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    
    // Calculate aspect ratio and create orthographic projection
    float aspect = float(w) / float(h);
    projectionMatrix.setToIdentity();
    
    projectionMatrix.perspective(45.0f, aspect, 0.1f, 100.0f);
}

void TheGrid::paintGL()
{
    move_light_cycles();
    updateLineGeometry();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get elapsed time in seconds
    static auto strt_tme = std::chrono::steady_clock::now();
    auto crrnt_tme = std::chrono::steady_clock::now();
    float time = std::chrono::duration<float>(crrnt_tme - strt_tme).count();

    // Model matrix: rotate + translate (move back and forth on Z)
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    // Oscillate along Z: between -2.0 and -5.0
    float zPos = -3.5f + std::sin(time) * 1.5f;  
    modelMatrix.translate(0.0f, 0.0f, zPos);

    degrees_rotated = std::fmod(360.0f + (degrees_rotated + 2.5f), 360.0f);

    // Rotate around Y axis
    // modelMatrix.rotate(degrees_rotated, 0.0f, 0.5f, 1.0f);

    // View matrix: place camera back at Z = 0
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();

    // Draw triangle
    shaderProgram->bind();
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

    // Draw light trails
    if (lineVertexCount > 0) {
        // Enable blending for alpha transparency
        glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glLineWidth(3.0f); // Make lines thicker for better visibility
        
        lineShaderProgram->bind();
        lineShaderProgram->setUniformValue("model", modelMatrix);
        lineShaderProgram->setUniformValue("view", viewMatrix);
        lineShaderProgram->setUniformValue("projection", projectionMatrix);
        lineShaderProgram->setUniformValue("lineColor", QVector3D(0.0f, 1.0f, 1.0f)); // Cyan color
        lineShaderProgram->setUniformValue("time", time);
        
        lineVBO.bind();
        int linePosLocation = lineShaderProgram->attributeLocation("position");
        lineShaderProgram->enableAttributeArray(linePosLocation);
        lineShaderProgram->setAttributeBuffer(linePosLocation, GL_FLOAT, 0, 3);
        glDrawArrays(GL_LINES, 0, lineVertexCount);
        lineShaderProgram->disableAttributeArray(linePosLocation);
        lineVBO.release();
        lineShaderProgram->release();
        
        // Disable blending
        glDisable(GL_BLEND);
    }
}