#pragma once

#include <QObject>
#include "save_array.h"

/*
 * При создание класса должна происходить попытка открытия
 * connect открывает устройства
*/
enum class debug
{
	OF,
	ON,
};

enum Speed_Can : char
{
	speed_250_KBaud,
	speed_500_KBaud,
	speed_1_MBaud
};

class i_adapter : public QObject
{
	Q_OBJECT
public:
	explicit i_adapter(QObject *parent = nullptr) : QObject(parent)
	{
		qRegisterMetaType <save_array>("save_array");
		param = debug :: OF;
		_isWork = false;
	}
public slots:
	virtual void initialize() = 0;
public:
	virtual save_array read(unsigned size = 0) = 0;
	virtual save_array readALL() = 0;
//	virtual int usual_read(save_array &buf, unsigned size) = 0;
	virtual bool write(const save_array &buf) = 0;
	virtual void close() = 0; /*закрыть устройство*/

//	virtual bool read_connect_status() const {return connect_status;}
	virtual void ClearBuf()  = 0;/*очистить буфер если есть такая возможность*/
//	void set_time_out(int time_out) {this->time_out = time_out;}
	debug ContolDebug() const {return param;}
	void SetDebug(debug param){this->param = param;}
	virtual unsigned bytesAvailable() = 0; /*если программа использует програмный буфер то вернет доступное количество байт*/
	bool isWork() const {return _isWork;}
signals:
	void message(QString);
	void disconnection(); /*Сигнал о отключение*/
	void readyRead(); /*есть новые устройства*/
	void StatusInitialize(bool); /*статус инциализации*/
protected:
	debug param;
	bool _isWork;
};

class i_can_adapter : public i_adapter
{
	Q_OBJECT
public:
	explicit i_can_adapter(QObject *parent = nullptr) : i_adapter(parent)
	{
		can_id = {
			{0, 0x00, 0x00, 0x07, 0xca},
			{0, 0x00, 0x00, 0x07, 0xda}
		};
		speed = Speed_Can::speed_250_KBaud;

	}
	virtual void setSpeedCan(Speed_Can speed) {this->speed = speed;}
	virtual void SetCanId(const QVector<save_array> &can_id) {this->can_id = can_id;}
protected:
	Speed_Can speed;
	QVector<save_array> can_id;
};

