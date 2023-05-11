#ifndef FILEPATHSOURCE_H
#define FILEPATHSOURCE_H

#include <QWidget>

namespace Ui {
class FilePathSource;
}

class FilePathSource : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QStringList filePaths READ getFilePaths WRITE setFilePaths);

public:
    explicit FilePathSource(QWidget *parent = nullptr);
    ~FilePathSource();

    QStringList getFilePaths() const;
    void setFilePaths(const QStringList& paths);
    void setFilePaths(const QString& paths);

private:
    Ui::FilePathSource *ui;
};

#endif // FILEPATHSOURCE_H
