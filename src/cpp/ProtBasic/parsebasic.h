#ifndef PARSEBASIC_H
#define PARSEBASIC_H

template <typename T, class R>
/* 协议解析基类 */
class ParseBasic
{
public:
    ParseBasic() {
    }

    virtual ~ParseBasic(){

    }

    virtual void parse(T &buf, R &mProtResult) = 0;

protected:

};

#endif // PARSEBASIC_H
