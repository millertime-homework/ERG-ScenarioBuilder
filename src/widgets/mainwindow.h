#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../mru.h"

class LogWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(const QString &scenario, QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void aboutDialog();
    void newScenario();
    void loadScenario();
    void loadScenario(const QString &path);
    void saveScenario();

private:
    void loadMru();
    void log(const QString &message);

    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QTimer *scenarioLoadTimer;
    Mru mru;
    QMenu *recentMenu;
    LogWindow *logWindow;
};

#endif // MAINWINDOW_H
