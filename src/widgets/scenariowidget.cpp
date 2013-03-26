#include <QInputDialog>
#include <QMessageBox>

#include "playerdialog.h"
#include "floordialog.h"
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

    // Signals for floors
    connect(ui->floors, SIGNAL(itemSelectionChanged()),
            this, SLOT(floorSelectionChanged()));
    connect(ui->addFloor, SIGNAL(clicked()),
            this, SLOT(addFloor()));
    connect(ui->editFloor, SIGNAL(clicked()),
            this, SLOT(editFloor()));
    connect(ui->floors, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(editFloor()));
    connect(ui->removeFloor, SIGNAL(clicked()),
            this, SLOT(removeFloor()));

    // Signals for conversations
    connect(ui->conversations, SIGNAL(itemSelectionChanged()),
            this, SLOT(conversationSelectionChanged()));
    connect(ui->addConversation, SIGNAL(clicked()),
            this, SLOT(addConversation()));
    connect(ui->editConversation, SIGNAL(clicked()),
            this, SLOT(editConversation()));
    connect(ui->conversations, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(editConversation()));
    connect(ui->removeConversation, SIGNAL(clicked()),
            this, SLOT(removeConversation()));

    // Signals for triggers
    connect(ui->triggers, SIGNAL(itemSelectionChanged()),
            this, SLOT(triggerSelectionChanged()));
    connect(ui->addTrigger, SIGNAL(clicked()),
            this, SLOT(addTrigger()));
    connect(ui->editTrigger, SIGNAL(clicked()),
            this, SLOT(editTrigger()));
    connect(ui->triggers, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(editTrigger()));
    connect(ui->removeTrigger, SIGNAL(clicked()),
            this, SLOT(removeTrigger()));

    // Signals for inactive props
    connect(ui->inactiveProps, SIGNAL(itemSelectionChanged()),
            this, SLOT(inactivePropSelectionChanged()));
    connect(ui->addInactiveProp, SIGNAL(clicked()),
            this, SLOT(addInactiveProp()));
    connect(ui->editInactiveProp, SIGNAL(clicked()),
            this, SLOT(editInactiveProp()));
    connect(ui->inactiveProps, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(editInactiveProp()));
    connect(ui->removeInactiveProp, SIGNAL(clicked()),
            this, SLOT(removeInactiveProp()));

    connect(ui->player, SIGNAL(clicked()),
            this, SLOT(showPlayerDialog()));
}

void ScenarioWidget::addFloor()
{
    QString floorName = QInputDialog::getText(this, "Add a new floor",
                                              "Please specify the name of the floor");
    if (!floorName.isEmpty()) {
        if (floorExists(floorName)) {
            QMessageBox::warning(this, "Floor Exists",
                                 "That floor name is already taken.");
            return;
        }
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
        if (conversationExists(conversationName)) {
            QMessageBox::warning(this, "Conversation Exists",
                                 "That conversation name is already taken.");
            return;
        }
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
        if (triggerExists(triggerName)) {
            QMessageBox::warning(this, "Trigger Exists",
                                 "That trigger name is already taken.");
            return;
        }
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
        if (inactivePropExists(propName)) {
            QMessageBox::warning(this, "Inactive Prop Exists",
                                 "That prop is already listed as inactive by default.");
            return;
        }
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

void ScenarioWidget::floorSelectionChanged()
{
    bool nothing_selected = ui->floors->selectedItems().isEmpty();
    ui->editFloor->setDisabled(nothing_selected);
    ui->removeFloor->setDisabled(nothing_selected);
}

void ScenarioWidget::editFloor()
{
    QList<QListWidgetItem*> selectedItems = ui->floors->selectedItems();
    if (!selectedItems.isEmpty()) {
        QString floorName = selectedItems.at(0)->text();
        Floor *f = getFloor(floorName);
        FloorDialog fd(floorName, f->z);
        if (fd.exec()) {

        }
    }
}

void ScenarioWidget::removeFloor()
{
    QList<QListWidgetItem*> selectedItems = ui->floors->selectedItems();
    if (!selectedItems.isEmpty()) {
        if (!confirm("Are you sure you want to delete the selected floor and EVERYTHING it contains?")) {
            return;
        }
        QListWidgetItem *floorToRemove = selectedItems.at(0);
        QString name = floorToRemove->text();
        int row = ui->floors->row(floorToRemove);
        ui->floors->takeItem(row);
        delete floorToRemove;
        Floor *f = getFloor(name);
        if (f) {
            int i = scenario->floors.indexOf(f);
            scenario->floors.removeAt(i);
            delete f;
        }
    }
}

void ScenarioWidget::conversationSelectionChanged()
{
    bool nothing_selected = ui->conversations->selectedItems().isEmpty();
    ui->editConversation->setDisabled(nothing_selected);
    ui->removeConversation->setDisabled(nothing_selected);
}

void ScenarioWidget::editConversation()
{
    QMessageBox::information(this, "Edit Conversation - Not Implemented",
                             "Sorry, the Edit Conversation feature is not available yet.");
}

void ScenarioWidget::removeConversation()
{
    QList<QListWidgetItem*> selectedItems = ui->conversations->selectedItems();
    if (!selectedItems.isEmpty()) {
        if (!confirm("Are you sure you want to delete the selected conversation?")) {
            return;
        }
        QListWidgetItem *conversationToRemove = selectedItems.at(0);
        QString name = conversationToRemove->text();
        int row = ui->conversations->row(conversationToRemove);
        ui->conversations->takeItem(row);
        delete conversationToRemove;
        Conversation *c = getConversation(name);
        if (c) {
            int i = scenario->conversations.indexOf(c);
            scenario->conversations.removeAt(i);
            delete c;
        }
    }
}

void ScenarioWidget::triggerSelectionChanged()
{
    bool nothing_selected = ui->triggers->selectedItems().isEmpty();
    ui->editTrigger->setDisabled(nothing_selected);
    ui->removeTrigger->setDisabled(nothing_selected);
}

void ScenarioWidget::editTrigger()
{
    QMessageBox::information(this, "Edit Trigger - Not Implemented",
                             "Sorry, the Edit Trigger feature is not available yet.");
}

void ScenarioWidget::removeTrigger()
{
    QList<QListWidgetItem*> selectedItems = ui->triggers->selectedItems();
    if (!selectedItems.isEmpty()) {
        if (!confirm("Are you sure you want to delete the selected trigger?")) {
            return;
        }
        QListWidgetItem *triggerToRemove = selectedItems.at(0);
        QString name = triggerToRemove->text();
        int row = ui->triggers->row(triggerToRemove);
        ui->triggers->takeItem(row);
        delete triggerToRemove;
        Trigger *t = getTrigger(name);
        if (t) {
            int i = scenario->triggers.indexOf(t);
            scenario->triggers.removeAt(i);
            delete t;
        }
    }
}

void ScenarioWidget::inactivePropSelectionChanged()
{
    bool nothing_selected = ui->inactiveProps->selectedItems().isEmpty();
    ui->editInactiveProp->setDisabled(nothing_selected);
    ui->removeInactiveProp->setDisabled(nothing_selected);
}

void ScenarioWidget::editInactiveProp()
{
    QMessageBox::information(this, "Edit Inactive Prop - Not Implemented",
                             "Sorry, the Edit Inactive Prop feature is not available yet.");
}

void ScenarioWidget::removeInactiveProp()
{
    QList<QListWidgetItem*> selectedItems = ui->inactiveProps->selectedItems();
    if (!selectedItems.isEmpty()) {
        QListWidgetItem *propToRemove = selectedItems.at(0);
        QString name = propToRemove->text();
        int row = ui->inactiveProps->row(propToRemove);
        ui->inactiveProps->takeItem(row);
        delete propToRemove;
        int i = scenario->inactiveProps.indexOf(name);
        if (i != -1) {
            scenario->inactiveProps.removeAt(i);
        }
    }
}

bool ScenarioWidget::floorExists(const QString &name)
{
    bool exists = false;
    for(int i = 0; i < scenario->floors.count(); ++i) {
        if (scenario->floors.at(i)->name == name) {
            exists = true;
            break;
        }
    }
    return exists;
}

Floor *ScenarioWidget::getFloor(const QString &name)
{
    Floor *f = NULL;
    for(int i = 0; i < scenario->floors.count(); ++i) {
        if (scenario->floors.at(i)->name == name) {
            f = scenario->floors[i];
            break;
        }
    }
    return f;
}

bool ScenarioWidget::conversationExists(const QString &name)
{
    bool exists = false;
    for(int i = 0; i < scenario->conversations.count(); ++i) {
        if (scenario->conversations.at(i)->name == name) {
            exists = true;
            break;
        }
    }
    return exists;
}

Conversation *ScenarioWidget::getConversation(const QString &name)
{
    Conversation *c = NULL;
    for(int i = 0; i < scenario->conversations.count(); ++i) {
        if (scenario->conversations.at(i)->name == name) {
            c = scenario->conversations[i];
            break;
        }
    }
    return c;
}

bool ScenarioWidget::triggerExists(const QString &name)
{
    bool exists = false;
    for(int i = 0; i < scenario->triggers.count(); ++i) {
        if (scenario->triggers.at(i)->name == name) {
            exists = true;
            break;
        }
    }
    return exists;
}

Trigger *ScenarioWidget::getTrigger(const QString &name)
{
    Trigger *t = NULL;
    for(int i = 0; i < scenario->triggers.count(); ++i) {
        if (scenario->triggers.at(i)->name == name) {
            t = scenario->triggers[i];
            break;
        }
    }
    return t;
}

bool ScenarioWidget::inactivePropExists(const QString &name)
{
    return scenario->inactiveProps.contains(name);
}

bool ScenarioWidget::confirm(const QString &question)
{
    QMessageBox::StandardButton response = QMessageBox::question(this, "Are you sure?",
                                                                 question, QMessageBox::Yes | QMessageBox::No);
    return (response == QMessageBox::Yes);
}
