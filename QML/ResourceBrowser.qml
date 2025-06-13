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

            ColumnLayout{


                anchors.fill: main
                anchors.leftMargin: main.width * 0.03
                anchors.rightMargin: main.width * 0.03
                anchors.topMargin: main.height * 0.05
                anchors.bottomMargin: main.height * 0.05
                spacing: main.height * 0.05

                Rectangle{
                    Layout.preferredHeight: main.height * 0.1
                    Layout.fillWidth: true
                    color: "#31606B"
                    radius : 20

                    Rectangle{
                        width: parent.width * 0.15
                        height: parent.height * 0.8
                        color: "#CADED7"
                        radius : 20
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.leftMargin: parent.height * 0.1
                    }
                    Rectangle{
                        width: parent.width * 0.4
                        height: parent.height * 0.8
                        color: "#CADED7"
                        radius : 20
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: parent.height * 0.1

                    }
                }
                Rectangle{
                    Layout.preferredHeight: main.height * 0.75
                    Layout.fillWidth: true
                    color: "transparent"
                    radius : 20

                    RowLayout{
                        anchors.fill: parent
                        spacing: parent.width * 0.04
                        Rectangle{
                            id : main1
                            Layout.fillHeight: true
                            Layout.preferredWidth: parent.width * 0.92
                            color: "transparent"
                            radius: 20
                            RowLayout{
                                anchors.fill: main1
                                spacing: main1.width * 0.0285
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                                Rectangle{
                                    Layout.preferredWidth: main1.width * 0.1
                                    Layout.preferredHeight: main1.height * 0.35
                                    color: "#31606B"
                                    radius: 20
                                }
                            }


                        }
                        Rectangle{
                            Layout.fillHeight: true
                            Layout.preferredWidth: parent.width * 0.04
                            color: "#31606B"
                            radius: 20

                        }
                    }
                }
            }

        }
    }


}
