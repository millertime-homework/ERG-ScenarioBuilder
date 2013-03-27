#include <QVBoxLayout>
#include <QLabel>

#include "wall.h"

WallThumbnail::WallThumbnail(const QString &name, const QString &imagePath, QWidget *parent) :
    QFrame(parent)
{
    QVBoxLayout *vertLayout = new QVBoxLayout();
    vertLayout->setMargin(0);
    setLayout(vertLayout);
    QLabel *l = new QLabel(name);
    vertLayout->addWidget(l);
    QLabel *p = new QLabel();
    p->setPixmap(QPixmap(imagePath));
    vertLayout->addWidget(p);
}
