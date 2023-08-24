#pragma once

#include <QObject>

class dtc_diagnostictroublecodes : public QObject
{
        Q_OBJECT
public:
    explicit dtc_diagnostictroublecodes(QObject *parent = nullptr);

    static QString DTC(QByteArray data, int dummy);

private:
    static QString parse_code(const QByteArray);
};

