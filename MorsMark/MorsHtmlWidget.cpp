#include <QTextDocument>
#include "MorsHtmlWidget.h"


MorsHtmlWidget::MorsHtmlWidget(QWidget* parent)
    : QWebEngineView(parent) {
}

/* *****************************************************************************
 *
 *                       get context and clear context
 *
 * ****************************************************************************/

void MorsHtmlWidget::clearHtml(void) {
    setHtml(MORS_EMPTY_STR);
    update();
}

/* *****************************************************************************
 *
 *                          synchronized scrolling
 *
 * ****************************************************************************/

int MorsHtmlWidget::scrollValue(void) {
    return 0;
    //return page()->mainFrame()->scrollBarValue(Qt::Vertical);
}

void MorsHtmlWidget::setScrollValue(int value) {
    //page()->mainFrame()->setScrollBarValue(Qt::Vertical, value);


}

void MorsHtmlWidget::setScrollRatio(float ratio) {
    //int maxv = page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    //int minv = page()->mainFrame()->scrollBarMinimum(Qt::Vertical);
    //page()->mainFrame()->setScrollBarValue(Qt::Vertical,
                                          // minv + ratio*(maxv-minv));
}
