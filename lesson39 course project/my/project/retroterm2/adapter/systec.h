#pragma once

#include "config.h"

class systec
{
public:
    systec();
    ~systec();

    // ... public methods ...

    void connect_Adapter(my_car);
    void disconnect_Adapter();
    void setup_Adapter();
    QString getStatus();
    void send(QString);
    void receive();

private:
    class Private; //pimpl
    Private * impl;
};
