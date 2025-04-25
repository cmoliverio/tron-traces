#include "tron_traces.hpp"
#include <QQmlEngine>
#include <QtQml>

static QObject *gol_singletontype_provider(QQmlEngine *, QJSEngine *) {
    return new GolPlugin();
}

void register_gol_plugin() {
    qmlRegisterSingletonType<GolPlugin>("Gol", 1, 0, "Gol", gol_singletontype_provider);
}

Q_COREAPP_STARTUP_FUNCTION(register_gol_plugin)