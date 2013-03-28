#ifndef MRU_H
#define MRU_H

#include <QObject>
#include <QStringList>

class QAction;

class Mru : public QObject
{
    Q_OBJECT
public:
    Mru(QObject *parent = 0);
    
    void addPath(const QString &scenarioPath);
    QList<QAction*> getScenarios() const { return scenarioActions; }

signals:
    void openRecent(const QString &path);

private slots:
    void actionClicked();

private:
    QString pathToMru;
    QStringList scenarios;
    QList<QAction*> scenarioActions;
};

#endif // MRU_H
