#include "afpsformat.h"

AfpsFormat::AfpsFormat()
{

}

void AfpsFormat::getDevId(DEV_ID &dev, bool &ok)
{
    switch(getInfor(PROT_FIELD::REGIST).at(0)){
    case AfpsProtPara::RGST_AD:
        dev = DEV_ID::DEV_AD;
        break;
    default:
        ok = false;
        return ;
    }
    ok = true;
}
