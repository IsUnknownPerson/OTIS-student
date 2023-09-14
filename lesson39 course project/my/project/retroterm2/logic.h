#pragma once

#include "config.h"
#include "connection.h"
#include "UDS/uds.h"

#include <QObject>
#include <QTimer>

class logic : public QObject
{
    Q_OBJECT
public:
    explicit logic(QObject *parent = nullptr);

signals:
    void recive(QString);
    void conection_stat(_connection_status);

public slots:
    void recive_from_connection(uchar *);
    void send_to_connection(Source source, QString data);
    void adapter_stat(_connection_status::_Adapter);

    void button_pressed(Buttons);
    void button_pressed(Buttons, QString);

private:
    connection *pConnection;
    UDS *pUDS;
    car_struct car;

    _connection_status connection_status;

    QVector<uds_task> TCU_identification{uds_task::ICCIDG,
                                         uds_task::SW_Version,
                                         uds_task::Vehicle_SW_Version,
                                         uds_task::Midlet_SW_Version,
                                         uds_task::Boot_SW_Version};
    QVector<uds_task> permanent_mainWindow{uds_task::gnss_reliability,
                                           uds_task::gnss_coords,
                                           uds_task::DTC,
                                           uds_task::Accelerometer};
};
