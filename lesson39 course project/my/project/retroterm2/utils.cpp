#pragma once
#include <QDebug>
#include <QString>

namespace utils {

uchar *from_string_to_uchar(QString data) //always 16
{
    bool success = false;
    static uchar X[] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (size_t i = 0; i < 16; i += 2) {
        QString d = data[i];
        d += data[i + 1];
        X[i / 2] = d.toInt(&success, 16);
    }
    if (!success)
        qDebug() << "ERROR utils: " << __LINE__;
    return X;
}
} // namespace utils
