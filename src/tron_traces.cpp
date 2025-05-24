#include "plugin_renderer.hpp"
#include "tron_traces.hpp"

QQuickFramebufferObject::Renderer *TronTraces::createRenderer() const {
    return new PluginRenderer();
}