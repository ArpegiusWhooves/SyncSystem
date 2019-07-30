#ifndef SYNCOBJECT_H
#define SYNCOBJECT_H

#include <QObject>

#include <syncstate.h>

class SyncObject : public SyncState
{
    Q_OBJECT

    QMap<QString, QPointer<SyncState>> m_syncObjects;
    QVariantMap m_map;
    friend class SyncClient;

public:
    explicit SyncObject(QObject *parent = nullptr);
    explicit SyncObject(SyncClient *client, QObject *parent = nullptr);

signals:

public slots:

    void updateState(SyncState* state);
    void addState(SyncState* state);
    void removeState(SyncState* state);

    void updateValue() override;
    void syncValue(const QVariant& value) override;
};

#endif // SYNCOBJECT_H
