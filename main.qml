import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.3
import SpacesListModel 1.0


Window {
    id: root
    height: 480
    title: qsTr("Miner")
    visible: true
    width: 640
    color: "black"

    SpacesListModel {
        id: listModel
        Component.onCompleted: {
            listModel.init()
        }

        onExplode: {
            root.color = "red"
           timer.running = true
        }

    }

    Timer {
        id: timer
        interval: 500
        onTriggered: {
            root.close()
        }
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 20
        columnSpacing: 2
        columns: 8
        rowSpacing: 2
        rows: 8

        Repeater {
            model: listModel

            delegate: Rectangle {
                color: model.isOpen ? "black" : "#4287f5"
                height: 75
                width: 75

                Text {
                    text: model.value === 0 ? "" : model.value
                    anchors.centerIn: parent
                    font.pixelSize: 30
                    font.bold: true
                    color: "white"
                    visible: model.isOpen
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        listModel.openSpace(model.index)
                    }
                }

            }
        }
    }
}
