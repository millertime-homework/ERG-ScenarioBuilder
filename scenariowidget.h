#ifndef SCENARIOWIDGET_H
#define SCENARIOWIDGET_H

#include <QWidget>
class Scenario;

namespace Ui {
class ScenarioWidget;
}

class ScenarioWidget : public QWidget
{
    Q_OBJECT
public:
    ScenarioWidget(Scenario *s, QWidget *parent = 0);

public slots:
    void addInactiveProp();
    void showPlayerDialog();

private:
    Ui::ScenarioWidget *ui;
    Scenario *scenario;
};

#endif // SCENARIOWIDGET_H
