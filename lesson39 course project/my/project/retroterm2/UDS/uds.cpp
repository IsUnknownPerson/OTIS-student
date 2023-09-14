#include "uds.h"
#include "decoding.cpp"
#include <QDebug>
#include <QTimer>

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
    if (Quere_type::Permanent == quere)
        permanent_quere[task] = timeout;
    else if (Quere_type::One_time == quere)
        one_time_quere[task] = timeout;
    else if (Quere_type::Car_Emulate == quere)
        car_Emulate_quere[task] = timeout;
    else
        qDebug() << "ERROR uds.cpp: " << __LINE__;

    if (permanent_quere.size() + one_time_quere.size() + car_Emulate_quere.size() == 1)
        choose_next();
}

void UDS::choose_next()
{
    qDebug() << "choose next";

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

void UDS::form_and_send_command_to_tcu()
{
    QString task = all_cmds[quere_condition.current_task];
    QString full_cmd = "0";
    full_cmd += QString::number(task.length() / 2, 16);
    full_cmd += task;
    for (int i = full_cmd.length(); i <= 14; i += 2)
        full_cmd += car.zagluski;
    emit send_to_tcu(Source::UDS, full_cmd);
    quere_condition.waiting_answer = true;

    qDebug() << "send: " << full_cmd;
}

void UDS::from_TCU(uchar *data)
{
    //tx  03 22 00 07 AA AA AA AA
    //rx  03 7f 22 78 aa aa aa aa //pending

    if (data[1] == 0x7f) { // error
        if (data[3] != 0x78)
            qDebug() << "unknown UDS error";
        else
            return; // answer pending, wait
    }

    for (size_t i = 0; i < 8; ++i)
        RXbuf += data[i];
    auto rx = (uchar *) RXbuf.data();



    if (rx[0] < 0x8) //single frame
    {
        auto task = quere_condition.current_task;
        request_results[task] = pdecode.decoding_answer(&RXbuf, task);
        quere_condition.waiting_answer = false;
        RXbuf = "";
    } else if (rx[0] == 0x10) // consequtive frame
    {
        ;
    }
    qDebug() << request_results[uds_task::gnss_reliability];

    QTimer::singleShot(DELAY, this, &UDS::choose_next);
}






