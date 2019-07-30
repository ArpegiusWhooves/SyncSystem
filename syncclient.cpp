#include "syncclient.h"
#include <QNetworkDatagram>
#include <QDataStream>
#include <QNetworkInterface>

SyncClient::SyncClient(QObject *parent) : SyncObject(this, parent),
                                          m_socket(new QUdpSocket(this)),
                                          m_slave(false)
{
    connect(m_socket,&QUdpSocket::readyRead,this,&SyncClient::reciveDatagram);
}

void SyncClient::configure(const QVariantMap &config)
{
    m_socket->bind(QHostAddress::AnyIPv4, m_port=quint16(config.value("port",57575).toInt()), QUdpSocket::ShareAddress);
    if (m_socket->state() != QAbstractSocket::BoundState)
        qDebug() << tr(" Failed to bound on port %1").arg(m_port);

    QList<QNetworkInterface> mListIfaces = QNetworkInterface::allInterfaces();
    for( QNetworkInterface const& iface : mListIfaces ) {
        qDebug() << iface.humanReadableName();
    }

//    m_socket->setMulticastInterface(mListIfaces.last());

    if ( !m_socket->joinMulticastGroup(
            m_sendAddress=QHostAddress( config.value("multicast","239.255.255.127").toString() )
            ) )
    {
        qDebug() << tr(" Failed to joing group %1").arg(m_sendAddress.toString());
    }

}

void SyncClient::updateValue()
{
    SyncObject::updateValue();
    sendState();
}

void SyncClient::sendState()
{
    if(slave()) return;
    if (m_socket->state() != QAbstractSocket::BoundState) return;
    QByteArray array;
    {
        QDataStream stream(&array,QIODevice::WriteOnly);
        stream << m_map;
    }

    m_socket->writeDatagram(array,m_sendAddress,m_port);
}


void SyncClient::setSocket(QUdpSocket *socket)
{
    if (m_socket == socket)
        return;

    m_socket = socket;
    emit socketChanged(m_socket);
}

void SyncClient::setSlave(bool slave)
{
    if (m_slave == slave)
        return;

    m_slave = slave;
    emit slaveChanged(m_slave);
}

void SyncClient::reciveDatagram()
{
    while(m_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = m_socket->receiveDatagram();
        QDataStream stream( datagram.data() );
        stream >> m_map;
        syncValue(m_map);
    }
}
