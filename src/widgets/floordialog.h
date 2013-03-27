#ifndef FLOORDIALOG_H
#define FLOORDIALOG_H

#include <QDialog>

#include "../scenario.h"

namespace Ui {
class FloorDialog;
}

class FloorTile;

class FloorDialog : public QDialog
{
    Q_OBJECT

public:
    FloorDialog(const QString &name, int z,
                QList<Room*> rooms, QWidget *parent = 0);
    ~FloorDialog();

public:
    void addRoom(Room *r);

private slots:
    void floorNameChanged(const QString &name);
    void enableOkButton();
    void tileClicked(FloorTile *tile);

private:
    void getMinAndMax(QList<Room*> rooms);
    void createBlankTiles();

    Ui::FloorDialog *ui;
    FloorTile *selectedTile;
    int minX;
    int maxX;
    int minY;
    int maxY;
};

#endif // FLOORDIALOG_H
