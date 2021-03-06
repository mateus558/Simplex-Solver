#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <limits>
#include <numeric>
#include <cmath>

#include "../includes/lu_decomp.hpp"
#include "../includes/simplex.hpp"

#define EPS 1E-9

using namespace std;

Simplex::Simplex(const char* file, std::vector<uint> Ib)
{
    string f(file);

    if(f != ""){
        load(f);
    }

    //Caso os indices das colunas da base nao sejam passadas, as m ultimas colunas de A sao usadas
    if(Ib.size() == 0){
        this->Ib.resize(m);
        this->Nb.resize(n-m);
        iota(this->Ib.begin(), this->Ib.end(), n-m);
        iota(this->Nb.begin(), this->Nb.end(), 0);
    }else{
        this->Ib = Ib;
    }
}

void Simplex::load(string file){
    ifstream input(file);
    string line, buffer;
    vector<string> vals;
    int i, j;
    bool flag = false;

    getline(input, line);
    //Pega o valor de m e de n separados por ,
    for(i = 0; i < line.size(); i++){
        if(line[i] != ','){
            buffer.push_back(line[i]);
        }else if(!flag){
            flag = true;
            m = stoi(buffer);
            buffer.clear();
        }
    }
    n = stoi(buffer);

    //Aloca memoria para a matriz A (mxn), e para os vetores b e c
    A.resize(m);
    b.resize(m);
    c.resize(n);
    for(i = 0; i < m; i++){
        A[i].resize(n);
    }

    //Pega os valores da matriz A
    for(i = 0; getline(input, line) && i < m; i++){
        vals = split_line(line);
        for(j = 0; j < n; j++){
            A[i][j] = stodn(vals[j]);
        }
    }

    //Pega os valores do vetor b
    vals = split_line(line);
    for(j = 0; j < m; j++){
        b[j] = stodn(vals[j]);
    }

    //Pega os valores do vetor c
    getline(input, line);
    vals = split_line(line);
    for(j = 0; j < vals.size(); j++){
        c[j] = stodn(vals[j]);
    }
}

void Simplex::reducedCosts(vector<double> lambda, vector<double> &r, int &iminr){
    int i, j, nbsize = Nb.size();
    double dot, min = numeric_limits<double>::infinity();

    for(i = 0; i < nbsize; i++){
        //Produto interno de lambda*aj, onde aj sao as constantes das var. nao basicas.
        for(j = 0, dot = 0.0; j < m; j++){
            dot += lambda[j] * A[j][Nb[i]];
        }
        //Custo reduzido da var. nao basica i.
        r[i] = c[Nb[i]] - dot;

        //Verifica se eh menor que o menor custo reduzido ate o momento.
        if(r[i] < min){
            min = r[i];
            iminr = Nb[i];
        }
    }

    //Se o menor custo reduzido eh positivo, entao ri > 0, para i = 1,...,m e a solucao eh otima.
    if(min >= -EPS) iminr = -1;
}

vector<double> Simplex::solve(){
    int i, j, itr, q, ie;
    double min, INF = numeric_limits<double>::infinity();
    dMatrix B(m, vector<double>(m, 0.0));
    vector<uint> p(m);
    vector<double> Cb(m, 0.0), xb, lambda, r(n-m, 0.0), yq(m, 0.0), aq(m, 0.0), x;

    itr = 0;
    do{
        iota(p.begin(), p.end(), 0);

        //Monta a matriz B com as colunas que estao na base
        for(i = 0; i < m; i++){
            for(j = 0; j < m; j++){
                B[i][j] = A[i][Ib[j]];
            }
        }

        //Inicializa o vetor de custos das variaveis na base
        for(i = 0; i < m; i++){
            Cb[i] = c[Ib[i]];
        }

        //Faz a decomposicao LU da matriz B
        lu(B, p);
        //Encontra uma SBF resolvendo o sistema B*xb = b
        xb = lu_solve(B, p, b);
        //Encontra o vetor de lambdas
        lambda = lu_solve_trans(B, p, Cb);
        // Computa os custos reduzidos com a formula rj = cj - lambda' * aj, onde
        // j sao os indices das variaveis q nao estao na base e aj sao as colunas que
        // nao estao na base
        reducedCosts(lambda, r, q);

        //  q eh o indice da coluna que vai entrar na base, se q = -1, então todos custos reduzidos
        // sao maiores que 0 e a solucao eh otima.
        if(q == -1){
            break;
        }

        // Pega a coluna da variavel escolhida para entrar na base B
        for(i = 0; i < m; i++){
            aq[i] = A[i][q];
        }

        // Resolve o sistema B*yq = aq para obter yq
        yq = lu_solve(B, p, aq);
        //Computa epslon = argmin{(xb)i / (yq)i | (yq)i > 0}, i = 1,...,m
        for(i = 0, min = INF; i < m; i++){
            if(yq[i] <= 0){
                continue;
            }else{
                if(xb[i]/yq[i] < min){
                    min = xb[i]/yq[i];
                    ie = i;
                }
            }
        }

        //Se min eh infinito, yq > 0 para todo i, logo o problema eh ilimitado.
        //Caso contrario, a coluna associada ao (yq)i com menor epsilon, sai da base.
        if(min == INF){
            cout << "Problema não limitado" << endl;
            return x;
        }else{
            //Adiciona q as var. basicas e ie as nao basicas.
            Ib[ie] = q;
            Nb[q] = ie;
        }
        //Como nao atingimos a otimalidade, voltamos ao inicio do loop.
        itr++;
    }while(true);

    x.resize(n, 0.0);

    // A solucao otima x eh igual a xb nos indices da base e igual a 0 nos indices que
    // correspondem as variaveis nao basicas.
    for(i = 0, j = 0; i < n; i++){
        for(j = 0; j < Ib.size(); j++){
            if(i == Ib[j]){
                break;
            }
        }
        if(j < Ib.size()){
            x[i] = xb[j];
        }
    }

    return x;
}
