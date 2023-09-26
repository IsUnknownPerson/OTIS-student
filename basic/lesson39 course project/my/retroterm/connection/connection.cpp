#include "connection.h"
#include <QtDebug>

connection::connection(QObject *parent)
    : QObject{parent}
{
    pExecuter = new executer_uds(this);
    connect (pExecuter, &executer_uds::send_to_connection,
             this, &connection::from_executer);

    pAdapter = new greyBox(this);
    signal_slot_forAdapter =
            connect (pAdapter, &greyBox::adapter_say,
                     this, &connection::from_adapter);
    connect (this, &connection::adapterTX,
             pAdapter, &greyBox::adapterTX);
}



void connection::make_query(uds_task directiv, uds_task cmd)
{
    pExecuter->make_query(directiv, cmd);
}

void connection::clear_query(){
    pExecuter->reset();
}


void connection::from_logic(int cmd, QByteArray data)
{
    //qDebug() << "pConnection->from_logic(adapter_connect, GreyBox)";
    switch (cmd) {
    case adapter_connect:
        //qDebug() << "pConnection adapter status: " << adapter_status;
        if ((adapter_status == Adapter_port_disconnected) ||
                (adapter_status == none) || (adapter_status == Adapter_port_bisy) ||
                (adapter_status == No_adapter))
        {
            //qDebug() << "pConnection if no adapter";
            if (data == "GreyBox") {
                //qDebug() << "pConnection data == \"GreyBox\"";
                adapter_type = grey_box;
                //                pAdapter = new greyBox;
                //                signal_slot_forAdapter =
                //                connect (pAdapter, &greyBox::adapter_say,
                //                this, &connection::from_adapter);
                pAdapter->connect_adapter();
            }
            else
                qDebug() << "Error. connection::from_logic Неизвестный адаптер";
        }
        break;

    case adapter_disconnect:
        qDebug() << "ERROR connection::from_logic disconnect_adapter Не реализованно";
        break;

    case set_car:
    {
        auto select_car = _adapter_settings::_Car_Model::model_unknown;
        if (data == "Haval")
            select_car = _adapter_settings::_Car_Model::Haval;
        else if (data == "VAZ")
            select_car = _adapter_settings::_Car_Model::VAZ;
        else if (data == "OMODA")
            select_car = _adapter_settings::_Car_Model::OMODA;
        else{
            qDebug() << "ERROR connection::from_logic model_unknown";
            return;
        }

        _car_CAN_settings *temp;
        temp = new _car_CAN_settings; //Удалить строчку
        auto settings = temp->get_settings(select_car);
        pExecuter->set_zagluski(settings.zagluski);
        delete temp; //Удалить строчку
        pAdapter->configure_adapter(select_car, "");
    }
        break;

    case Adapter_reset:
        pAdapter->reset_adapter("from gui");
        break;

    default:
        break;
    }
    ;
}



void connection::from_adapter(int cmd, QByteArray data)
{
    switch (cmd) {
    case No_adapter:
        pExecuter->reset();
        break;
    case Adapter_RX:
        //emit to_logic(cmd, data);
        //qDebug() << "connection::from_adapter. int: Adapter_RX. data: " << data;
        if (adapter_status == Adapter_configured){
            pExecuter->from_adapter(data);
        }
        return;
    case adapter_connected:
        //qDebug() << "connection::from_adapter. int: adapter_connected. data: " << data;
        ;
        break;
    case adapter_disconected:

        qDebug() << "ERROR connection::from_adapter disconnected_adapter Не реализованно";
        break;
    case Adapter_port_disconnected:

        break;
    case Adapter_port_bisy:
        qDebug() << "ERROR connection::from_adapter disconnected_adapter Не реализованно";
        break;
    case Adapter_is_configuring:
        //qDebug() << "connection::from_adapter. Adapter_is_configuring";
        ;
        break;
    case Adapter_configured:
        //qDebug() << "connection::from_adapter. int: Adapter_configured" << ". data: " << data;
        break;
    default:
        qDebug() << "ERROR!!! connection::from_adapter else. Не реализованно. int: "
                 << cmd << ". data: " << data;
        break;
    }

    adapter_status = cmd;
    emit to_logic(cmd, data);

}

void connection::from_executer(int dir, QString data){
    // qDebug() << "connection::from_executer. data: " << data;
    if (dir == UDS_answer)
        emit to_logic(UDS_answer, data);
    else if (dir == Adapter_TX){
        emit adapterTX(data.toLatin1());
        emit to_logic(Adapter_TX, data); //for debag
    }
    else
        qDebug() << "ERROR connection::from_executer unknown dirrective: " << dir;
}
