#include "tron_traces_plugin.hpp"
#include "tron_traces.hpp"

void TronTracesPlugin::registerTypes(const char *uri) {
    qmlRegisterType<TronTraces>(uri, 1, 0, "TronTraces");
}