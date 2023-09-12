#pragma once

#include <QDebug>
#include <QObject>

enum class Buttons : int { StartLog, StopLog, Connect, Disconnect, Send };

enum class Adapter : int { Not_chosed, GrayBox, Systec };

enum class Quere_type : int { None, Permanent, One_time, Car_Emulate };

struct _connection_status
{
    enum class _Adapter : int { Connected, Disconnected, Failed_to_connect };
    enum class _TCU : int { Answering, Not_answering };
    _Adapter Adapter;
    _TCU TCU;
};

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

enum class uds_task : int {
    None,
    keep_alive,

    gnss_reliability,
    gnss_coords,

    ICCIDG,

    DTC,

    SW_Version,
    Vehicle_SW_Version,
    Midlet_SW_Version,
    Boot_SW_Version,

    Accelerometer //angle
};


struct car_struct
{
public:
    QString model = "Выберите авто";
    _CanSpeed canSpeed = _CanSpeed::_500_KBaud;
    _UARTSpeed uartSpeed = _UARTSpeed::_115_2_KBaud;
    _Type_of_canID canID = _Type_of_canID::standard;
    QString CanIdTx = "0AAA";
    QString CanIdRx = "0BBB";
    QString zagluski = "AA";
    static QStringList cars_all();
};
car_struct _car(QString);

/*
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
        const QString CanIdRx = "07DE";
        const QString CanIdTx = "079E";
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
    QMap<uds_task, QString> all_cmds{
        {uds_task::keep_alive, "3E00"},
        {uds_task::gnss_reliability, "220008"},
        {uds_task::gnss_coords, "220007"},
        {uds_task::ICCIDG, "22001D"},
        {uds_task::DTC, "1902FF"},
        {uds_task::SW_Version, "220409"},
        {uds_task::Vehicle_SW_Version, "22040A"},
        {uds_task::Midlet_SW_Version, "22040B"},
        {uds_task::Boot_SW_Version, "22040D"},
        {uds_task::Accelerometer, "220401"}
    };

    const QStringList Cars = {{car_unknown.model}, {VAZ.model}, {OMODA.model}, {Haval.model}};
    test work;
*/

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
