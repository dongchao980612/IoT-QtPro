#ifndef RECORD_H
#define RECORD_H
#include <QDateTime>
#include <QString>


class Record
{
public:
    Record() = default;   // 默认构造，供容器使用
    Record(QDateTime time, int type, QString category, double amount, QString note);

    // getter
    QDateTime getTime()     const { return m_time; }
    int       getType()     const { return m_type; }
    QString   getCategory() const { return m_category; }
    double    getAmount()   const { return m_amount; }
    QString   getNote()     const { return m_note; }

    // setter（如需在外部修改）
    void setTime    (const QDateTime &t)  { m_time    = t;  }
    void setType    (int t)               { m_type    = t;  }
    void setCategory(const QString &c)    { m_category= c;  }
    void setAmount  (double a)            { m_amount  = a;  }
    void setNote    (const QString &n)    { m_note    = n;  }

    // 便于调试/日志
    QString toString() const
    {
        return QString("%1,%2,%3,%4,%5")
                .arg(m_time.toString(Qt::ISODate))
                .arg(m_type)
                .arg(m_category)
                .arg(m_amount, 0, 'f', 2)
                .arg(m_note);
    }

private:
    QDateTime m_time;
    int       m_type;       // 0收入 1支出
    QString   m_category;   // 工资/红包/其他/衣/食/住/行
    double    m_amount;
    QString   m_note;
};

#endif // RECORD_H
