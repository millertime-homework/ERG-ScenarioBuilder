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
    QString floorName() const;
    void addRoom(Room *r);

signals:
    void roomAdded(FloorDialog *d, Room *r);
    void roomRemoved(FloorDialog *d, Room *r);

private slots:
    void floorNameChanged(const QString &name);
    void enableOkButton();
    void tileClicked(FloorTile *tile);
    void addRoom();
    void editRoom();
    void removeRoom();

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
