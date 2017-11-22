#ifndef VECTOR_H
#define VECTOR_H

class Point;
class Plain;

class Vector{
    public:
        Vector(double = 0, double = 0, double = 0);
        Vector(Point&, Point&);
        Vector(Plain&);

        void print()const;
        double getX()const {return x;}
        double getY()const {return y;}
        double getZ()const {return z;}
        Point& getStart(){return start;}
        Point& getEnd(){return end;}


        Vector& sum(const Vector&);
        double getLen()const;
        double scalarWork(const Vector&);
        Vector& vectorWork (const Vector&);


        bool isCollinearWith(const Vector&);

        bool operator==(const Vector& v){ return x==v.getX() && y == v.getY() && z == v.getZ();}
    private:
        double x,y,z;
        Point start,end;


};
#endif
