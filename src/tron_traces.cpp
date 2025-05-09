#include "tron_traces_renderer.hpp"
#include "tron_traces.hpp"

// note to self, this destructor can't be declared
// in the header in order to be linkable
// TronTraces::TronTraces(){};
// TronTraces::~TronTraces(){};

QQuickFramebufferObject::Renderer *TronTraces::createRenderer() const {
    return new TronTracesRenderer();
}