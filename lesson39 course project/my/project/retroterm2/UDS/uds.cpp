#include "uds.h"
#include <QDebug>

UDS::UDS(QObject *parent)
    : QObject{parent}
{}

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
    if (current_task == uds_task::None)
        current_task = it.key();
    else {
        for (; it.key() != current_task;) {
            prev_perm_task = current_task;
            ++it;
            if (it != permanent_quere.end())
                current_task = it.key();
        }
    }
send_command_to_tcu
}
