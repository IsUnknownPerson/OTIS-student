#pragma once

#include "topk_words.h"
#include <QMainWindow>
#include <QFileDialog>

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
    void on_actionInstruction_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    topk_words *pTopk_words;
};
