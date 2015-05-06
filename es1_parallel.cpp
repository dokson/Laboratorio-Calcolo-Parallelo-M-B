#include <iostream>
#include <random>
#include <math.h>

using namespace std;

// Costanti
const int N = 10;
const int MAX_SCALAR = 7;
const float MAX_NUM = 100.0;

// Dichiarazione funzioni
void stampaVettore(float V[N]);
void prodottoScalare(float V[N], int c);
float modulo(float V[N]);
float prodottoScalare(float V1[N], float V2[N]);
void scambiaElemento(float& a, float& b);
void scambiaVettori(float V1[N], float V2[N]);

int main()
{
	// Inizializza vettore di dimensione N
	float A[N];
	// Inizializza generatore numeri casuali
	default_random_engine generator;
	// Inizializza distribuzione tra 0 e MAX_NUM
  	uniform_real_distribution<float> vectorDistribution(0.0, MAX_NUM);
  	// Inizializza distribuzione tra 1 e MAX_SCALAR
	uniform_int_distribution<int> scalarDistribution(1, MAX_SCALAR);
	
	// Generazione vettore
	cout << "Genero il vettore A e lo stampo:\n";
	for(int i = 0; i < N; i++) 
		A[i] = vectorDistribution(generator);
	stampaVettore(A);
	
	// Calcolo prodotto di vettore A per scalare c
	int c = scalarDistribution(generator);
	cout << "Moltiplico il vettore per " << c << ":\n";
	prodottoScalare(A, c);
	stampaVettore(A);
	
	// Calcolo modulo
	cout << "Il modulo del vettore è: " << modulo(A) << "\n";
	
	// Inizializza un altro vettore di dimensione N
	float B[N];
	// Generazione vettore
	cout << "Genero il vettore B e lo stampo:\n";
	for(int i = 0; i < N; i++) 
		B[i] = vectorDistribution(generator);
	stampaVettore(B);
	
	// Calcolo prodotto scalare tra i due vettori A e B
	cout << "Il prodotto scalare dei due vettori è: " << prodottoScalare(A, B) << "\n";
	
	// Scambio dei due vettori tra loro
	cout << "Inverto tra loro i due vettori A e B\n";
	scambiaVettori(A, B);
	cout << "Vettore A:\n";
	stampaVettore(A);
	cout << "Vettore B:\n";
	stampaVettore(B);
	return 1;
}

// Stampa il vettore
void stampaVettore(float V[N])
{
	for(int i = 0; i < N; i++) 
		cout << "Elemento " << i+1 << " = " << V[i] << "\n";
}

// Esegue prodotto scalare del vettore
void prodottoScalare(float vettore[N], int scalare)
{
	#pragma omp parallel for
	for(int i = 0; i < N; i++) 
		vettore[i] *= scalare;
}

// Calcola il modulo del vettore
float modulo(float V[N])
{
	float result = 0;
	
	// Eleva alla seconda tutti i valori del vettore e sommali
	#pragma omp parallel for reduction(+:result)
	for(int i = 0; i < N; i++)
		result += pow(V[i], 2);
	
	// Metti tutto sotto radice e restituiscilo
	result = sqrt(result);
	return result;
}

// Calcola il prodotto scalare tra 2 vettori
float prodottoScalare(float V1[N], float V2[N])
{
	float result = 0;
	for(int i = 0; i < N; i++) 
		result += V1[i]*V2[i];
	return result;
}

// Scambia due elementi float
void scambiaElemento (float& a, float& b)
{
	float c = a;
	a = b;
	b = c;
}

// Scambia due vettori di float di dimensione N
void scambiaVettori(float V1[N], float V2[N])
{
	for(int i = 0; i < N; i++) 
		scambiaElemento(V1[i], V2[i]);
}
