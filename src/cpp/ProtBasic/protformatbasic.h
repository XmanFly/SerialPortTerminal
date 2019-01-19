#ifndef PROTFORMATBASIC_H
#define PROTFORMATBASIC_H

#include <QVector>
#include <QMap>

template <typename K, typename T>
/* 协议内容基类 */
class ProtFormatBasic
{
public:
    ProtFormatBasic()
    {
    }
    ProtFormatBasic(const ProtFormatBasic<K, T> &src)
    {
        inforList = src.inforList;
    }
    virtual ~ProtFormatBasic()
    {

    }

    T getInfor(const K &name)
    {
        return inforList.value(name);
    }
    void addInfor(const K &key, const T &value)
    {
        inforList.insert(key, value);
    }
    void clear()
    {
        inforList.clear();
    }
    void setIsValid(bool valid) {
        isValid = valid;
    }
    bool getIsValid() const {
        return isValid;
    }

protected:
    QMap<K, T> inforList; //信息内容
    bool isValid; //内容是否有效

};

#endif // PROTFORMATBASIC_H
