#pragma once

#include <QObject>
#include <QTimer>

class logic : public QObject
{
    Q_OBJECT
public:
    explicit logic(QObject *parent = nullptr);
};
