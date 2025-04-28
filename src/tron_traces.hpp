#pragma once

#include <QQmlExtensionPlugin>

class TRONTraces : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.kde.plasma.wallpapers.tron_traces" FILE
                        "tron_traces.json")
public:
//   Q_INVOKABLE QString helloWorld() const {
//     return QStringLiteral("Hello from C++!");
//   }
  void registerTypes(const char *uri) override;
};