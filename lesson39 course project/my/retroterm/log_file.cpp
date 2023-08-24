#include "log_file.h"
#include <QDateTime>
#include <QDebug>

log_file::log_file(QObject *parent)
    : QObject{parent}
{

}


void log_file::start_log(QString data)
{

    if (data == ""){
        qDebug() << "ERROR log_file::start_log empty log_headers";
        return;
    }

    log_headers = data;
    QString full_date = QDateTime::currentDateTime().toString("yyyy_MM_dd hh_mm_ss");
    QString logFileName = "log_" + full_date + ".csv";
    LogFile.setFileName(logFileName);

    if(!LogFile.open(QIODevice::Append)){ //||(!ErrorFile.open(QIODevice::ReadWrite)))
        qDebug() << "ERROR log_file::create_file can't create file";
        return;
    }
    file_created = true;

    QTextStream stream_log(&LogFile);
    stream_log << "\n;";
    stream_log << log_headers;
    stream_log.flush();
}

void log_file::close_file(){
    if (!file_created)
        return;
    QString full_date = QDateTime::currentDateTime().toString("yyyy_MM_dd hh_mm_ss");
    QString text = "\n\n;";
    text += full_date + "Force stop. Adapter disconected;";

    QTextStream stream_log(&LogFile);
    stream_log << text;
    stream_log.flush();
    LogFile.close();
    file_created = false;
}
/*
void log_file::create_file(QMap<QString, QString> *storage)
{

    if (!storage->size()){
        qDebug() << "ERROR log_file::create_file empty storage";
        return;
    }

    QString full_date = QDateTime::currentDateTime().toString("yyyy_MM_dd hh_mm_ss");
    QString logFileName = "log_" + full_date + ".csv";
    LogFile.setFileName(logFileName);

    if(!LogFile.open(QIODevice::Append)){ //||(!ErrorFile.open(QIODevice::ReadWrite)))
        qDebug() << "ERROR log_file::create_file can't create file";
        return;
    }
    file_created = true;

    QString text = "\n;Time;";
    for (auto it = storage->begin(); it!=storage->end(); ++it)
        text += it.key() + ";";
    text += "\n";

    QTextStream stream_log(&LogFile);
    stream_log << text;
    stream_log.flush();

}
*/


void log_file::save(QMap<QString, QString> *storage)
{

    if (!storage->size()){
        qDebug() << "ERROR log_file::save empty storage";
        return;
    }

    if ((!file_created) && (log_headers != ""))
        start_log(log_headers);
    else if (log_headers == "") {
        qDebug() << "ERROR log_file::save empty headers";
        return;
    }

    //    if (!LogFile.open(QIODevice::Append)){ //||(!ErrorFile.open(QIODevice::ReadWrite)))
    //        qDebug() << "ERROR log_file::save can't open file";
    //        return;
    //    }
    if (!LogFile.isOpen()){ //||(!ErrorFile.open(QIODevice::ReadWrite)))
        qDebug() << "ERROR log_file::save file not opened";
        return;
    }

    //    columns[2];
    //    storage[2];

    QString full_date = QDateTime::currentDateTime().toString("yyyy_MM_dd hh_mm_ss");
    auto columns = log_headers.split(";");
    QTextStream stream_log(&LogFile);
    QString text = "\n";

    QString _DTC, _reliability, _coordinates, _test_present;

    for (auto it = storage->begin(); it!=storage->end(); ++it){
        if (it.key() == "DTC")
            _DTC = *it;
        else if (it.key() == "coords_reliability")
            _reliability = *it;
        else if (it.key() == "gnss_coordinates")
            _coordinates = *it;
        else if (it.key() == "test present")
            _test_present = *it;
    }
    //NOT reliable

    for (int i=0; i<columns.size(); ++i){
        if (columns[i] == "Time")
            text += ";" + full_date;
        else if (columns[i] == "DTC_quantity"){
            auto quntity = (_DTC.split("___")).size();
            if (_test_present == "not answering")
                text += ";" + _test_present;
//            else if (columns[i] == "TCU busy")
//                text += ";" + columns[i];
            else
                text += ";" + QString::number(quntity);
        }
        else if (columns[i] == "DTC_list"){
            if (_test_present == "not answering")
                text += ";" + _test_present;
            else
                text += ";" + _DTC;
        }
        else if (columns[i] == "Coords_reliability"){
            if (_test_present == "not answering")
                text += ";" + _test_present;
            else
                text += ";" + _reliability;
        }
        else if ((columns[i] == "Gnss_coordinates") ||
                 (columns[i] == "Distance")){
            if (_test_present == "not answering")
                text += ";" + _test_present;
            else if (_coordinates == "TCU busy")
                text += ";" + _coordinates;
            else{
                if (_reliability == "NOT reliable")
                    text += ";NA";
                else {
                    if (_coordinates.split("___").size() !=3)

                        text += ";ERROR";
                    else {
                        auto t = _coordinates.split("___");
                        if (columns[i] == "Gnss_coordinates")
                            text += ";" + t[0] + "___" + t[1];
                        else
                            text += ";" + t[2].split(" ")[1];
                    }
                }
            }
        }

        //        else if (columns[i] == "Distance")
        //            text += ";" + *it;
    }

    // Проверить на оффлайн. Если одно офлайн - то NA потом тест презент и все офлайн.





    //    for (auto it = storage->begin(); it!=storage->end(); ++it)
    //        text += it.value() + ";";//qDebug() << it.key() << ": " << it.value();
    //    //QTextStream stream_log(&LogFile);
    stream_log << text;

    stream_log.flush();
    //LogFile.close();


}
