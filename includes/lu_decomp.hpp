#ifndef LU_DECOMPOSE_H_INCLUDED
#define LU_DECOMPOSE_H_INCLUDED

#include <vector>
#include <string>

typedef std::vector<std::vector<double> > dMatrix;
typedef unsigned int uint;

/*!
 * \brief lu    A função faz a decomposição LU na matriz A.
 * \param A = Matriz
 * \param p = Vetor de permutação
 */
void lu(dMatrix &A, std::vector<uint> &p);

/*!
 * \brief lu_solve  Resolve o o sistema Ax=b usando a decomposição LU.
 * \param A = Matriz
 * \param p = Vetor de Permutação
 * \param b = Vetor de constantes
 * \return um array de double contendo a solução x.
 */
std::vector<double> lu_solve(dMatrix A, std::vector<uint> p, std::vector<double> b);

/*!
 * \brief lu_solve  Resolve o sistema labda^T A = b^T usando a decomposição LU.
 * \param A = Matriz
 * \param p = Vetor de Permutação
 * \param b = Vetor de constantes (do sistema lambda^T A = b^T)
 * \return um array de double contendo a solução lambda.
 */
std::vector<double> lu_solve_trans(dMatrix A, std::vector<uint> p, std::vector<double> b);

/*!
 * \brief suc_substitution  Faz a substituicao sucessiva de uma matrix triangular superior para achar a solucao de um sistema.
 * \param A = Matriz
 * \param p = Vetor de Permutação
 * \param b = Vetor de constantes
 * \return um array de double contendo a solução.
 */
std::vector<double> suc_substitution(dMatrix A, std::vector<uint> p, std::vector<double> b);

/*!
 * \brief ret_substitution  Faz a substituicao retroativa de uma matrix triangular inferior para achar a solucao de um sistema.
 * \param A = Matriz
 * \param p = Vetor de Permutação
 * \param b = Vetor de constantes
 * \return um array de double contendo a solução.
 */
std::vector<double> ret_substitution(dMatrix A, std::vector<uint> p, std::vector<double> b);

#endif
