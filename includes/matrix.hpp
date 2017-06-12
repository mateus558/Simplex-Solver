#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <string>

typedef std::vector<std::vector<double> > dMatrix;

/*!
 * \brief split_line Split a string ignoring spaces.
 * \param str String to be splited.
 * \return Vector with the tokens.
 */
std::vector<std::string> split_line(std::string str);

/*!
 * \brief load_matrix Load a matrix from a file.
 * \param file  Path to the file where the matrix is located.
 * \return An nxn matrix of doubles.
 */
void load_matrix(std::string file, dMatrix &A, std::vector<double> &b);

/*!
 * \brief print_matrix Print a matrix nxm to the console.
 * \param A A nxm matrix of doubles.
 */
void print_matrix(dMatrix A, std::vector<uint> p);

/*!
 * \brief print_matrix Print a matrix nxm to the console.
 * \param A A nxm matrix of doubles.
 */
void print_matrix(dMatrix A);

/*!
 * \brief print_matrix Print a lower triangular matrix.
 * \param A A nxm matrix of doubles.
 * \param p = Permutation vector.
 */
void print_Lmatrix(dMatrix A, std::vector<uint> p);

/*!
 * \brief print_matrix Print a upper triangular matrix.
 * \param A A nxm matrix of doubles.
 * \param p = Permutation vector.
 */
void print_Umatrix(dMatrix A, std::vector<uint> p);

/*!
 * \brief print_vector Print a vector of size n.
 * \param v The vector to be printed.
 */
template <class T>
void print_vector(std::vector<T> v);

double dot(std::vector<double> a, std::vector<double> b);

double stodn(std::string str);

#endif
