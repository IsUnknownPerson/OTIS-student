#include "decoding.h"

decoding::decoding(QObject *parent)
    : QObject{parent}
{

}

QString decoding::decoding_answer(QByteArray *RXbuf, uds_task task)
{
    QString answer;
    auto rx = (uchar *) RXbuf->data();

    switch (task) {
    case uds_task::keep_alive:
        if ((rx[0] == 0x02) && (rx[1] == 0x7e) && (rx[2] == 0x00))
            answer = "ok";
        else
            answer = "error";
        break;

    case uds_task::gnss_reliability:
        if (rx[3] == 0)
            answer = "NOT reliable";
        else if (rx[3] == 1)
            answer = "reliable";
        else if (rx[3] == 2)
            answer = "NOT defined";
        else if (rx[3] == 3)
            answer = "NOT used";
        else
            answer = "Unknown status";
        break;

    case uds_task::gnss_coords:

        break;

    case uds_task::ICCIDG:

        break;

    case uds_task::DTC:

        break;

    case uds_task::SW_Version:

        break;

    case uds_task::Vehicle_SW_Version:

        break;

    case uds_task::Midlet_SW_Version:

        break;

    case uds_task::Boot_SW_Version:

        break;

    case uds_task::Accelerometer:

        break;

    default:
        break;
    }




    return answer;
}
