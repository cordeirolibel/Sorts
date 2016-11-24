#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define MAX 100
#define MIN -100

using namespace std;

//imprime vetor
void imprime(int* vetor, int n_elem){
    for(int i=0;i<n_elem;i++)
        cout << vetor[i] << " ";
    cout << endl << endl;
}

//cria vetor randomico
int* criaVetor(int n_elem, int minimo, int maximo){
    srand(time(NULL));
    int *vetor = new int[n_elem];
    for(int i=0;i<n_elem;i++)
        vetor[i] = rand()%(maximo - minimo + 1) + minimo;
    return vetor;
}

//retorna uma copia de vetor
int* copiaVetor(int* vetor, int n_elem){
    int *novo_vetor = new int[n_elem];
    for(int i=0;i<n_elem;i++)
        novo_vetor[i] = vetor[i];
    return novo_vetor;
}

//retorna true se os dois vetores sao iguais
bool isEqual(int* vet1, int* vet2, int n_elem){
    for(int i=0;i<n_elem;i++)
        if(vet1[i]!=vet2[i])
            return false;
    return true;
}

//retorna true se o vetor esta ordenado
bool isOrderly(int* vet, int n_elem){
    for(int i=1;i<n_elem;i++)
        if(vet[i-1]>vet[i])
            return false;
    return true;
}

//troca na memoria as variaveis a e b
void troca(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//Algoritimo Bubble Sort
void bubbleSort(int* vetor, int n_elem){
    for(int i=0;i<n_elem;i++)
        for(int j=1;j<n_elem;j++)
            if(vetor[j-1] > vetor[j])
                troca(&vetor[j-1], &vetor[j]);
}

//Algoritimo Quick Sort
void quickSort(int* vetor, int n_elem){
    if(n_elem<=1)
        return;

    int pivo = n_elem-1;//ultimo elemento
    int i = -1;//ultimo indice dos valores menores que pivo
    int j = 0;

    while(j!=pivo){
        if(vetor[j]<vetor[pivo]){
            i++;
            troca(&vetor[j],&vetor[i]);
        }
        j++;
    }
    troca(&vetor[i+1],&vetor[pivo]);
    //metade inferior
    quickSort(vetor,i+1);
    //metade superior
    quickSort(vetor+i+2,n_elem-i-2);
}


int main()
{
    int *vetor, *bubble_vet, *quick_vet;

    //criando vetores de teste iguais
    vetor = criaVetor(SIZE, MIN, MAX);
    bubble_vet = copiaVetor(vetor, SIZE);
    quick_vet = copiaVetor(vetor, SIZE);

    //rodando os algoritimos
    bubbleSort(bubble_vet, SIZE);
    quickSort(quick_vet, SIZE);

    //verificando se deu tudo certo
    if(isOrderly(bubble_vet,SIZE)){
        if(isEqual(bubble_vet,quick_vet,SIZE))
            cout << "  Ordenacao concluida com exito para todos os algoritimos!" << endl;
    }

    //imprimindo resultados
    imprime(vetor, SIZE);
    imprime(bubble_vet, SIZE);
    imprime(quick_vet, SIZE);

    //desalocando memoria
    delete [] vetor;
    delete [] bubble_vet;
    delete [] quick_vet;

    return 0;
}
