#include "syncstate.h"
#include "syncclient.h"
#include "syncobject.h"

int SyncState::desyncInterval = 1000;

QTimer* SyncState::desyncTimer()
{
    if(!m_desyncTimer) {
        m_desyncTimer = new QTimer(this);
        m_desyncTimer->setSingleShot(true);
        m_desyncTimer->setInterval(desyncInterval);
        connect( m_desyncTimer, &QTimer::timeout, this, &SyncState::updateValue );
    }
    return m_desyncTimer;
}

const QVariant &SyncState::desyncValue() const
{
    return m_desyncValue;
}

SyncState::SyncState(QObject *parent) : QObject(parent), m_desyncTimer(nullptr)
{

}

SyncState::SyncState(SyncClient *client, QObject *parent) : QObject(parent), m_syncClient(client), m_desyncTimer(nullptr)
{

}

SyncObject *SyncState::parentState() const
{
    return m_parentState;
}

SyncClient *SyncState::syncClient() const
{
    return m_syncClient;
}

void SyncState::setParentState(SyncObject *parentState)
{
    if (m_parentState == parentState)
        return;

    if(m_parentState) {
        QObject::disconnect(this,nullptr,m_parentState.data(),nullptr);
        m_parentState->removeState(this);
    }

    m_parentState = parentState;

    if(parentState) {
        setSyncClient(parentState->syncClient());
        parentState->addState(this);
        QObject::connect(parentState,&SyncState::syncClientChanged,this,&SyncState::setSyncClient);
    }

    emit parentStateChanged(m_parentState);
}

void SyncState::setValue(const QVariant &value)
{
    if(m_value == value) return;
    if(m_desyncValue == value) return;
    m_desyncValue=value;

    if( !m_syncClient || m_syncClient->slave() ) {
        return desyncTimer()->start();
    }

    m_parentState->updateState(this);

}


void SyncState::setSyncClient(SyncClient *syncClient)
{
    if (m_syncClient == syncClient)
        return;

    m_syncClient = syncClient;

    emit syncClientChanged(m_syncClient);
}

void SyncState::updateValue()
{
    if (m_value == m_desyncValue)
        return;

    m_value = m_desyncValue;
    emit valueChanged(m_value);
}

void SyncState::syncValue(const QVariant &value)
{
    if (m_value == value)
        return;
    if(m_desyncTimer) m_desyncTimer->stop();
    m_value = value;
    emit valueChanged(m_value);
}
