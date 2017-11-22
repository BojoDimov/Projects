#ifndef PNL_H
#define PNL_H

#include "point.h"
#include "line.h"

class PointNLine:public Line, public Point
{
public:
    PointNLine(Point p, Line l):Point(p.getX(),p.getY(),p.getZ()),Line(l){};
private:
};

#endif // PNL_H

