#include "dtc_diagnostictroublecodes.h"

dtc_diagnostictroublecodes::dtc_diagnostictroublecodes(QObject *parent)
    : QObject{parent}
{

}

/*
RX: 000249195       79Eh (8) 03 19 02 FF AA AA AA AA
RX: 000249195       7DEh (8) 10 17 59 02 FF 90 12 91 //0x17=23; 6
RX: 000249196       79Eh (8) give all
RX: 000249196       7DEh (8) 21 01 90 62 02 01 90 42 //7
RX: 000249196       7DEh (8) 22 13 01 90 51 13 01 90 //7
RX: 000249197       7DEh (8) 23 41 13 01 AA AA AA AA //3
data: 90129101 90620201 итд
*/

QString dtc_diagnostictroublecodes::DTC(QByteArray data, int d)
{
    QString answer = "";
    QByteArray parsedData = "";
    //auto temp = (uchar*)data.data();


    //    if (data.size() <8){
    //        for (uint i=4; i<8; ++i)
    //            parsedData.append(data[i]);
    //        answer = parse_code(parsedData);
    //    }
    //    else
    //    {
    //        for(uint i=9; i<data.size(); ++i){
    //            if ( (! i%8) && (data[i] != d) )
    //                parsedData.append(data[i]);
    //        }

    //    }

    //for (uint i=0; i<data.size(); i+=4)
    uint i=0;
    if ((data.size() == 0) || (data.size() % 4 != 0))
        return "ERROR";

    while(1){
        parsedData.append(data[i]);
        parsedData.append(data[i+1]);
        parsedData.append(data[i+2]);
        parsedData.append(data[i+3]);
        answer += parse_code(parsedData);
        i +=4;
        if (i>=data.size())
            break;

        answer += "___";
        parsedData.clear();
    }

    return answer;
}


QString dtc_diagnostictroublecodes::parse_code(const QByteArray data)
{
    QString part_answer;
    auto temp = (uchar*)data.data();
    bool unknown_code = false;

    part_answer = "(";
    //part_answer += QString::fromLatin1(data);
    //part_answer += data;
    //part_answer += QByteArray::fromHex(data);         //data.fromHex();
    part_answer += data.toHex();
    part_answer += ") ";

    switch (temp[0]) {

    case 0x90:
        switch (temp[1]) {

        case 0x11:
            part_answer += "Board voltage error. ";
            if (temp[2] == 0x16)
                part_answer += "Circuit voltage below threshold (low voltage)";
            else if (temp[2] == 0x17)
                part_answer += "Circuit voltage above threshold (high voltage)";
            else if (temp[2] == 0x13)
                part_answer += "Circuit open";
            else
                unknown_code = true;
            break;

        case 0x12:
            part_answer += "Internal Battery error. ";
            if (temp[2] == 0x91)
                part_answer += "Parametric (battery charge too low)";
            else if (temp[2] == 0x92)
                part_answer += "Performance or incorrect operation (battery is old)";
            else if (temp[2] == 0x97)
                part_answer += "Component obstructed or blocked (battery unchargeable)";
            else if (temp[2] == 0x98)
                part_answer += "Component over temperature (battery temperature too high)";
            else
                unknown_code = true;
            break;

        case 0x13:
            part_answer += "Voltage Supplier error. ";
            if (temp[2] == 0x01)
                part_answer += "General Electrical Failure (supplier is defective)";
            else
                unknown_code = true;
            break;

        case 0x16:
            part_answer += "Flash error. ";
            if (temp[2] == 0x01)
                part_answer += "Incorrect CRC for flash application";
            else
                unknown_code = true;
            break;

        case 0x21:
            part_answer += "GSM/GPRS and UMTS module error. ";
            if (temp[2] == 0x46)
                part_answer += "Audiofiles error (missing or invalide)";
            else if (temp[2] == 0x47)
                part_answer += "Audiocodec error";
            else if (temp[2] == 0x48)
                part_answer += "Invalid software version of GSM module";
            else if (temp[2] == 0x81)
                part_answer += "Invalid serial data received (wrong frame format or data)";
            else if (temp[2] == 0x87)
                part_answer += "Missing message (no signals from module)";
            else
                unknown_code = true;
            break;

        case 0x31:
            part_answer += "GPS/GLONASS module error. ";
            if (temp[2] == 0x81)
                part_answer += "Invalid serial data received (wrong frame format or data)";
            else if (temp[2] == 0x87)
                part_answer += "Missing message (no signals from module)";
            else
                unknown_code = true;
            break;

        case 0x41:
            part_answer += "Microphone error. ";
            if (temp[2] == 0x09)
                part_answer += "Component Failures";
            else if (temp[2] == 0x13)
                part_answer += "Break";
            else
                unknown_code = true;
            break;

        case 0x42:
            part_answer += "Load Speaker error. ";
            if (temp[2] == 0x09)
                part_answer += "Component Failures";
            else if (temp[2] == 0x13)
                part_answer += "Break";
            else
                unknown_code = true;
            break;

        case 0x51:
            part_answer += "SOS button error. ";
            if (temp[2] == 0x23)
                part_answer += "Signal stuck low (SOS button is stuck)";
            else if (temp[2] == 0x13)
                part_answer += "Break";
            else
                unknown_code = true;
            break;

        case 0x53:
            part_answer += "Accelerometer error. ";
            if (temp[2] == 0x02)
                part_answer += "no signal from module";
            else if (temp[2] == 0x09)
                part_answer += "initialisation error";
            else if (temp[2] == 0x15)
                part_answer += "calibration error";
            else
                unknown_code = true;
            break;

        case 0x62:
            part_answer += "Vehicle Identification Number error. ";
            if (temp[2] == 0x02)
                part_answer += "General Signal Failures";
            else
                unknown_code = true;
            break;

        case 0x63:
            part_answer += "Error activation. ";
            if (temp[2] == 0x04)
                part_answer += "EOL error";
            else
                unknown_code = true;
            break;

        case 0x71:
            part_answer += "SIM-chip error. ";
            if (temp[2] == 0x4A)
                part_answer += "No response from SIM chip";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    case 0xC0:
        switch (temp[1]) {

        case 0x73:
            part_answer += "CAN-bus off. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    case 0xC1:

        switch (temp[1]) {

        case 0x00:
            part_answer += "Lost Communication with ECM. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x21:
            part_answer += "Lost Communication with ABS. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x40:
            part_answer += "Lost Communication with BCM. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x55:
            part_answer += "Lost Communication with Cluster. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    case 0xC4:
        switch (temp[1]) {

        case 0x01:
            part_answer += "Invalid Data Received From ECM. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x15:
            part_answer += "Invalid Data Received From ABS. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x22:
            part_answer += "Invalid Data Received From BCM. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        case 0x23:
            part_answer += "Invalid Data Received From Cluster. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    case 0xD1:

        switch (temp[1]) {

        case 0x20:
            part_answer += "Lost Communication with Airbag. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    case 0xD4:
        switch (temp[1]) {

        case 0x10:
            part_answer += "Invalid Data Received From Airbag. ";
            if (temp[2] == 0x08)
                part_answer += "Bus Signal/Message Failures";
            else
                unknown_code = true;
            break;

        default:
            unknown_code = true;
            break;
        }
        break;

    default:
        unknown_code = true;
        break;
    }

    if (unknown_code){
        part_answer += "Unknown DTC code";

    }
    else {
        if (temp[3] == 0x1)
            part_answer += " (A)";
        else
            part_answer += " (?)";
    }

    return part_answer;
}




