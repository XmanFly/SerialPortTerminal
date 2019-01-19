import QtQuick 2.4

AFPsForm {
    signal sig_start()
    signal sig_stop()

    startBtn {
        onClicked: {
            sig_start()
        }
    }

    stopBtn {
        onClicked: {
            sig_stop()
        }
    }
}
