#include "assembling_answer.h"
#include <QDebug>

assembling_answer::assembling_answer(QObject *parent)
    : QObject{parent}
{

}

QByteArray assembling_answer::get_answer(){
    auto temp = RX;
    RX = "";
    status = asm_stat::done;
    qDebug() << temp;
    return temp;
}

asm_stat assembling_answer::recived_data(QByteArray data, QString dummy)
{
    //status == asm_stat::wait;
    //return status;

    if ((data.size() == 0) || (status == asm_stat::error)) {
        status = asm_stat::error;
        RX = ""; dataLengh = 0;
        return status;
    }
    else if (status == asm_stat::done)
        RX = data;  //старое затираем, новое собираем
    else if ((status == asm_stat::wait) ||
             (status == asm_stat::ask_remaining))
        RX += data;

    check_pending(dummy); //сотрем из RX сообщение о пендинг если они есть

    auto temp = (uchar*)RX.data();
    auto dataLengh = temp[0];

    //qDebug() << "dataLengh: " << dataLengh;
    //qDebug() << "RX.length(): " << RX.length();


    if (dataLengh == 0x10) //10 - значит CF-consecutiveFrame
    {
        /*
         RX 10 0B 62 00 07 1F 58 6D
         0B - всего будет 11 байтов включая идентификаторы новой
         строчки, код сервиса и службы
         62 = 40+22 ответ на ReadDataByIdentifier service (ID 0x22)
         0007 - идентификатор. GNSS координаты
         TX "300000AAAAAAAAAA" - запросить весь остаток; or give one part: 300105AAAAAAAAAA
         RX 21 44 2E BF 6C 84 AA AA где 21 - идентификаторы новой
         строки 1. вторая строка, если будет, начнется с 22 и т.д.
        */

        if (RX.size() < 8)
            status = asm_stat::wait;
        else if (RX.size() == 8)
            status = asm_stat::ask_remaining;
        else if (RX.size() > 8)
        {
            //в RX[1] входит 1 байт на сервис 62 + 2 байта на код службы +
            //3 байта данных с первой посылки + по 7 байт с каждой следующей

            uint frame_size = temp[1] + 2; //+2 - учитываем 0х10 и RX[1]
            uint next_string_quantity = (frame_size - 8) / 7; //сколько будет строк, без учета первой строки
            if ((frame_size - 8) % 7) //учтем неполную строку, если есть
                ++next_string_quantity;
            frame_size += next_string_quantity; //учтем начала строк
            uint dummis_quantity = 8 - frame_size % 8;
            if (frame_size % 8)
                frame_size += dummis_quantity; //учитываем заглушки
            //на сервис 62 и 2 байта на код службы
            //всего строк: 1 + (frame_size


            if ((RX.size() < frame_size)){
                status = asm_stat::wait;
                qDebug() << "RX.size() < frame_size";
            }
            else if ((RX.size() > frame_size))
            {
                RX = "";
                qDebug() << "ERROR assembling_answer::recived_data RX.size() > frame_size";
                status = asm_stat::error;
            }
            else {

                //qDebug() << "frame_size: " << frame_size;
                status = asm_stat::done;
                QByteArray temp;
                temp.append(RX[5]);
                temp.append(RX[6]);
                temp.append(RX[7]);

                for (uint i=1; i<=next_string_quantity; ++i){
                    for (uint j=1; j<8; ++j)
                        temp.append(RX[j + i*8]);
                }
                if (dummis_quantity == 8)
                    dummis_quantity = 0;
                temp.chop(dummis_quantity);
                RX = temp;
            }
        }
    }
    else if (RX.size() >= 8){

        if (RX.size() > 8)
            status = asm_stat::error;
        else if (RX.size() < 8)
            status = asm_stat::wait;
        else { //RX.size() == 8
            uint dummis_quantity = 8 - 1 - RX[0];
//            auto RX_hex = (uchar*)RX.data();
////            auto xx = temp[7];
// //           auto yy = dummy.toInt(nullptr, 16);
//           // auto zz = temp[7]

//            for (uint i=0; i<dummis_quantity; i++){
//                if (RX_hex[7-i] != dummy.toInt(nullptr, 16)){
//                    status = asm_stat::error;
//                    return status;
//                }
//            }

            status = asm_stat::done;
            RX.chop(dummis_quantity);
            RX.remove(0, 1);

        }
    }
    else
        status = asm_stat::wait;

    return status;
}

/*
        [1] 7F - error;
        [2] service. обычно ReadDataByIdentifier service (ID 0x22)
        [3] 78 - requestCorrectlyReceived-ResponsePending;
        [3] 21 - busyRepeatRequest
*/


void assembling_answer::check_pending(QString dummy)
{
    if (RX.size() < 8){
        qDebug() << "ERROR. assembling_answer::check_pending. short frame";
        return;
    }

    auto d = dummy.toInt(nullptr, 16);

    while (1)//RX.size() >=8)
    {
        auto temp = (uchar*)RX.data();
        dataLengh = temp[0];

        if (temp[1] == 0x7F)
        {
            for (int i=(dataLengh+1); i<8; ++i)
            {
                if (temp[i] != d){

                    qDebug() << "ERROR. assembling_answer::check_pending. Not dummy";
                    return;
                }
            }

            if (temp[dataLengh] == 0x78){
                //                qDebug() << "133 RX.size() = " << RX.size()
                //                         << "; temp[dataLengh] = " << temp[dataLengh];
                RX = RX.last(RX.size() - 8);
                //RX.shrink_to_fit();
                if (RX.size() < 8)
                    break;
                else
                    continue;
            }
            else
                break;
        }
        break;
    }
}
