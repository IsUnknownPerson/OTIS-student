#include "filepathsource.h"
#include "ui_filepathsource.h"

FilePathSource::FilePathSource(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePathSource)
{
    ui->setupUi(this);
}

FilePathSource::~FilePathSource()
{
    delete ui;
}

QStringList FilePathSource::getFilePaths() const
{
    QStringList result;

    for(int row = 0; row < ui->filePathsSource->count(); row++)
    {
        auto item = ui->filePathsSource->item(row);
        if(item)
            result.append(item->text());
    }
    return result;
}

void FilePathSource::setFilePaths(const QStringList &paths)
{
    ui->filePathsSource->clear();
    for(auto path : paths)
        ui->filePathsSource->addItem(path);
}

void FilePathSource::setFilePaths(const QString &paths)
{
    setFilePaths(paths.split(';'));
}
