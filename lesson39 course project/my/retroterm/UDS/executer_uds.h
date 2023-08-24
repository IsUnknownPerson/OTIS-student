#pragma once

#include "protocol_uds.h"
#include <QObject>
#include <QVector>
#include <QDateTime>
//#include <QMap>




class executer_uds : public QObject
{
    Q_OBJECT
public:
    explicit executer_uds(QObject *parent = nullptr);

    void make_query(uds_task directiv, uds_task cmd);

    // void instructon_from_protocol(uds_task directiv,
    //                               QMap<uds_task, QList<QByteArray>>,
    //                              uds_task _adapter);
    //void execute_next(){
    //;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //}

    void set_zagluski(QString);
    void from_adapter(QByteArray data);
    void reset();


signals:
    void send_to_connection(int dir, QString data);

public slots:
    void send_to_device(QString, int delay);
    void TX_delayed();

private:
    QString TX_delayed_data;
    void query(QString dir);
    void send_request(QString);

private:
    QVector<uds_task> cmds_to_permanent_execute;
    QVector<uds_task> cmds_to_single_execute;

    void request(QString);
    const int delay_request = 1000;
    int current_permanent_request = 0;
    int current_single_request = 0;
    bool single_request_pending = false;

    QDateTime time;
    int not_answering_count = 0;

    protocol_uds *pProtocol_uds;

    /*QVector<uds_task> cmds_to_triple_time_execute;
    bool tripple_request_begin = false;
    int current_triple_request = 0;
    bool answer_is_pending = false;
    unsigned int answer_pending_count = 0;
    uds_task adapter;
    uds_task cur_cmd_name = uds_task::none;
    QList<QByteArray> cur_cmd_code;
    QMap<uds_task, QList<QByteArray>> all_cmds;
    QMap<uds_task, QList<QByteArray>>::iterator cmd_counter;*/
};

