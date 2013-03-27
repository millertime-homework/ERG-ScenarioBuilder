#ifndef FLOORTILE_H
#define FLOORTILE_H

#include <QFrame>

namespace Ui {
class FloorTile;
}

class FloorTile : public QFrame
{
    Q_OBJECT
    
public:
    explicit FloorTile(QWidget *parent = 0);
    ~FloorTile();
    
public slots:
    void select();
    void deselect();

signals:
    void tileClicked(FloorTile *tile);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::FloorTile *ui;
};

#endif // FLOORTILE_H
