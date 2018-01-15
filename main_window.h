#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QMainWindow>


namespace Ui {


class MainWindow;


} // Ui


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonStart_clicked();
    void on_buttonMenu_clicked();

private:
    Ui::MainWindow *ui;
    int m_menu_height;
};


#endif // MAIN_WINDOW_H
