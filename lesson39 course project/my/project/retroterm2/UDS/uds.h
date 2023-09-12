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

    QMap<uds_task, size_t> permanent_quere; //task, timeout
    QMap<uds_task, size_t> one_time_quere;
    QMap<uds_task, size_t> car_Emulate_quere;
    bool one_time_quere_pending = false;
    bool car_Emulate_quere_pending = false;
    Quere_type current_quere = Quere_type::None;
    uds_task current_task = uds_task::None;
    Quere_type prev_quere = Quere_type::None;
    uds_task prev_perm_task = uds_task::None;
    uds_task prev_oneTime_task = uds_task::None;
};

