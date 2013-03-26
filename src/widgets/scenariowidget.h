#ifndef SCENARIOWIDGET_H
#define SCENARIOWIDGET_H

#include <QWidget>

#include "../scenario.h"

namespace Ui {
class ScenarioWidget;
}

class ScenarioWidget : public QWidget
{
    Q_OBJECT
public:
    ScenarioWidget(Scenario *s, QWidget *parent = 0);

public slots:
    void addFloor();
    void addConversation();
    void addTrigger();
    void addInactiveProp();
    void showPlayerDialog();

private slots:
    // floors
    void floorSelectionChanged();
    void editFloor();
    void removeFloor();

    // conversations
    void conversationSelectionChanged();
    void editConversation();
    void removeConversation();

    // triggers
    void triggerSelectionChanged();
    void editTrigger();
    void removeTrigger();

    // inactive props
    void inactivePropSelectionChanged();
    void editInactiveProp();
    void removeInactiveProp();

private:
    bool floorExists(const QString &name);
    Floor *getFloor(const QString &name);

    bool conversationExists(const QString &name);
    Conversation *getConversation(const QString &name);

    bool triggerExists(const QString &name);
    Trigger *getTrigger(const QString &name);

    bool inactivePropExists(const QString &name);

    bool confirm(const QString &question);

    Ui::ScenarioWidget *ui;
    Scenario *scenario;
};

#endif // SCENARIOWIDGET_H
