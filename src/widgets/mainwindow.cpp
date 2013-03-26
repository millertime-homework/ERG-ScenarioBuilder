#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <QInputDialog>
#include <QFileDialog>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

#include "src/scenario.h"
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
    QMessageBox::about(this, "Emergency Response Game Scenario Builder",
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
    Scenario *s = new Scenario(name);
    ScenarioWidget *w = new ScenarioWidget(s);
    int tabNum = tabWidget->addTab(w, name);
    tabWidget->setCurrentIndex(tabNum);
    ui->actionSave_Scenario->setEnabled(true);
}

void MainWindow::loadScenario()
{
    QString scenarioFile = QFileDialog::getOpenFileName(this, "Select a Scenario File",
                                                        QString(), "Scenario JSON File (*.js)");
    if (scenarioFile.isEmpty())
        return;

    QElapsedTimer timer;
    timer.start();

    QFile f(scenarioFile);
    if (!f.open(QFile::ReadOnly))
        return;

    QByteArray rawJson = f.readAll();
    QScriptValue sc;
    QScriptEngine engine;
    sc = engine.evaluate(QString(rawJson));

    // scenario name
    QString name = sc.property("name").toString();
    Scenario *s = new Scenario(name);

    // floors
    QScriptValue floors = sc.property("_floors");
    QVariantMap floorMap = floors.toVariant().toMap();
    foreach (QString floor, floorMap.keys()) {
//        qDebug() << "Floor" << floor << "has value:";
//        qDebug() << floorMap.value(floor);
        Floor *f = new Floor(floor);
        s->floors.append(f);
    }

    QScriptValue conversations = sc.property("_conversations");
    QVariantMap conversationMap = conversations.toVariant().toMap();
    foreach (QString conversation, conversationMap.keys()) {
//        qDebug() << "Conversation" << conversation << "has value:";
//        qDebug() << conversationMap.value(conversation);
        Conversation *c = new Conversation(conversation);
        s->conversations.append(c);
    }

    QScriptValue triggers = sc.property("_triggers");
    QVariantMap triggerMap = triggers.toVariant().toMap();
    foreach (QString trigger, triggerMap.keys()) {
//        qDebug() << "Trigger" << trigger << "has value:";
//        qDebug() << triggerMap.value(trigger);
        Trigger *t = new Trigger(trigger);
        s->triggers.append(t);
    }

    QScriptValue inactiveProps = sc.property("inactiveProps");
    if (inactiveProps.isArray()) {
        QStringList props;
        qScriptValueToSequence(inactiveProps, props);
//        qDebug() << "Inactive Props: " << props;
        s->inactiveProps.append(props);
    }

    QScriptValue player = sc.property("_player");
    s->playerX = player.property("x").toInteger();
    s->playerY = player.property("y").toInteger();
    s->playerZ = player.property("z").toInteger();
    s->playerFacing = player.property("_facing").toString();

    QScriptValue playerInventory = player.property("inventory");
    if (playerInventory.isArray()) {
        QStringList inv;
        qScriptValueToSequence(playerInventory, inv);
        s->playerInventory.append(inv);
    }

    ScenarioWidget *w = new ScenarioWidget(s);
    int tabNum = tabWidget->addTab(w, name);
    tabWidget->setCurrentIndex(tabNum);
    ui->actionSave_Scenario->setEnabled(true);

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
