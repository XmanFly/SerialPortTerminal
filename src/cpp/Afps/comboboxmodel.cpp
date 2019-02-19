#include "comboboxmodel.h"

ComboBoxModel::ComboBoxModel(QString m_value, QObject *parent) :
    QObject(parent),
    value(m_value)
{

}

QString ComboBoxModel::getValue() const
{
    return value;
}

void ComboBoxModel::setValue(QString value)
{
    if(this->value.compare(value) != 0){
        this->value = value;
        emit sig_valueChanged();
    }
}
