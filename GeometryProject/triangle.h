#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "plain.h"

class Line;

class Triangle
{
    public:
        Triangle(Point&, Point&, Point&);

        Line getSide(Point&,Point&);

        Vector altitude(Point&);
        Vector median(Point&);
        Vector bisector(Point&);
        Line symmetral(Point&,Point&);

        Point orthocenter();
        Point centroid();
        Point circumcenter();
        Point incenter();

        double eulerDistance();

        Point getA()const{return A;}
        Point getB()const{return B;}
        Point getC()const{return C;}

        Plain getPlain()const{ return trianglePlain;}
    private:
    Point A,B,C;
    Plain trianglePlain;
};
#endif
