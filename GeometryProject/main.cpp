#include<iostream>
#include "point.cpp"
#include "vector.cpp"
#include "line.cpp"
#include "plain.cpp"
#include "triangle.cpp"
#include "Point_and_Line.h"
#include "geometry_functionality.cpp"
using namespace std;
void points_test(){
    Point p(1,0,0),q(0,0,0),t(0,0,0);
    cout<< (t==q);

}
void PNL_test()
{
    Point p(1,1,1),q(0,0,0);
    Line g(p,q);
    PointNLine pnl(p,g);
    Line test = pnl;
    test.print();
}
void additional_functionality_test()
{
    Point p(12,0,9),q(0,8,0),t(14,123,4);
    Line l(p,q);
    l.getDirection().print();
    Plain alpha(0,1,0,0);
    Point m = orthoProjection(l,alpha);
    m.print();
    cout<<"distance between ";
    q.print();
    cout<<"and alpha = "<<dist_between_point_and_plain(q,alpha)<<endl;
    angle_between_line_and_plain(l,alpha);
    cout<<"dist between point and line "<<dist_between_point_and_line(t,l)<<endl;
    Point a(0,0,0),b(1,0,0),c(0,5,0),d(1,5,-1);
    Line ab(a,b),cd(c,d);
    cout<<"dist between parallel lines "<<dist_between_line_and_line(ab,cd)<<endl;

}
void vector_test()
{
    Vector v1(12,5,6);
    Vector v2(6,5.0/2,3);
    Vector v3(-11,-5,-6);
    cout<<v1.isCollinearWith(v2)<<endl;
    Vector v = v1.sum(v3);
    v.print();

    Vector c(1,-3,1),a(12,1,0.75);
    cout<<endl<<c.scalarWork(a)<<endl;
}
void points_vectors_test()
{
    Point p(12.5 , 14.36,45),q(1,1,1);
    p.print();
    q.print();
    Vector pq(p,q);
    Vector a(15,0,6);
    pq.print();
    a.print();
    cout<<endl<<endl<<endl;

    Vector b(15,0,6);
    cout<<" are collinear a & b "<<b.isCollinearWith(a);

    cout<<"\n\nvector work test:\n";
    Vector m(14,2,3.12),z(21.32,0,0);
    m.vectorWork(z).print();
    //m.print();
}
void lines_test()
{
    Point p(1,5,8),s(10,0,2),r(6,2,2);
    Line l1(p,p),l2(p,*new Vector(0,0,0));
    l1.print();
    l2.print();
}

void plains_test()
{
    Point p(0,1,1),q(0,1,0),t(0,1,1),r(0,0,1);
    Plain a(1,2,0,0),b(r,t,q);
    Vector v(1,2,3);
    a.printGeneral();
    b.printGeneral();
    Line l(p,q);
    cout<<a.checkPoint(p)<<endl;
    cout<<"parallelism with line check "<<a.isLineParallel(l)<<endl;
    cout<<"parallelism with plain check "<<a.isPlainParallel(b)<<endl;

    Vector v1(1,0,0),v2(0,1,0);
    Plain pl(v1,v2);
    cout<<endl;
    pl.printGeneral();

    cout<<endl<<"\n\n\n testing plain constructor by point and line\n\n";
    Line tan(*new Point(0,0,0), *new Vector(1,1,1));
    tan.print();
    Plain plak(*new Point(3,3,3),tan);
    plak.printGeneral();
    plak.printParametric();
}
void pointByLineAndPlain()
{

    Point start(1.75,1,1);
    Vector dir(1.75,2,3);
    Line l(start, dir);
    cout<<" line ";
    l.print();
    Plain p(1,0,0,0);
    p.printGeneral();
    Point believe(l,p);
    believe.print();

    cout<<endl<<endl<<endl;
    Line l1(*new Point(0,1,1), *new Point(1,1,0)), l2(*new Point(1,1,0), *new Point(1,1,1));
    l1.print();
    l2.print();

    Point believe2(l1,l2);
    believe2.print();

}

void testLinesCollision()
{
    Line l1(*new Point(0,0,0), *new Point(1,0,0)), l(*new Point(1,1,0), *new Point(0,1,1));
    l1.print();
    l.print();
    l1.check(l);
}
void testPlainPrints()
{
    Plain test(0,1,0,1);
    test.printGeneral();
    test.printParametric();
}
void test_line_ctor_by_2_plains()
{
    Plain p(0,1,3,14), q(-5,2,1,0);
    p.printGeneral();
    q.printGeneral();
    Line believe (p,q);

    believe.print();
}
void test_triangles()
{
    Point p1(0,0,0), p2(4.20,0,0),p3(1,4.20,0);
    Triangle tr(p1,p2,p3);
    Line l1(p1,p3),l2(p2,p3);
    tr.bisector(p1).print();
    cout<<"circumcenter: ";
    tr.circumcenter().print();
    cout<<"incenter: ";
    tr.incenter().print();
    cout<<"euler distance = "<<tr.eulerDistance()<<endl;
    cout<<"centroid: ";
    tr.centroid().print();
}
int main(){
    //lines_test();
    //points_vectors_test();
    //points_test();
    //vector_test();
    //plains_test();
    //pointByLineAndPlain();
    //testLinesCollision();
    //testPlainPrints();
    //test_line_ctor_by_2_plains();
    //test_triangles();
    //PNL_test();
    additional_functionality_test();
    return 0;
}
