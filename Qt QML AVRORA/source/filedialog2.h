#ifndef FILEDIALOG2_H
#define FILEDIALOG2_H

#include <QDialog>

namespace Ui {
class FileDialog2;
}

class FileDialog2 : public QDialog
{
    Q_OBJECT

public:
    explicit FileDialog2(QWidget *parent = nullptr);
    virtual ~FileDialog2();

private Q_SLOTS:
    void onBrowseRequest();

private:
    Ui::FileDialog2 *ui;
};

#endif // FILEDIALOG2_H
