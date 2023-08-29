#include "connection.h"

#include <QDebug>

connection::connection() //Adapter ad)
    // : adap{ad}
{
    pSystec = new systec;
}



void connection::connect_Adapter(my_car car)
{
    pSystec->connect_Adapter(car);
}


