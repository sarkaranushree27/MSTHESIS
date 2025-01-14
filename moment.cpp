#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include<cmath>
#include<chrono>
#include<random>


int t=4000;
using namespace std;

int main()
{
    //ofstream out1  ("run1.txt");
    ofstream out2 ("moment4.txt");

    auto seed= chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt1(seed);

    int i, j, a;
    double b, r, x_new, y_new, p, moment[t+2]={0}, dm, n ;
    vector <double> area, x, y, endx, endy, length, width;
    cout<<"Enter the power="<<endl;
    cin>>n;

    //out1 << "set xr [0:1]" << endl;
    //out1 << "set yr [0:1]" << endl;
    //out1 << "set object rect from " << 0 <<"," << 0 << " to " << 1 <<"," << 1 << endl;

    area ={0, 1}, x={0, 0}, y={0, 0}, endx={0, 1}, endy={0, 1}, length={0, 1}, width={0, 1} ;

    for ( i=0; i<=t; i++)
    {
            r = (double) mt1()/(double)mt1.max() ;
            for ( j=0; j<area.size(); j++)
            {
                if (area[j] < r && r < area[j+1])
                {       a=j+1;     }
                moment[i] += pow(length[j],n)*pow(width[j],1/n);
            }

            x_new = ( (double) mt1()/(double)mt1.max() )*length[a] ;
            y_new = ( (double) mt1()/(double)mt1.max() )*width[a] ;
            p = (double) mt1()/(double)mt1.max() ;

            if (p<0.50000) //horizontal divide
            {
                x.insert(x.begin()+a+1, x[a]);
                y.insert(y.begin()+a+1, y[a]+y_new);
                endx.insert(endx.begin()+a+1, endx[a]);
                endy.insert(endy.begin()+a+1, endy[a]);

                endy[a]= y[a]+y_new;

                length[a] = endx[a]-x[a];
                width [a] = endy[a]-y[a];
                b = length[a]*width[a];
                area[a] = area[a-1]+b;

                length.insert(length.begin()+a+1, endx[a+1]-x[a+1]);
                width.insert(width.begin()+a+1, endy[a+1]-y[a+1]);
                b = length[a+1]*width[a+1];
                area.insert(area.begin()+a+1, area[a]+ b);

            }

            else //vertical divide
            {
                x.insert(x.begin()+a+1, x[a]+x_new);
                y.insert(y.begin()+a+1, y[a]);
                endx.insert(endx.begin()+a+1, endx[a]);
                endy.insert(endy.begin()+a+1, endy[a]);

                endx[a]= x[a]+x_new;

                length[a] = endx[a]-x[a];
                width [a] = endy[a]-y[a];
                b = length[a]*width[a];
                area[a] = area[a-1]+ b;

                length.insert(length.begin()+a+1, endx[a+1]-x[a+1]);
                width.insert(width.begin()+a+1, endy[a+1]-y[a+1]);
                b = length[a+1]*width[a+1];
                area.insert(area.begin()+a+1, area[a]+ b);
            }

    }

    for (i=0; i<=t; i++)
    {
        //out1 << "set object rect from " << x[i] <<"," << y[i] << " to " << endx[i] <<"," << endy[i] << endl;
        out2<<i <<"  " <<moment[i] <<endl;

    }


    return 0;
}
