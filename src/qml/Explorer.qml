import QtQuick 2.1
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.12
import QtQuick.Dialogs 1.3

Rectangle {

    signal sig_loadFile(var path)
    property var curPath

    RowLayout {
        id: explorLay
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: 50
        Button {
            id: explorBtn
            text: "浏览"            
            onClicked: {
                fds.open()
            }
        }
        Label {
            id: folderPath
            text: fds.fileUrl
            font {
                pixelSize: 25
            }
            color: "blue"
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

    FileDialog {
        id:fds
        title: "选择文件"
        folder: shortcuts.desktop
        selectExisting: true
        selectFolder: true
        selectMultiple: false
        onAccepted: {
            folderPath.text = fds.fileUrl;
            folderModel.folder = fds.fileUrl;
            curPath = fds.fileUrl;
            console.log("You chose: " + fds.fileUrl);
        }

        onRejected: {
            folderPath.text = "";
            console.log("Canceled");
        }
    }

    ListView {
        id: explorList
        anchors {
            top: explorLay.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        FolderListModel {
          id: folderModel
          showDirs: false
          nameFilters: [ "*.csv"]
          sortField: "Time"
        }
        Component {
          id: fileDelegate
          Text {
              id: fileTxt
              text: fileName
              font {
                  pixelSize: 25
              }
              MouseArea {
                anchors.fill: parent
                onClicked: {
                    explorList.currentIndex = index
                    var loadPath = curPath + "/" + fileTxt.text
                    sig_loadFile(loadPath)
                    console.log("load file path " + loadPath)
                }
              }
          }
        }

        model: folderModel
        delegate: fileDelegate
        highlight: highlight
        highlightFollowsCurrentItem: true
        highlightMoveDuration: -1
        highlightMoveVelocity: 20000
        clip: true
        focus: true
        ScrollBar.vertical: ScrollBar {
            id: listVerticalScrBar
            interactive: true
            width: 20
            minimumSize: 0.2
        }
    }
    Component {
      id: highlight
      Rectangle {
          width: explorList.width
          implicitWidth: explorList.width
          Layout.preferredWidth: explorList.width
          color: "lightsteelblue"; radius: 2
          y: explorList.y
          Behavior on y {
              SpringAnimation {
                  spring: 0.01
                  damping: 0.2
              }
          }
      }
    }

    Component.onCompleted: {
    }
}
