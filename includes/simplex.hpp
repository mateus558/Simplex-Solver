#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <string>

#include "../includes/matrix.hpp"

class Simplex
{
private:
    int m, n;
    dMatrix A;
    std::vector<double> b, c;
    std::vector<uint> Ib;

    int isOptimal(std::vector<double> r);
    std::vector<double> reducedCosts(std::vector<double> lambda, std::vector<double> &r, int &iminr);
public:
    Simplex(const char* file = "", std::vector<uint> Ib = std::vector<uint>());
    void load(std::string file);
    std::vector<double> solve();
};

#endif // SIMPLEX_H
