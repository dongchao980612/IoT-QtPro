#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QStandardItemModel>

#include "record.h"
#include "statsdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_reflash_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::MainWindow *ui;


    QVector<Record> m_data;
     QStandardItemModel *model;   // 表格模型

    // 辅助函数
    void load();
    void save();
    void refreshModel();
    // MainWindow.h 里增加
    QList<QStandardItem*> createRowItems(const Record &r, bool withCheck = true);
    bool matches(const Record &r, const QString &k);

    const QColor incomeColor = QColor(220, 255, 220);   // 浅绿
    const QColor spendColor  = QColor(255, 220, 220);   // 浅红

};

static QString dbPath();
#endif // MAINWINDOW_H
