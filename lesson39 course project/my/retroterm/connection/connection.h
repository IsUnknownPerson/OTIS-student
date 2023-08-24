#pragma once
#include "definitions.h"
#include "greyBox.h"
#include "UDS/executer_uds.h"

#include <QString>


class connection : public QObject
{    
    Q_OBJECT
public:
    explicit connection(QObject *parent = nullptr);
    void from_logic(int cmd, QByteArray data);
    void make_query(uds_task directiv, uds_task cmd);
    void clear_query();

signals:
    void to_logic(int cmd, QString data);
    void adapterTX(QByteArray data);

public slots:
    void from_adapter(int cmd, QByteArray data);
    void from_executer(int cmd, QString);

private:
    int adapter_type = none;
    int adapter_status = No_adapter;


    greyBox *pAdapter;
    //systec *pSystec
    QMetaObject::Connection signal_slot_forAdapter;

    executer_uds *pExecuter;
};

