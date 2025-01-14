#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

double datageneration(int n_iter)
{
    ofstream out1("run2.txt");

    auto seed= chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 mt1(seed);

    int i, j, a;
    double b, r, prob, x_new, y_new;
    vector<double>area {0,1};
    vector<vector<double>> lattice
    {
    {0, 0},//x
    {0, 0},//y
    {0, 1},//endx
    {0, 1} //endy
    };

    out1 << "set xr [0:1]" << endl;
    out1 << "set yr [0:1]" << endl;
    out1 << "set object rect from 0,0 to 1,1 " << endl;

    for (i = 0; i < n_iter; i++)
    {
        r = (double)rand()/(double)RAND_MAX;

        for (j = 0; j < area.size(); j++)
        {
            if (area[j] < r && r < area[j+1])
            {   a = j + 1;    }
        }

        x_new = ( ((double)mt1() / (double)mt1.max()) * (lattice[2][a] - lattice[0][a]) );
        y_new = ( ((double)mt1() / (double)mt1.max()) * (lattice[3][a] - lattice[1][a]) );
        prob = (double)mt1() / (double)mt1.max();

         if (prob < 0.50000) // horizontal divide
        {
            lattice[0].insert(lattice[0].begin()+a+1, lattice[0][a]) ;
            lattice[1].insert(lattice[1].begin()+a+1,  lattice[1][a] + y_new) ;
            lattice[2].insert(lattice[2].begin()+a+1,  lattice[2][a]) ;
            lattice[3].insert(lattice[3].begin()+a+1,  lattice[3][a]) ;


            lattice[3][a]=lattice[1][a]+y_new;
            area[a] = area[a-1]+( (lattice[2][a] - lattice[0][a]) * (lattice[3][a]- lattice[1][a]) );
            area.insert(area.begin()+a+1, (area[a]+ ( (lattice[2][a+1] - lattice[0][a+1]) * (lattice[3][a+1] - lattice[1][a+1]))) );



        }
        else // vertical divide
        {
            lattice[0].insert(lattice[0].begin()+a+1, lattice[0][a]+ x_new) ;
            lattice[1].insert(lattice[1].begin()+a+1,  lattice[1][a]) ;
            lattice[2].insert(lattice[2].begin()+a+1,  lattice[2][a]) ;
            lattice[3].insert(lattice[3].begin()+a+1,  lattice[3][a]) ;

            lattice[2][a] = lattice[0][a] + x_new;
            area[a] = area[a-1]+((lattice[2][a] - lattice[0][a]) * (lattice[3][a] - lattice[1][a]));
            area.insert(area.begin()+a+1, (area[a]+ ((lattice[2][a+1] - lattice[0][a+1])*(lattice[3][a+1] - lattice[1][a+1]))) );


        }
           }
    for (i = 0; i < lattice[0].size(); i++)
    {
        out1 << "set object rect from " << lattice[0][i] <<"," << lattice[1][i] << " to " << lattice[2][i] <<"," << lattice[3][i] << endl;
    }

      return 0;
}

 int main()
 {  int t;
      cout<<"enter the number of iteration =";
      cin>>t;
      datageneration(t);
      return 0;
 }

