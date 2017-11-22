
#ifndef LINE_H
#define LINE_H

#include "point.h"
#include  "vector.h"
//forward declred dependencies
class Plain;



class Line
{
    public:
        Line(Point&, Point&);
        Line(Point&, Vector);
        Line(Plain&, Plain&);
        Line(Point&, Plain&);

        void print()const;
        Vector& getDirection(){ return direction;}
        Point& getBase(){ return base;}

        void check(Line&) ;//0 za usporedni , 1 za prese4eni , 2 za krustosani
        bool crossing(Line&)const;
    private:
        Point base;
        Vector direction;
};
#endif
