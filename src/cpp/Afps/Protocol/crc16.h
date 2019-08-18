#ifndef CRC16_H
#define CRC16_H

#include <QByteArray>

typedef unsigned char       BYTE;
typedef unsigned short      WORD;

class CRC16
{
public:
    static const WORD wCRCTable[];

public:
    static QByteArray calc(const QByteArray &src, int len)
    {
        QByteArray res;
        WORD wRes = calcRaw(reinterpret_cast<const BYTE *>(src.data()), static_cast<WORD>(len));
        res.append(static_cast<char>(wRes&0xFF));
        res.append(static_cast<char>((wRes>>8)&0xFF));
        return res;
    }

    static WORD calcRaw(const BYTE *nData, WORD wLength)
    {
        BYTE nTemp;
        WORD wCRCWord = 0xFFFF;
        while (wLength--)
        {
            nTemp = *nData++ ^ wCRCWord;
            wCRCWord >>= 8;
            wCRCWord ^= wCRCTable[nTemp];
        }
        return wCRCWord;
    }

};

#endif // CRC16_H
