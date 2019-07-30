#include "syncobject.h"
#include <syncclient.h>

SyncObject::SyncObject(QObject *parent) : SyncState(parent)
{

}

SyncObject::SyncObject(SyncClient *client, QObject *parent): SyncState (client, parent)
{

}

void SyncObject::updateState(SyncState *state)
{
    m_map[state->objectName()] = state->m_value;
    if(m_parentState)
        m_parentState->updateState(this);
    else if(m_syncClient)
        m_syncClient->sendState();
}

void SyncObject::addState(SyncState *state)
{
    state->m_objectPosition = m_syncObjects.insert( state->objectName(), state );
    updateState(state);
}

void SyncObject::removeState(SyncState *state)
{
    m_syncObjects.erase(state->m_objectPosition);
}

void SyncObject::updateValue()
{
    SyncState::updateValue();
    m_map["_value"] = m_value;
}

void SyncObject::syncValue(const QVariant &value)
{
    m_map = value.toMap();
    SyncState::syncValue(m_map.value("_value",m_value));
    for(auto i = m_syncObjects.begin(); i != m_syncObjects.end(); ++i) {
        auto f = m_map.find(i.key());
        if(f != m_map.end())
            i.value()->syncValue(f.value());
    }
}
