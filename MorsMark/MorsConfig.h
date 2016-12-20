#ifndef MORSCONFIG_H
#define MORSCONFIG_H

#include <QString>
#include <QtCore>
#include <QtGui>
//#include <QDebug>

#include <QtWidgets>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#define MORS_VERSION "mors 1.0.0"

#ifdef _WIN32
# define MORS_WINDOWS_PLATFORM
#endif

const QChar   MORS_LINE_END(L'\u2029');
const QString MORS_EMPTY_STR("");
#define MORS_EMPTY_STR MORS_EMPTY_STR
#define MORS_LINE_END  MORS_LINE_END

#endif // MORSCONFIG_H
