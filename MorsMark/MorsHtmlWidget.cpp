#include <QTextDocument>
#include "MorsHtmlWidget.h"

#if (QT_VERSION < 0x050000)
#   include <QtWebKit/QWebFrame>
#endif

MorsHtmlWidget::MorsHtmlWidget(QWidget* parent)
    : QWebView(parent) {
}

/* *****************************************************************************
 *
 *                       get context and clear context
 *
 * ****************************************************************************/

void MorsHtmlWidget::clearHtml(void) {
    setHtml(SMK_EMPTY_STR);
    update();
}

/* *****************************************************************************
 *
 *                          synchronized scrolling
 *
 * ****************************************************************************/

int MorsHtmlWidget::scrollValue(void) {
    return page()->mainFrame()->scrollBarValue(Qt::Vertical);
}

void MorsHtmlWidget::setScrollValue(int value) {
    page()->mainFrame()->setScrollBarValue(Qt::Vertical, value);
}

void MorsHtmlWidget::setScrollRatio(float ratio) {
    int maxv = page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    int minv = page()->mainFrame()->scrollBarMinimum(Qt::Vertical);
    page()->mainFrame()->setScrollBarValue(Qt::Vertical,
                                           minv + ratio*(maxv-minv));
}
