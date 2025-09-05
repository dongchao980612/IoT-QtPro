/********************************************************************************
** Form generated from reading UI file 'statsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATSDIALOG_H
#define UI_STATSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_StatsDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *labelResult;

    void setupUi(QDialog *StatsDialog)
    {
        if (StatsDialog->objectName().isEmpty())
            StatsDialog->setObjectName(QString::fromUtf8("StatsDialog"));
        StatsDialog->resize(400, 300);
        horizontalLayout = new QHBoxLayout(StatsDialog);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelResult = new QLabel(StatsDialog);
        labelResult->setObjectName(QString::fromUtf8("labelResult"));
        labelResult->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelResult);


        retranslateUi(StatsDialog);

        QMetaObject::connectSlotsByName(StatsDialog);
    } // setupUi

    void retranslateUi(QDialog *StatsDialog)
    {
        StatsDialog->setWindowTitle(QCoreApplication::translate("StatsDialog", "Dialog", nullptr));
        labelResult->setText(QCoreApplication::translate("StatsDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatsDialog: public Ui_StatsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATSDIALOG_H
