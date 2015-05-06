#include <iostream>
#include <random>
#include <math.h>

using namespace std;

// Costanti
const int N = 5;
const float MAX_NUM = 9.0;
const float e0 = 1e-7;

// Dichiarazione funzioni
void stampaVettore(float V[N]);
void stampaMatrice(float M[N][N]);
void stampaRisultato(float RIS[N]);

int main () 
{
	// Inizializza matrice A di dimensione NxN
	float A[N][N];
	// Inizializza vettore B di dimensione N
	float b[N];
	// Inizializza generatore numeri casuali
	default_random_engine generator;
	// Inizializza distribuzione tra 0 e MAX_NUM
  	uniform_real_distribution<float> vectorDistribution(0.0, MAX_NUM);

	// Generazione matrice
	cout << "Genero la matrice A e la stampo:\n";
	for(int i = 0; i < N; i++)
		for(int j = 0 ; j < N; j++)
		{
			A[i][j] = (int)vectorDistribution(generator) + 1;
			// Per imporre la dominanza, faccio sì che i valori lungo la diagonale siano maggiori o uguali alla somma dei restanti elementi
			if(i==j)
				A[i][j] += MAX_NUM*(N-1);
		}
	stampaMatrice(A);
	
	// Generazione vettore
	cout << "Genero il vettore b e lo stampo:\n";
	for(int i = 0; i < N; i++) 
		b[i] = (int)vectorDistribution(generator) + 1;
	stampaVettore(b);

	float x[N], newX[N], r[N];
	
	// Inizializzazione (azzero tutto)
	int n = 0;
	for(int i = 0; i < N; i++) 
	{
		x[i] = 0.0;
		newX[i] = 0.0;
	}
	
	float b_tot = 0, r_tot;
	
	// Sommatoria b
	for(int i = 0; i < N; i++) 
		b_tot += fabs(b[i]);

	r_tot = b_tot;
	float conv = r_tot/b_tot;
	
	// Controllo convergenza
	while(conv > e0)
	{
		for(int i = 0; i < N; i++)
			x[i] = newX[i];
		
		#pragma omp parallel for num_threads(N)
		for(int i = 0; i < N; i++)
		{
			float sommatoria = 0.0;
			
			// Calcolo sommatoria A[i][j]*x[j]
			for(int j = 0; j < N; j++)
				sommatoria += A[i][j] * x[j];
			
			r[i] = b[i] - sommatoria;
			
			// Calcolo x
			newX[i] = x[i] + (r[i]/A[i][i]);
		}
		
		r_tot = 0.0;
		
		for(int i = 0; i < N; i++) 
		{
			r_tot += fabs(r[i]);
		}
		
		n++;
		
		conv = r_tot / b_tot;
		
		cout << "Iterazione " << n << ": r(k)/b = " << conv << "\n";
	}
	
	// Visualizzazione risultato
	stampaRisultato(x);

	return 0;
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
			cout << M[i][j] << "\t";
		}
		cout << "\n";
	}	
}

// Stampa il risultato
void stampaRisultato(float RIS[N])
{
	for(int i = 0; i < N; i++) 
		cout << "X" << i+1 << " = " << RIS[i] << "\n";
}
