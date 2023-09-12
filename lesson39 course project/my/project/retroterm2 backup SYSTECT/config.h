#pragma once

#include <QDebug>
#include <QObject>

enum class Buttons : int { StartLog, StopLog, Connect, Disconnect, Send };

enum class Adapter : int { Not_chosed, GrayBox, Systec };

//enum class _Car_Model : int { model_unknown, Haval, VAZ, OMODA };

enum class _Mode : int { Trunsparent, Packet, Monitoring_standard, Monitoring_extended };

enum class _CanSpeed : int { _250_KBaud, _500_KBaud, _1_MBaud };

enum class _UARTSpeed : int {
    _9_6_KBaud,
    _57_6_KBaud,
    _115_2_KBaud,
    _256_KBaud,
    _460_8_KBaud,
    _921_6_KBaud
};

enum class _Type_of_canID : int { standard, extended };

class my_car
{
private:
    struct _car_unknown
    {
        const QString model = "Выберите авто";
        const _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
        const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
        const _Type_of_canID canID = _Type_of_canID::standard;
        const QString CanIdTx = "0AAA";
        const QString CanIdRx = "0BBB";
        const QString zagluski = "AA";
    };

    struct _Haval
    {
        const QString model = "Хавэйл";
        const _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
        const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
        const _Type_of_canID canID = _Type_of_canID::standard;
        const QString CanIdTx = "07DE";
        const QString CanIdRx = "079E";
        const QString zagluski = "AA";
    };

    struct _VAZ
    {
        const QString model = "АвтоВАЗ";
        const _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
        const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
        const _Type_of_canID canID = _Type_of_canID::standard;
        const QString CanIdTx = "07DA";
        const QString CanIdRx = "07CA";
        const QString zagluski = "AA";
    };

    struct _OMODA
    {
        const QString model = "ОМОДА";
        const _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
        const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
        const _Type_of_canID canID = _Type_of_canID::standard;
        const QString CanIdTx = "0778";
        const QString CanIdRx = "0768";
        const QString zagluski = "AA";
    };

     _car_unknown car_unknown;
     _Haval Haval;
     _VAZ VAZ;
     _OMODA OMODA;

public:
    explicit my_car(QString);
    QString model;
    _CanSpeed canSpeed;
    _UARTSpeed uartSpeed;
    _Type_of_canID canID;
    QString CanIdTx;
    QString CanIdRx;
    QString zagluski;

    const QStringList Cars = {{car_unknown.model},
                        {VAZ.model},
                        {OMODA.model},
                        {Haval.model}};
};





/*
class Cars //singltone
{
public:
    static Cars *get()
    {
        static Cars instance;
        return &instance;
    }

    void test() { qDebug() << "Singleton test"; }
    _CanSpeed canSpeed() { return __canSpeed; }

private:
    Cars()
    {
        model = _Car_Model::Haval;
        __canSpeed = _CanSpeed::_500_KBaud;
        uartSpeed = _UARTSpeed::_115_2_KBaud;
        canID = _Type_of_canID::standard;
        CanIdTx = "ABC";
        CanIdRx = "DEF";
        zagluski = "AA";
    }

    _Car_Model model;
    _CanSpeed __canSpeed;
    _UARTSpeed uartSpeed;
    _Type_of_canID canID;
    _CanIdTx CanIdTx;
    _CanIdRx CanIdRx;
    _zagluski zagluski;
};
in cpp    Cars::get()->test();
in cpp    Cars::get()->canSpeed();
*/
