#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <QInputDialog>

#include "scenario.h"
#include "scenariowidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    tabWidget(new QTabWidget())
{
    ui->setupUi(this);
    if (!ui->centralWidget->layout()) {
        QVBoxLayout *vertLayout = new QVBoxLayout();
        ui->centralWidget->setLayout(vertLayout);
    }
    ui->centralWidget->layout()->addWidget(tabWidget);

    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(aboutDialog()));
    connect(ui->actionNew_Scenario, SIGNAL(triggered()),
            this, SLOT(newScenario()));
    connect(ui->actionLoad_Scenario, SIGNAL(triggered()),
            this, SLOT(loadScenario()));
    connect(ui->actionSave_Scenario, SIGNAL(triggered()),
            this, SLOT(saveScenario()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aboutDialog()
{
    QMessageBox::information(this, "About...",
                             "This is the scenario builder for the Emergency Response Game, "
                             "Portland State University Capstone Senior Project - completed "
                             "Winter 2013 by Team Banana for Clark College.");
}

void MainWindow::newScenario()
{
    QString name = QInputDialog::getText(this, "New Scenario",
                                         "Enter a name for the scenario");
    if (name.isEmpty()) {
        return;
    }
    Scenario *s = new Scenario();
    s->name = name;
    s->playerX = 0;
    s->playerY = 0;
    s->playerZ = 0;
    ScenarioWidget *w = new ScenarioWidget(s);
    int tabNum = tabWidget->addTab(w, name);
    tabWidget->setCurrentIndex(tabNum);
    ui->actionSave_Scenario->setEnabled(true);
}

void MainWindow::loadScenario()
{
    QElapsedTimer timer;
    timer.start();
    QMessageBox::information(this, "Load Scenario - Not Implemented",
                             "Sorry, the Load Scenario feature is not available yet.");
    qint64 elapsed = timer.elapsed();
    ui->statusBar->showMessage("Completed command in " + QString::number(elapsed/1000.0) + " seconds", 3000);
}

void MainWindow::saveScenario()
{
    QElapsedTimer timer;
    timer.start();
    QMessageBox::information(this, "Save Scenario - Not Implemented",
                             "Sorry, the Save Scenario feature is not available yet.");
    qint64 elapsed = timer.elapsed();
    ui->statusBar->showMessage("Completed command in " + QString::number(elapsed/1000.0) + " seconds", 3000);
}
