#include "config.h"


QMap<QString, car_struct> tt = {{"Выберите авто",
                                  {"Выберите авто",
                                   _CanSpeed::_500_KBaud,
                                   _UARTSpeed::_115_2_KBaud,
                                   _Type_of_canID::standard,
                                   "0AAA",
                                   "0BBB",
                                   "AA"}},
                                 {"Хавэйл",
                                  {"Хавэйл",
                                   _CanSpeed::_500_KBaud,
                                   _UARTSpeed::_115_2_KBaud,
                                   _Type_of_canID::standard,
                                  "079E",
                                   "07DE",
                                   "AA"}},
                                 {"АвтоВАЗ",
                                  {"АвтоВАЗ",
                                   _CanSpeed::_500_KBaud,
                                   _UARTSpeed::_115_2_KBaud,
                                   _Type_of_canID::standard,
                                   "07DA",
                                   "07CA",
                                   "AA"}},
                                 {"ОМОДА",
                                  {"ОМОДА",
                                   _CanSpeed::_500_KBaud,
                                   _UARTSpeed::_115_2_KBaud,
                                   _Type_of_canID::standard,
                                   "0778",
                                   "0768",
                                   "AA"}}
};

QStringList car_struct::cars_all()
{
    QStringList const cc = {"Выберите авто", "Хавэйл", "АвтоВАЗ", "ОМОДА"};
    return cc;
}

car_struct _car(QString cur_car)
{
    return tt[cur_car];
}









//my_car::my_car(/*QString model*/)
//{
/*
    QMap<QString, test> tt = {{"Хавэйл",
                               {"Выберите авто",
                                _CanSpeed::_500_KBaud,
                                _UARTSpeed::_115_2_KBaud,
                                _Type_of_canID::standard,
                                "0AAA",
                                "0BBB",
                                "AA"}}



    };


    work = tt[model];
    this->model = work.model;


        if (model == "Хавэйл"){
            model = Haval.model;
            canSpeed = Haval.canSpeed;
            uartSpeed = Haval.uartSpeed;
            canID = Haval.canID;
            CanIdTx = Haval.CanIdTx;
            CanIdRx = Haval.CanIdRx;
            zagluski = Haval.zagluski;
            //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
        }
        else if (model == "АвтоВАЗ"){
            model = VAZ.model;
            canSpeed = VAZ.canSpeed;
            uartSpeed = VAZ.uartSpeed;
            canID = VAZ.canID;
            CanIdTx = VAZ.CanIdTx;
            CanIdRx = VAZ.CanIdRx;
            zagluski = VAZ.zagluski;
            //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
        }
        else if (model == "ОМОДА"){
            model = OMODA.model;
            canSpeed = OMODA.canSpeed;
            uartSpeed = OMODA.uartSpeed;
            canID = OMODA.canID;
            CanIdTx = OMODA.CanIdTx;
            CanIdRx = OMODA.CanIdRx;
            zagluski = OMODA.zagluski;
            //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
        }
        else {
            model = car_unknown.model;
            canSpeed = car_unknown.canSpeed;
            uartSpeed = car_unknown.uartSpeed;
            canID = car_unknown.canID;
            CanIdTx = car_unknown.CanIdTx;
            CanIdRx = car_unknown.CanIdRx;
            zagluski = car_unknown.zagluski;
            //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
        }




    if (model == "Хавэйл"){
        model = Haval.model;
        canSpeed = Haval.canSpeed;
        uartSpeed = Haval.uartSpeed;
        canID = Haval.canID;
        CanIdTx = Haval.CanIdTx;
        CanIdRx = Haval.CanIdRx;
        zagluski = Haval.zagluski;
        //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
    }
    else if (model == "АвтоВАЗ"){
        model = VAZ.model;
        canSpeed = VAZ.canSpeed;
        uartSpeed = VAZ.uartSpeed;
        canID = VAZ.canID;
        CanIdTx = VAZ.CanIdTx;
        CanIdRx = VAZ.CanIdRx;
        zagluski = VAZ.zagluski;
        //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
    }
    else if (model == "ОМОДА"){
        model = OMODA.model;
        canSpeed = OMODA.canSpeed;
        uartSpeed = OMODA.uartSpeed;
        canID = OMODA.canID;
        CanIdTx = OMODA.CanIdTx;
        CanIdRx = OMODA.CanIdRx;
        zagluski = OMODA.zagluski;
        //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
    }
    else {
        model = car_unknown.model;
        canSpeed = car_unknown.canSpeed;
        uartSpeed = car_unknown.uartSpeed;
        canID = car_unknown.canID;
        CanIdTx = car_unknown.CanIdTx;
        CanIdRx = car_unknown.CanIdRx;
        zagluski = car_unknown.zagluski;
        //all_cmds[uds_task::DTC] = "1902FF"; //override if needed
    }
}
*/
