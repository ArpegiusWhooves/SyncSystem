#include "qmlsyncstate.h"

QMLSyncState::QMLSyncState(QObject *parent) : SyncState(parent)
{

}

void QMLSyncState::setTarget(const QQmlProperty &prop)
{
   m_property = prop;
   if(objectName().isEmpty()) setObjectName(prop.name());
   m_value = m_desyncValue = prop.read();
   prop.connectNotifySignal(this,SLOT(propertyChanged()));
}

void QMLSyncState::updateValue()
{
    SyncState::updateValue();
    if(m_property.isWritable()) m_property.write(m_value);
}

void QMLSyncState::syncValue(const QVariant &value)
{
    if (m_value == value)
        return;
    SyncState::syncValue(value);
    if(m_property.isWritable()) m_property.write(m_value);
}

void QMLSyncState::propertyChanged()
{
    setValue(m_property.read());
}
