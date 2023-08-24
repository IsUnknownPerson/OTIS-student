#include "gnss.h"
#include <QDebug>

gnss::gnss(QObject *parent)
    : QObject{parent}
{

}

//answer for check coords reliability
//03 7F 22 78 AA AA AA AA
//03 7F 22 78 AA AA AA AA 03 7F 22 78 AA AA AA AA
//04 62 00 08 00 AA AA AA

QString gnss::get_coordinates(QByteArray data, int d)
{
//        qDebug() << "size:" << data.size();
//        qDebug() << "length:" << data.length();


    double North, East;
    auto temp = (uchar*)data.data();
    QString answer;

    double a1 = (temp[3]) + (temp[2]<<8) + (temp[1]<<16) + (temp[0]<<24);
    double a2 = (temp[7]) + (temp[6]<<8) + (temp[5]<<16) + (temp[4]<<24);
    //tcuGNSS.longitude = a0/3600000 - 90;
     North = a1/3600000 - 90;
     East = a2/3600000 - 180;

     answer = "latitude ";
     answer += QString::number(North, 10, 8);
     answer += "___longitude ";
     answer += QString::number(East, 10, 8);

     //distance
        double delta_E, koef, numerator, denominator, result;
    const double N_reper = 55.678419866;
    const double E_reper = 37.632225494;
    const double EarthRadius =  6372795;

    koef = M_PI/180;
    East = East*koef;
    North = North*koef;
    delta_E = East - E_reper*koef;

    numerator = qPow((qPow((qCos(North)*qSin(delta_E)), 2) +
                      qPow((qCos(N_reper*koef)*qSin(North) - qSin(N_reper*koef)*qCos(North)*qCos(delta_E)), 2)), 0.5);

    denominator = qSin(N_reper*koef)*qSin(North) + qCos(N_reper*koef)*qCos(North)*qCos(delta_E);
    result = EarthRadius * qAtan(numerator/denominator);
    result = round(result*10)/10;

    answer += "___distance ";
    answer += QString::number(result, 10, 1);

//    if (result >100000)
//        qDebug() << "Wrong GNSS data from TCU";


    return answer;
}



QString gnss::check_reliability(QByteArray data, int d)
{
    QString answer; //d -> dummy
    uchar* hex_data = (uchar*)data.data();

    //проверка кадра на корректность
    /*
    if ((hex_data[0]==0x04)&&(hex_data[1]==0x62)&&(hex_data[2]==0x00)
            &&(hex_data[3]==0x08)&&(hex_data[5]==d)//hex_data[4] - ответ
            &&(hex_data[6]==d)&&(hex_data[7]==d)){
*/
//    else if ((hex_datadata[0]==0x02)&&(hex_datadata[1]==0x7E)&&(hex_datadata[2]==0x00)
//             &&(hex_datadata[3]==d)&&(hex_datadata[4]==d)&&(hex_datadata[5]==d)
//             &&(data[6]==d)&&(data[7]==d))
//        answer = "^-coords_reliability:answer is pending-^";

    if (hex_data[3] == 0)
        answer = "NOT reliable-^";
    else if (hex_data[3] == 1)
        answer = "reliable-^";
    else if (hex_data[3] == 2)
        answer = "NOT defined-^";
    else if (hex_data[3] == 3)
        answer = "NOT used-^";
    else
        answer = "Unknown status-^";
 //   }
//    else{
//        qDebug() << "ERROR gnss::check_reliability Unknown UDS error";
//        answer = "Unknown UDS error-^";
//    }
return answer;
}
