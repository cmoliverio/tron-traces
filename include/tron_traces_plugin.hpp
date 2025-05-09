#ifndef TRON_TRACES_PLUGIN_H
#define TRON_TRACES_PLUGIN_H

#include <QObject>
#include <QtQml>
#include <QQmlExtensionPlugin>
#include <QtQml/qqmlextensionplugin.h>

class TronTracesPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    // Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlEngineExtensionInterface")
public:
    // void registerTypes(const char *uri) override;
    void TronTracesPlugin::registerTypes(const char *uri) override {
        qmlRegisterType<TronTraces>(uri, 1, 0, "TronTraces");
    }
};

#endif // TRON_TRACES_PLUGIN_H