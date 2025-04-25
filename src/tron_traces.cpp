#include "tron_traces.hpp"
#include <QQmlEngine>
#include <QtQml>

static QObject *tron_traces_singletontype_provider(QQmlEngine *, QJSEngine *) {
    return new TRONTraces();
}

void register_tron_traces_plugin() {
    qmlRegisterSingletonType<TRONTraces>("TRON Traces", 1, 0, "Gol", tron_traces_singletontype_provider);
}

Q_COREAPP_STARTUP_FUNCTION(register_tron_traces_plugin)