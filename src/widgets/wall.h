#ifndef WALL_H
#define WALL_H

#include <QFrame>

class WallThumbnail : public QFrame
{
    Q_OBJECT
public:
    WallThumbnail(const QString &name, const QString &imagePath, QWidget *parent = 0);
};

#endif // WALL_H
