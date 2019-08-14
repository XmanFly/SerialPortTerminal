#ifndef REGRWLISTVM_H
#define REGRWLISTVM_H

#include <QObject>
#include <QtQml>
#include <QList>
#include "regreadwritemodel.h"

class RegRWListVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<RegReadWriteModel> readWriteList READ getRWList CONSTANT)
public:
    explicit RegRWListVM(QObject *parent = nullptr);

    QQmlListProperty<RegReadWriteModel> getRWList();
    void appendRWList(RegReadWriteModel*);
    int rwListCount() const;
    RegReadWriteModel* get(int) const;
    void clearRWList();
    QList<RegReadWriteModel* >* getRawList();

signals:

public slots:

private:
    QList<RegReadWriteModel* > rwList;

    static void appendRWList(QQmlListProperty<RegReadWriteModel>*, RegReadWriteModel*);
    static int rwListCount(QQmlListProperty<RegReadWriteModel>*);
    static RegReadWriteModel* get(QQmlListProperty<RegReadWriteModel>*, int);
    static void clearRWList(QQmlListProperty<RegReadWriteModel>*);

};

#endif // REGRWLISTVM_H
