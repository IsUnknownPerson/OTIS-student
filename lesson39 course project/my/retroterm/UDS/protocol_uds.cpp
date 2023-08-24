#include "protocol_uds.h"
#include "gnss/gnss.h"
#include "dtc_diagnostictroublecodes.h"
#include <QByteArray>
#include <QDebug>

protocol_uds::protocol_uds(QObject *parent)
    : QObject{parent}
{
    pAssembling = new assembling_answer;
}


QString protocol_uds::send_request(uds_task task)
{
    currenr_task = task;
    QString full_cmd;

    if (all_cmds.find(task) == all_cmds.end()){

        qDebug() << "ERROR protocol_uds::send_request vector with task out of bounds";
        //check all_cmds, нехватает чего-то типа:  {uds_task::пропущенная команда, "22001D"}
        return "ERROR";
    }
    else if (all_cmds[task].length()/2 > 0x7){
        qDebug() << "ERROR protocol_uds::get_uds_code. Не реализованно";
        return "ERROR";
    }

    pAssembling->get_answer(); //clear assembling buffer

    full_cmd = "0" + QString::number(all_cmds[task].length()/2, 16);
    full_cmd += all_cmds[task];
    for (int i=full_cmd.length(); i<=14; i+=2)
        full_cmd += dummy;
    return full_cmd;
}

QString protocol_uds::received_answer(QByteArray data)
{
    //qDebug() << "Protocol get data: " << data;

    QString answer;
    if(!data.size()){
        switch (currenr_task) {
        case uds_task::keep_alive:
            answer = "^-test present:";
            break;
        case uds_task::gnss_reliability:
            answer = "^-coords_reliability:";
            break;
        case uds_task::gnss_coords:
            answer = "^-gnss_coordinates:";
            break;
        case uds_task::ICCIDG:
            answer = "^-ICCIDG:";
            break;
        case uds_task::DTC:
            answer = "^-DTC:";
            break;
        case uds_task::SW_Version:
            answer = "^-SW:";
            break;
        case uds_task::Vehicle_SW_Version:
            answer = "^-Vehicle_SW:";
            break;
        case uds_task::Midlet_SW_Version:
            answer = "^-Midlet_SW:";
            break;
        case uds_task::Boot_SW_Version:
            answer = "^-Boot_SW:";
            break;
        default:
            qDebug() << "ERROR. protocol_uds::received_answer. unknown uds_task";
            answer = "";
            break;
        }
        return answer;
    }

    auto ass_status = pAssembling->recived_data(data, dummy);

    if (ass_status == asm_stat::wait)
        answer = "";
    else if (ass_status == asm_stat::error)
        answer = "";
    else if (ass_status == asm_stat::ask_remaining){
        emit ask_remaining("300000AAAAAAAAAA", 0); //delay
        answer = "";
    }
    else if (ass_status == asm_stat::done){
        QByteArray data = pAssembling->get_answer();

        auto hex_data = (uchar*)data.data();
        auto d = dummy.toInt(nullptr, 16);

        //check busyRepeatRequest
        if ((hex_data[0]==0x03)&&(hex_data[1]==0x7F)/*&&(hex_data[2]==0x00) служба*/
                &&(hex_data[3]==0x21)&&(hex_data[4]==d)&&(hex_data[5]==d)
                &&(hex_data[6]==d)&&(hex_data[7]==d))
            answer = "TCU busy-^";
        else
        {
            switch (currenr_task) {
            case uds_task::keep_alive:
               /* if ((hex_data[0]==0x02)&&(hex_data[1]==0x7E)&&(hex_data[2]==0x00)
                        &&(hex_data[3]==d)&&(hex_data[4]==d)&&(hex_data[5]==d)
                        &&(hex_data[6]==d)&&(hex_data[7]==d)) */

                if ((hex_data[0]==0x7E) && (hex_data[1]==0x00))
                    answer = "online-^";
                else
                    answer = "wrong answer-^";
                break;

            case uds_task::gnss_reliability:
                answer += gnss::check_reliability(data, d);
                break;

            case uds_task::gnss_coords:
                answer += gnss::get_coordinates(data, d);
                break;

            case uds_task::ICCIDG:

                if (data.size() < 19)
                    answer = "";
                else
                    answer = "_" + data;
                break;

            case uds_task::DTC:

                answer = dtc_diagnostictroublecodes::DTC(data, d);
                break;

            case uds_task::SW_Version:
                answer = data;
                break;

            case uds_task::Vehicle_SW_Version:
                //answer = get_data(data, uds_task::Vehicle_SW, d);
                //06 62 04 0A 30 30 31 AA
                answer = data.remove(0, 3);
                break;

                //test-present answer: 027E00AAAAAAAAAA
            case uds_task::Midlet_SW_Version:
                //100D62040B323830
                //2133323331333233
                answer = data;
                //32 38
                break;

            case uds_task::Boot_SW_Version:
                answer += data;
                break;

            default:
                qDebug() << "ERROR. protocol_uds::received_answer. unknown uds_task";
                break;
            }
        }
    }
    else
        qDebug() << "ERROR. protocol_uds::received_answer. else";

    return answer;
}

/*
void protocol_uds::from_logic(uds_task directiv, uds_task command,
                              uds_task _adapter, QString _dummy)
{
    dummy = _dummy;
    if (directiv == uds_task::clear_quares)
        qDebug() << "protocol_uds::from_logic. Не реализованно";
    else if (directiv == uds_task::single_command)
        qDebug() << "protocol_uds::from_logic. Не реализованно";
    else if (directiv == uds_task::single_request)
        qDebug() << "protocol_uds::from_logic. Не реализованно";
    else if (directiv == uds_task::permanent_request) {
        auto xx = get_uds_code(command);
        //to_executer(command, adapter)
    }
}

QList<QByteArray> protocol_uds::get_uds_code(uds_task command)
{
    QString cmd, full_cmd;
    QList<QByteArray> temp;
    switch (command) {
    case uds_task::keep_alive:
        cmd = "3E00";
        break;
    default:
        qDebug() << "protocol_uds::get_uds_code. Ошибка";
        break;
    }

    if (cmd.length()/2 > 0x7)
        qDebug() << "protocol_uds::get_uds_code. Не реализованно";
    else
    {
        full_cmd = "0" + QString::number(cmd.length()/2, 16);
        full_cmd += cmd + dummy;
        temp.push_back(full_cmd.toLatin1());
    }
    return temp;
}

*/





