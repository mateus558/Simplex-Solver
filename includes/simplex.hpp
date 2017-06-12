#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <vector>
#include <string>

#include "../includes/matrix.hpp"

/**
 * @brief The Simplex class implements the simplex method to solve linear programming problems.
 * @author Mateus Coutinho Marim - mateus.marim@ice.ufjf.br
 */
class Simplex
{
private:
    /// m eh o numero de restricoes e n o numero de variaveis.
    int m, n;
    /// A e a matriz de custos das restricoes do problema.
    dMatrix A;
    /// b eh o bias e c sao os custos da funcao objetivo.
    std::vector<double> b, c;
    /// Ib eh o vetor de indices das colunas que estao na base.
    std::vector<uint> Ib;

    /**
     * @brief reducedCosts Computa os custos reduzidos e verifica se a SBF eh otima.
     * @param lambda Vetor de lambdas para computar os r.
     * @param r Vetor de custos reduzidos.
     * @param iminr Indice do menor custo reduzido, se igual -1, a solucao eh otima.
     * @return void
     */
    void reducedCosts(std::vector<double> lambda, std::vector<double> &r, int &iminr);
public:
    /**
     * @brief Simplex Construtor da classe.
     * @param file  Arquivo com o problema de PL.
     * @param Ib Indices de uma matriz associada a uma SBF inicial, caso nao seja passado, as ultimas
     *  m variaveis sao consideradas como as colunas da base.
     */
    Simplex(const char* file = "", std::vector<uint> Ib = std::vector<uint>());
    /**
     * @brief load  Carrega um problema de PL a partir de um arquivo.
     * @param file  Arquivo com o problema de PL.
     */
    void load(std::string file);
    /**
     * @brief solve Resolve o problema de PL e retorna uma solucao otima, caso retorne
     *  um vetor vazio, o problema eh ilimitado.
     * @return  vector<double>
     */
    std::vector<double> solve();
};

#endif // SIMPLEX_H
