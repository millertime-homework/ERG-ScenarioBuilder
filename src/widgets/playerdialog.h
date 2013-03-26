#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>

namespace Ui {
class PlayerDialog;
}

class PlayerDialog : public QDialog
{
    Q_OBJECT
public:
    PlayerDialog(int x, int y, int z, const QString &facing,
                 const QStringList &inventory, QWidget *parent = 0);

    int getX() const;
    int getY() const;
    int getZ() const;
    QString getFacing() const;
    QStringList getInventory() const;

public slots:
    void addItem();

private:
    Ui::PlayerDialog *ui;
};

#endif // PLAYERDIALOG_H
