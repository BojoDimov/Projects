#ifndef PLAIN_H
#define PLAIN_H
#include "vector.h"
#include "point.h"

//forward declared dependencies
class Line;

class Plain
{
    public:
        Plain(double = 0, double = 0, double = 0, double = 0);
        Plain(Point&, Plain&);
        Plain(Point, Line);
        Plain(Vector&, Vector&);
        Plain(Point&, Point&, Point&);


        void printGeneral()const;
        void printParametric()const;


        Vector& getNormalVector(){return n;}
        Vector& getV1(){return v1;}
        Vector& getV2(){return v2;}
        Point& getBase(){ return base;}

        bool checkPoint(Point& p)const{return t==0-p.getX()*x-p.getY()*y-p.getZ()*z;}
        bool isLineParallel(Line &l)const {return l.getDirection().scalarWork(n) != 0;}
        bool isPlainParallel(Plain &a)const{return a.getNormalVector().vectorWork(n) == 0;}

        double getX()const{return x;}
        double getY()const{return y;}
        double getZ()const{return z;}
        double getT()const{return t;}
    private:
        double x,y,z,t;
        Vector n,v1,v2;
        Point base;
};
#endif //PLAIN_H
