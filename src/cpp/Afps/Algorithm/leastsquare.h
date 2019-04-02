#ifndef LEASTSQUARE_H
#define LEASTSQUARE_H

#include <vector>
#include <QDebug>

using namespace std;

class LeastSquare{
    double a, b;
public:
    LeastSquare(){

    }

    LeastSquare(const vector<double>& x, const vector<double>& y)
    {
        double t1=0, t2=0, t3=0, t4=0;
        for(int i=0; i<x.size(); ++i)
        {
            t1 += x[i]*x[i];
            t2 += x[i];
            t3 += x[i]*y[i];
            t4 += y[i];
        }
        a = (t3*x.size() - t2*t4) / (t1*x.size() - t2*t2);
        //b = (t4 - a*t2) / x.size();
        b = (t1*t4 - t2*t3) / (t1*x.size() - t2*t2);
    }

    double getY(const double x) const
    {
        return a*x + b;
    }

    void print() const
    {
        qDebug() <<"y = "<<a<<"x + "<<b<<"\n";
    }

};

#endif
