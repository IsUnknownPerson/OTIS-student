#include "filesdialog1.h"
#include "ui_filesdialog1.h"

#include <QDebug>

FilesDialog1::FilesDialog1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FilesDialog1)
{
    ui->setupUi(this);
    connect(ui->browse, &QAbstractButton::clicked, this, &FilesDialog1::onBrowseRequest);
}

FilesDialog1::~FilesDialog1()
{
    delete ui;
}

void FilesDialog1::onBrowseRequest()
{
    QStringList filePaths = ui->filePathsSource->text().split(';');
    qDebug()<<"FilesDialog1::onBrowseRequest(): "<<filePaths;
}
