#pragma once

#include "definitions.h"
#include "connection/connection.h"
#include "log_file.h"
#include <QObject>
#include <QTimer>
#include <QMap>


class logic : public QObject
{
    Q_OBJECT
public:
    explicit logic(QObject *parent = nullptr);

    void loop();

public slots:
    void startTimer(int t) {
        pTimer_loop->start(t);
    }
    void from_connection(int, QString);
    void from_mainwindow(from_gui, QString);

signals:
    void to_mainwindow(directives , int, QString);


private:
    void update_gui();


    QTimer *pTimer_loop;
    connection *pConnection;
    //std::unique_ptr<connection> pConnection{new connection};

    log_file *plog;
    bool need_log = false;
    bool uds_query_made = false;
    bool identifikation_made = false;
//    void pereodically_identify_TCU();
//    size_t check_identifikation = 0;

    QMap<QString, QString> storage;

    _car_CAN_settings *pChoseCar;
    int adapter_status = none;
    int select_adapter = grey_box;
    QByteArray select_car = "model_unknown";
};
