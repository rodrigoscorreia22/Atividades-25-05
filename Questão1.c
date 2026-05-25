#include <stdio.h>
#include <string.h>

#define N 26

typedef struct {
    char nome[50];
    int  veiculos;
    int  acidentes;
} Estado;

void  coletarDados      (Estado cadastro[], int n);
void  buscarMaiorMenor  (Estado cadastro[], int n, int *iMaior, int *iMenor);
float calcularPercentual(Estado cadastro[], int i);
float calcularMedia     (Estado cadastro[], int n);
void  exibirAcimaMedia  (Estado cadastro[], int n, float media);


int main(void)
{
    Estado cadastro[N];
    int    iMaior, iMenor, i;
    float  media;

    coletarDados(cadastro, N);

    buscarMaiorMenor(cadastro, N, &iMaior, &iMenor);
    printf("\n--- Extremos de Acidentes de Transito ---\n");
    printf("Maior numero de acidentes : %s (%d acidentes)\n",
           cadastro[iMaior].nome, cadastro[iMaior].acidentes);
    printf("Menor numero de acidentes : %s (%d acidentes)\n",
           cadastro[iMenor].nome, cadastro[iMenor].acidentes);

    printf("\n--- Percentual de Veiculos Envolvidos em Acidentes ---\n");
    for (i = 0; i < N; i++) {
        printf("%-30s : %.4f%%\n",
               cadastro[i].nome,
               calcularPercentual(cadastro, i));
    }

    media = calcularMedia(cadastro, N);
    printf("\n--- Media Nacional de Acidentes ---\n");
    printf("Media: %.2f acidentes por estado\n", media);

    printf("\n--- Estados Acima da Media ---\n");
    exibirAcimaMedia(cadastro, N, media);

    return 0;
}

void coletarDados(Estado cadastro[], int n)
{
    int i;
    printf("=== Coleta de Dados - Acidentes de Transito 2007 ===\n");
    for (i = 0; i < n; i++) {
        printf("\n--- Estado %d de %d ---\n", i + 1, n);
        printf("Nome do estado           : ");
        scanf(" %[^\n]", cadastro[i].nome);
        printf("Numero de veiculos       : ");
        scanf("%d", &cadastro[i].veiculos);
        printf("Numero de acidentes      : ");
        scanf("%d", &cadastro[i].acidentes);
    }
}

void buscarMaiorMenor(Estado cadastro[], int n, int *iMaior, int *iMenor)
{
    int i;
    *iMaior = 0;
    *iMenor = 0;
    for (i = 1; i < n; i++) {
        if (cadastro[i].acidentes > cadastro[*iMaior].acidentes)
            *iMaior = i;
        if (cadastro[i].acidentes < cadastro[*iMenor].acidentes)
            *iMenor = i;
    }
}


float calcularPercentual(Estado cadastro[], int i)
{
    if (cadastro[i].veiculos == 0)
        return 0.0f;
    return (float)cadastro[i].acidentes / (float)cadastro[i].veiculos * 100.0f;
}


float calcularMedia(Estado cadastro[], int n)
{
    int i, soma = 0;
    for (i = 0; i < n; i++)
        soma += cadastro[i].acidentes;
    return (float)soma / (float)n;
}


void exibirAcimaMedia(Estado cadastro[], int n, float media)
{
    int i, encontrou = 0;
    for (i = 0; i < n; i++) {
        if ((float)cadastro[i].acidentes > media) {
            printf("%-30s : %d acidentes\n",
                   cadastro[i].nome, cadastro[i].acidentes);
            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Nenhum estado acima da media.\n");
}
