#include<iostream>
#include "plain.h"
#include "line.h"
using namespace std;
Point& makePointNotInPlain(Plain &pl)
{
    int _x,_y,_z;
    Point p;
    do
    {
        _x = rand()%20+1;
        _y = rand()%20+1;
        _z = rand()%20+1;
        p = *new Point(_x,_y,_z);
    }while( pl.checkPoint(p) );

    return p;
}

Plain::Plain(double _x, double _y, double _z, double _t)
    :x(_x), y(_y), z(_z), t(_t) {
        n = *new Vector(x,y,z);
        if(x==0&&y==0&&z==0)
        {
            t = 0;
        }else
        {

            Point q1 = makePointNotInPlain(*this);
            Point q2,q3;
            do
            {
                q2 = makePointNotInPlain(*this);
            }while(q2 == q1);

            do
            {
                q3 = makePointNotInPlain(*this);
            }while(q3.isOnLine(*new Line(q1,q2) ));

            Point p1(*new Line(q1,n), *this);
            Point p2(*new Line(q2,n), *this);
            Point p3(*new Line(q3,n), *this);

            base = p1;
            v1 = *new Vector(p1,p2);
            v2 = *new Vector(p1,p3);

        }
    }


Plain::Plain(Point &p, Point &q, Point &r)
{
    Vector v(p,q),m(p,r);
    v1 = v,v2 = m;
    n = v.vectorWork(m);
    x = n.getX();
    y = n.getY();
    z = n.getZ();
    if(x==0&&y==0&&z==0)
    {
        cout<<"Plain could not be created\n";
        return;
    }
   // cout<<"x = "<<x<<"   y = "<<y<<"   z = "<<z<<endl;
    //cout<<"x1 = "<<p.getX()<<"   y1 = "<<p.getY()<<"   z1 = "<<p.getZ()<<endl;
    t = 0 - x*p.getX() - y*p.getY() - z*p.getZ();
}

Plain::Plain(Vector &p, Vector &q)
{
    n = p.vectorWork(q);
    v1 = p;
    v2 = q;
    x = n.getX();
    y = n.getY();
    z = n.getZ();
    if(x==0&&y==0&&z==0)
    {
        cout<<"Plain could not be created\n";
        return;
    }
    t = 0 - x - y - z;
}

Plain::Plain(Point p, Line l)
{
    n = l.getDirection();
    x = n.getX();
    y = n.getY();
    z = n.getZ();
    t = 0 - x*p.getX() - y*p.getY() - z*p.getZ();
    *this = *new Plain(x,y,z,t);
}

Plain::Plain(Point &p, Plain &a)
{
    x = a.getNormalVector().getX();
    y = a.getNormalVector().getY();
    z = a.getNormalVector().getZ();
    n = *new Vector(x,y,z);
    if(x==0&&y==0&&z==0)
    {
        cout<<"Plain could not be created\n";
    }
    t = 0 - x*p.getX() - y*p.getY() - z*p.getZ();
}
void Plain::printGeneral()const
{
    cout<<" a:";
    if(x>0)cout<<"+"<<x<<"x";
    else if(x<0)cout<<x<<"x";
    if(y>0)cout<<"+"<<y<<"y";
    else if(y<0)cout<<y<<"y";
    if(z>0)cout<<"+"<<z<<"z";
    else if(z<0)cout<<z<<"z";
    if(t>0)cout<<"+"<<t;
    else if(t<0)cout<<t;
    cout<<"=0\n";
}
void Plain::printParametric()const
{
    cout<<"alpha:\nx = "<<base.getX()<<" ";

    if(v1.getX() >=0)cout<<"+"<<v1.getX()<<"s";
    else cout<<v1.getX()<<"s";

    if(v2.getX() >=0)cout<<"+"<<v2.getX()<<"p";
    else cout<<v2.getX()<<"p";

    cout<<"\ny = "<<base.getY()<<" ";

    if(v1.getY() >=0)cout<<"+"<<v1.getY()<<"s";
    else cout<<v1.getY()<<"s";

    if(v2.getY() >=0)cout<<"+"<<v2.getY()<<"p";
    else cout<<v2.getY()<<"p";

    cout<<"\nz = "<<base.getZ()<<" ";

    if(v1.getZ() >=0)cout<<"+"<<v1.getZ()<<"s";
    else cout<<v1.getZ()<<"s";

    if(v2.getZ() >=0)cout<<"+"<<v2.getZ()<<"p";
    else cout<<v2.getZ()<<"p";

    cout<<"\nwhere s and p are from R\n";
}





