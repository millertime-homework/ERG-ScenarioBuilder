#include <QDebug>

#include "floortile.h"
#include "ui_floortile.h"

FloorTile::FloorTile(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FloorTile)
{
    ui->setupUi(this);
    setFrameStyle(QFrame::Box | QFrame::Plain);
    ui->roomFrame->hide();
    ui->walls->hide();
}

FloorTile::~FloorTile()
{
    delete ui;
}

void FloorTile::select()
{
    setLineWidth(5);
    update();
}

void FloorTile::deselect()
{
    setLineWidth(1);
    update();
}

void FloorTile::mousePressEvent(QMouseEvent *event)
{
    emit tileClicked(this);

    QFrame::mousePressEvent(event);
}
