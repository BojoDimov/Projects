#include <iostream>
#include <cmath>
#include "point.h"
#include "vector.h"
#include "line.h"
#include "plain.h"

using namespace std;

Vector::Vector(double _x, double _y, double _z)
    :x(_x), y(_y), z(_z)
    {
        end = *new Point(x,y,z);
    }

Vector::Vector(Point &p1, Point &p2)
{
    x = p2.getX() - p1.getX();
    y = p2.getY() - p1.getY();
    z = p2.getZ() - p1.getZ();
    start = p1;
    end = p2;
}

Vector::Vector(Plain &pl)
{
    x = pl.getNormalVector().getX();
    y = pl.getNormalVector().getY();
    z = pl.getNormalVector().getZ();

    end = *new Point(x,y,z);

}
bool Vector::isCollinearWith(const Vector &v)
{
    return vectorWork(v) == *new Vector(0,0,0);
}

Vector& Vector::vectorWork(const Vector &v)
{
    double a = y*v.getZ() - z*v.getY();
    double b = z*v.getX() - x*v.getZ();
    double c = x*v.getY() - y*v.getX();
    return *new Vector(a,b,c);
}

Vector& Vector::sum(const Vector &v)
{
    return *new Vector(x + v.getX(), y + v.getY(), z + v.getZ() );
}

double Vector::scalarWork(const Vector &v)
{
    return x*v.getX() + y*v.getY() + z*v.getZ();
}

double Vector::getLen()const
{
   return abs( sqrt(x*x + y*y + z*z) );
}

void Vector::print()const
{
    cout<<"vector ("<<x<<", "<<y<<", "<<z<<")\n";
}
