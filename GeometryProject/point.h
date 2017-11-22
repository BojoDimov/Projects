
#ifndef POINT_H
#define POINT_H

//forward declared dependencies
class Line;
class Plain;
class Vector;
//class Plain

class Point{
    public:
        Point(double = 0, double = 0, double = 0);
        Point(Line ,Line);
        Point(Line&, Plain&);
        Point(Line,Line, int);

        //local needed
        void print()const;
        double getX()const {return x;}
        double getY()const {return y;}
        double getZ()const {return z;}
        bool operator==(const Point &p) {return x==p.getX()&&y==p.getY()&&z==p.getZ();}
        bool operator!=(const Point &p) {return !(x==p.getX()&&y==p.getY()&&z==p.getZ());}

        Point& translate(Vector &v);
        //functionality
        bool isOnLine(Line&);
    private:
        double x;
        double y;
        double z;
};
#endif
