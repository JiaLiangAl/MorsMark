#ifndef MORSHTMLHIGHLIGHTER_H
#define MORSHTMLHIGHLIGHTER_H

#include <QTextCharFormat>
#include <QSyntaxHighlighter>
#include "MorsConfig.h"

class MorsHtmlHighlighter : public QSyntaxHighlighter
{

private:
    QHash<int,QColor> colors_;

public:
    explicit MorsHtmlHighlighter(QTextDocument* document);

protected:
    virtual void highlightBlock(const QString& text);
};

#endif // MORSHTMLHIGHLIGHTER_H
