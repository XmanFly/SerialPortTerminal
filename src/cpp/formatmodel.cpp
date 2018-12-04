#include "formatmodel.h"

FormatModel::FormatModel(QString m_name, bool m_isSelected, DisplayFormat m_format, QObject *parent)
  : QObject(parent),
    name(m_name),
    isSelected(m_isSelected),
    format(m_format)
{

}

QString FormatModel::getName()
{
    return name;
}

bool FormatModel::getIsSelected()
{
    return isSelected;
}


void FormatModel::setIsSelected(bool state)
{
    isSelected = state;
    if(isSelected){
        emit sig_selected(format);
    }
}
