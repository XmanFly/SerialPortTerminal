#ifndef MONITORMODULE_H
#define MONITORMODULE_H

#include <QObject>
#include "paramonitor.h"

class MonitorModule : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<ParaMonitor> list READ getList CONSTANT)
public:
    explicit MonitorModule(QObject *parent = nullptr);

    QQmlListProperty<ParaMonitor> getList();
    void appendList(ParaMonitor*);
    int listCount() const;
    ParaMonitor* get(int) const;
    void clearList();
    QList<ParaMonitor* >* getRawList();

signals:

public slots:
    void slot_serialPortState(bool isOpen); //串口状态

private:
    QList<ParaMonitor* > list;

    static void appendList(QQmlListProperty<ParaMonitor>*, ParaMonitor*);
    static int listCount(QQmlListProperty<ParaMonitor>*);
    static ParaMonitor* get(QQmlListProperty<ParaMonitor>*, int);
    static void clearList(QQmlListProperty<ParaMonitor>*);

};

#endif // MONITORMODULE_H
