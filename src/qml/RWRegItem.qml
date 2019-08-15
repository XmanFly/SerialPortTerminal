import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import RequestStyle 1.0
import RegReadWriteModel 1.0

Item {
    width: 600
    height: 40

    RowLayout {
        id: rootLayout
        anchors.fill: parent
        spacing: 40

        Text {
            text: name
            Layout.preferredWidth: 200
        }
    }

    Component.onCompleted: {        
        //创建设置值控件
        createSetControl()
        //创建读取设置值控件
        createReadSetControl()
        //创建读取实时值控件
        createReadRealControl()
    }

    //创建float设置值控件
    function createSetControl(){
        if(floatW !== null){
            //float型
            if(valueType === RegReadWriteModel.FLOAT) {
                var setFloatItem = Qt.createComponent("RegSetFloatItem.qml");
                var setFloatObj = setFloatItem.createObject(rootLayout );
                if (setFloatObj !== null) {
                    setFloatObj.msgTxt.text = Qt.binding(function() { return floatW.dbgMsg } )
                    setFloatObj.msgTxt.color = Qt.binding(function() { return getMsgColor(floatW.state) } )
                    setFloatObj.setBtn.enabled = Qt.binding(function() { return getIsEnable(floatW.state) } )
                    setFloatObj.setBtn.clicked.connect(function() { floatW.writeSync(parseFloat(setFloatObj.input.text)) })
                } else {
                    console.log("Error creating setFloatItem");
                }
            }            
        }
        if(u8W !== null){
            //bool型
            if(valueType === RegReadWriteModel.BOOL){
                var setBoolItem = Qt.createComponent("RegSetBoolItem.qml");
                var setBoolObj = setBoolItem.createObject(rootLayout );
                if (setBoolObj !== null) {
                    setBoolObj.msgTxt.text = Qt.binding(function() { return u8W.dbgMsg } )
                    setBoolObj.msgTxt.color = Qt.binding(function() { return getMsgColor(u8W.state) } )
                    setBoolObj.input.enabled = Qt.binding(function() { return getIsEnable(u8W.state) } )
                    setBoolObj.input.clicked.connect(function() { u8W.writeSync(setBoolObj.input.checked)})
                    console.log("creating setBoolItem success ");
                } else {
                    console.log("Error creating setBoolItem");
                }
            }
        }
    }

    //创建读取设置值控件
    function createReadSetControl(){
         if(floatRSet !== null){
            //float型
            if(valueType === RegReadWriteModel.FLOAT) {
                var readSetFloatItem = Qt.createComponent("RegReadFloatItem.qml");
                var readSetFloatObj = readSetFloatItem.createObject(rootLayout );
                if (readSetFloatObj !== null) {
                    readSetFloatObj.value.text = Qt.binding(function() { return floatRSet.value.toFixed(1)} )
                    readSetFloatObj.msgTxt.text = Qt.binding(function() { return floatRSet.dbgMsg } )
                    readSetFloatObj.msgTxt.color = Qt.binding(function() { return getMsgColor(floatRSet.state) } )
                    readSetFloatObj.readBtn.enabled = Qt.binding(function() { return getIsEnable(floatRSet.state) } )
                    readSetFloatObj.readBtn.clicked.connect(floatRSet.readSync)
                    readSetFloatObj.readBtn.text = qsTr("读设置值")
                } else {
                    console.log("Error creating readSetFloatItem");
                }
            }
        }
        if(u8RSet !== null){
            //bool型
            if(valueType === RegReadWriteModel.BOOL){
                var readSetBoolItem = Qt.createComponent("RegReadBoolItem.qml");
                var readSetBoolObj = readSetBoolItem.createObject(rootLayout );
                if (readSetBoolObj !== null) {
                    readSetBoolObj.value.checked = Qt.binding(function() { return u8RSet.value > 0.5} )
                    readSetBoolObj.msgTxt.text = Qt.binding(function() { return u8RSet.dbgMsg } )
                    readSetBoolObj.msgTxt.color = Qt.binding(function() { return getMsgColor(u8RSet.state) } )
                    readSetBoolObj.readBtn.enabled = Qt.binding(function() { return getIsEnable(u8RSet.state) } )
                    readSetBoolObj.readBtn.clicked.connect(u8RSet.readSync)
                    readSetBoolObj.readBtn.text = qsTr("读设置值")
                } else {
                    console.log("Error creating readSetBoolItem");
                }
            }
        }
    }

    //创建读取实时值控件
    function createReadRealControl(){
         if(floatRReal !== null){
            //float型
            if(valueType === RegReadWriteModel.FLOAT) {
                var readRealFloatItem = Qt.createComponent("RegReadFloatItem.qml");
                var readRealFloatObj = readRealFloatItem.createObject(rootLayout );
                if (readRealFloatObj !== null) {
                    readRealFloatObj.value.text = Qt.binding(function() {
                                                    return floatRReal.value.toFixed(1)
                                                    } )
                    readRealFloatObj.msgTxt.text = Qt.binding(function() { return floatRReal.dbgMsg } )
                    readRealFloatObj.msgTxt.color = Qt.binding(function() { return getMsgColor(floatRReal.state) } )
                    readRealFloatObj.readBtn.enabled = Qt.binding(function() { return getIsEnable(floatRReal.state) } )
                    readRealFloatObj.readBtn.clicked.connect(floatRReal.readSync)
                    readRealFloatObj.readBtn.text = qsTr("读实时值")
                } else {
                    console.log("Error creating readRealFloatItem");
                }
            }
        }
         if(u8RReal !== null){
            //U8型
            if(valueType === RegReadWriteModel.U8) {
                var readRealU8Item = Qt.createComponent("RegReadFloatItem.qml");
                var readRealU8Obj = readRealU8Item.createObject(rootLayout );
                if (readRealU8Obj !== null) {
                    readRealU8Obj.value.text = Qt.binding(function() {
                                                    return u8RReal.value
                                                    } )
                    readRealU8Obj.msgTxt.text = Qt.binding(function() { return u8RReal.dbgMsg } )
                    readRealU8Obj.msgTxt.color = Qt.binding(function() { return getMsgColor(u8RReal.state) } )
                    readRealU8Obj.readBtn.enabled = Qt.binding(function() { return getIsEnable(u8RReal.state) } )
                    readRealU8Obj.readBtn.clicked.connect(u8RReal.readSync)
                    readRealU8Obj.readBtn.text = qsTr("读实时值")
                } else {
                    console.log("Error creating readRealFloatItem");
                }
            }
            //bool型
            if(valueType === RegReadWriteModel.BOOL){
                var readRealBoolItem = Qt.createComponent("RegReadBoolItem.qml");
                var readRealBoolObj = readRealBoolItem.createObject(rootLayout );
                if (readRealBoolObj !== null) {
                    readRealBoolObj.value.checked = Qt.binding(function() { return u8RReal.value > 0.5} )
                    readRealBoolObj.msgTxt.text = Qt.binding(function() { return u8RReal.dbgMsg } )
                    readRealBoolObj.msgTxt.color = Qt.binding(function() { return getMsgColor(u8RReal.state) } )
                    readRealBoolObj.readBtn.enabled = Qt.binding(function() { return getIsEnable(u8RReal.state) } )
                    readRealBoolObj.readBtn.clicked.connect(u8RReal.readSync)
                    readRealBoolObj.readBtn.text = qsTr("读实时值")
                } else {
                    console.log("Error creating readRealBoolItem");
                }
            }
         }
    }

    function getMsgColor(state){
        var color
        switch(state){
        case RequestStyle.READY :
        case RequestStyle.IN_PROCESS:
            color = "black"
            break;
        case RequestStyle.RESPONSED:
            color = "green"
            break;
        case RequestStyle.TIMEOUT:
        case RequestStyle.ERROR_ST:
            color = "red"
            break;
        }
        return color
    }

    function getIsEnable(state){
        var isEnable
        switch(state){
        case RequestStyle.IN_PROCESS:
            isEnable = false
            break
        case RequestStyle.READY :
        case RequestStyle.RESPONSED:
        case RequestStyle.TIMEOUT:
        case RequestStyle.ERROR_ST:
            isEnable = true
            break;
        }
        return isEnable
    }
}
