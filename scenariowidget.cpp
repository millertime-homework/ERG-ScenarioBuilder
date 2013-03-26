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

    connect(ui->player, SIGNAL(clicked()),
            this, SLOT(showPlayerDialog()));
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
