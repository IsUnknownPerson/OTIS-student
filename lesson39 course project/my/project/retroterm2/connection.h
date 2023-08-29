#pragma once

#include "config.h"
#include "adapter/systec.h"


class connection
{
public:
    explicit connection();//Adapter);
    ~connection();

    void connect_Adapter(my_car);
    void disconnect_Adapter();
    void setup_Adapter();
    QString getStatus();
    void send(QString);
    void receive();

private:
    systec *pSystec;
 //   grayBox pGrayBox;
};


