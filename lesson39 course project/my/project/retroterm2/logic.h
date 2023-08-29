#pragma once

#include "config.h"
#include "connection.h"

#include <QObject>
#include <QTimer>

class logic : public QObject
{
    Q_OBJECT
public:
    explicit logic(QObject *parent = nullptr);

public slots:
    void button_pressed(Buttons);
    void button_pressed(Buttons, my_car);

private:
    connection *pConnection;
    //connection pConnection(Adapter::Systec);
};
