#include<iostream>
#include<cmath>
#include "line.h"
#include "point.h"
#include "vector.h"
#include "plain.h"
#include "Point_and_Line.h"
using namespace std;

PointNLine orthoProjection(Line &l, Plain &pl)
{
    if(l.getDirection().isCollinearWith(pl.getNormalVector()))
    {
        Line empty(l.getBase(),l.getBase());
        Point prop(l,pl);
        PointNLine projection(prop, empty);
        return projection;
    }
    Line g(l.getBase(),pl.getNormalVector() ), h(l.getBase().translate(l.getDirection()), pl.getNormalVector());
    Point p1(g,pl),p2(h,pl);
    Line finalLine(p1,p2);
    PointNLine  projection(p1,finalLine);
    return projection;
}
double dist_between_point_and_plain(Point &p, Plain &pl)
{
    Line l(p,pl.getNormalVector());
    Point projection(l,pl);
    Vector vl(p,projection);
    return vl.getLen();
}

double angle_between_line_and_plain(Line &g, Plain &pl)
{
    Point base(g,pl);
    Point notIntersectionPoint(g.getBase());
    while(pl.checkPoint(notIntersectionPoint))
    {
        notIntersectionPoint = notIntersectionPoint.translate(g.getDirection());
    }
    Line l(notIntersectionPoint,pl.getNormalVector());
    Point projection(l,pl);
    Vector onLine(base,notIntersectionPoint),inPlain(base,projection);
    double hypotenuse = onLine.getLen();
    double cathetus = inPlain.getLen();
    double sin = cathetus/hypotenuse;
    cout<<"sin = "<<sin<<endl;

}

double dist_between_point_and_line(Point &p, Line &l)
{
    Plain orthogonalToLine(p,l);
    Point onLine(l,orthogonalToLine);
    Vector distVector(p,onLine);
    return distVector.getLen();
}

double dist_between_line_and_line(Line &l1,Line &l2)
{
    if(l1.getDirection().isCollinearWith(l2.getDirection()))
    {
        Point p = l1.getBase();
        return dist_between_point_and_line(p,l2);
    }

    Plain orthogonalPlain(l1.getBase(),l1);
    Line l2Projection = orthoProjection(l2,orthogonalPlain);
    return dist_between_point_and_line(l1.getBase(),l2Projection);
}
