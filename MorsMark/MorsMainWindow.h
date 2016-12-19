#ifndef MORSMAINWINDOW_H
#define MORSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MorsMainWindow;
}

class MorsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MorsMainWindow(QWidget *parent = 0);
    ~MorsMainWindow();

private:
    Ui::MorsMainWindow *ui;
};

#endif // MORSMAINWINDOW_H
