#ifndef TRON_TRACES_H
#define TRON_TRACES_H

#include <QObject>
#include <QQuickFramebufferObject>

class TronTraces : public QQuickFramebufferObject {
    Q_OBJECT
public:
    Renderer *createRenderer() const override;
};

#endif // TRON_TRACES_H