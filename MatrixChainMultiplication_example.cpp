#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand()
#include <string>
#include <vector>
using namespace std;
#include<iostream>
using namespace std;

//const int INT_MAX = 2147483647;
int const M = 4;

void MATRIX_CHAIN_ORDER(int* p, int Length, int m[][M], int s[][M])
{
	int q, n = Length - 1;
	for (int i = 1; i <= n; i++) m[i][i] = 0;
	for (int l = 2; l <= n; l++) 	/* �������ĳ��� */
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;         /* �ȼ��� l=j-i+1 */
			m[i][j] = INT_MAX;
			for (int k = i; k <= j - 1; k++)
			{
				q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}
void PRINT_OPTIMAL_PARENS(int s[][M], int i, int j)
{
	if (i == j) cout << "A" << i;
	else
	{
		cout << "(";
		PRINT_OPTIMAL_PARENS(s, i, s[i][j]);
		PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j);
		cout << ")";
	}
}

int main()
{
	//M=the number of matrices + 1
	//int p[M] = { 30,35,15,5,10,20,25 }; //6 matrices
	//int p[M] = { 5, 10, 3, 12, 5, 50, 6 };
	int p[M] = { 10,100,5,50 };
	int m[M][M], s[M][M];
	MATRIX_CHAIN_ORDER(p, M, m, s);
	cout << "���Ž�����������: \n" << m[1][M-1];
	cout << "\n���Ż�����Ϊ��\n";
	PRINT_OPTIMAL_PARENS(s, 1, M-1);
	return 0;
}