#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#include <QtGlobal>

#ifdef Q_OS_WIN32

#include <Windows.h>
#include <DbgHelp.h>


extern "C" LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException); //程式异常捕获


#endif // CRASHHANDLER_H

#endif
