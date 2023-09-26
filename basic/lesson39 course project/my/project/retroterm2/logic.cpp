#include "logic.h"
#include "utils.cpp"

logic::logic(QObject *parent)
    : QObject{parent}
{
    pUDS = new UDS(this);
    connect(pUDS, &UDS::send_to_tcu, this, &logic::send_to_connection);

    pConnection = new connection(this);
    connect(pConnection, &connection::recive, this, &logic::recive_from_connection);
    connect(pConnection, &connection::adapter_says, this, &logic::adapter_stat);

    connection_status.TCU = _connection_status::_TCU::Not_answering;
    connection_status.Adapter = _connection_status::_Adapter::Disconnected;
}


void logic::send_to_connection(Source source, QString data)
{
    auto x = utils::from_string_to_uchar(data);
    pConnection->send(x);
}

void logic::recive_from_connection(uchar *d)
{
    pUDS->from_TCU(d);

    QString data;
    for (size_t i = 0; i < 8; ++i) {
        auto x = data.number(d[i], 16);
        if (x.length() == 1)
            x.push_front("0");
        data += x + " ";
    }
    emit recive(data);
}


void logic::button_pressed(Buttons but)
{
    Q_UNUSED(but)
    if (but == Buttons::Disconnect)
        pConnection->disconnect_Adapter();
    else
    qDebug() << "Error. logic нет кнопки: " << __LINE__;
}

void logic::button_pressed(Buttons but, QString data)
{
    if (but == Buttons::Connect)
    {
        car = _car(data);
        pConnection->connect_Adapter(data);
        pUDS->setCar(data);
        qDebug() << "logic: buton connect pressed";
    }
    else if (but == Buttons::Send) {
        if (data.length() != 16) {
            qDebug() << "ERROR logic Buttons::Send";
            return;
        }
        send_to_connection(Source::MainWindow, data);
    }
    else
        qDebug() << "Error. logic нет кнопки: " << __LINE__;
}

void logic::adapter_stat(_connection_status::_Adapter stat)
{
    //qDebug() << "logic::adapter_stat";

    connection_status.Adapter = stat;
    emit conection_stat(connection_status);

    if (stat == _connection_status::_Adapter::Connected) {
        for (auto &task : permanent_mainWindow) {
            pUDS->make_qure(Quere_type::Permanent, task);
            qDebug() << "insert task";
        }
    }





    //pUDS->make_qure(Quere_type::Permanent, uds_task::keep_alive);
    //pUDS->make_qure(Quere_type::Permanent, uds_task::gnss_reliability);

    //UDS(Quere_type::One_time, uds_task::keep_alive);
        //pConnection->send("jkhkjh");
}
