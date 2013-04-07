#include <QVBoxLayout>
#include <QTextEdit>
#include "logwindow.h"

LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    shown(false)
{
    QVBoxLayout *v = new QVBoxLayout();
    v->setMargin(0);
    setLayout(v);
    log = new QTextEdit();
    v->addWidget(log);
}

void LogWindow::info(const QString &message)
{
    log->append("INFO "+message);
}

void LogWindow::showEvent(QShowEvent *event)
{
    if (!shown) {
        resize(640, 480);
    }
    QDialog::showEvent(event);
}
