#include "tron_traces.hpp"
#include "tron_traces_renderer.hpp"

QQuickFramebufferObject::Renderer *TronTraces::createRenderer() const {
    return new TronTracesRenderer();
}