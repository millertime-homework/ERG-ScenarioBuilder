#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void aboutDialog();
    void newScenario();
    void loadScenario();
    void saveScenario();

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QTimer *scenarioLoadTimer;
};

#endif // MAINWINDOW_H
