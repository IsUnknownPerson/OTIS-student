
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionInstruction_triggered(){
    QMessageBox::information(this, "Instruction", "1. Open file\n 2. Choose thread pattern\n 3. Click Start");
}


void MainWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open A File", "../threads");

    QFile file(fileName);
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
            return;
    data = file.readAll();
    ui->textBrowserInput->setText(data);

    char b[] = "File_name";

    char **test = (char **)malloc(sizeof(char *) * 3);
    test[1] = data.data();
    test[0] = b;
    test[2] = NULL;

    /*
    char *str = (char *)malloc(sizeof(char) * (len + 1));
    int i =0;
    char *temp = *test;
    while (temp)
    {
        temp = test[i];
        if (!temp)
            break;
        free(temp);
        ++i;
    }
*/
    pTopk_words = new topk_words(3, test);
   free(test);
}

