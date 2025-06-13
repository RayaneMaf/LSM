import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

Window {
    id: root
    width: 1280
    height: 720
    minimumWidth: 1280
    minimumHeight: 720
    visible: true
    title: qsTr("Library")

    ColumnLayout{
        anchors.fill: parent
        anchors.leftMargin: parent.width * 0.04
        anchors.rightMargin: parent.width * 0.04
        anchors.topMargin: parent.height * 0.05
        anchors.bottomMargin: parent.height * 0.05
        spacing: parent.height * 0.05

        Rectangle{
            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.08
            color: "#CADED7"
            radius: 20

            Rectangle{
                height: root.height * 0.06
                width: root.height * 0.2
                radius: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.height * 0.09

                property bool hovered: false

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered:  parent.hovered = true
                    onExited:   parent.hovered = false
                }

                color: hovered ? "#143842" : "#31606B"
            }
            Rectangle{
                height: root.height * 0.07
                width: root.height * 0.07
                radius: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: parent.height * 0.09

                property bool hovered: false

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered:  parent.hovered = true
                    onExited:   parent.hovered = false
                }

                color: hovered ? "#143842" : "#31606B"
            }
        }

        Rectangle{
            id: main
            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.77
            color: "#EFF4EE"
            radius : 20

            Rectangle{
                id: kk
                height: parent.height * 0.95
                width: parent.width * 0.65
                radius: 20
                color: "#CADED7"
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: parent.height * 0.025



                RowLayout{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 10
                    anchors.bottomMargin: 10
                    spacing: parent.width * 0.05

                    Rectangle{
                        Layout.preferredHeight: kk.height * 0.09
                        Layout.preferredWidth: kk.width * 0.2
                        radius: 20

                        property bool hovered: false

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered:  parent.hovered = true
                            onExited:   parent.hovered = false
                        }

                        color: hovered ? "#143842" : "#31606B"
                    }
                    Rectangle{
                        Layout.preferredHeight: kk.height * 0.09
                        Layout.preferredWidth: kk.width * 0.2

                        radius: 20

                        property bool hovered: false

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onEntered:  parent.hovered = true
                            onExited:   parent.hovered = false
                        }

                        color: hovered ? "#143842" : "#31606B"
                    }
                     Item { Layout.fillWidth: true }
                }
            }
            Rectangle{
                height: parent.height * 0.95
                width: parent.width * 0.3
                radius: 20
                color: "#CADED7"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: parent.height * 0.025
            }

        }
    }


}
