#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
class QTextEdit;

class LogWindow : public QDialog
{
    Q_OBJECT

public:
    LogWindow(QWidget *parent = 0);

public slots:
    void info(const QString &message);

protected:
    void showEvent(QShowEvent *event);

private:
    QTextEdit *log;
    bool shown;
};

#endif // LOGWINDOW_H
