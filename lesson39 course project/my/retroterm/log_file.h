#pragma once

#include <QFile>
#include <QMap>
#include <QObject>

class log_file : public QObject
{
    Q_OBJECT
public:
    explicit log_file(QObject *parent = nullptr);


    void start_log(QString);
    void save(QMap<QString, QString>*);
    void close_file();

private:
    QFile LogFile;

    QString log_headers;
    bool file_created = false;
    //void create_file(QMap<QString, QString>*);

};

