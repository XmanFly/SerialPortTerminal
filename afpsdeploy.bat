@echo off
rem 支持中文显示 设为UTF-8
chcp 65001
rem 设置相关路径
set SwName=SerialPortTerminal.exe
set SwPath=C:\D\SerialPortTerminal\bin
set QtMsvcPath="C:\Qt\Qt5.13.0\5.13.0\msvc2017\bin"
set QtQmlPath=C:\Qt\Qt5.13.0\5.13.0\msvc2017\qml
set DeployFolder="Deploy"
rem 设置工作文件夹
cd /d %~dp0
if not exist %DeployFolder% (
	md %DeployFolder%
)
cd %DeployFolder%
set /p fileName=请输入文件名 
echo fileName = %fileName%
if exist %fileName% (
    echo 已经存在文件夹
	rmdir /s/q %fileName%
)
echo 创建文件夹
md %fileName%
cd %fileName%
rem 复制源程序
xcopy %SwPath%\%SwName% .\ /q
rem 加载环境变量
set Path=%Path%;%QtMsvcPath%
rem 复制QtSerialPort.dll
xcopy %QtMingwPath%\Qt5SerialPort.dll .\ /q
rem 复制QtCharts文件夹
xcopy %QtQmlPath%\QtCharts\*.* .\QtCharts\ /e/q
echo QtCharts文件夹复制完成
set xxx=xxx
echo 请等待...
rem release
windeployqt %SwName% --qmldir %QtQmlPath%
echo 部署完成
pause