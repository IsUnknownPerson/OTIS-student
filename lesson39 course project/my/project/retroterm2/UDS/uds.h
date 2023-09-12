#pragma once

#include "config.h"
#include <QObject>
#include <QMap>

//enum class Quere_type : int { Permanent, One_time, Car_Emulate };

class UDS : public QObject
{
    Q_OBJECT
public:
    explicit UDS(QObject *parent = nullptr);

    void make_qure(Quere_type, uds_task, size_t);
    void make_qure(Quere_type a, uds_task b) { make_qure(a, b, 1000); }

private:
    void choose_next();
    void form_and_send_command_to_tcu();

    QMap<uds_task, size_t> permanent_quere; //task, timeout
    QMap<uds_task, size_t> one_time_quere;
    QMap<uds_task, size_t> car_Emulate_quere;

    struct quere_maintance
    {
        bool one_time_quere_pending;
        bool car_Emulate_quere_pending;
        Quere_type current_quere;
        uds_task current_task;
        Quere_type prev_quere;
        uds_task prev_perm_task;
        uds_task prev_oneTime_task;
    };
    quere_maintance quere_condition;

    QMap<uds_task, QString> all_cmds{
        {uds_task::keep_alive, "3E00"},
        {uds_task::gnss_reliability, "220008"},
        {uds_task::gnss_coords, "220007"},
        {uds_task::ICCIDG, "22001D"},
        {uds_task::DTC, "1902FF"},
        {uds_task::SW_Version, "220409"},
        {uds_task::Vehicle_SW_Version, "22040A"},
        {uds_task::Midlet_SW_Version, "22040B"},
        {uds_task::Boot_SW_Version, "22040D"},
        {uds_task::Accelerometer, "220401"}
    };
};

//namespace UDS_codes {

//}



