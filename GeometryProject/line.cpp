#include <iostream>
#include "line.h"
using namespace std;

Line::Line(Point &p1, Point &p2)
{
    if(p1 == p2)
    {
        cout<<"These points are same!\nLine is set to default\n";
    }else
    {
        direction = *new Vector(p1, p2);
        base = p1;
    }
}

Line::Line(Point  &p, Vector v)
{
    if(v == *new Vector(0,0,0))
    {
        cout<<"The vector is (0,0,0)\nLine is set to default\n";
    }else
    {
        direction = v;
        base = p;
    }

}

Line::Line(Plain &pl, Plain &ql)
{
    Point pl1 = pl.getBase();
    Line firstRay(pl1,pl.getV1()), secondRay(pl1,pl.getV2());

    Point ql1(firstRay,ql), ql2(secondRay,ql);
    direction = *new Vector(ql1, ql2);
    base = ql1;
}

Line::Line(Point &p,Plain &pl)
{
    base = p;
    direction = pl.getNormalVector();
}

void Line::check(Line& l)
{
    if(direction.isCollinearWith(l.getDirection()))
    {
        cout<<"Lines are parallel\n";
    }else
    {
        double _x = base.getX()*base.getX() +1;
        double _y = base.getY()*base.getY() +1;
        double _z = base.getZ()*base.getZ() +1;

        Point plainPoint(_x,_y,_z),pointFromLine = base;

        while(plainPoint.isOnLine(*this)||plainPoint.isOnLine(l))
        {
            plainPoint = plainPoint.translate(*new Vector(_x,_y,_z));
            _x = _x*_x; _z = _z*_z ; _y = _y*_y;
        }
        Plain projectionField(plainPoint, pointFromLine, pointFromLine.translate(direction) );
        Point lineIntersectedWithPlain(l,projectionField);

        if(lineIntersectedWithPlain.isOnLine(*this))
        {
            cout<<"lines are intersected\n";
        }
        else
        {
            cout<<"Lines are crossed\n";
        }
    }
}

bool Line::crossing(Line& l)const
{

}


void Line::print()const
{
    cout<<"g:\nx = "<<base.getX()<<" ";
    if(direction.getX() >=0)cout<<"+"<<direction.getX()<<"s";
    else cout<<direction.getX()<<"s";
    cout<<"\ny = "<<base.getY()<<" ";
    if(direction.getY() >=0)cout<<"+"<<direction.getY()<<"s";
    else cout<<direction.getY()<<"s";
    cout<<"\nz = "<<base.getZ()<<" ";
    if(direction.getZ() >=0)cout<<"+"<<direction.getZ()<<"s";
    else cout<<direction.getZ()<<"s";
    cout<<"\nwhere s is from R\n";
}
