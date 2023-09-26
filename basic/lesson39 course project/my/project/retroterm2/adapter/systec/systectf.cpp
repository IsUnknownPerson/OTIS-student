#include "systectf.h"

Systect::Systect(QObject *parent)
    : i_can_adapter{parent}
{
    this->speed = Speed_Can::speed_500_KBaud;
    timer.setParent(this);
    tx = 0x7CA;
    rx = 0xCDA;
    size_rx_and_tx = false;
    memset(&InitParam, 0, sizeof(tUcanInitCanParam));
    m_UcanHandle = 0;
    InitParam.m_dwSize = sizeof(InitParam); // size of this struct
    InitParam.m_bMode = kUcanModeNormal;    // normal operation mode
    InitParam.m_bOCR = USBCAN_OCR_DEFAULT;  // 0x1A;
    //	InitParam.m_dwAMR                = USBCAN_AMR_ALL;               // receive all CAN messages
    //	InitParam.m_dwACR                = USBCAN_ACR_ALL;

    //	InitParam.m_wNrOfRxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;
    //	InitParam.m_wNrOfTxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;

    //	connect(&monitor, &SystecMonitor::readyRead, this, &Systect::readyRead, Qt::DirectConnection);
    //	connect(&readThread, &QThread::started, &monitor, &SystecMonitor::run);
    //	monitor.moveToThread(&readThread);
    UcanInitHwConnectControlEx(UcanConnectControlFktEx, (void *) this);
    bRet = ::UcanInitHardwareEx(&m_UcanHandle, USBCAN_ANY_MODULE, NULL, NULL);

    qDebug() << "UcanHandle " << m_UcanHandle;
    qDebug() << "UcanInitHardwareEx " << bRet;
    connect(this, &Systect::NewData, this, &Systect::appenedFrame, Qt::QueuedConnection); //not used
    connect(&timer, &QTimer::timeout, this, &Systect::appenedFrame);
}

extern "C" void PUBLIC UcanConnectControlFktEx(DWORD dwEvent_p, DWORD dwParam_p, void *pArg_p)
{

    Systect *a = (Systect *) (pArg_p);
    switch (dwEvent_p) {
    // new USB-CANmodul connected
    case USBCAN_EVENT_CONNECT:
        qDebug() << "USBCAN_EVENT_CONNECT";
        //        a->
        //            pEventWnd->PostMessage (WM_UCAN_CONNECT, (WPARAM) dwParam_p, 0);
        break;

    // an other USB-CANmodul disconnected
    case USBCAN_EVENT_DISCONNECT:
        emit a->disconnection();
        qDebug() << "USBCAN_EVENT_DISCONNECT";
        //            pEventWnd->PostMessage (WM_UCAN_DISCONNECT, (WPARAM) dwParam_p, 0);
        break;

    // an used USB-CANmodul disconnected
    case USBCAN_EVENT_FATALDISCON:
         emit a->disconnection();
        qDebug() << "USBCAN_EVENT_FATALDISCON";
        //            pEventWnd->PostMessage (WM_UCAN_FATAL_DISCONNECT, (WPARAM) dwParam_p, 0);
        break;

    // unknown event
    default:
        break;
    }
}

extern "C" void PUBLIC UcanCallbackFktEx(tUcanHandle UcanHandle_p,
                                         DWORD dwEvent_p,
                                         BYTE bChannel_p,
                                         void *pArg_p)
{


    Systect *pEventWnd = (Systect *) pArg_p;

    //	ASSERT (pEventWnd != NULL);

    //----------------------------------------------------------------------------
    // NOTE:
    // Do not call functions of USBCAN32.DLL directly from this callback handler.
    // Use events or windows messages to notify the event to the application.
    //----------------------------------------------------------------------------

    // check event
    //	qDebug() <<"Event " <<  dwEvent_p;
    switch (dwEvent_p) {
    // hardware initialized
    case USBCAN_EVENT_INITHW:
        emit pEventWnd->message("the USB-CANmodul has been initialized");
        break;

    // CAN interface initialized
    case USBCAN_EVENT_INITCAN:
        emit pEventWnd->message("the CAN interface has been initialized");
        break;

    // CAN message received
    case USBCAN_EVENT_RECEIVE:

    {
        emit pEventWnd->NewData();

        //		qDebug() <<"USBCAN_EVENT_RECEIVE " << buf.byte_in_string();
        //			emit pEventWnd->message();

        break;
    }
    // status message received
    case USBCAN_EVENT_STATUS:
        //		UcanResetCan(pEventWnd->m_UcanHandle);
        //		if (pEventWnd != NULL) pEventWnd->PostMessage(WM_UCAN_STATUS, (WPARAM)UcanHandle_p, 0);
        break;

    // CAN interface deinitialized
    case USBCAN_EVENT_DEINITCAN:
        emit pEventWnd->message(("CAN interface deinitialized"));
        emit pEventWnd->disconnection();
        break;

    // hardware deinitialized
    case USBCAN_EVENT_DEINITHW:
        emit pEventWnd->message(("USBCAN_EVENT_DEINITHW"));
        emit pEventWnd->disconnection();
        break;
    case USBCAN_EVENT_DISCONNECT:
        emit pEventWnd->message(("USBCAN_EVENT_DISCONNECT"));
        emit pEventWnd->disconnection();
        break;
    case USBCAN_EVENT_FATALDISCON:
        emit pEventWnd->message(("USBCAN_EVENT_FATALDISCON"));
        emit pEventWnd->disconnection();
        break;
    // unknown event
    default:
        emit pEventWnd->disconnection();
        break;
    }
}

Systect::~Systect()
{
    //	monitor.close();
    //	readThread.quit();

    ::UcanDeinitHwConnectControl();
    ::UcanDeinitHardware(m_UcanHandle);
    /*	readThread.wait()*/;
}

void translate(DWORD &v, const save_array &r)
{
    DWORD test;
    uchar *temp = (uchar *) &test;
    temp[3] = r[1];
    temp[2] = r[2];
    temp[1] = r[3];
    temp[0] = r[4];
    v = test;
}

void Systect::initialize()
{
    if (bRet) {
        emit message("Ошибка подключения. Переподключите систек и перезапустите программу");
        emit StatusInitialize(false);
        return;
    }
    close();

    if (speed == Speed_Can::speed_500_KBaud) {
        InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUD_500kBit);
        InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUD_500kBit);
        //			InitParam.m_bBTR0  = 1;
    } else if (speed == Speed_Can::speed_250_KBaud) {
        InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUD_250kBit);
        InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUD_250kBit);

    } else if (speed == Speed_Can::speed_1_MBaud) {
        InitParam.m_bBTR0 = HIBYTE(USBCAN_BAUD_1MBit);
        InitParam.m_bBTR1 = LOBYTE(USBCAN_BAUD_1MBit);
    }
    size_rx_and_tx = can_id[0][0];
    translate(tx, can_id[0]);
    translate(rx, can_id[1]);

    qDebug() << "m_bBTR0 " << InitParam.m_bBTR0;
    qDebug() << "m_bBTR1 " << InitParam.m_bBTR1;

    InitParam.m_dwAMR = USBCAN_CALCULATE_AMR(size_rx_and_tx, tx, rx, false, false);
    InitParam.m_dwACR = USBCAN_CALCULATE_ACR(size_rx_and_tx, tx, rx, false, false);
    InitParam.m_dwBaudrate = USBCAN_BAUDEX_USE_BTR01;
    InitParam.m_wNrOfRxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;
    InitParam.m_wNrOfTxBufferEntries = USBCAN_DEFAULT_BUFFER_ENTRIES;

    if (::UcanInitCanEx(m_UcanHandle, &InitParam) != USBCAN_SUCCESSFUL)
        emit StatusInitialize(false);
    //	ReadCanMsg = CreateEvent(NULL, TRUE, FALSE, NULL);
    //	readThread.start();
    //	start();
    _isWork = true;
    qDebug() << rx;
    qDebug() << tx;
    timer.start(5);
    QTimer::singleShot(10, this, [&] { emit StatusInitialize(true); });
}

save_array Systect::read(unsigned size)
{
    if (global_buf.size() < size)
        return global_buf.read_all();
    return global_buf.mid(0, size);
}

save_array Systect::readALL()
{
    return global_buf.read_all();
}

bool Systect::write(const save_array &buf)
{
    tCanMsgStruct w;
    memset(&w, 0, sizeof(tCanMsgStruct));
    //	w.m_bDLC = size;
    w.m_bFF = can_id[0][0] ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD;
    w.m_dwID = tx;
    //	w.m_dwTime = 50;

    unsigned local_size;
    auto size = buf.size();

    auto p = (uchar *) buf.u_data();
    //		qDebug() <<"UcanHandle write" <<  m_UcanHandle;
    //	UcanResetCanEx(m_UcanHandle, USBCAN_CHANNEL_CH0, USBCAN_RESET_ONLY_ALL_BUFF);
    //		ResetEvent(ReadCanMsg);
    while (size) {
        if (size >= 8)
            local_size = 8;
        else
            local_size = size;
        w.m_bDLC = local_size;
        memmove(w.m_bData, p, local_size);

        DWORD ub = 1;
        auto bRet = ::UcanWriteCanMsgEx(m_UcanHandle, 0, &w, &ub);
        //		qDebug() << "UcanWriteCanMsgEx " << bRet;
        if (bRet != USBCAN_SUCCESSFUL) {
            return false;
        }
        size -= local_size;
        p += local_size;
    }

    return true;
}

void Systect::close()
{
    //	monitor.close();
    timer.stop();
    ::UcanDeinitCan(m_UcanHandle);
    emit disconnection();
    // deinitialize hardware
    //	::UcanDeinitHardware (m_UcanHandle);
}

unsigned Systect::bytesAvailable()
{
    return global_buf.size();
}

bool Systect::WriteWithID(DWORD id, const save_array &buf)
{
    tCanMsgStruct w;
    memset(&w, 0, sizeof(tCanMsgStruct));
    //	w.m_bDLC = size;
    w.m_bFF = can_id[0][0] ? USBCAN_MSG_FF_EXT : USBCAN_MSG_FF_STD;
    w.m_dwID = id;
    //	w.m_dwTime = 50;

    unsigned local_size;
    auto size = buf.size();

    auto p = (uchar *) buf.u_data();
    //		qDebug() <<"UcanHandle write" <<  m_UcanHandle;
    //	UcanResetCanEx(m_UcanHandle, USBCAN_CHANNEL_CH0, USBCAN_RESET_ONLY_ALL_BUFF);
    //		ResetEvent(ReadCanMsg);
    while (size) {
        if (size >= 8)
            local_size = 8;
        else
            local_size = size;
        w.m_bDLC = local_size;
        memmove(w.m_bData, p, local_size);

        DWORD ub = 1;
        auto bRet = ::UcanWriteCanMsgEx(m_UcanHandle, 0, &w, &ub);
        //		qDebug() << "UcanWriteCanMsgEx " << bRet;
        if (bRet != USBCAN_SUCCESSFUL) {
            return false;
        }
        size -= local_size;
        p += local_size;
    }

    return true;
}

void Systect::appenedFrame()
{
    //в случае дисконектов и т.п.   //Считывать пока они не закончаться, прежде чем идти дальше
    // но это не точно
    tCanMsgStruct msg;
    int bRet = 0;
    bRet = UcanReadCanMsg(m_UcanHandle, &msg);
    //		qDebug() <<"UcanReadCanMsg " <<  bRet;
    if (bRet == USBCAN_WARN_NODATA)
        return;
    if (bRet != USBCAN_SUCCESSFUL) {
        //		emit message(("Ошибка чтения"));
        return;
    }
    auto pMsg_ln = msg.m_bDLC;
    save_array buf;
    buf.resize(pMsg_ln);
    memmove(buf.data(), msg.m_bData, pMsg_ln);
    if (buf.size()) {
        global_buf.appened(buf);
        emit readyRead();
    }
}

void Systect::ClearBuf()
{
    global_buf.clear();
}
