import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    ListModel
    {
        id: pathsModel
        ListElement
        {
            path:"/qml/tmp/"
        }
        ListElement
        {
            path:"/qml/bin/"
        }
        ListElement
        {
            path:"/qml/src/"
        }
    }

    ListView
    {
        id: pathView
        anchors.left: parent.left
        anchors.top : parent.top
        anchors.bottom: parent.bottom
        width: parent.width /2
        model: pathsModel

        delegate: Text {
            text: path
        }

        function getFilesPaths()
        {
            console.log('called')
            var result = [];
            for (var row = 0; row < model.rowCount(); row++){
                result.push(model.get(row).path);
            }
            return result;
        }

        function setFilesPaths(value)
        {}

        Component.onCompleted: {
            Object.defineProperty(
                pathView,
                "filesPaths",
                {
                    get: function () {
                        return getFilesPaths()
                    },
                    set: function (value) {
                        setFilesPaths(value)
                    }
                }
            );
        }
    }

    Rectangle
    {
        color: "green"
        anchors.right: parent.right
        anchors.top : parent.top
        anchors.bottom: parent.bottom
        width: parent.width /2

        Button
        {
            anchors.centerIn: parent
            text: "browse!!!!"
            onClicked:
            {
                var data = pathView.filesPaths
                console.log(data)
            }
        }
    }
}
