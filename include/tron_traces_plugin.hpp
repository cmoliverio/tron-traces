#ifndef TRON_TRACES_PLUGIN_H
#define TRON_TRACES_PLUGIN_H

#include <QObject>
#include <QQmlExtensionPlugin>

class TronTracesPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri);
};

#endif // TRON_TRACES_PLUGIN_H