#pragma once

#include "config.h"
#include "systectf.h"
#include <QObject>


class systec : public QObject
{
    Q_OBJECT

public:
    explicit systec(QObject *parent = nullptr);
    ~systec();

    void connect_Adapter(car_struct);
    void disconnect_Adapter();
    void send(uchar*);
    void receive(QString);

signals:
    void recived(uchar*);
    void systec_status(_connection_status::_Adapter);

private slots:
    void systect_init_status(bool);
    void systect_close_status();
    void ready_read();

private:
    QVector<int> from_string_to_hex(QString);

    Systect *pSystec;
};
