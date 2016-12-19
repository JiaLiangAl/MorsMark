#ifndef MORS_OPTION_DIALOG_H
#define MORS_OPTION_DIALOG_H

#include "MorsConfig.h"
#include "MorsHtmlHighlighter.h"

namespace Ui {
    class MorsOptionDialog;
}

class MorsOptionDialog : public QDialog
{
    Q_OBJECT

public:

    explicit MorsOptionDialog(QWidget *parent = 0);
    ~MorsOptionDialog();

public:

    void initGui();

private slots:

    void on_comboBoxGuiStyle_currentIndexChanged(const QString&);
    void on_comboBoxEnglishFont_currentFontChanged(const QFont&);
    void on_spinBoxFontSize_valueChanged(int);
    void on_listColor_itemDoubleClicked(QListWidgetItem*);
    void on_buttonCSSURL_clicked();
    void on_buttonMathJaxURL_clicked();
    void on_buttonBox_accepted();
    void on_lineEditCSSURL_textEdited(const QString& arg);
    void on_lineEditMathJaxURL_textEdited(const QString& arg);
    void on_buttonDefault_clicked();
private:

    Ui::MorsOptionDialog* ui;
    MorsHtmlHighlighter*  pHighlighter_[4];
};

#endif // SMARK_SMK_OPTION_DIALOG_H
