#include <QInputDialog>

#include "scenario.h"
#include "playerdialog.h"
#include "scenariowidget.h"
#include "ui_scenariowidget.h"

ScenarioWidget::ScenarioWidget(Scenario *s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScenarioWidget),
    scenario(s)
{
    ui->setupUi(this);

    foreach (Floor *f, s->floors) {
        ui->floors->addItem(f->name);
    }
    foreach (Conversation *c, s->conversations) {
        ui->conversations->addItem(c->name);
    }
    foreach (Trigger *t, s->triggers) {
        ui->triggers->addItem(t->name);
    }
    foreach (QString p, s->inactiveProps) {
        ui->inactiveProps->addItem(p);
    }

    connect(ui->addFloor, SIGNAL(clicked()),
            this, SLOT(addFloor()));
    connect(ui->addConversation, SIGNAL(clicked()),
            this, SLOT(addConversation()));
    connect(ui->addTrigger, SIGNAL(clicked()),
            this, SLOT(addTrigger()));
    connect(ui->addInactiveProp, SIGNAL(clicked()),
            this, SLOT(addInactiveProp()));
    connect(ui->player, SIGNAL(clicked()),
            this, SLOT(showPlayerDialog()));
}

void ScenarioWidget::addFloor()
{
    QString floorName = QInputDialog::getText(this, "Add a new floor",
                                              "Please specify the name of the floor");
    if (!floorName.isEmpty()) {
        Floor *f = new Floor(floorName);
        scenario->floors.append(f);
        ui->floors->addItem(floorName);
    }
}

void ScenarioWidget::addConversation()
{
    QString conversationName = QInputDialog::getText(this, "Add a new conversation",
                                                     "Please specify the name of the character");
    if (!conversationName.isEmpty()) {
        Conversation *c = new Conversation(conversationName);
        scenario->conversations.append(c);
        ui->conversations->addItem(conversationName);
    }
}

void ScenarioWidget::addTrigger()
{
    QString triggerName = QInputDialog::getText(this, "Add a new trigger",
                                                "Please specify a name for the trigger");
    if (!triggerName.isEmpty()) {
        Trigger *t = new Trigger(triggerName);
        scenario->triggers.append(t);
        ui->triggers->addItem(triggerName);
    }
}

void ScenarioWidget::addInactiveProp()
{
    QString propName = QInputDialog::getText(this, "Add an inactive prop",
                                             "Please specify the name of the prop");
    if (!propName.isEmpty()) {
        scenario->inactiveProps.append(propName);
        ui->inactiveProps->addItem(propName);
    }
}

void ScenarioWidget::showPlayerDialog()
{
    PlayerDialog p(scenario->playerX, scenario->playerY,
                   scenario->playerZ, scenario->playerFacing,
                   scenario->playerInventory);
    if (p.exec()) {
        scenario->playerX = p.getX();
        scenario->playerY = p.getY();
        scenario->playerZ = p.getZ();
        scenario->playerFacing = p.getFacing();
        scenario->playerInventory = p.getInventory();
    }
}
