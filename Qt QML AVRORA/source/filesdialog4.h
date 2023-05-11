#ifndef FILESDIALOG4_H
#define FILESDIALOG4_H

#include <QDialog>

namespace Ui {
class FilesDialog4;
}

class FilesDialog4 : public QDialog
{
    Q_OBJECT

public:
    explicit FilesDialog4(QWidget *parent = nullptr);
    ~FilesDialog4();

private:
    Ui::FilesDialog4 *ui;
};

#endif // FILESDIALOG4_H
