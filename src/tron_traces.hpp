#include <QObject>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QtQml/qqmlextensionplugin.h>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class TronGridRenderer : public QObject, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit TronGridRenderer(QObject *parent = nullptr);
    void initialize();
    void render(QOpenGLFramebufferObject *fbo);
    void update(qreal deltaTime);
    
private:
    // OpenGL objects, grid and line data
    GLuint gridVAO, gridVBO;
    // ... other OpenGL resources
};

class TronRendererItem : public QQuickFramebufferObject {
    Q_OBJECT
public:
    Renderer *createRenderer() const override;
};

class TronTracesPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override {
        qmlRegisterType<TronRendererItem>(uri, 1, 0, "TronRendererItem");
    }
};