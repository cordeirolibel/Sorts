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

//Algoritimo Selection Sort
void selectionSort(int* vetor, int n_elem){
    int menor;
    for(int i=0;i<(n_elem-1);i++){
        //buscando o menor valor apartir de i
        menor = i;
        for(int j=i+2;j<n_elem;j++)
            if(vetor[j]<vetor[menor])
                menor = j;
        //fixa valor na posicao i
        troca(&vetor[i], &vetor[menor]);
    }
}

//Algoritimo Insertion Sort
void insertionSort(int* vetor, int n_elem){
    int local;
    for(int i=1;i<n_elem;i++){
        //procura o local apropriado para o valor i
        local = 0;
        for(int j=0;j<i;j++)
            if(vetor[j]<vetor[i])
                local++;
        //deslocando valores para frete, para por o valor i no local local
        int tmp = vetor[i];
        for(int j=i;j>local;j--)
            vetor[j]=vetor[j-1];
        //fixo valor em i no seu lugar apropriado
        vetor[local] = tmp;
    }
}
//Algoritimo Shell Sort
void shellSort(int* vetor, int n_elem, int pula = -1){
    bool flag = false;//indica mudança
    if(pula == -1)//primeira interacao
        pula = n_elem/2;
    for(int i=0;(i+pula)<n_elem;i++)
        if(vetor[i]>vetor[i+pula]){
            troca(&vetor[i],&vetor[i+pula]);
            flag = true;
        }
    if(flag)//se ocorreu mudaca repete
        shellSort(vetor,n_elem,pula);
    //repita ate janela pular igual 1, isto é valores proximos
    else if(pula != 1)
        shellSort(vetor,n_elem,(pula+1)/2);
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
    int *vetor, *select_vet, *insert_vet, *bubble_vet, *shell_vet, *quick_vet;

    //criando vetores de teste iguais
    vetor = criaVetor(SIZE, MIN, MAX);
    select_vet = copiaVetor(vetor, SIZE);
    insert_vet = copiaVetor(vetor, SIZE);
    bubble_vet = copiaVetor(vetor, SIZE);
    shell_vet = copiaVetor(vetor, SIZE);
    quick_vet = copiaVetor(vetor, SIZE);

    //rodando os algoritimos
    selectionSort(select_vet,SIZE);
    insertionSort(insert_vet,SIZE);
    bubbleSort(bubble_vet, SIZE);
    shellSort(shell_vet,SIZE);
    quickSort(quick_vet, SIZE);

    //verificando se deu tudo certo
    if(isOrderly(bubble_vet,SIZE)){
        if(!isEqual(select_vet,insert_vet,SIZE));
        else if(!isEqual(insert_vet,bubble_vet,SIZE));
        else if(!isEqual(bubble_vet,shell_vet,SIZE));
        else if(!isEqual(shell_vet,quick_vet,SIZE));
        else//todos os vetores são iguais
            cout << "  Ordenacao concluida com exito para todos os algoritimos!" << endl;
    }

    //imprimindo resultados
    imprime(vetor, SIZE);
    imprime(shell_vet, SIZE);

    //desalocando memoria
    delete [] vetor;
    delete [] select_vet;
    delete [] insert_vet;
    delete [] bubble_vet;
    delete [] shell_vet;
    delete [] quick_vet;

    return 0;
}
