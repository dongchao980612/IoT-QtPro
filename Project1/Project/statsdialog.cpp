#include "StatsDialog.h"
#include "ui_StatsDialog.h"

StatsDialog::StatsDialog(const QString &html, QWidget *parent)
    : QDialog(parent), ui(new Ui::StatsDialog)
{
    ui->setupUi(this);
    ui->labelResult->setTextFormat(Qt::RichText);
    ui->labelResult->setText(html);
    setWindowTitle("收支统计");
    resize(300, 200);
}

StatsDialog::~StatsDialog() { delete ui; }
