#ifndef FORMATMODEL_H
#define FORMATMODEL_H

#include <QObject>

/* 显示格式model */
class FormatModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(bool isSelected READ getIsSelected WRITE setIsSelected NOTIFY sig_selected)

public:
    //显示格式
    enum DisplayFormat{
        HEX, //十六进制
        ASCII, //ASCII
    };
    Q_ENUM(DisplayFormat)

public:
    FormatModel(QString m_name="", bool m_isSelected=false, DisplayFormat m_format=DisplayFormat::HEX, QObject *parent = nullptr);

    QString getName();
    bool	getIsSelected();
    void setIsSelected(bool state);

private:
    QString name; //名称
    bool isSelected; //选中标志
    DisplayFormat format; //格式

signals:
    void sig_selected(DisplayFormat format); //已被选中

public slots:

};

#endif // FORMATMODEL_H
