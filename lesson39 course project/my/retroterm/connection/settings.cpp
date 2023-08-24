#include "settings.h"


_car_CAN_settings::_car_CAN_settings(QObject *parent)
    : QObject{parent}
{

}

_adapter_settings _car_CAN_settings::get_settings(_adapter_settings::_Car_Model model)
{
    switch (model) {
    case _adapter_settings::_Car_Model::model_unknown:
        car_settings.car_Model = _Car_Model::Haval;
        break;

    case _adapter_settings::_Car_Model::Haval:
        car_settings.car_Model = _Car_Model::Haval;
        car_settings.mode = _Mode::Trunsparent;
        car_settings.canSpeed = _CanSpeed::_500_KBaud;
        car_settings.UARTSpeed = _UARTSpeed::_115_2_KBaud;
        car_settings.CanIdTx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdRx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdTx.value = "07DE";
        car_settings.CanIdRx.value = "079E";
        car_settings.zagluski = "AA";
        break;

    case _adapter_settings::_Car_Model::VAZ:
        car_settings.car_Model = _Car_Model::Haval;
        car_settings.mode = _Mode::Trunsparent;
        car_settings.canSpeed = _CanSpeed::_500_KBaud;
        car_settings.UARTSpeed = _UARTSpeed::_115_2_KBaud;
        car_settings.CanIdTx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdRx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdTx.value = "07DA";
        car_settings.CanIdRx.value = "07CA";
        car_settings.zagluski = "AA";
        break;

    case _adapter_settings::_Car_Model::OMODA:
        car_settings.car_Model = _Car_Model::Haval;
        car_settings.mode = _Mode::Trunsparent;
        car_settings.canSpeed = _CanSpeed::_500_KBaud;
        car_settings.UARTSpeed = _UARTSpeed::_115_2_KBaud;
        car_settings.CanIdTx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdRx.type = _CanID::_Type_of_canID::standard;
        car_settings.CanIdTx.value = "0778";
        car_settings.CanIdRx.value = "0768";
        car_settings.zagluski = "AA";
        break;

    default:
        break;
    }




    return car_settings;
}
