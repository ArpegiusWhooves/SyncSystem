#include "syncsystem_plugin.h"
#include "syncsystem.h"

#include <qqml.h>
#include <syncclient.h>
#include <qmlsyncstate.h>

void SyncSystemPlugin::registerTypes(const char *uri)
{
    // @uri com.github.ArpegiusWhooves.SyncSystem

    qmlRegisterType<SyncClient>(uri,1,0,"SyncClient");
    qmlRegisterType<SyncObject>(uri,1,0,"SyncObject");
    //    qmlRegisterType<SyncState>(uri,1,0,"SyncState");
    qmlRegisterType<QMLSyncState>(uri,1,0,"SyncState");
}

