#include <iostream>
#include <cmath>

using namespace std;

const double WL = 5;
const double GRAVITY = 9.81;
const double MAX_LENGTH = 361;

class Point {
private:

    double x;
    double y;

public:

    Point(){
        x = 0;
        y = 0;
    }

    Point(double x0, double y0){
        x = x0;
        y = y0;
    }

    double getx()const{
        return x;
    }

    double gety()const{
        return y;
    }

    double distOrigin()const{
        return sqrt(pow(x,2) + pow(y,2));
    }

    double angleOrigin()const{
        return atan(y/x);
    }
};

class Link {
private:

    Point start;
    Point end;
    double length;
    double width;

public:

    Link(Point start0, Point end0, double width0){
        start = start0;
        end = end0;
        length = sqrt(pow(end.getx() - start.getx(),2) + pow(end.gety() - start.gety(),2));
        width = width0;
    };

    Point getStart()const{
        return start;
    }

    Point getEnd()const{
        return end;
    }

    double getLength()const{
        return length;
    }
    //radians wrt x axis
    double getAngle()const{
        return atan((end.gety() - start.gety())/(end.getx() - start.getx()));
    }

    double xDist()const{
        return end.getx() - start.getx();
    }

    double getWeight()const{
        return length*width*GRAVITY;
    }

};

double getTorque(Link links[3]){
    return links[0].xDist()*links[0].getWeight()/2
           + (links[0].xDist() + links[1].xDist()/2)*links[1].getWeight()
           + (links[0].xDist() + links[1].xDist() + links[2].xDist()/2)*links[2].getWeight()
           + (links[0].xDist() + links[1].xDist() + links[2].xDist())*WL*GRAVITY;
}

double firstPosition(double l1, double l2, double l3){
    Point end = Point(0.75,0.10);
    Point p2 = Point(0.75 - l3*cos(M_PI/3), 0.10 + l3*sin(M_PI/3));
    if(l1 + l2 < p2.distOrigin())
    {
        return 1000;
    }
    double angle1 = acos((pow(l2,2) - pow(l1,2) - pow(p2.distOrigin(),2))/(-2*l1*p2.distOrigin()));
    Point p11 = Point(l1*cos(angle1+p2.angleOrigin()),l1*sin(angle1+p2.angleOrigin()));
    Point p12 = Point(l1*cos(p2.angleOrigin()-angle1),l1*sin(p2.angleOrigin()-angle1));
    if(p11.getx() > p2.getx() && p11.gety() > p2.gety() && (p11.gety()-p2.gety())/(p11.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    if(p12.getx() > p2.getx() && p12.gety() > p2.gety() && (p12.gety()-p2.gety())/(p12.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(getTorque(links1),getTorque(links2));
}

double secondPosition(double l1, double l2, double l3){
    Point end = Point(0.50,0.50);
    Point p2 = Point(0.50 - l3, 0.50);
    if(l1 + l2 < p2.distOrigin())
    {
        return 1000;
    }
    double angle1 = acos((pow(l2,2) - pow(l1,2) - pow(p2.distOrigin(),2))/(-2*l1*p2.distOrigin()));
    Point p11 = Point(l1*cos(angle1+p2.angleOrigin()),l1*sin(angle1+p2.angleOrigin()));
    Point p12 = Point(l1*cos(p2.angleOrigin()-angle1),l1*sin(p2.angleOrigin()-angle1));
    if(p11.getx() > p2.getx() && p11.gety() > p2.gety() && (p11.gety()-p2.gety())/(p11.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    if(p12.getx() > p2.getx() && p12.gety() > p2.gety() && (p12.gety()-p2.gety())/(p12.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(getTorque(links1),getTorque(links2));
}

double thirdPosition(double l1, double l2, double l3){
    Point end = Point(0.20,0.60);
    Point p2 = Point(0.20 - l3*cos(M_PI/4), 0.60 - l3*sin(M_PI/4));
    if(l1 + l2 < p2.distOrigin())
    {
        return 1000;
    }
    double angle1 = acos((pow(l2,2) - pow(l1,2) - pow(p2.distOrigin(),2))/(-2*l1*p2.distOrigin()));
    Point p11 = Point(l1*cos(angle1+p2.angleOrigin()),l1*sin(angle1+p2.angleOrigin()));
    Point p12 = Point(l1*cos(p2.angleOrigin()-angle1),l1*sin(p2.angleOrigin()-angle1));
    if(p11.getx() > p2.getx() && p11.gety() > p2.gety() && (p11.gety()-p2.gety())/(p11.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    if(p12.getx() > p2.getx() && p12.gety() > p2.gety() && (p12.gety()-p2.gety())/(p12.getx()-p2.getx()) <= 1)
    {
        return 1000;
    }
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(getTorque(links1),getTorque(links2));
}

double getTotalTorque(double t1, double t2, double t3)
{
    return sqrt(pow(t1,2) + pow(t2,2) + pow(t3,2));
}

double combinations(){
    double least = 1000;
    for(int i = 1; i < MAX_LENGTH - 2; i++)
    {
        for(int k = 1; k < MAX_LENGTH - i - 1; k++)
        {
            int j = MAX_LENGTH - k - i;
            double j1 = j/100.0;
            double i1 = i/100.0;
            double k1 = k/100.0;
            double total_torque = getTotalTorque(firstPosition(j1,k1,i1), secondPosition(j1,k1,i1), thirdPosition(j1,k1,i1));
            if(total_torque < least && total_torque > 0)
            {
                cout << j << " " << k << " " << i << endl;
                least = total_torque;
            }
        }
    }
    return least;
}

int main() {
    cout << combinations() << endl;
    return 0;
}
