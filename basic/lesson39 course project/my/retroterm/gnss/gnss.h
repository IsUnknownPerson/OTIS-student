#pragma once

#include <QObject>


class gnss : public QObject
{
    Q_OBJECT

public:
    explicit gnss(QObject *parent = nullptr);

    static QString check_reliability(QByteArray data, int dummy);
    static QString get_coordinates(QByteArray data, int dummy);
};
