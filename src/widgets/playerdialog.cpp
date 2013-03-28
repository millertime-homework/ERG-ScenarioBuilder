#include <QInputDialog>

#include "playerdialog.h"
#include "ui_playerdialog.h"

PlayerDialog::PlayerDialog(int x, int y, int z, const QString &facing,
                           const QStringList &inventory, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);

    ui->x->setValidator(new QIntValidator());
    ui->y->setValidator(new QIntValidator());
    ui->z->setValidator(new QIntValidator());

    ui->x->setText(QString::number(x));
    ui->y->setText(QString::number(y));
    ui->z->setText(QString::number(z));
    ui->facing->setText(facing);
    ui->inventory->addItems(inventory);

    connect(ui->addInvItem, SIGNAL(clicked()),
            this, SLOT(addItem()));
}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

int PlayerDialog::getX() const
{
    return ui->x->text().toInt();
}

int PlayerDialog::getY() const
{
    return ui->y->text().toInt();
}

int PlayerDialog::getZ() const
{
    return ui->z->text().toInt();
}

QString PlayerDialog::getFacing() const
{
    return ui->facing->text();
}

QStringList PlayerDialog::getInventory() const
{
    QStringList items;
    for (int i = 0; i < ui->inventory->count(); ++i) {
        items.append(ui->inventory->item(i)->text());
    }
    return items;
}

void PlayerDialog::addItem()
{
    QString itemName = QInputDialog::getText(this, "New Item",
                                             "Enter item name");
    if (!itemName.isEmpty())
        ui->inventory->addItem(itemName);
}
