#include "config.h"

my_car::my_car(QString model)
{
    if (model == "Хавэйл"){
        model = Haval.model;
        canSpeed = Haval.canSpeed;
        uartSpeed = Haval.uartSpeed;
        canID = Haval.canID;
        CanIdTx = Haval.CanIdTx;
        CanIdRx = Haval.CanIdRx;
        zagluski = Haval.zagluski;
    }
    else if (model == "АвтоВАЗ"){
        model = VAZ.model;
        canSpeed = VAZ.canSpeed;
        uartSpeed = VAZ.uartSpeed;
        canID = VAZ.canID;
        CanIdTx = VAZ.CanIdTx;
        CanIdRx = VAZ.CanIdRx;
        zagluski = VAZ.zagluski;
    }
    else if (model == "ОМОДА"){
        model = OMODA.model;
        canSpeed = OMODA.canSpeed;
        uartSpeed = OMODA.uartSpeed;
        canID = OMODA.canID;
        CanIdTx = OMODA.CanIdTx;
        CanIdRx = OMODA.CanIdRx;
        zagluski = OMODA.zagluski;
    }
    else {
        model = car_unknown.model;
        canSpeed = car_unknown.canSpeed;
        uartSpeed = car_unknown.uartSpeed;
        canID = car_unknown.canID;
        CanIdTx = car_unknown.CanIdTx;
        CanIdRx = car_unknown.CanIdRx;
        zagluski = car_unknown.zagluski;
    }
}
