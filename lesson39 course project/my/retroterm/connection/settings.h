#pragma once

#include <QObject>
#include <QString>

struct _adapter_settings
{
    enum class _Car_Model : int {
        model_unknown,
        Haval,
        VAZ,
        OMODA};

    enum class _Mode : int {
        Trunsparent,
        Packet,
        Monitoring_standard,
        Monitoring_extended };

    enum class _CanSpeed : int {
        _250_KBaud,
        _500_KBaud,
        _1_MBaud };

    enum class _UARTSpeed : int {
        _9_6_KBaud,
        _57_6_KBaud,
        _115_2_KBaud,
        _256_KBaud,
        _460_8_KBaud,
        _921_6_KBaud };

    struct _CanID {
        enum class _Type_of_canID : int {
            standard,
            extended};
        _Type_of_canID type;
        QString value; };

    _Car_Model car_Model;
    _Mode mode;
    _CanSpeed canSpeed;
    _UARTSpeed UARTSpeed;
    _CanID CanIdTx;
    _CanID CanIdRx;
    QString zagluski;
}typedef _adapter_settings;


class _car_CAN_settings : public QObject, _adapter_settings
{
    Q_OBJECT
public:
    explicit _car_CAN_settings(QObject *parent = nullptr);
    _adapter_settings get_settings(_adapter_settings::_Car_Model);

private:
    _adapter_settings car_settings;
};




