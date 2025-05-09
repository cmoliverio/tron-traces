#include "tron_traces.hpp"

QQuickFramebufferObject::Renderer *TronTraces::createRenderer() const {
    return new TronRendererObject();
}