#ifndef SYNCCLIENT_H
#define SYNCCLIENT_H

#include <QObject>
#include <QUdpSocket>

#include <syncobject.h>

class SyncClient : public SyncObject
{
    Q_OBJECT
    Q_PROPERTY(QUdpSocket* socket READ socket WRITE setSocket NOTIFY socketChanged)
    Q_PROPERTY(bool slave READ slave WRITE setSlave NOTIFY slaveChanged)

    QUdpSocket* m_socket;
    quint16 m_port;
    QHostAddress m_sendAddress;
    QList<QHostAddress> m_clients;

    bool m_slave;

public:
    explicit SyncClient(QObject *parent = nullptr);

    QUdpSocket* socket() const
    {
        return m_socket;
    }

    bool slave() const
    {
        return m_slave;
    }

signals:

    void socketChanged(QUdpSocket* socket);

    void slaveChanged(bool slave);

public slots:
    void configure(QVariantMap const& config);

    void updateValue() override;
    void sendState();

    void setSocket(QUdpSocket* socket);
    void setSlave(bool slave);

private slots:
    void reciveDatagram();
};

#endif // SYNCCLIENT_H
