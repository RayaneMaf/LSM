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



    ColumnLayout {
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
            Layout.fillWidth: true
            Layout.preferredHeight: root.height * 0.77
            color: "transparent"

            RowLayout{
                spacing: root.width * 0.04
                anchors.fill: parent
                Rectangle{
                Layout.fillHeight: true
                color: "#143842"
                Layout.preferredWidth: root.width * 0.28
                radius: 20
                }
                Rectangle{

                    Layout.fillHeight: true
                    color: "transparent"
                    Layout.preferredWidth: root.width * 0.6
                    ColumnLayout {
                        anchors.fill: parent
                        spacing: root.height * 0.05
                        Rectangle{
                            id: hello
                            Layout.fillWidth: true
                            //color: "#31606B"
                            Layout.preferredHeight: root.height * 0.22
                            radius: 20

                            property bool hovered: false

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onEntered:  parent.hovered = true
                                onExited:   parent.hovered = false
                            }

                            color: hovered ? "#143842" : "#31606B"

                            Row{
                                anchors.centerIn: parent



                                spacing: 15
                                Text {

                                    text: qsTr("Search")
                                    font.family: "Helvetica"
                                    font.pixelSize: hello.height * 0.4
                                    font.bold : true
                                    color: "#CADED7"
                                }


                            }
                        }
                        Rectangle{
                            Layout.fillWidth: true
                            color: "transparent"
                            Layout.preferredHeight: root.height * 0.5
                            GridLayout {
                                anchors.fill: parent
                                columns: 2
                                rows: 2
                                rowSpacing: root.height * 0.05
                                columnSpacing: root.width * 0.04
                                Rectangle{
                                    id: hi
                                    Layout.row: 0
                                    Layout.column: 0
                                    //Layout.preferredHeight: root.height * 0.225
                                    //Layout.preferredWidth: root.width * 0.28
                                    color: "#CADED7"
                                    radius: 20

                                    property bool hovered: false


                                      Behavior on Layout.preferredWidth {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }
                                      Behavior on Layout.preferredHeight {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered:  parent.hovered = true
                                        onExited:   parent.hovered = false
                                    }

                                    Layout.preferredHeight: hovered ? root.height * 0.235 : root.height * 0.225
                                    Layout.preferredWidth: hovered ? root.width * 0.29 : root.width * 0.28


                                    Row{
                                        anchors.centerIn: parent



                                        spacing: 15
                                        Text {

                                            text: qsTr("Notifications")
                                            font.family: "Helvetica"
                                            font.pixelSize: hi.height * 0.3
                                            font.bold : true
                                            color: "#31606B"
                                        }




                                    }
                                }
                                Rectangle{
                                    Layout.row: 0
                                    Layout.column: 1
                                    //Layout.preferredHeight: root.height * 0.225
                                    //Layout.preferredWidth: root.width * 0.28
                                    color: "#CADED7"
                                    radius: 20

                                    property bool hovered: false


                                      Behavior on Layout.preferredWidth {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }
                                      Behavior on Layout.preferredHeight {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered:  parent.hovered = true
                                        onExited:   parent.hovered = false
                                    }

                                    Layout.preferredHeight: hovered ? root.height * 0.235 : root.height * 0.225
                                    Layout.preferredWidth: hovered ? root.width * 0.29 : root.width * 0.28

                                    Row{
                                        anchors.centerIn: parent



                                        spacing: 15
                                        Text {

                                            text: qsTr("My History")
                                            font.family: "Helvetica"
                                            font.pixelSize: hi.height * 0.3
                                            font.bold : true
                                            color: "#31606B"
                                        }


                                    }
                                }
                                Rectangle{
                                    Layout.row: 1
                                    Layout.column: 0
                                    //Layout.preferredHeight: root.height * 0.225
                                    //Layout.preferredWidth: root.width * 0.28
                                    color: "#CADED7"
                                    radius: 20

                                    property bool hovered: false


                                      Behavior on Layout.preferredWidth {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }
                                      Behavior on Layout.preferredHeight {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered:  parent.hovered = true
                                        onExited:   parent.hovered = false
                                    }

                                    Layout.preferredHeight: hovered ? root.height * 0.235 : root.height * 0.225
                                    Layout.preferredWidth: hovered ? root.width * 0.29 : root.width * 0.28
                                    Row{
                                        anchors.centerIn: parent


                                        spacing: 15
                                        Text {

                                            text: qsTr("Events")
                                            font.family: "Helvetica"
                                            font.pixelSize: hi.height * 0.3
                                            font.bold : true
                                            color: "#31606B"
                                        }


                                    }
                                }
                                Rectangle{
                                    Layout.row: 1
                                    Layout.column: 1
                                    //Layout.preferredHeight: root.height * 0.225
                                    //Layout.preferredWidth: root.width * 0.28
                                    color: "#CADED7"
                                    radius: 20

                                    property bool hovered: false


                                      Behavior on Layout.preferredWidth {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }
                                      Behavior on Layout.preferredHeight {
                                          NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
                                      }

                                    MouseArea {
                                        anchors.fill: parent
                                        hoverEnabled: true
                                        onEntered:  parent.hovered = true
                                        onExited:   parent.hovered = false
                                    }

                                    Layout.preferredHeight: hovered ? root.height * 0.235 : root.height * 0.225
                                    Layout.preferredWidth: hovered ? root.width * 0.29 : root.width * 0.28

                                    Row{
                                        anchors.centerIn: parent


                                        spacing: 15
                                        Text {

                                            text: qsTr("SOON")
                                            font.family: "Helvetica"
                                            font.pixelSize: hi.height * 0.4
                                            font.bold : true
                                            color: "#31606B"
                                        }


                                    }
                                }
                            }
                        }



                    }
                }


            }
        }
    }





}
