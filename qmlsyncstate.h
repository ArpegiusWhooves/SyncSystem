#ifndef QMLSYNCSTATE_H
#define QMLSYNCSTATE_H
#include <syncstate.h>
#include <QQmlPropertyValueSource>
#include <QQmlProperty>

class QMLSyncState : public SyncState, public QQmlPropertyValueSource
{
    Q_OBJECT
    Q_INTERFACES(QQmlPropertyValueSource)

    QQmlProperty m_property;
public:
    explicit QMLSyncState(QObject *parent = nullptr);

    void setTarget(const QQmlProperty &prop) override;

signals:

public slots:
    void updateValue() override;
    void syncValue(const QVariant& value) override;
private slots:
    void propertyChanged();
};

#endif // QMLSYNCSTATE_H
