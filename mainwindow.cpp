#include <QMessageBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QTime>
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
    Scenario *s = new Scenario();
    s->name = name;
    s->playerX = 0;
    s->playerY = 0;
    s->playerZ = 0;
    ScenarioWidget *w = new ScenarioWidget(s);
    int tabNum = tabWidget->addTab(w, name);
    tabWidget->setCurrentIndex(tabNum);
}

void MainWindow::loadScenario()
{
    QTime start = QTime::currentTime();
    QLabel *tabOneWidget = new QLabel("Scenario!");
    int tabNum = tabWidget->addTab(tabOneWidget, "Scenario");
    tabWidget->setCurrentIndex(tabNum);
    double elapsed = QTime::currentTime().msec() - start.msec();
    ui->statusBar->showMessage("Scenario loaded in " + QString::number(elapsed/1000) + " seconds", 3000);
}
