#ifndef SYNCSTATE_H
#define SYNCSTATE_H

#include <QObject>
#include <QVariant>
#include <QTimer>
#include <QPointer>

class SyncObject;
class SyncClient;

class SyncState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(SyncObject* parentState READ parentState WRITE setParentState NOTIFY parentStateChanged)
    Q_PROPERTY(SyncClient* syncClient READ syncClient NOTIFY syncClientChanged)

    QPointer<SyncObject> m_parentState;
    QPointer<SyncClient> m_syncClient;

protected:
    QVariant m_value;
    QVariant m_desyncValue;
    QTimer* m_desyncTimer;
    QMap<QString,QPointer<SyncState>>::iterator m_objectPosition;
    friend class SyncObject;

public:
    explicit SyncState(QObject *parent = nullptr);
    explicit SyncState(SyncClient *client, QObject *parent = nullptr);

    SyncObject *parentState() const;

    const QVariant &value() const {
        return m_value;
    }

    SyncClient *syncClient() const;

    QTimer *desyncTimer();

    static int desyncInterval;

    const QVariant &desyncValue() const;

signals:

    void parentStateChanged(SyncObject* parentState);
    void valueChanged(QVariant value);
    void syncClientChanged(SyncClient* syncClient);

    void nextValueChanged(QVariant nextValue);

public slots:
    void setParentState(SyncObject* parentState);
    void setValue(const QVariant &value);

private slots:
    void setSyncClient(SyncClient* syncClient);

protected slots:
    virtual void updateValue();
    virtual void syncValue(const QVariant& value);
};

#endif // SYNCSTATE_H
