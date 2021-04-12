#include <iostream>
#include <cmath>

using namespace std;

const double WL = 5;
const double GRAVITY = 9.81;

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
        length = sqrt(pow(end.getx() - start.getx(),2) + pow(end.gety() - end.gety(),2));
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
        return atan((end.gety() - end.gety())/(end.getx() - start.getx()));
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

double getTotalTorque(double t1, double t2, double t3)
{
    return sqrt(pow(t1,2) + pow(t2,2) + pow(t3,2));
}

int main() {
    Point p0 = Point(0,0);
    Point p1 = Point(10,0);
    Point p2 = Point(20,0);
    Point p3 = Point(30,0);
    Link links[] = {Link(p0,p1,4), Link(p1,p2,2), Link(p2,p3,1)};
    cout << getTorque(links)<< endl;
    return 0;
}
