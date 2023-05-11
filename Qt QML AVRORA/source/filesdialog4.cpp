#include "filesdialog4.h"
#include "ui_filesdialog4.h"

#include <QQmlContext>

FilesDialog4::FilesDialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilesDialog4)
{
    ui->setupUi(this);
    auto qmlContext = ui->quickWidget->rootContext();
    auto qmlEngine  = ui->quickWidget->engine();
    ui->quickWidget->setSource(QUrl("qrc:/qmlfiledialog.qml"));
}

FilesDialog4::~FilesDialog4()
{
    delete ui;
}
