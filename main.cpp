#include <iostream>
#include <cmath>

using namespace std;

const double WL = 5;
const double GRAVITY = 9.81;
const double MAX_LENGTH = 554;

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
        return atan2(y,x);
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

    bool intersects(Link link0)const{
        double a1 = end.gety() - start.gety();
        double b1 = start.getx() - end.getx();
        double c1 = a1*(start.getx()) + b1*(start.gety());

        double a2 = link0.end.gety() - link0.start.gety();
        double b2 = link0.start.getx() - link0.end.getx();
        double c2 = a2*(link0.start.getx())+ b2*(link0.start.gety());

        double determinant = a1*b2 - a2*b1;

        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;

        Link i0 = Link(start,Point(x,y),1);
        Link i1 = Link(Point(x,y),end,1);
        if(abs(i0.getLength() + i1.getLength() - length) < 0.000001)
        {
            return true;
        }
        return false;
    }
};

double getTorque(Link links[3]){
    if(links[0].intersects(links[2]))
    {
        return 1000;
    }
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
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(abs(getTorque(links1)),abs(getTorque(links2)));
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
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(abs(getTorque(links1)),abs(getTorque(links2)));
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
    Link links1[] = {Link(Point(0,0),p11,4), Link(p11,p2,2), Link(p2,end,1) };
    Link links2[] = {Link(Point(0,0),p12,4), Link(p12,p2,2), Link(p2,end,1) };
    return min(abs(getTorque(links1)),abs(getTorque(links2)));
}

double getTotalTorque(double t1, double t2, double t3)
{
    return sqrt(pow(t1,2) + pow(t2,2) + pow(t3,2));
}

double combinations(int length){
    double least = 1000;
    for(int i = 1; i < length - 2; i++)
    {
        for(int k = 1; k < length- i - 1; k++)
        {
            int j = length - k - i;
            double j1 = j/100.0;
            double i1 = i/100.0;
            double k1 = k/100.0;
            double total_torque = getTotalTorque(firstPosition(j1,k1,i1), secondPosition(j1,k1,i1), thirdPosition(j1,k1,i1));
            if(total_torque < least && total_torque > 0)
            {
                cout << j << " " << k << " " << i << endl;
                cout << firstPosition(j1,k1,i1) << " " << secondPosition(j1,k1,i1) << " " << thirdPosition(j1,k1,i1) << endl;
                least = total_torque;
            }
        }
    }
    return least;
}

int main() {
    int length = 700;
    double least = 10000;
    /*for(int i = 500; i < length; i++)
    {
        double least1 = combinations(i);
        if(least1 < least)
        {
            least = least1;
        }
    }*/
    cout << combinations(559) << endl;
    return 0;
}
