#ifndef FLOORDIALOG_H
#define FLOORDIALOG_H

#include <QDialog>

namespace Ui {
class FloorDialog;
}

class FloorDialog : public QDialog
{
        Q_OBJECT
        
    public:
        FloorDialog(const QString &name, int z, QWidget *parent = 0);
        ~FloorDialog();
        
    private slots:
        void floorNameChanged(const QString &name);
        void enableOkButton();

    private:
        Ui::FloorDialog *ui;
};

#endif // FLOORDIALOG_H
