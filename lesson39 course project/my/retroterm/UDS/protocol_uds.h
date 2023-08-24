#pragma once
#include "definitions.h"
#include "assembling_answer.h"
#include <QMap>
#include <QObject>

class protocol_uds : public QObject
{
    Q_OBJECT
public:
    explicit protocol_uds(QObject *parent = nullptr);


    //void from_logic(uds_task directives, uds_task commands,
                    //uds_task adapter, QString dummy);

    QString send_request(uds_task);
    QString received_answer(QByteArray);

    QString dummy;
signals:
    void ask_remaining(QString, int delay);

private:
    QMap<uds_task, QString> all_cmds{
        {uds_task::keep_alive, "3E00"},
        {uds_task::gnss_reliability, "220008"},
        {uds_task::gnss_coords, "220007"},
        {uds_task::ICCIDG, "22001D"},
        {uds_task::DTC, "1902FF"},
        {uds_task::SW_Version, "220409"},
        {uds_task::Vehicle_SW_Version, "22040A"},
        {uds_task::Midlet_SW_Version, "22040B"},
        {uds_task::Boot_SW_Version, "22040D"}
    };

    assembling_answer *pAssembling;
    uds_task currenr_task = uds_task::keep_alive;

    //bool answer_assembled = false;
//    QList<QByteArray> get_uds_code(uds_task);
//    uds_task adapter = uds_task::none;
//    QString dummy = "";
};

