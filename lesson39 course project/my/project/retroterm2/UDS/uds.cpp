#include "uds.h"
#include <QDebug>

UDS::UDS(QObject *parent)
    : QObject{parent}
{
    quere_condition.one_time_quere_pending = false;
    quere_condition.car_Emulate_quere_pending = false;
    quere_condition.current_quere = Quere_type::None;
    quere_condition.current_task = uds_task::None;
    quere_condition.prev_quere = Quere_type::None;
    quere_condition.prev_perm_task = uds_task::None;
    quere_condition.prev_oneTime_task = uds_task::None;

//    if (car.name == "HAVAL") //redefine if nedeed
//        all_cmds[uds_task::ICCIDG] = "123456";
}

void UDS::make_qure(Quere_type quere, uds_task task, size_t timeout)
{
    if (Quere_type::Permanent == quere) {
        permanent_quere.insert({{task, timeout}});
    } else if (Quere_type::One_time == quere)
        one_time_quere.insert({{task, timeout}});
    else if (Quere_type::Car_Emulate == quere)
        car_Emulate_quere.insert({{task, timeout}});
    else
        qDebug() << "ERROR uds.cpp: " << __LINE__;

    if (permanent_quere.size() + one_time_quere.size() + car_Emulate_quere.size() == 1)
        choose_next();
}

void UDS::choose_next()
{
    if (permanent_quere.size() == 0) {
        qDebug() << "ERROR uds.cpp: " << __LINE__;
        return;
    }

    QMap<uds_task, size_t>::iterator it = permanent_quere.begin();
    quere_condition.current_quere = Quere_type::Permanent;
    if (quere_condition.current_task == uds_task::None)
        quere_condition.current_task = it.key();
    else {
        for (; it.key() != quere_condition.current_task;) {
            quere_condition.prev_perm_task = quere_condition.current_task;
            ++it;
            if (it != permanent_quere.end())
                quere_condition.current_task = it.key();
        }
    }
    form_and_send_command_to_tcu();
}

void UDS::form_and_send_command_to_tcu(){

}





