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
        permanent_quere.push_back({task, timeout}); //[task] = timeout;
    else if (Quere_type::One_time == quere)
        one_time_quere.push_back({task, timeout}); //[task] = timeout;
    else if (Quere_type::Car_Emulate == quere)
        car_Emulate_quere.push_back({task, timeout}); //[task] = timeout;
    else
        qDebug() << "ERROR uds.cpp: " << __LINE__;

    if (permanent_quere.size() + one_time_quere.size() + car_Emulate_quere.size() == 1)
        choose_next();


}

void UDS::choose_next()
{
    qDebug() << "choose next";
    static uint16_t operationNum;

    if (permanent_quere.size() == 0) {
        qDebug() << "ERROR uds.cpp: " << __LINE__;
        return;
    }

    if (quere_condition.waiting_answer) {
        if (operationNum == quere_condition.operationNumber)
            qDebug() << "ERROR No answer uds.cpp: " << __LINE__;
        else
            return; //still waiting
    }


    operationNum = quere_condition.operationNumber;
    RXbuf = "";


    /*
    QMap<uds_task, size_t>::iterator it = permanent_quere.begin();
    quere_condition.current_quere = Quere_type::Permanent;
    if (quere_condition.current_task == uds_task::None)
        quere_condition.current_task = it.key();
    else {
        for (; it.key() != quere_condition.current_task;)
        {
            ++it;
            if (it != permanent_quere.end())
                quere_condition.current_task = it.key();
        }
    }
    */


    form_and_send_command_to_tcu();
}

void UDS::form_and_send_command_to_tcu()
{
    quere_condition.operationNumber++;
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
        if (RXbuf.size() == 8) {
            emit send_to_tcu(Source::UDS, AskRemaining);
            return;
        } else if (frame_assembled()) {
            qDebug() << "consequted frame assembled" << RXbuf;
            choose_next();
        }
        else
            ;

        //RXbuf = "";;
    }
    qDebug() << request_results[uds_task::gnss_reliability];

    QTimer::singleShot(DELAY, this, &UDS::choose_next);
}


bool UDS::frame_assembled()
{
    //в RX[1] входит 1 байт на сервис 62 + 2 байта на код службы +
    //3 байта данных с первой посылки + по 7 байт с каждой следующей

    auto temp = (uchar *) RXbuf.data();
    uint frame_size = temp[1] + 2; //+2 - учитываем 0х10 и RX[1]
    uint next_string_quantity = (frame_size - 8) / 7; //сколько будет строк, без учета первой строки
    if ((frame_size - 8) % 7) //учтем неполную строку, если есть
        ++next_string_quantity;
    frame_size += next_string_quantity; //учтем начала строк
    uint dummis_quantity = 8 - frame_size % 8;
    if (frame_size % 8)
        frame_size += dummis_quantity; //учитываем заглушки

    if ((RXbuf.size() < frame_size))
        return false; //wait
    else if ((RXbuf.size() > frame_size)) {
        qDebug() << "ERROR uds.cpp Too long frame" << __LINE__;
        return false; //wait
    }
    else if ((RXbuf.size() == frame_size)) {
        QByteArray temp2;
        temp2.append(RXbuf[5]);
        temp2.append(RXbuf[6]);
        temp2.append(RXbuf[7]);

        for (uint i=1; i<=next_string_quantity; ++i){
            for (uint j=1; j<8; ++j)
                temp2.append(RXbuf[j + i*8]);
        }
        if (dummis_quantity == 8)
            dummis_quantity = 0;
        temp2.chop(dummis_quantity);
        RXbuf = temp2;
    }
    return true;
}



