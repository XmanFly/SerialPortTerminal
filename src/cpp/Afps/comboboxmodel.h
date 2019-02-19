#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>

/* 下拉列表数据model */
class ComboBoxModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString value READ getValue WRITE setValue NOTIFY sig_valueChanged)
public:
    explicit ComboBoxModel(QString m_value = "", QObject *parent = nullptr);

    QString getValue() const;
    void setValue(QString value);

signals:
    void sig_valueChanged();

public slots:

private:
    QString value;

};

#endif // COMBOBOXMODEL_H
