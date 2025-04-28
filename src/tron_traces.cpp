#include "tron_traces.hpp"
#include <QQmlEngine>
#include <QtQml>

void TRONTraces::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("org.kde.plasma.wallpapers.tron_traces"));
    
    qmlRegisterSingletonType<TRONTraces>(
        uri, 1, 0, "TRONTraces",
        [](QQmlEngine *engine, QJSEngine *) -> QObject* {
            return new TRONTraces();
        }
    );
}

// static QObject *tron_traces_singletontype_provider(QQmlEngine *, QJSEngine *) {
//   return new TRONTraces();
// }

// void register_tron_traces_plugin() {
//   qmlRegisterSingletonType<TRONTraces>("org.kde.plasma.wallpapers.tron_traces",
//                                        1, 0, "TRONTraces",
//                                        tron_traces_singletontype_provider);
// }

// Q_COREAPP_STARTUP_FUNCTION(register_tron_traces_plugin)