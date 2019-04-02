#include "algorithmviewmodel.h"

AfpsAlgorithmViewModel::AfpsAlgorithmViewModel(QObject *parent) : QObject(parent)
{
    setResult("Ready");
}


QString AfpsAlgorithmViewModel::getResult()
{
    return result;
}

void AfpsAlgorithmViewModel::setResult(QString result)
{
    if(this->result != result){
        this->result = result;
        emit sig_resultChanged();
    }
}

void AfpsAlgorithmViewModel::slot_updateResult(QString result)
{
    setResult(result);
}

