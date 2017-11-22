#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "line.h"
#include "point.h"
#include "vector.h"
#include "plain.h"

using namespace std;

Point::Point(double _x, double _y, double _z)
    :x(_x), y(_y), z(_z){}

Point& makePointNotOnLine(Line &l1){

    srand(time(0));
    int _x,_y,_z;
    Point p;
    do
    {
        _x = rand()%10+1;
        _y = rand()%10+1;
        _z = rand()%10+1;
        p = *new Point(_x,_y,_z);
    }while( p.isOnLine(l1));
    return p;
}

Point::Point(Line l1, Line l2)
{
    if(l1.getDirection().isCollinearWith(l2.getDirection() )  )
    {
        cout<<"they are parallel lines\nthe point is set to be the (0,0,0) point\n";
        x=0;y=0;z=0;
    }else
    {

        Point plainPoint = makePointNotOnLine(l1) ,pointFromLine = l1.getBase();
        plainPoint.print();
        pointFromLine.print();
        pointFromLine.translate(l1.getDirection()).print();
        Plain projectionField(plainPoint, pointFromLine, pointFromLine.translate(l1.getDirection()) );
        cout<<"projection plain : ";projectionField.printGeneral();
        Point lineIntersectedWithPlain(l2,projectionField);

        cout<<"the expected point is ";lineIntersectedWithPlain.print();
        if(lineIntersectedWithPlain.isOnLine(l1))
        {
            x = lineIntersectedWithPlain.getX();
            y = lineIntersectedWithPlain.getY();
            z = lineIntersectedWithPlain.getZ();
        }
        else
        {
            cout<<"Lines are crossed so point is set to default 0,0,0 coordinates\n";
            x = 0; y = 0; z = 0;
        }
    }
}

Point::Point(Line &l, Plain &p)
{
    if(l.getDirection().scalarWork(p.getNormalVector()) == 0)
    {
        x = 0;y = 0; z = 0;
        cout<<"Line is not crossing the plane point is set to default\n";
    }else
    {
        double k = p.getX()*l.getDirection().getX() + p.getY()*l.getDirection().getY() + p.getZ()*l.getDirection().getZ();
        double result = 0 - p.getT() - l.getBase().getX()*p.getX() - l.getBase().getY()*p.getY() - l.getBase().getZ()*p.getZ();
        double s = result/k;
        //cout<<" k = "<<k<<"   result = "<<result<<"  paremeter = "<<s<<endl;
        x = l.getBase().getX() + l.getDirection().getX()*s;
        y = l.getBase().getY() + l.getDirection().getY()*s;
        z = l.getBase().getZ() + l.getDirection().getZ()*s;
    }

}

Point& Point::translate(Vector &v)
{
    return *new Point(x+v.getX(),y + v.getY(), z + v.getZ());
}
void Point::print()const{
    cout<<"point ("<<x<<", "<<y<<", "<<z<<")\n";
}

bool Point::isOnLine(Line &l)
{
    Vector translation(x-l.getBase().getX(), y - l.getBase().getY(), z - l.getBase().getZ());
    //cout<<"checking ";translation.print();
    //cout<<"with ";l.getDirection().print();
    return translation.isCollinearWith(l.getDirection());
}
Point::Point(Line l1, Line l2,int command)
{
   if(command == 0){
    *this = *new Point(l1,l2);
   }else{
        Point plainPoint = makePointNotOnLine(l1) ,pointFromLine = l1.getBase();
        Plain projectionField(plainPoint, pointFromLine, pointFromLine.translate(l1.getDirection()) );
        Point lineIntersectedWithPlain(l2,projectionField);

        x = lineIntersectedWithPlain.getX();
        y = lineIntersectedWithPlain.getY();
        z = lineIntersectedWithPlain.getZ();
   }
}
