#include <cmath>
#include <iostream>
#include "../includes/lu_decomp.hpp"
#include "../includes/matrix.hpp"

using namespace std;

vector<double> suc_substitution(dMatrix A, std::vector<uint> p, std::vector<double> b){
    int i, j, n = A.size();
    vector<double> x(n, 0);

    for(i = 0; i < n; i++){
        x[i] = b[p[i]];

        for(j = 0; j < i; j++){
            x[i] = x[i] - A[p[i]][j] * x[j];
        }
        x[i] = x[i] / 1.0;
    }

    return x;
}

vector<double> ret_substitution(dMatrix A, std::vector<uint> p, std::vector<double> b){
    int i, j, n = A.size();
    vector<double> x(n, 0);

    for(i = n-1; i >= 0; i--){
        x[i] = b[i];

        for(j = i+1; j < n; j++){
            x[i] = x[i] - A[p[i]][j] * x[j];
        }
        x[i] = x[i] / A[p[i]][i];
    }

    return x;
}

void lu(dMatrix &A, std::vector<uint> &p){
    int i, j, k, n = A.size(), imax, tmp;
    double max, m;

    for(k = 0; k < n-1; k++){
        max = fabs(A[p[k]][k]);
        imax = k;

        for(i = k+1; i < n; i++){
            if(max < fabs(A[p[i]][k])){
                max = fabs(A[p[i]][k]);
                imax = i;
            }
        }

        tmp = p[k];
        p[k] = p[imax];
        p[imax] = tmp;

        for(i = k + 1; i < n; i++){
            m = A[p[i]][k] / A[p[k]][k];
            for(j = k; j < n; j++){
                A[p[i]][j] = A[p[i]][j] - m * A[p[k]][j];
            }
            A[p[i]][k] = m;
        }
    }
}

vector<double> lu_solve(dMatrix A, std::vector<uint> p, std::vector<double> b){
    vector<double> x;

    x = suc_substitution(A, p, b);
    x = ret_substitution(A, p, x);

    return x;
}

vector<double> lu_solve_trans(dMatrix A, std::vector<uint> p, std::vector<double> b){
    int i, j, n = A.size();
    vector<double> x(n, 0), y(n, 0), lambda(n, 0);

    //Solve U'y = b
    for(i = 0; i < n; i++){
        y[i] = b[i];

        for(j = 0; j < i; j++){
            y[i] = y[i] - A[p[j]][i] * y[j];
        }
        y[i] = y[i] / A[p[i]][i];
    }

    //Solve L'x = y
    for(i = n-1; i >= 0; i--){
        x[i] = y[i];

        for(j = i+1; j < n; j++){
            x[i] = x[i] - A[p[j]][i] * x[j];
        }
        x[i] = x[i] / 1.0;
    }

    //Solve P*lambda = x
    for(i = 0; i < n; i++){
        lambda[p[i]] = x[i];
    }

    return lambda;
}
