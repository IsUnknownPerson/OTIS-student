#pragma once

#include <QObject>
#include <QDebug>


enum class _Car_Model : int { model_unknown, Haval, VAZ, OMODA };

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

typedef QString _CanIdTx;
typedef QString _CanIdRx;
typedef QString _zagluski;

struct car_unknown
{
    const _Car_Model model = _Car_Model::model_unknown;
    const static _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
    const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
    const _Type_of_canID canID = _Type_of_canID::standard;
    const _CanIdTx CanIdTx = "AAA";
    const _CanIdRx CanIdRx = "BBB";
    const _zagluski zagluski = "AA";
};

struct Haval
{
    const _Car_Model model = _Car_Model::Haval;
    const static _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
    const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
    const _Type_of_canID canID = _Type_of_canID::standard;
    const _CanIdTx CanIdTx = "07DE";
    const _CanIdRx CanIdRx = "079E";
    const _zagluski zagluski = "AA";
};

struct VAZ
{
    const _Car_Model model = _Car_Model::VAZ;
    const static _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
    const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
    const _Type_of_canID canID = _Type_of_canID::standard;
    const _CanIdTx CanIdTx = "07DA";
    const _CanIdRx CanIdRx = "07CA";
    const _zagluski zagluski = "AA";
};

struct OMODA
{
    const _Car_Model model = _Car_Model::OMODA;
    const static _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
    const _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
    const _Type_of_canID canID = _Type_of_canID::standard;
    const _CanIdTx CanIdTx = "0778";
    const _CanIdRx CanIdRx = "0768";
    const _zagluski zagluski = "AA";
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




