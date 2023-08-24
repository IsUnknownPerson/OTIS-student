#include "executer_uds.h"
#include <QTimer>
#include <QDebug>

executer_uds::executer_uds(QObject *parent)
    : QObject{parent}
{
    pProtocol_uds = new protocol_uds(this);
    connect(pProtocol_uds, &protocol_uds::ask_remaining,
            this, &executer_uds::send_to_device);
}

void executer_uds::reset(){
    make_query(uds_task::clear_permanent_quares, uds_task::none);
    qDebug() << "executer reset";
}


void executer_uds::make_query(uds_task directiv, uds_task cmd)
{
    if (directiv == uds_task::permanent_request)
    {
        for (auto &v : cmds_to_permanent_execute){
            if (v == cmd)
                return;
        }
        cmds_to_permanent_execute.push_back(cmd);
        if (cmds_to_permanent_execute.size() == 1){
            QTimer::singleShot(delay_request, this, [&]() {
                request("start");  });
        }
    }
    else if (directiv == uds_task::single_request)
    {
//        for (auto &v : cmds_to_single_execute){
//            if (v == cmd)
//                return;
//        }

        cmds_to_single_execute.push_back(cmd);

        if (!single_request_pending){  //поменял тут
            single_request_pending = true;

            if (cmds_to_permanent_execute.size() == 0){
                QTimer::singleShot(delay_request, this, [&]() {
                    request("start"); });
            }
        }
    }

    else if (directiv == uds_task::single_triple_request) {
        qDebug() << "ERROR need to troubleshoot treeple request";
        //        for (auto &v : cmds_to_triple_time_execute){
        //            if (v == cmd)
        //                return;
        //        }
        //        cmds_to_triple_time_execute.push_back(cmd);
        //        if (cmds_to_triple_time_execute.size() == 1)
        //            request("start");
    }

    else if (directiv == uds_task::clear_permanent_quares){
        cmds_to_permanent_execute.clear();
        current_permanent_request = 0;
    }
    //qDebug() << "ERROR executer_uds::instructon_from_protocol. clear_quares Не реализованно";
    //request("reset"); all_cmds.clear;
    else
        qDebug() << "ERROR executer_uds::instructon_from_protocol. else Не реализованно";
}

void executer_uds::request(QString dir)
{    
    /*    if (cmds_to_triple_time_execute.size()){
        qDebug() << "ERROR need to troubleshoot treeple request";

        tripple_request_begin = true;
        if (dir == "start"){
            current_triple_request = 0;
            auto request = pProtocol_uds->send_request(cmds_to_triple_time_execute[current_triple_request]);
            send_request(request);
        }
        else if (dir == "one more time")
            send_request(pProtocol_uds->send_request(cmds_to_triple_time_execute[current_triple_request]));
        else if (dir == "next"){
            ++current_triple_request;

            if (!cmds_to_triple_time_execute.size()){// <= current_triple_request){
                current_triple_request = 0;
                cmds_to_triple_time_execute.clear();
                tripple_request_begin = false;

                /////////////////////////////////////////////////////////////
                auto request = pProtocol_uds->send_request(cmds_to_triple_time_execute[current_triple_request]);
                send_request(request);

            }

        }
        else
            qDebug() << "ERROR executer_uds::request. triple else Не реализованно";

    }
    //    else if (!cmds_to_permanent_execute.size())
    //        qDebug() << "ERROR. request unknown directive null size";


 else*/ if (dir == "start"){
        current_single_request = current_permanent_request = 0;
        QString request;
        if (single_request_pending){
            request = pProtocol_uds-> send_request(cmds_to_single_execute[current_single_request]);
            qDebug() << "request: " << request;
        }
        else
            request = pProtocol_uds->send_request(cmds_to_permanent_execute[current_permanent_request]);
        send_request(request);
    }
    else if (dir == "next"){
        QString ask_TCU;

        if (single_request_pending){ //SINGLE

            if (cmds_to_single_execute.size() < current_single_request +1){
                cmds_to_single_execute.clear();
                current_single_request = 0;
                single_request_pending = false;
                request("next");
                return;
            }
            else {
                ask_TCU = pProtocol_uds->send_request(cmds_to_single_execute[current_single_request]);
                ++current_single_request;
            }
        }
        else {
            ++current_permanent_request; //PERMANENT

            if (cmds_to_permanent_execute.size() <= current_permanent_request)
                current_permanent_request = 0;
            else if (cmds_to_permanent_execute.size() == 0)
                qDebug() <<"executer::request empty cmds_to_permanent_execute";
            else
            ask_TCU = pProtocol_uds->send_request(cmds_to_permanent_execute[current_permanent_request]);
        }
        send_request(ask_TCU);
    }
    else if (dir == "answer")
        ;
    else if (dir == "reset")
        qDebug() << "ERROR executer_uds::request. else Не реализованно"; //current_permanent_request = 0;
    else
        qDebug() << "ERROR executer_uds::request. else. dir: " << dir;
}

void executer_uds::send_request(QString data)
{
    /*if (!cmds_to_permanent_execute.size())
            return;  if (tripple_request_begin)*/

    time = QDateTime::currentDateTime();

    QTimer::singleShot(delay_request, this, [&]() {
        auto timeout = (QDateTime::currentDateTime() - time);
        if(timeout.count() > 950){
            QString answer = pProtocol_uds->received_answer("");
            answer += "not answering-^";
            ++not_answering_count;
            if (not_answering_count > 2)
                emit send_to_connection(UDS_answer, answer);
            request("next");
        }
    });
    send_to_device(data, 0);
}
// gnns coord: 03220007AAAAAAAA
//03 7F 22 78 AA AA AA AA 03 7F 22 78 AA AA AA AA 10 0B 62 00 07 1F 58 6D

void executer_uds::from_adapter(QByteArray data)
{
    not_answering_count = 0;

    /* if(tripple_request_begin){
            static int num = 0;
            static QString prew_answer = "";
            QString answer = pProtocol_uds->received_answer(data);

            if (answer.length()){
                if (num == 0){
                    prew_answer = answer;
                    ++num;
                    request("one more time");
                }
                else if (num == 1){
                    if (prew_answer != answer){
                        num = 0;
                        auto full_answer = pProtocol_uds->received_answer("");
                        full_answer += "ERROR";
                        emit send_to_connection(UDS_answer, full_answer);
                        request("next");
                    }
                    else {
                        ++num;
                        request("one more time");
                    }
                }
                else if (num == 2) {
                    num = 0;
                    auto full_answer = pProtocol_uds->received_answer("");
                    if (prew_answer != answer)
                        full_answer += "ERROR";
                    else
                        full_answer += answer;
                    emit send_to_connection(UDS_answer, full_answer);
                    request("next");
                }
            }
            else if (!answer.length())
                ;//qDebug() << "ошибка, таймаут. Либо ответ еще не полный ждем.";
        }
    else */

    if ((single_request_pending) && (!cmds_to_single_execute.size()))
        qDebug() << "ERROR executer_uds::from_adapter cmds_to_single_execute.size()=0";
    else if ((!cmds_to_permanent_execute.size()) && (!single_request_pending))
        qDebug() << "ERROR executer_uds::from_adapter. cmds_to_permanent_execute is empty";
    else
    {
        auto answer = pProtocol_uds->received_answer(data);
        //qDebug() << "Data in executer: " << answer;

        if (answer.length()){
            auto full_answer = pProtocol_uds->received_answer("");
            full_answer += answer;
            qDebug() << "answer: " << answer;
            emit send_to_connection(UDS_answer, full_answer);
            request("next");
        }
        else
            ;//qDebug() << "ошибка, таймаут. Либо ответ еще не полный ждем.";
    }
}


void executer_uds::send_to_device(QString data, int delay){

    delay = 50;

    if (TX_delayed_data.size())
        qDebug() << "ERROR. executer_uds::send_to_device to moore delay TX";
    else if (!delay)
        emit send_to_connection(Adapter_TX, data);
    else {
        TX_delayed_data = data;
        QTimer::singleShot(delay, this, &executer_uds::TX_delayed);
    }
}

void executer_uds::TX_delayed(){
    emit send_to_connection(Adapter_TX, TX_delayed_data);
    TX_delayed_data.clear();
}

void executer_uds::set_zagluski(QString d){
    pProtocol_uds->dummy = d;
}

/*
//to_executer(command, adapter)
void executer_uds::instructon_from_protocol(uds_task directiv,
                                            QMap<uds_task, QList<QByteArray>> command,
                                            uds_task _adapter)
{
    adapter = _adapter;

    if (directiv == uds_task::permanent_request)
    {
        all_cmds.insert(command);
        if (cur_cmd_name == uds_task::none){
            query();
            cmd_counter = all_cmds.begin();
        }
    }
    else if (directiv == uds_task::clear_quares)
        qDebug() << "executer_uds::instructon_from_protocol. clear_quares Не реализованно";
    else
        qDebug() << "executer_uds::instructon_from_protocol. else Не реализованно";
}


void executer_uds::query()
{
//    auto xx = all_cmds.first();
//    auto yy = all_cmds;
//    auto *zz = &all_cmds;

    if (cmd_counter == all_cmds.end())
        cmd_counter = all_cmds.begin();

    cur_cmd_name = cmd_counter.key();
    cur_cmd_code = cmd_counter.value();


    //++cmd_counter;




//    for (cmd_counter = all_cmds.begin(); cmd_counter != all_cmds.end(); ++cmd_counter)
//    {
//        cur_cmd_name = cmd_counter.key();
//        cur_cmd_code = cmd_counter.value();
//    }


//    for (const auto & xx : all_cmds)
//    {
//        cur_cmd_name = xx.first();
//        cur_cmd_code = xx;
//    }

    //    std::cout << '[' << key << "] = " << value << "; ";




//    auto aa = all_cmds;
//    auto bb = all_cmds.first(0);
//    //auto cc;



//    current_command = all_cmds.firstKey();
}
*/
