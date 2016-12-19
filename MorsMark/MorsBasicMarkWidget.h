#ifndef SMARK_SMK_BASIC_MARK_WIDGET_H
#define SMARK_SMK_BASIC_MARK_WIDGET_H

#include <QPlainTextEdit>
#include "MorsMarkHighlighter.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class MorsBasicMarkWidget
        : public QPlainTextEdit
{
    Q_OBJECT

public:

    explicit MorsBasicMarkWidget(QWidget* parent = 0);

public:

    void updateOption(void);

public:

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int  lineNumberAreaWidth(void);

protected:

    void resizeEvent(QResizeEvent* event);

private slots:

    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine(void);
    void updateLineNumberArea(const QRect &, int);

private:

    QWidget*            pLineNumberArea_;
    MorsMarkHighlighter* pHighlighter_;
};

#endif // SMARK_SMK_BASIC_MARK_WIDGET_H
