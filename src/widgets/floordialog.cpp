#include <QAbstractButton>

#include "floordialog.h"
#include "ui_floordialog.h"

FloorDialog::FloorDialog(const QString &name, int z, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FloorDialog)
{
    ui->setupUi(this);

    ui->name->setText(name);
    setWindowTitle(name);

    ui->z->setText(QString::number(z));
    ui->z->setValidator(new QIntValidator());

    connect(ui->name, SIGNAL(textEdited(QString)),
            this, SLOT(floorNameChanged(QString)));
    connect(ui->z, SIGNAL(textEdited(QString)),
            this, SLOT(enableOkButton()));
}

FloorDialog::~FloorDialog()
{
    delete ui;
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

