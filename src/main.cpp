#include <QtGui/QApplication>
#include "src/widgets/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString scenarioFile;
    QStringList args = a.arguments();
    int i = args.indexOf("-load");
    if (i != -1 && args.count() > i+1)
        scenarioFile = args.at(i+1);

    MainWindow w(scenarioFile);
    w.show();
    
    return a.exec();
}
