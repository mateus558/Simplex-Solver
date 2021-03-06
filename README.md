﻿Objetivo:
---------
	 Implementar uma versão do resolvedor de problemas de programação linear (PL) simplex para problemas já com
	uma base associada a uma SBF.
	 
	 O projeto é composto por 3 pastas:
	../includes - Contém os arquivos .hpp do projeto
	../src 	 - Contém os arquivos .cpp do projeto
	../build	 - Contém os arquivos do CMake para compilação do projeto.
	 
	 Arquivos .hpp:
	lu_decomp.hpp - Biblioteca de métodos para decomposição LU e resolução de sistemas lineares utilizando a mesma.
	matrix.hpp	   - Utilidades para impressão e leitura de matrizes e impressão de vetores no console.
	simplex.hpp   - Biblioteca com os métodos que compõem o método simplex.
	 
	 Arquivos .cpp:
	main.cpp 	   - Arquivo principal do programa onde o projeto é executado.
	lu_decomp.cpp - Implementação dos métodos para decomposição LU e solução de sistemas lineares.
	utils.cpp 	   - Implementação dos métodos de utilidades utilizados no projeto. 
	simplex.cpp   - Implementação do método simplex.
 
Autor:
------
 	Mateus Coutinho Marim (mateus.marim@ice.ufjf.br)

Data:
-----
 	Junho 2017.

Como Compilar:
--------------
 	Digite "make" no diretório build que se encontra na pasta onde o projeto foi extraído.

Como Rodar:
-----------
	 Para executar o programa deve-se entrar no diretório build onde o projeto 
	foi extraído e fazer o seguinte: "./Project <input>" (<input> é o nome
	do arquivo onde o problema de PL está armazenado, deve estar no mesmo diretório do programa).
	 
	 O problema de PL deve estar na seguinte forma:
		m,n
		a11 a12 ... a1n
		 .  .		.
		 .  .		.
		am1 am2	... amn
		b1	b2	... bm
		c1	c2	...	cn
	
	 Onde m é o número de linhas da matriz, n é o número de colunas da matriz A, a ij são os coeficientes
	da matriz, b i são os coeficientes do vetor b, e c j são os coeficientes do vetor de custos c. Você pode
	sempre assumir que (i) m < n; (ii) b >= 0; e (iii) as últimas m variáveis formarão uma base inicial para
	o problema e que B = Im.
	
	 Para salvar a saída da execução basta fazer o seguinte: "./Project <input> >> <output>"
	Onde <output> é o nome do arquivo de saída que vai ser salvo na pasta onde o comando foi executado.
