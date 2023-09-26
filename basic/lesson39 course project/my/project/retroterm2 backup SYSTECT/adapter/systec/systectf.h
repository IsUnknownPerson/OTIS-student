#ifndef SYSTECT_H
#define SYSTECT_H

#include <QObject>
#include "i_adapter.h"
#include "Usbcan32.h"
#include "save_transcriotion.h"

class Systect : public i_can_adapter
{
	Q_OBJECT
	friend void PUBLIC UcanCallbackFktEx (tUcanHandle UcanHandle_p, DWORD dwEvent_p, BYTE bChannel_p, void* pArg_p);
public:
	explicit Systect(QObject *parent = nullptr);
	~Systect();
signals:


	// i_adapter interface
public slots:
	void initialize() override;

public:
	save_array read(unsigned size) override;
	save_array readALL() override;
	bool write(const save_array &buf) override;
	void close() override;
	unsigned bytesAvailable() override;


	bool WriteWithID(DWORD id, const save_array &buf);
private:
	void appenedFrame(/*const save_array &f*/);

signals:
	void NewData();

private:
//	SystecMonitor monitor;
	tUcanHandle m_UcanHandle;
	tUcanInitCanParam   InitParam;

	bool size_rx_and_tx;
	DWORD tx;
	DWORD rx;

	save_transcriotion global_buf;
	uchar bRet;
	QTimer timer;
//	QThread readThread;
//	HANDLE ReadCanMsg;
//	save_transcriotion global_buf;
//	bool wait_condition = true;

	// i_adapter interface
public:
	void ClearBuf() override;
};

#endif // SYSTECT_H
