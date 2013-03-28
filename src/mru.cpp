#include <QFile>
#include <QAction>
#include "mru.h"

#define MRU_FILE ".erg_sb_mru"

Mru::Mru(QObject *parent) :
    QObject(parent)
{
    pathToMru = QString(getenv("HOME")) + "/" + QString(MRU_FILE);
    QFile f(pathToMru);
    if (f.exists()) {
        if (f.open(QFile::ReadOnly)) {
            QString contents = f.readAll();
            contents.replace("\r","");
            scenarios = contents.split("\n", QString::SkipEmptyParts);
            f.close();
        }
    }
    foreach (QString s, scenarios) {
        QAction *a = new QAction(s, this);
        connect(a, SIGNAL(triggered()),
                this, SLOT(actionClicked()));
        scenarioActions.append(a);
    }
}

void Mru::addPath(const QString &scenarioPath)
{
    if (!scenarios.contains(scenarioPath))
    scenarios.append(scenarioPath);
    QFile f(pathToMru);
    if (f.open(QFile::Append)) {
        QByteArray data = scenarios.join("\n").toAscii() + "\n";
        f.write(data);
        f.close();
    }
    QAction *action = new QAction(scenarioPath, this);
    connect(action, SIGNAL(triggered()),
            this, SLOT(actionClicked()));
    scenarioActions.append(action);
}

void Mru::actionClicked()
{
    QAction *action = static_cast<QAction*>(sender());
    emit openRecent(action->text());
}
