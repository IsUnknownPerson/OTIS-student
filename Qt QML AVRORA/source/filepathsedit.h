#ifndef FILEPATHSEDIT_H
#define FILEPATHSEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QWidget>

class FilePathsEdit : public QLineEdit
{
    Q_OBJECT
    Q_PROPERTY(QString filePaths READ text WRITE setText);

public:
    FilePathsEdit(QWidget* parent = nullptr)
        :QLineEdit(parent)
    {}
};

#endif // FILEPATHSEDIT_H
