#include "filedialog2.h"
#include "ui_filedialog2.h"

#include <QDebug>

FileDialog2::FileDialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDialog2)
{
    ui->setupUi(this);
    connect(ui->browse, &QAbstractButton::clicked, this, &FileDialog2::onBrowseRequest);
}

FileDialog2::~FileDialog2()
{
    delete ui;
}

void FileDialog2::onBrowseRequest()
{
    QStringList filePaths = ui->filePathsSource->property("filePaths").toStringList();
    qDebug()<<filePaths;
}
