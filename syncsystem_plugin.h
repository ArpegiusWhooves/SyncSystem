#ifndef SYNCSYSTEM_PLUGIN_H
#define SYNCSYSTEM_PLUGIN_H

#include <QQmlExtensionPlugin>

class SyncSystemPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // SYNCSYSTEM_PLUGIN_H
