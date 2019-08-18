#include "crashhandler.h"

#include <QTime>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QtGlobal>

#ifdef Q_OS_WIN32

LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException){//程式异常捕获
    /*
      ***保存数据代码***
    */
    //创建 Dump 文件
    HANDLE hDumpFile = CreateFile((LPCWSTR)(QTime::currentTime().toString("HH_mm_ss_zzz")+QString("_ms")+QString(".dmp")).utf16(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if( hDumpFile != INVALID_HANDLE_VALUE){
        //Dump信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //写入Dump文件内容
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    }
    //这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16));
    QString errAdr(QString::number((uint)record->ExceptionAddress,16));
    QString errThread(QString::number((uint)(GetCurrentThreadId()),16));
    qDebug() << "错误线程id " << QThread::currentThread();
    QMessageBox::critical(NULL,"程式崩溃","对于发生的错误，表示诚挚的歉意\r\n"+
        QString("错误代码:%1 \r\n错误地址:%2 \r\n线程id: %3 ").arg(errCode).arg(errAdr).arg(errThread),
        QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}


#endif
