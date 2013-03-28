#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../mru.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void aboutDialog();
    void newScenario();
    void loadScenario();
    void loadScenario(const QString &path);
    void saveScenario();

private:
    void loadMru();

    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QTimer *scenarioLoadTimer;
    Mru mru;
    QMenu *recentMenu;
};

#endif // MAINWINDOW_H
