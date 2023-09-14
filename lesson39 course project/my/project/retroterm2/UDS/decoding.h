#pragma once

#include "config.h"
#include <QObject>

class decoding : public QObject
{
    Q_OBJECT
public:
    explicit decoding(QObject *parent = nullptr);

    QString decoding_answer(QByteArray *, uds_task);

signals:

};

