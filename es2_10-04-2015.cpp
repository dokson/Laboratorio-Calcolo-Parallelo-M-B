#include <iostream>
#include <random>
#include <math.h>
#include <iomanip>

using namespace std;

// Costanti
const int N = 3;
const int MAX_SCALAR = 9;
const float MAX_NUM = 5.0;

// Dichiarazione funzioni
void stampaVettore(float V[N]);
void stampaMatrice(float M[N][N]);

void prodottoPerScalare(float M[N][N], int c);
float *prodottoMatriceVettore(float M[N][N], float V[N]);
float prodottoMatriciale(float M1[N][N], float M2[N][N], float prodotto[N][N]);

int main()
{
	// Inizializza vettore di dimensione N
	float a[N];
	// Inizializza una matrice di dimensione NxN
	float A[N][N];
	// Inizializza generatore numeri casuali
	default_random_engine generator;
	// Inizializza distribuzione tra 0 e MAX_NUM
  	uniform_real_distribution<float> vectorDistribution(0.0, MAX_NUM);
  	// Inizializza distribuzione tra 1 e MAX_SCALAR
	uniform_int_distribution<int> scalarDistribution(1, MAX_SCALAR);
	
	// Generazione vettore
	cout << "Genero il vettore a e lo stampo:\n";
	for(int i = 0; i < N; i++) 
		a[i] = vectorDistribution(generator);
	stampaVettore(a);
	
	// Generazione matrice
	cout << "Genero la matrice A e la stampo:\n";
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			A[i][j] = vectorDistribution(generator);
	stampaMatrice(A);
	
	// Calcolo prodotto della matrice A per scalare c
	int c = scalarDistribution(generator);
	cout << "Moltiplico la matrice A per " << c << ":\n";
	prodottoPerScalare(A, c);
	stampaMatrice(A);
	
	// Calcolo prodotto della matrice A per il vettore a
	cout << "Moltiplico la matrice A per il vettore a:\n";
	stampaVettore(prodottoMatriceVettore(A, a));
	
	// Inizializza una matrice di dimensione NxN
	float B[N][N];
	
	// Generazione matrice
	cout << "Genero la matrice B e la stampo:\n";
	for(int i = 0 ; i < N; i++)
		for(int j = 0 ; j < N; j++)
			B[i][j] = vectorDistribution(generator);
	stampaMatrice(B);
	
	// Calcolo prodotto della matrice A per la matrice B
	cout << "Moltiplico la matrice A per la matrice B:\n";
	float prodotto[N][N];
	prodottoMatriciale(A, B, prodotto);
	stampaMatrice(prodotto);
	
	return 1;
}

// Stampa il vettore
void stampaVettore(float V[N])
{
	for(int i = 0 ; i < N; i++) 
		cout << "Elemento " << i+1 << " = " << V[i] << "\n";
}

// Stampa la matrice
void stampaMatrice(float M[N][N])
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout << setprecision(4) << M[i][j] << "\t";
		}
		cout << "\n";
	}
}

// Esegue prodotto di una matrice per uno scalare
void prodottoPerScalare(float matrice[N][N], int scalare)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++) 
			matrice[i][j] *= scalare;
}

// Calcola il prodotto scalare di una matrice per un vettore
float *prodottoMatriceVettore(float M[N][N], float V[N])
{
	float result[N];

	for(int i = 0; i < N; i++)
	{
		float x = 0;

		for(int j = 0; j < N; j++) 
		{
			x += M[i][j] * V[j];
		}
		result[i] = x;
	}
	return result;
}

// Calcola il prodotto di due matrici NxN
float prodottoMatriciale(float M1[N][N], float M2[N][N], float result[N][N])
{
	#pragma omp parallel for collapse(2)
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			{
				float x = 0;
				#pragma omp parallel for reduction(+:x)
		        for (int r = 0; r < N; r++)
		        {
		           x += M1[i][r] * M2[r][j];
		        }
		        result[i][j] = x;
            }
}


