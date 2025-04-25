#pragma once

#include <QObject>

class TRONTraces : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE QString helloWorld() const { return "Hello from C++!"; }
};