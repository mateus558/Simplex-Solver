#include <iostream>
#include <iomanip>
#include "../includes/simplex.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    Simplex solver(argv[1]);
    vector<double> x;
    int i;

    cout << fixed;
    cout << setprecision(3);

    x = solver.solve();
    if(x.size() > 0){
        cout << "Solucao x =" << endl;
        cout << "\t";
        for(i = 0; i < x.size(); i++){
            cout << x[i] << "\t";
        }
        cout << endl;
    }

    return 0;
}
