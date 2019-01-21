#include "afpsformat.h"

AfpsFormat::AfpsFormat()
{

}

DEV_ID AfpsFormat::getDevId()
{
    return static_cast<DEV_ID>(getInfor(PROT_FIELD::REGIST).at(0));
}
