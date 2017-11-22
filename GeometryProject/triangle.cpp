#include<iostream>
#include<cmath>
#include "triangle.h"
#include "line.h"
using namespace std;
Triangle::Triangle(Point &p, Point &q, Point &t)
{
    A = p;
    B = q;
    C = t;
    trianglePlain = *new Plain(p,q,t);
    /**cout<<"triangle plain is ";
    trianglePlain.printGeneral();*/

}
Line Triangle::getSide(Point &p, Point &q)
{
    if(p == q){
        cout<<"invalid parameters\n";
    }
    else
    {
        if( (p==A || p==B || p==C) && (q==A || q==B || q==C) )
        {
            Line fin(p,q);
            return fin;
        }
        else
        {
            cout<<"invalid paramaters\n";
        }
    }
}

Vector Triangle::median(Point &vertex)
{
    if(vertex == A )
    {
        Vector fin(vertex,*new Point( (B.getX() + C.getX())/2,
                                        (B.getY() + C.getY())/2,
                                        (B.getZ() + C.getZ())/2 ));
        return fin;
    }
    if(vertex == B )
    {
        Vector fin(vertex,*new Point( (A.getX() + C.getX())/2,
                                        (A.getY() + C.getY())/2,
                                        (A.getZ() + C.getZ())/2 ));
        return fin;
    }
    if(vertex == C )
    {
        Vector fin(vertex,*new Point( (A.getX() + B.getX())/2,
                                        (A.getY() + B.getY())/2,
                                        (A.getZ() + B.getZ())/2 ));
        return fin;
    }

    cout<<"Invalid vertex\n";
    return *new Vector(0,0,0);
}

Line Triangle::symmetral(Point &p,Point &q)
{
    Point vertex;
    if(A != p && A != q)
    {
        vertex = A;
    }
    if(B != p && B != q)
    {
        vertex = B;
    }
    if(C != p && C != q)
    {
        vertex = C;
    }

    Point midPoint((p.getX() + q.getX())/2, (p.getY() + q.getY())/2, (p.getZ() + q.getZ())/2);
    Vector alt = altitude(vertex);
    Line symmetral(midPoint,alt);
    return symmetral;
}

Vector Triangle::altitude(Point &vertex)
{
    Point p,q;
    if(vertex == A)
    {
        p = B;
        q = C;
    }
    if(vertex == B)
    {
        p = A;
        q = C;
    }
    if(vertex == C)
    {
        p = A;
        q = B;
    }

    Vector vp(vertex,p),pq(p,q);
    double k = (-1)*(pq.getX()*vp.getX() + pq.getY()*vp.getY() + pq.getZ()*vp.getZ())/(pq.getX()*pq.getX() + pq.getY()*pq.getY() + pq.getZ()*pq.getZ());
    Point H(k*q.getX() + (1-k)*p.getX(), k*q.getY() + (1-k)*p.getY(), k*q.getZ() + (1-k)*p.getZ());
    Vector fin(vertex,H);
    return fin;
}

Vector Triangle::bisector(Point &vertex)
{
    Point p,q;
    if(vertex == A)
    {
        p = B;
        q = C;
    }
    if(vertex == B)
    {
        p = A;
        q = C;
    }
    if(vertex == C)
    {
        p = A;
        q = B;
    }
    Vector VP(vertex,p);
    Vector VQ(vertex,q);
    double vpLen = VP.getLen(), vqLen = VQ.getLen();
    Vector VL(VP.getX()/vpLen + VQ.getX()/vqLen, VP.getY()/vpLen + VQ.getY()/vqLen, VP.getZ()/vpLen + VQ.getZ()/vqLen);
    return VL;
}
Point Triangle::orthocenter()
{
    Line l1(A,altitude(A)),l2(B,altitude(B));
    //l1.print();
    //l2.print();
    Point H(l1,l2,1);
    return H;
}

Point Triangle::centroid()
{
    Line l1(A,median(A)),l2(B,median(B));
    Point G(l1,l2,1);
    return G;
}

Point Triangle::circumcenter()
{
    Point O(symmetral(A,B),symmetral(A,C),1);
    return O;
}

Point Triangle::incenter()
{
    Line l1(A,bisector(A)),l2(B,bisector(B));
    Point I(l1,l2,1);
    return I;
}

double Triangle::eulerDistance()
{
    Point I(incenter()),O(circumcenter());
    Vector IO(I,O);
    return IO.getLen();
}
