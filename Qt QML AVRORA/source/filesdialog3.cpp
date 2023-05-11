#include "filesdialog3.h"
#include "ui_filesdialog3.h"

#include <QDebug>

FilesDialog3::FilesDialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilesDialog3)
{
    ui->setupUi(this);
    connect(ui->browse, SIGNAL(clicked()), this, SLOT(onBrowseRequest()));
}

FilesDialog3::~FilesDialog3()
{
    delete ui;
}

void FilesDialog3::onBrowseRequest()
{
    QStringList filePaths = ui->filePathsSource->property("filePaths").toStringList();
    qDebug()<<filePaths;
}
