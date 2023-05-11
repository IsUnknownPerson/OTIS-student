#ifndef FILESDIALOG3_H
#define FILESDIALOG3_H

#include <QDialog>

namespace Ui {
class FilesDialog3;
}

class FilesDialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit FilesDialog3(QWidget *parent = nullptr);
    virtual ~FilesDialog3();

private Q_SLOTS:
    void onBrowseRequest();

private:
    Ui::FilesDialog3 *ui;
};

#endif // FILESDIALOG3_H
