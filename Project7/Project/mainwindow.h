#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>

#include <QBluetoothLocalDevice>

#include <QBluetoothSocket>

#include "QListWidgetItem"

#include <QMessageBox>

#include <QBluetoothUuid>

#include <QLowEnergyController>

#include <QBluetoothUuid>

#include <QLowEnergyService>

#include <QScrollBar>

#include <QInputDialog>

#include <QListWidgetItem>

#include <QScroller>

#include <QDebug>
#include <QFile>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;  //这个是指扫描周围蓝牙设备！

    QBluetoothLocalDevice *localDevice; //是指配置获取设备的蓝牙状态信息等！

    QLowEnergyController *m_control;

    QLowEnergyService *m_service;

    QBluetoothDeviceInfo remoteDevice;

    QLowEnergyCharacteristic m_readCharacteristic; //读特性

    QLowEnergyCharacteristic m_writeCharacteristic[5]; //写特性

    QLowEnergyService::WriteMode m_writeMode;

    QLowEnergyDescriptor m_notificationDesc;
    QTimer *my_timer;

    int SendMaxMode; //发送模式

    int SendModeSelect;//选择发送模式


private:
    Ui::MainWindow *ui;
private slots:

    //void SetStyle(const QString &qssFile);
    void on_pushButton_OpenBluetooth_clicked();
    void on_pushButton_CloseBluetooth_clicked();

    void on_pushButton_StopScan_clicked();
    void on_pushButton_BluetoothScan_clicked();

    void addBlueToothDevicesToList(const QBluetoothDeviceInfo &info);
    void on_pushButton_SendData_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_ConnectDev_clicked();
    void BlueServiceDiscovered(const QBluetoothUuid &gatt);
    void on_pushButton_help_clicked();
    void BlueServiceScanDone();
    void searchCharacteristic();
    void BlueDeviceConnected();
    void BlueDeviceDisconnected();
    void on_comboBox_UUID_currentIndexChanged(const QString &arg1);
    void BleServiceServiceStateChanged(QLowEnergyService::ServiceState s);
    void BleServiceCharacteristicChanged(const QLowEnergyCharacteristic &c,
                                         const QByteArray &value);
    //void BleServiceCharacteristicRead(const QLowEnergyCharacteristic &c,
   //                                   const QByteArray &value);
   // void BleServiceCharacteristicWrite(const QLowEnergyCharacteristic &c,
    //                                   const QByteArray &value);
    void on_pushButton_SendMode_clicked();
};
#endif // MAINWINDOW_H
