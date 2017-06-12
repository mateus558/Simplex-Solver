#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include "../includes/matrix.hpp"

using namespace std;

vector<string> split_line(string str){
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);

    return vstrings;
}

void print_matrix(dMatrix A, vector<uint> p){
    int i, j, n, m;

    n = A.size();
    m = A[0].size();

    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            cout << setprecision(3) << A[p[i]][j] << "\t";
        }
        cout << endl;
    }
}

void print_matrix(dMatrix A){
    int i, j, n, m;

    n = A.size();
    m = A[0].size();

    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            cout << setprecision(3) << A[i][j] << "\t";
        }
        cout << endl;
    }
}

void print_Lmatrix(dMatrix A, vector<uint> p){
    int i, j, n = A.size();

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j < i){
                cout << A[p[i]][j] << "\t";
            }else if(i == j){
                cout << 1.0 << "\t";
            }else{
                cout << 0.0 << "\t";
            }
        }
        cout << endl;
    }
}

void print_Umatrix(dMatrix A, vector<uint> p){
    int i, j, n = A.size();

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j >= i){
                cout << A[p[i]][j] << "\t";
            }else{
                cout << 0.0 << "\t";
            }
        }
        cout << endl;
    }
}

template <class T>
void print_vector(vector<T> v){
    int i, dim = v.size();

    cout << "[";
    for(i = 0; i < dim-1; i++){
        cout << v[i] << ", ";
    }
    cout << v[i] << "]" << endl;
}

double stodn(string str){
    double num, f = 0.1;
    int i = 1, m = 1, j = 0, sign = 0, size = str.size();

    if(str[0] == '-'){
        sign = 1;
    }

    for(i = i + sign; i < size; ++i){
        if(str[i] == '.') break;
        m *= 10;
    }

    for(i = sign; i < size; ++i){
        if(str[i] == '.'){
            i++;
            break;
        }
        num += int(str[i] - '0')*m;
        m /= 10;
    }

    for(j = i; j < size; ++j){
        if(str[j] >= int('0') && str[j] <= int('9')){
            num += int(str[j] - '0')*f;
            f *= 0.1;
        }
    }

    return (sign) ? num * -1 : num;
}

template void print_vector<int>(vector<int> v);
template void print_vector<uint>(vector<uint> v);
template void print_vector<double>(vector<double> v);
