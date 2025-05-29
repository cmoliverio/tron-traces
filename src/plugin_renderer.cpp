#include "plugin_renderer.hpp"

#include <QCoreApplication>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>

PluginRenderer::PluginRenderer() {


    // QDBusInterface iface("org.kde.kscreen",
    //                      "/backend",
    //                      "org.kde.kscreen.Backend",
    //                      QDBusConnection::sessionBus());

    // if (!iface.isValid()) {
    //     qWarning() << "KScreen DBus interface is not valid!";
    //     return 1;
    // }

    // QDBusReply<QVariantMap> reply = iface.call("config");
    // if (!reply.isValid()) {
    //     qWarning() << "Failed to get screen config:" << reply.error().message();
    //     return 1;
    // }

    // QVariantMap config = reply.value();
    // QVariantList outputs = config["outputs"].toList();

    // for (const QVariant &outputVar : outputs) {
    //     QVariantMap output = outputVar.toMap();
    //     QString name = output["name"].toString();
    //     bool connected = output["connected"].toBool();
    //     bool enabled = output["enabled"].toBool();

    //     if (!connected || !enabled) continue;

    //     QVariantMap currentMode = output["currentMode"].toMap();
    //     int width = currentMode["width"].toInt();
    //     int height = currentMode["height"].toInt();
    //     double refresh = currentMode["refresh"].toDouble();

    //     qDebug() << "Monitor:" << name;
    //     qDebug() << "  Resolution:" << width << "x" << height;
    //     qDebug() << "  Refresh rate:" << refresh << "Hz";
    // }


    qDebug() << "I'm initializing!";

    the_grid = new TheGrid();
    the_grid->initializeGL();
    
    // starts the timer
    m_timer.start();
    
    // timer to trigger redraws
    m_frameTimer = new QTimer();
    m_frameTimer->setInterval(16); // in milliseconds
    
    // Connect the timer to trigger updates
    QObject::connect(m_frameTimer, &QTimer::timeout, [this]() {
        update(); // requests the render() function to be called
    });
    
    // Start the timer
    m_frameTimer->start();
}

PluginRenderer::~PluginRenderer() {
    // destroy
    qDebug() << "DYing";
}

void PluginRenderer::render() {
    // Calculate time since last render
    // qint64 currentTime = m_renderTimer.elapsed();
    // qint64 timeSinceLastRender = currentTime - m_lastRenderTime;

    // qDebug() << "Time since last render:" << timeSinceLastRender << "ms";
    // qDebug() << "Holy crap I'm RENdering";

    // QOpenGLFramebufferObject *fbo = framebufferObject();
    // the_grid->paintGL(fbo);
    the_grid->resizeGL(2560, 1440);
    the_grid->paintGL();

    // Update last render time
    // m_lastRenderTime = currentTime;
}