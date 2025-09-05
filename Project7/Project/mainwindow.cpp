#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->SetStyle(":/qss/blue.css");     //设置样式表
    this->setWindowTitle("BLE蓝牙调试助手"); //设置标题
    this->setWindowIcon(QIcon(":/wbyq.ico")); //设置图标

    /*1. 实例化蓝牙相关的对象*/
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();

    /*2. 关联蓝牙设备相关的信号*/
    /*2.1 关联发现设备的槽函数，当扫描发现周围的蓝牙设备时，会发出deviceDiscovered信号*/
    connect(discoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&MainWindow::addBlueToothDevicesToList);
//            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
//            this,
//            SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
//            );

    /*3. 检查蓝牙的状态，用于设置按钮的初始状态*/
    /*3.1 检查蓝牙是否开启*/
    qDebug()<<"当前蓝牙状态模式为："<<localDevice->hostMode();
    if(localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff)
    {
            //如果蓝牙处于关闭状态
            ui->pushButton_OpenBluetooth->setEnabled(true);   //打开按钮
            ui->pushButton_CloseBluetooth->setEnabled(false); //关闭按钮

    }
    else    //如果蓝牙处于开启状态
    {
            ui->pushButton_OpenBluetooth->setEnabled(false);//打开按钮
            ui->pushButton_CloseBluetooth->setEnabled(true);//关闭按钮
            ui->pushButton_BluetoothScan->setEnabled(true); //设置扫描按钮可用
    }

    /*3.2 设置标签显示本地蓝牙的名称*/
    QString name_info("本机蓝牙:");
    name_info+=localDevice->name();
    ui->label_BluetoothName->setText(name_info);

     ui->pushButton_StopScan->setEnabled(false);      //设置停止扫描蓝牙的按钮不可用
     ui->plainTextEdit_BluetoothInfiShow->setEnabled(false); //设置不可编辑

     m_control=NULL; //初始值
     m_service=NULL;  //初始值
     SendModeSelect=0;
     SendMaxMode=0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete discoveryAgent;
    delete localDevice;
}




void MainWindow::on_pushButton_OpenBluetooth_clicked()
{
    /*请求打开蓝牙设备*/
    localDevice->powerOn();
    ui->pushButton_OpenBluetooth->setEnabled(false);//打开按钮
    ui->pushButton_CloseBluetooth->setEnabled(true);//关闭按钮
    ui->pushButton_BluetoothScan->setEnabled(true); //设置扫描按钮可用

}

void MainWindow::on_pushButton_CloseBluetooth_clicked()
{
    /*关闭蓝牙设备*/
    localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    ui->pushButton_OpenBluetooth->setEnabled(true);//打开按钮
    ui->pushButton_CloseBluetooth->setEnabled(false);//关闭按钮
    ui->pushButton_BluetoothScan->setEnabled(false); //设置扫描按钮不可用
}


void MainWindow::on_pushButton_BluetoothScan_clicked()
{
    qDebug()<<"开始扫描周围的蓝牙设备...\n";
     /*开始扫描周围的蓝牙设备*/
    discoveryAgent->start();
    ui->comboBox_BluetoothDevice->clear(); //清除条目
    ui->pushButton_BluetoothScan->setEnabled(false); //设置扫描按钮不可用
    ui->pushButton_StopScan->setEnabled(true);     //设置停止扫描按钮可用
}

void MainWindow::on_pushButton_StopScan_clicked()
{
    /*停止扫描周围的蓝牙设备*/
    discoveryAgent->stop();
    ui->pushButton_StopScan->setEnabled(false);     //设置停止扫描按钮不可用
    ui->pushButton_BluetoothScan->setEnabled(true); //设置扫描按钮可用
}


/*当扫描到周围的设备时会调用当前的槽函数*/
void MainWindow::addBlueToothDevicesToList(const QBluetoothDeviceInfo &info)
{

   // QString label = QString("%1 %2").arg(info.name()).arg(info.address().toString());

    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
         qDebug()<<"当扫描到周围的设备:"+label<<"\n";
    ui->comboBox_BluetoothDevice->addItem(label); //添加字符串到comboBox上
}


/*
在说蓝牙设备连接之前，不得不提一个非常重要的概念，就是蓝牙的Uuid，引用一下百度的：
在蓝牙中，每个服务和服务属性都唯一地由"全球唯一标识符" （UUID）来校验。
正如它的名字所暗示的，每一个这样的标识符都要在时空上保证唯一。
UUID类可表现为短整形（16或32位）和长整形（128位）UUID。
他提供了分别利用String和16位或32位数值来创建类的构造函数，提供了一个可以比较两个UUID（如果两个都是128位）的方法，还有一个可以转换一个UUID为一个字符串的方法。
UUID实例是不可改变的（immutable），只有被UUID标示的服务可以被发现。
在Linux下你用一个命令uuidgen -t可以生成一个UUID值；
在Windows下则执行命令uuidgen 。UUID看起来就像如下的这个形式：2d266186-01fb-47c2-8d9f-10b8ec891363。当使用生成的UUID去创建一个UUID对象，你可以去掉连字符。
*/




//清空收到的数据
void MainWindow::on_pushButton_Clear_clicked()
{
    ui->plainTextEdit_BluetoothInfiShow->setPlainText("");
}

//连接蓝牙
void MainWindow::on_pushButton_ConnectDev_clicked()
{
    QString text = ui->comboBox_BluetoothDevice->currentText();
    int index = text.indexOf(' ');
    if(index == -1)
        return;

    QBluetoothAddress address(text.left(index));

    QString connect_device="开始连接蓝牙设备:\n";
    connect_device+=ui->comboBox_BluetoothDevice->currentText();
    QMessageBox::information(this,tr("连接提示"),connect_device);

    /*低功耗蓝牙设备*/
//    if(m_control!=NULL)
//    {
//        qDebug()<<"不是低功耗蓝牙设备\n";
//        m_control->disconnectFromDevice(); //断开远程设备
//        delete m_control;
//        m_control = NULL;
//    }

    ui->comboBox_UUID->clear();         //清除显示UUID服务的列表框
    QList<QBluetoothDeviceInfo> info_list=discoveryAgent->discoveredDevices(); //得到扫描的所有设备信息
    for(int i=0;i<info_list.count();i++)
    {
        if(info_list.at(i).address().toString()==text.left(index))
        {
             remoteDevice=info_list.at(i);
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("连接设备:");
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText(remoteDevice.name());
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("\n");
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText(remoteDevice.address().toString());
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("\n");
            break;
        }
   }

    //创建中央角色设备
    m_control = new QLowEnergyController(remoteDevice, this);
    //m_control=QLowEnergyController::createCentral(remoteDevice,this);
    if(m_control==0)
    {
        ui->plainTextEdit_BluetoothInfiShow->insertPlainText("创建中央角色设备失败!\n");
    }
    else
    {
        ui->plainTextEdit_BluetoothInfiShow->insertPlainText("创建中央角色设备成功!\n");
    }
    //每次发现新的服务就会发送此信号
    connect(m_control, SIGNAL(serviceDiscovered(QBluetoothUuid)),this, SLOT(BlueServiceDiscovered(QBluetoothUuid)));

    //正在运行的服务发现完成时发出此信号。
    connect(m_control, SIGNAL(discoveryFinished()),this, SLOT(BlueServiceScanDone()));

    //当控制器成功连接到远程Low Energy设备时，会发出此信号。
     connect(m_control, SIGNAL(connected()),this, SLOT(BlueDeviceConnected()));

    //当控制器从远程低功耗设备断开时发出此信号。
     connect(m_control, SIGNAL(disconnected()),this, SLOT(BlueDeviceDisconnected()));

     //该信号在发生错误时发出。
     connect(m_control, static_cast<void(QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
           [=](QLowEnergyController::Error error){

         if(error==QLowEnergyController::NoError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("没有发生错误\n");
         }
         else if(error==QLowEnergyController::UnknownError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("出现未知错误。\n");
         }
          else if(error==QLowEnergyController::UnknownRemoteDeviceError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("无法找到传递给此类构造函数的远程Bluetooth Low Energy设备。\n");
         }

         else if(error==QLowEnergyController::NetworkError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("尝试读取或写入远程设备失败\n");
         }

          else if(error==QLowEnergyController::InvalidBluetoothAdapterError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("传递给此类构造函数的本地蓝牙设备无法找到，或者没有本地蓝牙设备\n");
         }

          else if(error==QLowEnergyController::InvalidBluetoothAdapterError)
         {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("尝试连接到远程设备失败。\n");
         }
         else
          ui->plainTextEdit_BluetoothInfiShow->insertPlainText("*****未知错误!******\n");
     });

     //连接到远程蓝牙低功耗设备。
      m_control->connectToDevice();
}



//每次发现新的服务，就会调用该槽函数
void MainWindow::BlueServiceDiscovered(const QBluetoothUuid &gatt)
{
     ui->comboBox_UUID->addItem(gatt.toString()); //添加字符串到comboBox上
     ui->plainTextEdit_BluetoothInfiShow->insertPlainText("\n");
     ui->plainTextEdit_BluetoothInfiShow->insertPlainText(gatt.toString());
}


//帮助提示
void MainWindow::on_pushButton_help_clicked()
{
    QMessageBox::information(this,tr("帮助提示"),"MEI YOU BANGZHU ");
}


//默认指定UUID服务
static const QLatin1String serviceUuid("{0003CDD0-0000-1000-8000-00805F9B0131}");
//static const QLatin1String serviceUuid("{00001101-0000-1000-8000-00805F9B34FB}");

//正在运行的服务发现完成时发出此信号。
void MainWindow::BlueServiceScanDone()
{

    /*判断之前有没有连接过*/
    if(m_service!=NULL)
    {
        delete m_service;
        m_service=NULL;
    }

    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("\n选中的服务:");
    ui->plainTextEdit_BluetoothInfiShow->insertPlainText(serviceUuid);
    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("\n");

    /*与设备之间建立服务*/
    m_service=m_control->createServiceObject(QBluetoothUuid(serviceUuid),this);

    if(m_service==NULL)
    {
        ui->plainTextEdit_BluetoothInfiShow->insertPlainText("服务建立失败!\n");
        ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        return;
    }
    else
    {
        ui->plainTextEdit_BluetoothInfiShow->insertPlainText("服务建立成功!\n");
        ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
    }
    /*服务状态改变时发出此信号。newState也可以通过state（）。*/
    connect(m_service, SIGNAL(stateChanged(QLowEnergyService::ServiceState)),
                this, SLOT(BleServiceServiceStateChanged(QLowEnergyService::ServiceState)));

    /*特性值由事件改变时发出此信号在外设上。 newValue参数包含更新后的值特性*/
    connect(m_service, SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
                this, SLOT(BleServiceCharacteristicChanged(QLowEnergyCharacteristic,QByteArray)));

    /*当特征读取请求成功返回其值时，发出此信号。*/
     connect(m_service, SIGNAL(characteristicRead(QLowEnergyCharacteristic,QByteArray)),
                this, SLOT(BleServiceCharacteristicRead(QLowEnergyCharacteristic,QByteArray)));

    /*当特性值成功更改为newValue时，会发出此信号。*/
    connect(m_service, SIGNAL(characteristicWritten(QLowEnergyCharacteristic,QByteArray)),
                this, SLOT(BleServiceCharacteristicWrite(QLowEnergyCharacteristic,QByteArray)));

    /*错误信号*/
    connect(m_service, static_cast<void(QLowEnergyService::*)(QLowEnergyService::ServiceError)>(&QLowEnergyService::error),
         [=](QLowEnergyService::ServiceError newErrorr)
    {
        if(QLowEnergyService::NoError == newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("没有发生错误。\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::OperationError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("错误: 当服务没有准备好时尝试进行操作!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::CharacteristicReadError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("尝试读取特征值失败!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::CharacteristicWriteError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("尝试为特性写入新值失败!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::DescriptorReadError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("尝试读取描述符值失败!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::DescriptorWriteError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText(" 尝试向描述符写入新值失败!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
        if(QLowEnergyService::UnknownError==newErrorr)
        {
             ui->plainTextEdit_BluetoothInfiShow->insertPlainText("与服务交互时发生未知错误!\n");
             ui->plainTextEdit_BluetoothInfiShow->ensureCursorVisible();
        }
    });

    if(m_service->state() == QLowEnergyService::DiscoveryRequired)
    {
        m_service->discoverDetails(); //启动服务发现扫描
    }
    else
        searchCharacteristic();
}


//搜索特性
void MainWindow::searchCharacteristic()
{
    if(m_service)
    {
        QList<QLowEnergyCharacteristic> list=m_service->characteristics();
        qDebug()<<"list.count()="<<list.count();
        //characteristics 获取详细特性

        SendMaxMode=list.count();  //设置模式选择上限
        for(int i=0;i<list.count();i++)
        {
            QLowEnergyCharacteristic c=list.at(i);

            /*如果QLowEnergyCharacteristic对象有效，则返回true，否则返回false*/
            if(c.isValid())
            {
//                返回特征的属性。
//                这些属性定义了特征的访问权限。
               if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse || c.properties() & QLowEnergyCharacteristic::Write)
               // if(c.properties() & QLowEnergyCharacteristic::Write)
                {
                    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("具有写权限!\n");
                    m_writeCharacteristic[i] = c;  //保存写权限特性
                    if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse)
//                        如果使用此模式写入特性，则远程外设不应发送写入确认。
//                        无法确定操作的成功，并且有效负载不得超过20个字节。
//                        一个特性必须设置QLowEnergyCharacteristic :: WriteNoResponse属性来支持这种写模式。
//                         它的优点是更快的写入操作，因为它可能发生在其他设备交互之间。
                        m_writeMode = QLowEnergyService::WriteWithoutResponse;
                    else
                        m_writeMode = QLowEnergyService::WriteWithResponse;
                    //如果使用此模式写入特性，则外设应发送写入确认。
                    //如果操作成功，则通过characteristicWritten（）信号发出确认。
                    //否则，发出CharacteristicWriteError。
                    //一个特性必须设置QLowEnergyCharacteristic :: Write属性来支持这种写模式。

                }
                if(c.properties() & QLowEnergyCharacteristic::Read)
                {
                    m_readCharacteristic = c; //保存读权限特性
                }

                //描述符定义特征如何由特定客户端配置。
                m_notificationDesc = c.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);

                //值为真
                if(m_notificationDesc.isValid())
                {
                    //写描述符
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                  //   m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("FEE1"));
                    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("写描述符!\n");
                }
            }
        }
    }
}


//当控制器成功连接到远程Low Energy设备时，会发出此信号。
void MainWindow::BlueDeviceConnected()
{
    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("成功连接设备!\n");

    //启动发现服务Services
    m_control->discoverServices();


}


//当控制器从远程低功耗设备断开时发出此信号。
void MainWindow::BlueDeviceDisconnected()
{
    ui->plainTextEdit_BluetoothInfiShow->insertPlainText("成功断开!\n");
}

//当前选中的服务
void MainWindow::on_comboBox_UUID_currentIndexChanged(const QString &arg1)
{

}

//服务状态改变时发出此信号
void MainWindow::BleServiceServiceStateChanged(QLowEnergyService::ServiceState s)
{
    //ui->plainTextEdit_BluetoothInfiShow->insertPlainText("服务状态改变时发出此信号!\n");
    if(s == QLowEnergyService::ServiceDiscovered)  //所有细节都已同步
    {
        ui->plainTextEdit_BluetoothInfiShow->insertPlainText("所有细节都已发现!\n");
        searchCharacteristic();
    }
}

//读取到数据
void MainWindow::BleServiceCharacteristicChanged(const QLowEnergyCharacteristic &c,
                                                 const QByteArray &value)
{
   // ui->plainTextEdit_BluetoothInfiShow->insertPlainText("特性值由事件改变时发出此信号在外设上!\n");
    ui->plainTextEdit_BluetoothInfiShow->insertPlainText(QString(value));
    //移动滚动条到底部
    QScrollBar *scrollbar = ui->plainTextEdit_BluetoothInfiShow->verticalScrollBar();
    if(scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}
/*
void MainWindow::BleServiceCharacteristicRead(const QLowEnergyCharacteristic &c,
                                              const QByteArray &value)
{
   ui->plainTextEdit_BluetoothInfiShow->insertPlainText("当特征读取请求成功返回其值时\n");
   ui->plainTextEdit_BluetoothInfiShow->insertPlainText(QString(value));
}
*/
/*
void MainWindow::BleServiceCharacteristicWrite(const QLowEnergyCharacteristic &c,
                                               const QByteArray &value)
{
    //ui->plainTextEdit_BluetoothInfiShow->insertPlainText("当特性值成功更改为newValue时!\n");

         ui->plainTextEdit_BluetoothInfiShow->insertPlainText(QString(value));
}
*/
//发送数据
void MainWindow::on_pushButton_SendData_clicked()
{
    QString text=ui->lineEdit_SendData->text();
    QByteArray array=text.toLocal8Bit();
    /*写入newValue作为特性的值。
     如果操作成功，将发射characteristicWritten（）信号;
    低功耗设备: 每次最多写20个字节
    */
      SendModeSelect=1;
      m_service->writeCharacteristic(m_writeCharacteristic[SendModeSelect],array, m_writeMode);
}

//发送模式
void MainWindow::on_pushButton_SendMode_clicked()
{
    bool ok;
    int data = QInputDialog::getInt(this, tr("获取输入模式"),tr("选择模式:"), 0, 0,SendMaxMode,1, &ok);
    if(ok)
    {
        SendModeSelect=data;
    }
}
