#pragma once

#include "config.h"
#include "adapter/systec.h"
//#include "systectf.h"

#include <QObject>


class connection : public QObject
{
    Q_OBJECT

public:
    explicit connection(QObject *parent = nullptr);
    ~connection();

    void connect_Adapter(QString); //conect and init
    void disconnect_Adapter();
    void send(uchar *);

signals:
    void recive(uchar *); //always 8 bytes
    void adapter_says(_connection_status::_Adapter);

public slots:
    void adapter_stat(_connection_status::_Adapter);
    void ready_read(uchar*);

private:
       systec *pAdapter;

       uchar data[8];
       car_struct car;
    // grayBox pGrayBox;
};


