import QtQuick

import QtQuick.Layouts


Rectangle{
    id: root
    Layout.fillHeight: true
    Layout.fillWidth: true

    implicitWidth:  text1.implicitWidth > text2.implicitWidth ?
                        text1.implicitWidth : text2.implicitWidth
    implicitHeight: text1.implicitHeight > text2.implicitHeight ?
                        text1.implicitHeight : text2.implicitHeight

    anchors.margins: win.defLayoutMargin
    border.width: win.defLayoutBorderWidth
    border.color: win.defLayoutBorderColor
    color: "transparent"

    //    Item {
    //        id: statuses
    //        //property string adapterText
    //        property string TCUText: "-"
    //    }



    //    function getAdapterStatus() {
    //        if (logic.QMLconnection === "Адаптер занят")
    //            return "yellow";
    //        else if (logic.QMLconnection === "Адаптер настраивается")
    //            return "greenyellow";
    //        else if (logic.QMLconnection === "Адаптер соединен")
    //            return "greenyellow"
    //        else if (logic.QMLconnection === "Адаптер работает")
    //            return "green"
    //        else if (logic.QMLconnection === "БЭГ работает")
    //            return "green"
    //        else if (logic.QMLconnection === "БЭГ не отвечает")
    //            return "red"
    //        else
    //            return "red"
    //    }

    //    function getTCU_Status() {
    //        if (logic.QMLconnection === "БЭГ работает")
    //            return "green"
    //        else
    //            return "red"
    //    }


    //    function logicData() {
    //        if (logic.QMLconnection)
    //            return logic.QMLconnection;
    //        else
    //            return "2" //logic.QMLconnection
    //    }

    //property string adapterText
    //property string TCUText: "-"
    function dataAboutAdapter(){
        if (logic.QMLconnection === "Адаптер занят"){
            //adapterText = logic.QMLconnection;
            return "yellow";
        }
        else if (logic.QMLconnection === "Адаптер настраивается"){
            //adapterText = logic.QMLconnection;
            return "greenyellow";
        }
        else if (logic.QMLconnection === "Адаптер соединен") {
            //adapterText = logic.QMLconnection;
            return "greenyellow"
        }
        else if (logic.QMLconnection === "Адаптер работает") {
            //adapterText = logic.QMLconnection;
            return "greenyellow"
        }
        else if (logic.QMLconnection === "БЭГ работает"){
            //TCUText = logic.QMLconnection;
            return "green"
        }
        else if (logic.QMLconnection === "БЭГ не отвечает"){
            //TCUText = logic.QMLconnection;
            return "red"
        }

        else if ((logic.QMLconnection === "Адаптера нет") ||
                 (logic.QMLconnection === "Адаптер отключен") ||
                 (logic.QMLconnection === "Адаптер не отвечает")) {
            //adapterText = logic.QMLconnection;
            //TCUText = "БЭГ не отвечает";
            return "red"
        }
    }


    function dataAboutTCU(){
        if (logic.QMLconnection === "БЭГ работает"){
            //TCUText = logic.QMLconnection;
            return "green"
        }
        else if (logic.QMLconnection === "БЭГ не отвечает"){
            //TCUText = logic.QMLconnection;
            return "red"
        }
    }





    //    property variant adapterStatus: data.split("^_adapter_^")
    //    property variant tcu_status: data.split("^_TCU _^")

    ColumnLayout{
        spacing: win.defElementsSpacing
        anchors.fill: parent
        Layout.fillHeight: true
        Layout.fillWidth: true
        anchors.margins: win.defElementsMargin

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.width: win.defElementsBorderWidth
            border.color: win.defElementsBorderColor
            color: dataAboutAdapter()
            Text{
                id: text1
                font.pointSize: win.defBigElementsFontSise
                color: win.defElementsTextColor
                anchors.centerIn: parent
                text: logic.QMLconnection //.split("^_adapter_^")
                //text: "HelloHelloHello"; fontSizeMode: Text.Fit; minimumPixelSize: 10; font.pixelSize: 72
            }
        }
        /*
    Rectangle {
        Layout.fillHeight: true
        Layout.fillWidth: true
        border.color: win.defElementsBorderColor
        color: dataAboutTCU()
        Text{
            id: text2
            font.pointSize: win.defBigElementsFontSise
            color: win.defElementsTextColor
            anchors.centerIn: parent
            text: logic.QMLconnection  //"TCUText"//logic.QMLconnection//logicData() //.split("^_TCU _^")
        }
    }
    */
    }
}

