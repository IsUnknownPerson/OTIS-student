#pragma once

/*
enum class example_MouseButtons : int { LEFT_BTN = 1,
                                MIDDLE_BTN = 3,
                                RIGHT_BTN = 2,
                                EXTRA_BTN = 0 };
example_MouseButtons mouse_btn = example_MouseButtons::EXTRA_BTN;
*/

enum class directives : int {
    Connection,
    DTC,

    //GNSS
    GNSS_realibility,
    GNSS_coordinates,
    //GNSS

    //TCU_Info
    ICCIDG,
//    SW,
//    Vehicle_SW,
//    Midlet_SW,
//    Boot_SW
    SW_Version,
    Vehicle_SW_Version,
    Midlet_SW_Version,
    Boot_SW_Version


    //TCU_Info
};

enum class from_gui : int {
    buttonConect,
    buttonDisconect,
    buttonStart_Log,
    buttonStop_Log
};

enum {
    none,
    No_adapter, //1
    Adapter_port_disconnected,
    Adapter_port_bisy,
    Adapter_is_configuring,
    Adapter_error,
    Adapter_configured,  //6
    Adapter_reset,

    //adapter -->
    adapter_connect,
    adapter_connected,
    adapter_disconnect,
    adapter_disconected,
    check_TCU_presence,
    TCU_online,
    TCU_offline,
    UDS_answer,
    Adapter_RX,
    Adapter_TX,
    set_car,
    grey_box,
    systec,
    fixic
    //<-- adapter


};

enum class uds_task : int {
    none,

    //directives -->
    clear_permanent_quares,
    single_command, //send comand, dont't need unswer
    single_request,
    single_triple_request,
    permanent_request,
    //<-- directives

    //commands -->
    keep_alive,
    ICCIDG,
    DTC,

    SW_Version,
    Vehicle_SW_Version,
    Midlet_SW_Version,
    Boot_SW_Version,

    //GNSS_set,
    gnss_coords,
    gnss_reliability,

    //Info
//    SW,
//    Vehicle_SW,
//    Midlet_SW,
//    Boot_SW
    //Info
    //<-- commands
};

