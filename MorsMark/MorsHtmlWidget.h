#ifndef MORS_HTML_WIDGET_H
#define MORS_HTML_WIDGET_H

#include <QtWebEngineWidgets/QWebEngineView>
#include "MorsConfig.h"
#pragma comment(lib,"Qt5Widgets.lib")
#pragma comment(lib,"Qt5WebEngineWidgets.lib")
class MorsHtmlWidget: public QWebEngineView
{
    Q_OBJECT

public:

    explicit MorsHtmlWidget(QWidget *parent = 0);

/* *****************************************************************************
 *
 *                       get context and clear context
 *
 * ****************************************************************************/

public:

    // clear html context
    void clearHtml(void);

/* *****************************************************************************
 *
 *                          synchronized scrolling
 *
 * ****************************************************************************/

public:

    // synchronized scrolling
    int scrollValue(void);
    void setScrollValue(int value);

public slots:

    void setScrollRatio(float ratio);

};

#endif // SMARK_SMK_HTML_WIDGET_H
