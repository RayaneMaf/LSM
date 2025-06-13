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

    // Mock authentication manager - replace with your actual authentication class
    QtObject {
        id: authManager

        property string username: ""
        property string password: ""
        property string newEmail: ""
        property string newPassword: ""
        property string newPasswordConfirm: ""
        property string errorMessage: ""
        property string currentUserId: ""
        property bool isLoggedIn: false

        signal loginSuccessful()
        signal loginFailed(string message)
        signal signUpSuccessful()
        signal signUpFailed(string message)

        function login() {
            errorMessage = ""

            // Basic validation
            if (username.trim() === "" || password.trim() === "") {
                errorMessage = "Please enter both username and password"
                loginFailed(errorMessage)
                return
            }

            // Simulate authentication - replace with actual authentication logic
            // For demo purposes, accept any non-empty credentials
            if (username.length > 0 && password.length > 0) {
                currentUserId = username
                isLoggedIn = true
                errorMessage = ""
                loginSuccessful()
            } else {
                errorMessage = "Invalid username or password"
                loginFailed(errorMessage)
            }
        }

        function signUp() {
            errorMessage = ""

            // Validation
            if (username.trim() === "") {
                errorMessage = "Username is required"
                signUpFailed(errorMessage)
                return
            }

            if (newEmail.trim() === "") {
                errorMessage = "Email is required"
                signUpFailed(errorMessage)
                return
            }

            if (newPassword.trim() === "") {
                errorMessage = "Password is required"
                signUpFailed(errorMessage)
                return
            }

            if (newPassword !== newPasswordConfirm) {
                errorMessage = "Passwords do not match"
                signUpFailed(errorMessage)
                return
            }

            // Email validation
            var emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/
            if (!emailRegex.test(newEmail)) {
                errorMessage = "Please enter a valid email address"
                signUpFailed(errorMessage)
                return
            }

            // Password strength validation
            if (newPassword.length < 6) {
                errorMessage = "Password must be at least 6 characters long"
                signUpFailed(errorMessage)
                return
            }

            // Simulate successful signup
            errorMessage = "Account created successfully! Please log in."
            signUpSuccessful()
        }

        function clearFields() {
            username = ""
            password = ""
            newEmail = ""
            newPassword = ""
            newPasswordConfirm = ""
            errorMessage = ""
        }
    }

    // Handle authentication events
    Connections {
        target: authManager
        function onLoginSuccessful() {
            console.log("Login successful for user:", authManager.currentUserId)
            // Add navigation logic here - e.g., load main application window
            // mainWindow.show()
            // root.close()
        }

        function onLoginFailed(message) {
            console.log("Login failed:", message)
        }

        function onSignUpSuccessful() {
            // Switch back to login page after successful signup
            stack.currentIndex = 0
        }

        function onSignUpFailed(message) {
            console.log("Sign up failed:", message)
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Left side - decorative panel
        Rectangle {
            Layout.preferredHeight: root.height
            Layout.preferredWidth: root.width * 0.6
            color: "#EFF4EE"

            // You can add a logo or decorative elements here
            Text {
                anchors.centerIn: parent
                text: "📚"
                font.pointSize: 72
                color: "#143842"
                opacity: 0.3
            }
        }

        // Right side - login/signup forms
        Rectangle {
            Layout.preferredHeight: root.height
            Layout.preferredWidth: root.width * 0.4
            color: "white"

            Text {
                id: welcome
                text: qsTr("Welcome")
                font.bold: true
                font.pointSize: root.height * 0.065
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 40
                color: "#143842"
            }

            StackLayout {
                id: stack
                anchors.fill: parent
                anchors.topMargin: welcome.height + 80
                currentIndex: 0

                // ────────────────────────
                // 1) LOGIN PAGE
                // ────────────────────────
                Item {
                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 20
                        width: parent.width * 0.8

                        Text {
                            text: "Login"
                            font.pointSize: root.height * 0.05
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillWidth: true
                            color: "#143842"
                        }

                        // Error message display
                        Text {
                            text: authManager.errorMessage
                            color: "red"
                            font.pointSize: root.height * 0.025
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillWidth: true
                            visible: authManager.errorMessage !== ""
                            wrapMode: Text.WordWrap
                        }

                        TextField {
                            id: usernameField
                            placeholderText: "Username"
                            text: authManager.username
                            onTextChanged: authManager.username = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }
                        }

                        TextField {
                            id: passwordField
                            placeholderText: "Password"
                            echoMode: TextInput.Password
                            text: authManager.password
                            onTextChanged: authManager.password = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }

                            // Allow Enter key to trigger login
                            Keys.onReturnPressed: loginButton.clicked()
                            Keys.onEnterPressed: loginButton.clicked()
                        }

                        Button {
                            id: loginButton
                            text: "Log In"
                            Layout.fillWidth: true
                            Layout.preferredHeight: root.height * 0.06
                            onClicked: authManager.login()

                            background: Rectangle {
                                color: parent.pressed ? "#0f2c36" : "#143842"
                                radius: 20
                            }

                            contentItem: Text {
                                text: parent.text
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.bold: true
                                font.pointSize: 12
                            }
                        }

                        Button {
                            text: "Create New Account"
                            Layout.fillWidth: true
                            Layout.preferredHeight: root.height * 0.06
                            onClicked: {
                                authManager.clearFields()
                                stack.currentIndex = 1
                            }

                            background: Rectangle {
                                color: parent.pressed ? "#d4e5d3" : "transparent"
                                radius: 20
                                border.color: "#143842"
                                border.width: 2
                            }

                            contentItem: Text {
                                text: parent.text
                                color: "#143842"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.bold: true
                                font.pointSize: 12
                            }
                        }
                    }
                }

                // ─────────────────────────────
                // 2) CREATE NEW ACCOUNT PAGE
                // ─────────────────────────────
                Item {
                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 16
                        width: parent.width * 0.8

                        Text {
                            text: "Sign Up"
                            font.pointSize: root.height * 0.05
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillWidth: true
                            color: "#143842"
                        }

                        // Error/Success message display
                        Text {
                            text: authManager.errorMessage
                            color: authManager.errorMessage.includes("successful") ? "green" : "red"
                            font.pointSize: root.height * 0.025
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillWidth: true
                            visible: authManager.errorMessage !== ""
                            wrapMode: Text.WordWrap
                        }

                        TextField {
                            placeholderText: "Username"
                            text: authManager.username
                            onTextChanged: authManager.username = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }
                        }

                        TextField {
                            placeholderText: "Email"
                            text: authManager.newEmail
                            onTextChanged: authManager.newEmail = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }
                        }

                        TextField {
                            placeholderText: "Password"
                            echoMode: TextInput.Password
                            text: authManager.newPassword
                            onTextChanged: authManager.newPassword = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }
                        }

                        TextField {
                            placeholderText: "Confirm Password"
                            echoMode: TextInput.Password
                            text: authManager.newPasswordConfirm
                            onTextChanged: authManager.newPasswordConfirm = text

                            Layout.preferredWidth: parent.width
                            Layout.preferredHeight: root.height * 0.06
                            Layout.alignment: Qt.AlignHCenter

                            font.pointSize: 12

                            background: Rectangle {
                                anchors.fill: parent
                                color: "#EFF4EE"
                                radius: 20
                                border.width: parent.activeFocus ? 2 : 0
                                border.color: "#143842"
                            }

                            // Allow Enter key to trigger signup
                            Keys.onReturnPressed: signUpButton.clicked()
                            Keys.onEnterPressed: signUpButton.clicked()
                        }

                        Button {
                            id: signUpButton
                            text: "Sign Up"
                            Layout.fillWidth: true
                            Layout.preferredHeight: root.height * 0.06
                            onClicked: authManager.signUp()

                            background: Rectangle {
                                color: parent.pressed ? "#0f2c36" : "#143842"
                                radius: 20
                            }

                            contentItem: Text {
                                text: parent.text
                                color: "white"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.bold: true
                                font.pointSize: 12
                            }
                        }

                        Button {
                            text: "Back to Login"
                            Layout.fillWidth: true
                            Layout.preferredHeight: root.height * 0.06
                            onClicked: {
                                authManager.clearFields()
                                stack.currentIndex = 0
                            }

                            background: Rectangle {
                                color: parent.pressed ? "#d4e5d3" : "transparent"
                                radius: 20
                                border.color: "#143842"
                                border.width: 2
                            }

                            contentItem: Text {
                                text: parent.text
                                color: "#143842"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                font.bold: true
                                font.pointSize: 12
                            }
                        }
                    }
                }
            }
        }
    }
}
