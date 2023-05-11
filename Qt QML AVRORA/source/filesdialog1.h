#ifndef FILESDIALOG1_H
#define FILESDIALOG1_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class FilesDialog1; }
QT_END_NAMESPACE

class FilesDialog1 : public QDialog
{
    Q_OBJECT

public:
    FilesDialog1(QWidget *parent = nullptr);
    virtual ~FilesDialog1();

private Q_SLOTS:
    void onBrowseRequest();

private:
    Ui::FilesDialog1 *ui;
};
#endif // FILESDIALOG1_H
