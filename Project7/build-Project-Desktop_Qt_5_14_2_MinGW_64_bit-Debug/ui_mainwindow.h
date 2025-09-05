/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_OpenBluetooth;
    QPushButton *pushButton_CloseBluetooth;
    QLabel *label_BluetoothName;
    QPushButton *pushButton_StopScan;
    QPushButton *pushButton_BluetoothScan;
    QComboBox *comboBox_BluetoothDevice;
    QPlainTextEdit *plainTextEdit_BluetoothInfiShow;
    QComboBox *comboBox_UUID;
    QLineEdit *lineEdit_SendData;
    QPushButton *pushButton_ConnectDev;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_OpenBluetooth = new QPushButton(centralwidget);
        pushButton_OpenBluetooth->setObjectName(QString::fromUtf8("pushButton_OpenBluetooth"));
        pushButton_OpenBluetooth->setGeometry(QRect(520, 110, 112, 34));
        pushButton_CloseBluetooth = new QPushButton(centralwidget);
        pushButton_CloseBluetooth->setObjectName(QString::fromUtf8("pushButton_CloseBluetooth"));
        pushButton_CloseBluetooth->setGeometry(QRect(660, 110, 112, 34));
        label_BluetoothName = new QLabel(centralwidget);
        label_BluetoothName->setObjectName(QString::fromUtf8("label_BluetoothName"));
        label_BluetoothName->setGeometry(QRect(320, 260, 391, 161));
        pushButton_StopScan = new QPushButton(centralwidget);
        pushButton_StopScan->setObjectName(QString::fromUtf8("pushButton_StopScan"));
        pushButton_StopScan->setGeometry(QRect(690, 40, 112, 34));
        pushButton_BluetoothScan = new QPushButton(centralwidget);
        pushButton_BluetoothScan->setObjectName(QString::fromUtf8("pushButton_BluetoothScan"));
        pushButton_BluetoothScan->setGeometry(QRect(510, 40, 112, 34));
        comboBox_BluetoothDevice = new QComboBox(centralwidget);
        comboBox_BluetoothDevice->setObjectName(QString::fromUtf8("comboBox_BluetoothDevice"));
        comboBox_BluetoothDevice->setGeometry(QRect(30, 30, 451, 24));
        plainTextEdit_BluetoothInfiShow = new QPlainTextEdit(centralwidget);
        plainTextEdit_BluetoothInfiShow->setObjectName(QString::fromUtf8("plainTextEdit_BluetoothInfiShow"));
        plainTextEdit_BluetoothInfiShow->setGeometry(QRect(110, 280, 107, 107));
        comboBox_UUID = new QComboBox(centralwidget);
        comboBox_UUID->setObjectName(QString::fromUtf8("comboBox_UUID"));
        comboBox_UUID->setGeometry(QRect(50, 100, 451, 24));
        lineEdit_SendData = new QLineEdit(centralwidget);
        lineEdit_SendData->setObjectName(QString::fromUtf8("lineEdit_SendData"));
        lineEdit_SendData->setGeometry(QRect(340, 450, 113, 25));
        pushButton_ConnectDev = new QPushButton(centralwidget);
        pushButton_ConnectDev->setObjectName(QString::fromUtf8("pushButton_ConnectDev"));
        pushButton_ConnectDev->setGeometry(QRect(570, 200, 112, 34));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_OpenBluetooth->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\350\223\235\347\211\231", nullptr));
        pushButton_CloseBluetooth->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\350\223\235\347\211\231", nullptr));
        label_BluetoothName->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_StopScan->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\346\211\253\346\217\217", nullptr));
        pushButton_BluetoothScan->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\211\253\346\217\217", nullptr));
        pushButton_ConnectDev->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\223\235\347\211\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
