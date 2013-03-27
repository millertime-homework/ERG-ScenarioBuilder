#include <QDebug>
#include <QAbstractButton>

#include "floortile.h"
#include "floordialog.h"
#include "ui_floordialog.h"

FloorDialog::FloorDialog(const QString &name, int z,
                         QList<Room*> rooms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FloorDialog),
    selectedTile(NULL)
{
    ui->setupUi(this);

    ui->name->setText(name);
    setWindowTitle(name);

    ui->z->setText(QString::number(z));
    ui->z->setValidator(new QIntValidator());

    getMinAndMax(rooms);

    createBlankTiles();

    foreach (Room *r, rooms) {
        addRoom(r);
    }

    connect(ui->name, SIGNAL(textEdited(QString)),
            this, SLOT(floorNameChanged(QString)));
    connect(ui->z, SIGNAL(textEdited(QString)),
            this, SLOT(enableOkButton()));
}

FloorDialog::~FloorDialog()
{
    delete ui;
}

void FloorDialog::addRoom(Room *r)
{

}

void FloorDialog::floorNameChanged(const QString &name)
{
    setWindowTitle(name);
    enableOkButton();
}

void FloorDialog::enableOkButton()
{
    bool invalid = ui->name->text().isEmpty() || ui->z->text().isEmpty();
    ui->buttonBox->buttons().at(0)->setDisabled(invalid);
}

void FloorDialog::tileClicked(FloorTile *tile)
{
    if (selectedTile)
        selectedTile->deselect();
    tile->select();
    selectedTile = tile;
}

void FloorDialog::getMinAndMax(QList<Room*> rooms)
{
    if (rooms.isEmpty()) {
        minX = maxX = minY = maxY = 0;
        return;
    }

    minX = INT_MAX;
    minY = INT_MAX;
    maxX = INT_MIN;
    maxY = INT_MIN;
    foreach (Room *r, rooms) {
        if (r->x < minX)
            minX = r->x;
        if (r->x > maxX)
            maxX = r->x;
        if (r->y < minY)
            minY = r->y;
        if (r->y > maxY)
            maxY = r->y;
    }
    qDebug() << "minX" << minX << "maxX" << maxX << "minY" << minY << "maxY" << maxY;
}

void FloorDialog::createBlankTiles()
{
    int num_rows = maxY - minY + 3; // one extra row above and below
    int num_cols = maxX - minX + 3; // one extra column to the left and right
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            FloorTile *t = new FloorTile();
            ui->grid->addWidget(t, i, j);

            connect(t, SIGNAL(tileClicked(FloorTile*)),
                    this, SLOT(tileClicked(FloorTile*)));
        }
    }
}
