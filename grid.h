#ifndef GRID_H
#define GRID_H

#include <QObject>

class Grid
{
    Q_OBJECT
public:
    Grid();
};

#endif // GRID_H
//this class represents a resizeable grid size,
// maintains a constant grid square as the image gets scaled up.
//when the user clicks, it will find the closest grid square to where they clicked, and return it's center cord to draw a square there.
// also translates between actual and rendered coords.
// a set representing pixel ranges, 0-10, that are equivelent to actual pixel sizes
