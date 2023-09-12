#pragma once

#include "config.h"
//#include "adapter/systec.h"
#include "systectf.h"

#include <QObject>


class connection : public QObject
{
    Q_OBJECT

public:
    explicit connection(QObject *parent = nullptr);
    ~connection();

    void connect_Adapter(my_car);
    void disconnect_Adapter();
    void send(QString data);
    void receive(QString data);

private slots:
    void systect_init_stat(bool);
    void systect_close_stat();
    void ready_read();

private:
    //   systec *pSystec;
    //   grayBox pGrayBox;
    Systect *pSystec;
};


