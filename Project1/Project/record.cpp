#include "record.h"


Record::Record(QDateTime time, int type, QString category, double amount, QString note)
{
    this->m_time=time;
    this->m_type=type;
    this->m_category=category;
    this->m_amount=amount;
    this->m_note=note;
}
