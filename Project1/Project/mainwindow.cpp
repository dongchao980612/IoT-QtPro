#include "mainwindow.h"
#include "ui_mainwindow.h"


static QString dbPath()
{
    return QCoreApplication::applicationDirPath() + "/finance.txt";
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("个人财务管理软件");

    setFixedSize(1200, 600);

    // 创建模型
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);

    ui->tableView->verticalHeader()->setVisible(false);      // 去掉行号
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->resizeColumnsToContents();                // 首次自适应
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许双击编辑


    // 设置列标题
     model->setHorizontalHeaderLabels({"","时间","收支","类别","金额","备注"});

    load();          // 把文件读进 m_data
    refreshModel();  // 显示到表格


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_search_clicked()
{
    QString key = ui->lineEdit_input->text().trimmed();
    model->clear();
    model->setHorizontalHeaderLabels({"","时间","收支","类别","金额","备注"});

    for (const Record &r : m_data)
    {
        if (key.isEmpty() || matches(r, key))
            model->appendRow(createRowItems(r));
    }
    ui->tableView->resizeColumnToContents(0);
}


void MainWindow::on_pushButton_add_clicked()
{
    // 添加数据
}

void MainWindow::on_pushButton_delete_clicked()
{
    // 删除数据
}

void MainWindow::on_pushButton_update_clicked()
{
    // 更新数据
}

void MainWindow::on_pushButton_reflash_clicked()
{
    // 1. 总收支
    double totalIn = 0, totalOut = 0;
    for (const Record &r : m_data)
        (r.getType() == 0 ? totalIn : totalOut) += r.getAmount();
    double balance = totalIn - totalOut;

    // 2. 分类别统计
    const QStringList inCats  = {"工资","红包","其他"};
    const QStringList outCats = {"衣","食","住","行"};
    QMap<QString,double> inMap, outMap;

    for (const Record &r : m_data)
        if (r.getType() == 0)
            inMap[r.getCategory()] += r.getAmount();
        else
            outMap[r.getCategory()] += r.getAmount();

    // 3. 拼 HTML
    QString html;
    html += QString("<h3>总览</h3>"
                    "<p><b>总收入：</b><span style='color:green'>¥ %1</span></p>"
                    "<p><b>总支出：</b><span style='color:red'>¥ %2</span></p>"
                    "<p><b>净结余：</b><span style='color:blue'>¥ %3</span></p><hr>")
            .arg(totalIn,0,'f',2)
            .arg(totalOut,0,'f',2)
            .arg(balance,0,'f',2);

    // 收入类别
    html += "<h3>收入类别</h3><table width='100%' border='1' cellspacing='0'>"
            "<tr><th>类别</th><th>金额</th><th>占比</th></tr>";
    for (const QString &cat : inCats)
    {
        double v = inMap.value(cat,0);
        double p = (totalIn>0)? v/totalIn*100 : 0;
        html += QString("<tr><td>%1</td><td>¥ %2</td><td>%3%</td></tr>")
                .arg(cat).arg(v,0,'f',2).arg(p,0,'f',1);
    }
    html += "</table>";

    // 支出类别
    html += "<h3>支出类别</h3><table width='100%' border='1' cellspacing='0'>"
            "<tr><th>类别</th><th>金额</th><th>占比</th></tr>";
    for (const QString &cat : outCats)
    {
        double v = outMap.value(cat,0);
        double p = (totalOut>0)? v/totalOut*100 : 0;
        html += QString("<tr><td>%1</td><td>¥ %2</td><td>%3%</td></tr>")
                .arg(cat).arg(v,0,'f',2).arg(p,0,'f',1);
    }
    html += "</table>";

    StatsDialog dlg(html, this);
    dlg.exec();
}

void MainWindow::on_pushButton_exit_clicked()
{
    this->close();
}

// 写：保存 QVector<Record> m_data
void MainWindow::save()
{
    QFile f(dbPath());
    if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream ts(&f);
        ts.setCodec("UTF-8");
        for (const Record &r : m_data) {
            ts << r.getTime().toString(Qt::ISODate) << ','
               << r.getType() << ',' << r.getCategory() << ','
               <<QString::number(r.getAmount(), 'f', 2) << ',' << r.getNote() << '\n';
        }

         qDebug() << "finance.txt saved to:" << QDir::currentPath(); // 打印路径
    }
    else
      {
          qDebug() << "save failed:" << f.errorString();
      }
}

void MainWindow::refreshModel()
{



    model->clear();
    model->setHorizontalHeaderLabels({"","时间","收支","类别","金额","备注"});
    for (const Record &r : m_data) {
        model->appendRow(createRowItems(r));

    }
}


QList<QStandardItem*> MainWindow::createRowItems(const Record &r, bool withCheck)
{
    QList<QStandardItem*> row;
    if (withCheck) {
        auto *check = new QStandardItem();
        check->setCheckable(true);
        check->setCheckState(Qt::Unchecked);
        row << check;
    }
    row << new QStandardItem(r.getTime().toString("yyyy-MM-dd hh:mm"))
        << new QStandardItem(r.getType() == 0 ? "收入" : "支出")
        << new QStandardItem(r.getCategory())
        << new QStandardItem(QString::number(r.getAmount(), 'f', 2))
        << new QStandardItem(r.getNote());

    const QColor bg = (r.getType() == 0) ? incomeColor : spendColor;
    for (auto *it : row) it->setBackground(bg);

    return row;
}


// 读
void MainWindow::load()
{
    m_data.clear();
    QFile f(dbPath());
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&f);
        ts.setCodec("UTF-8");
        while (!ts.atEnd()) {
            QStringList l = ts.readLine().split(',');
            if (l.size() != 5) continue;
            Record r;
            r.setTime(QDateTime::fromString(l[0], Qt::ISODate));
            r.setType(l[1].toInt());
            r.setCategory(l[2]);
            r.setAmount(l[3].toDouble());
            r.setNote(l[4]);
            r.toString();
            m_data.append(r);
        }
    }
}


bool MainWindow::matches(const Record &r, const QString &k)
{
    return r.getTime().toString("yyyy-MM-dd hh:mm").contains(k, Qt::CaseInsensitive) ||
           QString(r.getType() == 0 ? "收入" : "支出").contains(k, Qt::CaseInsensitive) ||
           r.getCategory().contains(k, Qt::CaseInsensitive) ||
           QString::number(r.getAmount(), 'f', 2).contains(k, Qt::CaseInsensitive) ||
           r.getNote().contains(k, Qt::CaseInsensitive);
}


