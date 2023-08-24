#include "logic.h"
//#include "UDS/executer_uds.h"
#include <QDebug>
#include <QSet>

logic::logic(QObject *parent)
    : QObject{parent}
{
    pTimer_loop = new QTimer(this);
    connect (pTimer_loop, &QTimer::timeout, this, &logic::loop);

    pConnection = new connection(this);
    connect (pConnection, &connection::to_logic, this, &logic::from_connection);

    plog = new log_file(this);
}

void logic::loop()
{
    //    test.append(0x03);
    //    qDebug() << "size:" << test.size();
    //        qDebug() << "length:" << test.length();
    //    if (test.size() > 5)
    //        test = " ";

    if (need_log){
        plog->save(&storage);
    }
    if (adapter_status != TCU_online){
        uds_query_made = false;
        identifikation_made = false;
        //check_identifikation = 0;
    }

    qDebug() << "loop(). adapter_status: " << adapter_status;

    if (adapter_status == none)
        ;
    else if (adapter_status == No_adapter){
        pConnection->from_logic(adapter_connect, "GreyBox");
        storage.clear();
        //plog->close_file();
        //        uds_query_made = false;
        //        identifikation_made = false;
    }
    else if (adapter_status == Adapter_reset)
        ;
    else if (adapter_status == adapter_connected){
        storage.clear();
        pConnection->from_logic(set_car, select_car);
    }
    else if (adapter_status == Adapter_configured){
        adapter_status = check_TCU_presence;
        pConnection->clear_query();
        pConnection->make_query(uds_task::permanent_request, uds_task::keep_alive);
    }
    else if (adapter_status == check_TCU_presence){
        //        uds_query_made = false;
        //        identifikation_made = false;
    }
    else if (adapter_status == TCU_online)
    {
        update_gui();
        if (!identifikation_made){
            identifikation_made = true;
           }

            static size_t counter = 0;

            if (!counter){
            ++counter;

            pConnection->make_query(uds_task::single_request, uds_task::ICCIDG);
            pConnection->make_query(uds_task::single_request, uds_task::SW_Version);
            pConnection->make_query(uds_task::single_request, uds_task::Vehicle_SW_Version);
            pConnection->make_query(uds_task::single_request, uds_task::Midlet_SW_Version);
            pConnection->make_query(uds_task::single_request, uds_task::Boot_SW_Version);
            }
            else if (counter == 4)
                counter = 0;
            else
                ++counter;
            // переспрашиваю так как бэг постоянно багует


        if(!uds_query_made){
            storage.clear();
            pConnection->clear_query();
            pConnection->make_query(uds_task::permanent_request, uds_task::gnss_coords);
            pConnection->make_query(uds_task::permanent_request, uds_task::gnss_reliability);
            pConnection->make_query(uds_task::permanent_request, uds_task::DTC);

            //pConnection->make_query(uds_task::permanent_request, uds_task::ICCIDG);
            //            pConnection->make_query(uds_task::permanent_request, uds_task::SW_Version);
            //            pConnection->make_query(uds_task::permanent_request, uds_task::Vehicle_SW_Version);
            //            pConnection->make_query(uds_task::permanent_request, uds_task::Midlet_SW_Version);
            //            pConnection->make_query(uds_task::permanent_request, uds_task::Boot_SW_Version);

            uds_query_made = true;
        }
    }
}


void logic::from_connection(int cmd, QString data)
{
    //qDebug() << "logic. from_connection: " << cmd;

    if (adapter_status == Adapter_reset){
        qDebug() << "return in connection";
        return;
    }

    switch (cmd) {
    case adapter_connected:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case Adapter_port_bisy: //!!!!!  при переподключении всегда тут
        adapter_status = adapter_connected;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;

    case No_adapter:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case Adapter_port_disconnected:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case Adapter_is_configuring:
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case Adapter_configured:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case check_TCU_presence:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;
    case TCU_online:
        adapter_status = cmd;
        emit to_mainwindow(directives::Connection, cmd, data);
        break;

    case Adapter_TX:
        //qDebug() << "logic::from_connection.Adapter_TX: " << data;
        break;
    case UDS_answer:
    {
        //data;
        qDebug() << "logic::from_connection. UDS_answer: " << data;

        if (data == "^-test present:online-^"){
            adapter_status = TCU_online;
            emit to_mainwindow(directives::Connection, TCU_online, data);
        }
        else if ((data.contains("not answering-^")) &&
                 (adapter_status == TCU_online)){
            storage.clear();
            adapter_status = Adapter_configured;
            emit to_mainwindow(directives::Connection, TCU_offline, data);

        }
        //auto s1 = data.split("^-");
        //auto s10 = data.split("^-")[0];

        if (!data.contains(":")){
            qDebug() << "ERROR logic. from_connection ERROR";
            return;
        }
        auto s11 = data.split("^-")[1];
        auto s20 = s11.split(":")[0];
        auto s21 = s11.split(":")[1];
        auto s30 = s21.split("-^")[0];

        storage.insert(s20, s30);

        //storage.insert(data.split("^-"));

        //auto xx = QString::fromLatin1(data);
        //qDebug() << "logic::from_connection fromLatin1(data): " << xx;
    }
        break;
    default:
        qDebug() << "ERROR logic. adapter_status: " << cmd;
        break;
    }
}


void logic::update_gui()
{
    QString temp;
    if (storage["test present"] == "online")
        emit to_mainwindow(directives::Connection, TCU_online, temp);
    else if (storage["test present"] == "not answering")
        emit to_mainwindow(directives::Connection, TCU_offline, temp);

    emit to_mainwindow(directives::DTC, 0, storage["DTC"]);
    emit to_mainwindow(directives::GNSS_realibility, 0, storage["coords_reliability"]);
    emit to_mainwindow(directives::GNSS_coordinates, 0, storage["gnss_coordinates"]);
    emit to_mainwindow(directives::ICCIDG, 0, storage["ICCIDG"]);
    emit to_mainwindow(directives::SW_Version, 0, storage["SW"]);
    emit to_mainwindow(directives::Vehicle_SW_Version, 0, storage["Vehicle_SW"]);
    emit to_mainwindow(directives::Midlet_SW_Version, 0, storage["Midlet_SW"]);
    emit to_mainwindow(directives::Boot_SW_Version, 0, storage["Boot_SW"]);
}


void logic::from_mainwindow(from_gui dir, QString data)
{
    switch (dir) {
    case from_gui::buttonDisconect:
        qDebug() << "Button disconnect pressed";
        adapter_status = Adapter_reset;
        pConnection->from_logic(Adapter_reset, "GreyBox");
        break;

    case from_gui::buttonConect:
        qDebug() << "Button connect pressed";
        adapter_status = No_adapter;
        select_car = data.toLatin1();
        break;

    case from_gui::buttonStart_Log:
        plog->start_log(data);
        need_log = true;
        break;

    case from_gui::buttonStop_Log:
        plog->close_file();
        need_log = false;
        break;

    default:
        break;
    }
}
//void logic::pereodically_identify_TCU()
//{
////    if (check_identifikation == 0)
////    {
////    ++check_identifikation;
//    pConnection->make_query(uds_task::single_request, uds_task::ICCIDG);
//    pConnection->make_query(uds_task::single_request, uds_task::SW_Version);
//    pConnection->make_query(uds_task::single_request, uds_task::Vehicle_SW_Version);
//    pConnection->make_query(uds_task::single_request, uds_task::Midlet_SW_Version);
//    pConnection->make_query(uds_task::single_request, uds_task::Boot_SW_Version);
////    }
////    else if (check_identifikation < 3)
////        ;
//}


//void logic::connect_adapter()// отправить в коннект
//{
//    if ((adpter_status == No_adapter) ||
//            (adpter_status == Adapter_port_bisy))
//        pConnection->connect_adapter();
//    else if (adpter_status == Adapter_connected)
//    {
//        greyBox::_adapter_settings settings;
//        greyBox::_adapter_settings::_CanID rx, tx;

//        rx.type = greyBox::_adapter_settings::_CanID::_Type_of_canID::standard;
//        rx.value = "079E";
//        tx.type = greyBox::_adapter_settings::_CanID::_Type_of_canID::standard;
//        tx.value = "07DE";

//        settings.mode = greyBox::_adapter_settings::_Mode::Trunsparent;
//        settings.canSpeed = greyBox::_adapter_settings::_CanSpeed::_500_KBaud;
//        settings.UARTSpeed = greyBox::_adapter_settings::_UARTSpeed::_115_2_KBaud;
//        settings.CanIdRx = rx;
//        settings.CanIdTx = tx;
//        pConnection->configure_adapter(settings);
//        adpter_status = Adapter_is_configuring;
//    }
//}
