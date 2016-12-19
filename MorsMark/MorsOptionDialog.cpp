#include "MorsApp.h"
#include "MorsOptionDialog.h"
#include "ui_MorsOptionDialog.h"

MorsOptionDialog::MorsOptionDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::MorsOptionDialog)
{
    ui->setupUi(this);
    initGui();
}

MorsOptionDialog::~MorsOptionDialog() {
    delete ui;
    delete pHighlighter_[0];
    delete pHighlighter_[1];
    delete pHighlighter_[2];
    delete pHighlighter_[3];
}

void MorsOptionDialog::initGui()
{
    // Gui Style
    QString         style = qMorsApp()->option("gui.style");
    QStringList styleList = QStyleFactory::keys();
    ui->comboBoxGuiStyle->clear();
    ui->comboBoxGuiStyle->addItems(styleList);
    ui->comboBoxGuiStyle->setCurrentIndex(styleList.indexOf(style));

    // Font Options
    QStringList fontFamily = qMorsApp()->option("font.family").split(",");
    if(fontFamily.size() == 2) {
        ui->comboBoxEnglishFont->setCurrentFont(QFont(fontFamily[0]));
        ui->comboBoxChineseFont->setCurrentFont(QFont(fontFamily[1]));
    } else if(fontFamily.size() == 1) {
        ui->comboBoxEnglishFont->setCurrentFont(QFont(fontFamily[0]));
        ui->comboBoxChineseFont->setCurrentFont(QFont(fontFamily[0]));
    }
    ui->spinBoxFontSize->setValue(qMorsApp()->option("font.size").toInt());

    // Syntax Color
    ui->listColor->clear();
    ui->listColor->setFont(QFont(qMorsApp()->option("font.family"),
                                 qMorsApp()->option("font.size").toInt()));
    QListWidgetItem* pItem = NULL;

    pItem = new QListWidgetItem("Background");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.foreground")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Foreground");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.foreground")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Focusline");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.focusline")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.foreground")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Focusword");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.focusword")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.foreground")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Header");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.header")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Code");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.code")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Latex");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.latex")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("HTML");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.html")));
    ui->listColor->addItem(pItem);

    pItem = new QListWidgetItem("Link");
    pItem->setBackgroundColor(QColor(qMorsApp()->option("color.background")));
    pItem->setTextColor(QColor(qMorsApp()->option("color.link")));
    ui->listColor->addItem(pItem);

    // URL setting
    QString cssURL = qMorsApp()->option("url.css");
    if(QFileInfo(cssURL).exists()==false && cssURL.startsWith("http")==false) {
        // 如果 cssURL 不存在则将其标记为红色
        QPalette palette = ui->lineEditCSSURL->palette();
        palette.setColor(QPalette::Text, Qt::red);
        ui->lineEditCSSURL->setPalette(palette);
    }
    if(cssURL.startsWith(qMorsApp()->applicationDirPath()))
        cssURL.replace(qMorsApp()->applicationDirPath(), ".");
    ui->lineEditCSSURL->setText(cssURL);

    QString mathJaxURL = qMorsApp()->option("url.mathjax");
    if(QFileInfo(mathJaxURL).exists()==false && mathJaxURL.startsWith("http")==false) {
        // 如果 MathJaxURL 不存在则将其标记为红色
        QPalette palette = ui->lineEditMathJaxURL->palette();
        palette.setColor(QPalette::Text, Qt::red);
        ui->lineEditMathJaxURL->setPalette(palette);
    }
    if(mathJaxURL.startsWith(qMorsApp()->applicationDirPath()))
        mathJaxURL.replace(qMorsApp()->applicationDirPath(), ".");
    ui->lineEditMathJaxURL->setText(mathJaxURL);

    // context setting
    ui->textEditHeader->setPlainText(qMorsApp()->option("text.head"));
    ui->textEditHat->setPlainText(qMorsApp()->option("text.hat"));
    ui->textEditTail->setPlainText(qMorsApp()->option("text.tail"));
    ui->textEditFoot->setPlainText(qMorsApp()->option("text.foot"));

    pHighlighter_[0] = new MorsHtmlHighlighter(ui->textEditHeader->document());
    pHighlighter_[1] = new MorsHtmlHighlighter(ui->textEditHat->document());
    pHighlighter_[2] = new MorsHtmlHighlighter(ui->textEditTail->document());
    pHighlighter_[3] = new MorsHtmlHighlighter(ui->textEditFoot->document());
}

void MorsOptionDialog::on_comboBoxGuiStyle_currentIndexChanged(const QString& style) {
    qMorsApp()->setStyle(style);
}

void MorsOptionDialog::on_comboBoxEnglishFont_currentFontChanged(const QFont& font) {
    QFont currentFont = font;
    currentFont.setPointSize(ui->spinBoxFontSize->value());
    ui->listColor->setFont(currentFont);
}

void MorsOptionDialog::on_spinBoxFontSize_valueChanged(int fontSize) {
    QFont currentFont = ui->comboBoxEnglishFont->font();
    currentFont.setPointSize(fontSize);
    ui->listColor->setFont(currentFont);
}

void MorsOptionDialog::on_listColor_itemDoubleClicked(QListWidgetItem* pItem)
{
    QString text = pItem->text();
    if(text == "Background" || text == "Focusline" || text == "Focusword") {
        // 选择背景色
        QColor color = pItem->backgroundColor();
        color = QColorDialog::getColor(color,
                                       this,
                                       tr("Choose Color for ") + text);
        if(! color.isValid()) return;
        pItem->setBackgroundColor(color);
        if(text == "Background") {
            // 需要更新整体的背景色
            for(int i=0; i<ui->listColor->count(); i++) {
                if(ui->listColor->item(i)->text() != "Focusword" &&
                   ui->listColor->item(i)->text() != "Focusline" ) {
                    ui->listColor->item(i)->setBackgroundColor(color);
                }
            }//for..
        }//if(..
    } else {
        // 选择前景色
        QColor color = pItem->textColor();
        color = QColorDialog::getColor(color,
                                       this,
                                       tr("Choose Color for ") + text);
        if(! color.isValid()) return;
        pItem->setTextColor(color);
        if(text == "Foreground") {
            // 需要更新整体的前景色
            for(int i=0; i<ui->listColor->count(); i++) {
                if(ui->listColor->item(i)->text() == "Background" ||
                   ui->listColor->item(i)->text() == "Focusword" ||
                   ui->listColor->item(i)->text() == "Focusline" ) {
                    ui->listColor->item(i)->setTextColor(color);
                }
            }//for..
        }//if(..
    }
    update();
}

void MorsOptionDialog::on_buttonCSSURL_clicked() {
    QString path = QFileDialog::getOpenFileName(
                       this,
                       trUtf8("Choose Style Sheet File URL"),
                       qMorsApp()->applicationDirPath(),
                       trUtf8("Style Sheeet (*.css)") );
    if(path.isEmpty()) return;
    if(path.startsWith(qMorsApp()->applicationDirPath()))
        path.replace(qMorsApp()->applicationDirPath(), ".");
    ui->lineEditCSSURL->setText(path);
}

void MorsOptionDialog::on_buttonMathJaxURL_clicked() {
    QString path = QFileDialog::getOpenFileName(
                       this,
                       trUtf8("Choose MathJax File URL"),
                       qMorsApp()->applicationDirPath(),
                       trUtf8("JavaScript (*.js)") );
    if(path.isEmpty()) return;
    if(path.startsWith(qMorsApp()->applicationDirPath()))
        path.replace(qMorsApp()->applicationDirPath(), ".");
    ui->lineEditMathJaxURL->setText(path);
}

void MorsOptionDialog::on_buttonBox_accepted()
{
    // gui color options
    qMorsApp()->setOption("gui.style", ui->comboBoxGuiStyle->currentText());
    qMorsApp()->setOption("font.size", QString::number(ui->spinBoxFontSize->value()));
    QString fontFamily = ui->comboBoxEnglishFont->currentFont().family() + "," +
                         ui->comboBoxChineseFont->currentFont().family();
    qMorsApp()->setOption("font.family",  fontFamily);

    // syntax color options
    for(int i=0; i<ui->listColor->count(); i++) {
        QListWidgetItem* pItem = ui->listColor->item(i);
        if(pItem->text() == "Background")
            qMorsApp()->setOption("color.background", pItem->backgroundColor().name());
        else if(pItem->text() == "Foreground")
            qMorsApp()->setOption("color.foreground", pItem->textColor().name());
        else if(pItem->text() == "Focusline")
            qMorsApp()->setOption("color.focusline", pItem->backgroundColor().name());
        else if(pItem->text() == "Focusword")
            qMorsApp()->setOption("color.focusword", pItem->backgroundColor().name());
        else if(pItem->text() == "Header")
            qMorsApp()->setOption("color.header", pItem->textColor().name());
        else if(pItem->text() == "Code")
            qMorsApp()->setOption("color.code", pItem->textColor().name());
        else if(pItem->text() == "Latex")
            qMorsApp()->setOption("color.latex", pItem->textColor().name());
        else if(pItem->text() == "HTML")
            qMorsApp()->setOption("color.html", pItem->textColor().name());
        else if(pItem->text() == "Link")
            qMorsApp()->setOption("color.link", pItem->textColor().name());
    }//for..

    // mathjax url options
    QString mathJaxURL = ui->lineEditMathJaxURL->text();
    if(mathJaxURL.startsWith("./"))
        mathJaxURL.replace(0, 1, qMorsApp()->applicationDirPath());
    qMorsApp()->setOption("url.mathjax", mathJaxURL);

    // CSS url options
    QString cssURL = ui->lineEditCSSURL->text();
    if(cssURL.startsWith("./"))
        cssURL.replace(0, 1, qMorsApp()->applicationDirPath());
    qMorsApp()->setOption("url.css", cssURL);

    // context options
    qMorsApp()->setOption("text.head",   ui->textEditHeader->toPlainText());
    qMorsApp()->setOption("text.hat",    ui->textEditHat->toPlainText());
    qMorsApp()->setOption("text.tail",   ui->textEditTail->toPlainText());
    qMorsApp()->setOption("text.foot",   ui->textEditFoot->toPlainText());
}

void MorsOptionDialog::on_lineEditCSSURL_textEdited(const QString& arg) {
    QString url = arg;
    if(url.startsWith("./"))
        url.replace(0, 1, qMorsApp()->applicationDirPath());
    if(QFileInfo(url).exists() || url.startsWith("http")) {
        // 如果 url 对应的文件存在或为在线文件则恢复其为默认颜色
        QPalette palette = this->palette();
        ui->lineEditCSSURL->setPalette(palette);
    } else {
        // 如果 url 对应的文件不存在则将其标记为红色
        QPalette palette = ui->lineEditCSSURL->palette();
        palette.setColor(QPalette::Text, Qt::red);
        ui->lineEditCSSURL->setPalette(palette);
    }
}

void MorsOptionDialog::on_lineEditMathJaxURL_textEdited(const QString& arg) {
    QString url = arg;
    if(url.startsWith("./"))
        url.replace(0, 1, qMorsApp()->applicationDirPath());
    if(QFileInfo(url).exists() || url.startsWith("http")) {
        // 如果 url 对应的文件存在或为在线文件则恢复其为默认颜色
        QPalette palette = this->palette();
        ui->lineEditCSSURL->setPalette(palette);
    } else {
        // 如果 url 对应的文件不存在则将其标记为红色
        QPalette palette = ui->lineEditCSSURL->palette();
        palette.setColor(QPalette::Text, Qt::red);
        ui->lineEditCSSURL->setPalette(palette);
    }
}

void MorsOptionDialog::on_buttonDefault_clicked() {
    // 恢复默认设置
    qMorsApp()->loadDefaultOption();
    initGui();
}
