#pragma once
#include <QObject>

enum class asm_stat : int {
    wait,
    done,
    ask_remaining,
    error
};

class assembling_answer : public QObject
{
    Q_OBJECT
public:
    explicit assembling_answer(QObject *parent = nullptr);

    asm_stat recived_data(QByteArray, QString dummy);
    QByteArray get_answer(); //send answer and reset this

private:
    void check_pending(QString dummy);

    QByteArray RX = "";
    int dataLengh = 0;
    asm_stat status = asm_stat::done;
};

