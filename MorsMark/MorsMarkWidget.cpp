
#include "MorsMarkWidget.h"

MorsMarkWidget::MorsMarkWidget(QWidget* parent) :
    MorsBasicMarkWidget(parent)
{
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)),
            this,                SLOT(when_VerticalScrollBar_valueChanged(int)) );
}

/* *****************************************************************************
 *
 *                          synchronized scrolling
 *
 * ****************************************************************************/

float MorsMarkWidget::scrollRatio() {
    QScrollBar* scroll = verticalScrollBar();
    return float(scroll->value()-scroll->minimum())
            / float(scroll->maximum()-scroll->minimum());
}

void MorsMarkWidget::when_VerticalScrollBar_valueChanged(int val) {
    QScrollBar* scroll = verticalScrollBar();
    float ratio = float(val-scroll->minimum())
                  / float(scroll->maximum()-scroll->minimum());
    emit verticalScroll(ratio);
}

/* *****************************************************************************
 *
 *                              find and replace
 *
 * ****************************************************************************/

void MorsMarkWidget::findPrevious(const QString& text, bool cased, bool whole) {
    QTextDocument::FindFlags find_flags;
    find_flags |= QTextDocument::FindBackward;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void MorsMarkWidget::findNext(const QString& text, bool cased, bool whole) {
    QTextDocument::FindFlags find_flags;
    if(cased)
        find_flags |= QTextDocument::FindCaseSensitively;
    if(whole)
        find_flags |= QTextDocument::FindWholeWords;
    this->find(text, find_flags);
}

void MorsMarkWidget::replaceCurrent(const QString& new_text) {
    QTextCursor cursor = this->textCursor();
    cursor.insertText(new_text);
}

void MorsMarkWidget::replaceAll(const QString& old_text,
                               const QString& new_text,
                               bool cased, bool /*whole*/)
{
    // \todo replace all like this can't redo & undo
    Qt::CaseSensitivity cs = cased ? Qt::CaseSensitive : Qt::CaseInsensitive;
    QString context = this->toPlainText();
    context.replace(old_text, new_text, cs);
    this->setPlainText(context);
}

/* *****************************************************************************
 *
 *                              set selected format
 *
 * ****************************************************************************/

void MorsMarkWidget::setSelectedFormat(const QString& before, const QString& after) {
    QTextCursor cursor = this->textCursor();
    QString   selected = cursor.selectedText();
    if(selected.startsWith(before) && selected.endsWith(after)) {
        selected.remove(before);
        selected.remove(after);
    } else {
        selected.prepend(before);
        selected.append(after);
    }
    cursor.insertText(selected);
}

void MorsMarkWidget::setSelectedBlod(void) {
    setSelectedFormat("<b>", "</b>");
}

void MorsMarkWidget::setSelectedItalic(void) {
    setSelectedFormat("<i>", "</i>");
}

void MorsMarkWidget::setSelectedUnderLine(void) {
    setSelectedFormat("<u>", "</u>");
}

void MorsMarkWidget::setSelectedDeleted(void) {
    setSelectedFormat("<del>", "</del>");
}

void MorsMarkWidget::setSelectedQuote(void) {
    QTextCursor cursor = this->textCursor();
    if(cursor.hasSelection()) {
        QString  selected = cursor.selectedText();
        QStringList lines = selected.split(MORS_LINE_END);
        if(lines.size() == 1) {
            setSelectedFormat("<q>", "</q>");
        } else {
            for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
                it->prepend("> ");
            cursor.insertText(lines.join(MORS_LINE_END));
        }
    } // if(cursor.hasSelection())
}

void MorsMarkWidget::setSelectedCode(void) {
    setSelectedFormat("`", "`");
}

void MorsMarkWidget::setSelectedSub(void) {
    setSelectedFormat("<sub>", "</sub>");
}

void MorsMarkWidget::setSelectedSup(void) {
    setSelectedFormat("<sup>", "</sup>");
}

void MorsMarkWidget::setSelectedBigger(void) {
    setSelectedFormat("<big>", "</big>");
}

void MorsMarkWidget::setSelectedSmaller(void) {
    setSelectedFormat("<small>", "</small>");
}

void MorsMarkWidget::setSelectedOrderedList(void) {
    QTextCursor cursor = this->textCursor();
    QString   selected = cursor.selectedText();
    QStringList  lines = selected.split(MORS_LINE_END);
    int list_num = 1;
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it) {
        if(! it->isEmpty()) {
            it->prepend(" " + QString::number(list_num) + ". ");
            ++list_num;
        }
    }
    cursor.insertText(lines.join(MORS_LINE_END));
}

void MorsMarkWidget::setSelectedUnorderedList(void) {
    QTextCursor cursor = this->textCursor();
    QString selected =  cursor.selectedText();
    QStringList lines = selected.split(MORS_LINE_END);
    for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
        if(! it->isEmpty()) it->prepend(" + ");
    cursor.insertText(lines.join(MORS_LINE_END));
}

void MorsMarkWidget::setSelectedLeftAlign(void) {
    setSelectedFormat("<p align=left>", "</p>");
}

void MorsMarkWidget::setSelectedRightAlign(void) {
    setSelectedFormat("<p align=right>", "</p>");
}

void MorsMarkWidget::setSelectedCenterAlign(void) {
    setSelectedFormat("<center>", "</center>");
}

/* *****************************************************************************
 *
 *                        insert context template
 *
 * ****************************************************************************/

void MorsMarkWidget::insertImage(void) {
    QTextCursor cursor = this->textCursor();
    cursor.insertText("<p align=\"center\">\n"
                      "    <img src=\"____\" width=\"60%\">\n"
                      "    <br />"
                      "    <small> tittle </small>\n"
                      "</p>");
}

void MorsMarkWidget::insertLink(void) {
    QTextCursor cursor = this->textCursor();
    QString selected   = cursor.selectedText();
    if(selected.isEmpty()) {
        cursor.insertText("[___](___)");
    } else {
        selected.prepend("[");
        selected.append("](____)");
        cursor.insertText(selected);
    }
}

void MorsMarkWidget::insertMathJax(void) {
    QTextCursor cursor = this->textCursor();
    QString   selected = cursor.selectedText();
    if(cursor.atBlockStart()) {
        // the cursor is at the start of a block
        // insert a center align math formation
        if(selected.isEmpty()) {
            cursor.insertText("<center>$$\n"
                              "____\n"
                              "$$</center>");
        } else {
            selected.prepend("<center>$$\n");
            selected.append("$$</center>");
            cursor.insertText(selected);
        }
    } else {
        // the cursor is not at the start of a block
        // insert a inline math formation
        if(selected.isEmpty()) {
            cursor.insertText("${  }$");
        } else {
            selected.prepend("${ ");
            selected.append(" }$");
            cursor.insertText(selected);
        }
    }//if(cursor.atBlockStart()...
}

/* *****************************************************************************
 *
 *                              event porcess
 *
 * ****************************************************************************/

void MorsMarkWidget::keyPressEvent(QKeyEvent* event)
{
    // switch tab char to spaces
    if(event->key() == Qt::Key_Tab) {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection()) {
            QString  selected = cursor.selectedText();
            QStringList lines = selected.split(MORS_LINE_END);
            bool inverse_operation = (event->modifiers() & Qt::ControlModifier) ||
                                     (event->modifiers() & Qt::ShiftModifier);
            if( inverse_operation ) {
                // [Ctrl + Tab] or [Shift + Tab], remove an indentation
                for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
                    if(it->startsWith("    ")) it->remove(0, 4);
            } else {
                // Only Tab, add an indentation
                for(QStringList::iterator it=lines.begin(); it!=lines.end(); ++it)
                    if(! it->isEmpty()) it->prepend("    ");
            }
            cursor.insertText(lines.join(MORS_LINE_END));
        } else { // if(cursor.hasSelection())
            // Just insert a '\t', but we replace '\t' as "    "
            cursor.insertText("    ");
        } // if(cursor.hasSelection())
        return;
    }
    MorsBasicMarkWidget::keyPressEvent(event);
}
