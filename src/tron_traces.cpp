#include "tron_traces_renderer.hpp"
#include "tron_traces.hpp"

QQuickFramebufferObject::Renderer *TronTraces::createRenderer() const {
    return new TronTracesRenderer();
}