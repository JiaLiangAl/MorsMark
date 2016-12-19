#include "MorsMainWindow.h"
#include "ui_morsmainwindow.h"

MorsMainWindow::MorsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MorsMainWindow)
{
    ui->setupUi(this);
}

MorsMainWindow::~MorsMainWindow()
{
    delete ui;
}
