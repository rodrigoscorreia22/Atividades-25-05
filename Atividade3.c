// Questão 3

#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100


typedef struct {
    int   numero;
    char  nome[100];
    char  cpf[15];
    char  telefone[15];
    float saldo;
} Conta;

typedef struct {
    Conta contas[MAX_CONTAS];
    int   qtd;       
} Cadastro;

int  buscar        (Cadastro *cad, int numero);
void cadastrar     (Cadastro *cad, int numero);
void consultarSaldo(Cadastro *cad, int numero);
void depositar     (Cadastro *cad, int numero);
void sacar         (Cadastro *cad, int numero);
void exibir        (Cadastro *cad, const char *tipo);
void menu          (Cadastro *corrente, Cadastro *poupanca);

int main(void)
{
    Cadastro corrente, poupanca;

    corrente.qtd = 0;
    poupanca.qtd = 0;

    menu(&corrente, &poupanca);

    return 0;
}

int buscar(Cadastro *cad, int numero)
{
    int i;
    if (cad->qtd == 0)
        return -1;
    for (i = 0; i < cad->qtd; i++) {
        if (cad->contas[i].numero == numero)
            return i;
    }
    return -2;
}

void cadastrar(Cadastro *cad, int numero)
{
    int pos;

    if (cad->qtd >= MAX_CONTAS) {
        printf("Cadastro cheio! Nao e possivel inserir mais contas.\n");
        return;
    }

    pos = buscar(cad, numero);

    if (pos >= 0) {
    
        printf("Erro: numero de conta %d ja esta cadastrado.\n", numero);
        return;
    }

    cad->contas[cad->qtd].numero = numero;

    printf("Nome do titular : ");
    scanf(" %[^\n]", cad->contas[cad->qtd].nome);

    printf("CPF             : ");
    scanf(" %[^\n]", cad->contas[cad->qtd].cpf);

    printf("Telefone        : ");
    scanf(" %[^\n]", cad->contas[cad->qtd].telefone);

    cad->contas[cad->qtd].saldo = 0.0f;
    cad->qtd++;

    printf("Conta %d cadastrada com sucesso! Saldo inicial: R$ 0,00\n", numero);
}

void consultarSaldo(Cadastro *cad, int numero)
{
    int pos = buscar(cad, numero);

    if (pos >= 0) {
        printf("Conta   : %d\n",   cad->contas[pos].numero);
        printf("Titular : %s\n",   cad->contas[pos].nome);
        printf("Saldo   : R$ %.2f\n", cad->contas[pos].saldo);
    } else {
        printf("Conta %d nao esta cadastrada.\n", numero);
    }
}

void depositar(Cadastro *cad, int numero)
{
    float valor;
    int pos = buscar(cad, numero);

    if (pos >= 0) {
        printf("Valor do deposito: R$ ");
        scanf("%f", &valor);
        if (valor <= 0.0f) {
            printf("Valor invalido para deposito.\n");
            return;
        }
        cad->contas[pos].saldo += valor;
        printf("Deposito de R$ %.2f realizado.\n", valor);
        printf("Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
    } else {
        printf("Conta %d nao esta cadastrada.\n", numero);
    }
}

void sacar(Cadastro *cad, int numero)
{
    float valor;
    int pos = buscar(cad, numero);

    if (pos < 0) {
        printf("Conta %d nao esta cadastrada.\n", numero);
        return;
    }

    printf("Valor do saque  : R$ ");
    scanf("%f", &valor);

    if (valor <= 0.0f) {
        printf("Valor invalido para saque.\n");
        return;
    }

    if (valor > cad->contas[pos].saldo) {
        printf("Saldo insuficiente. Saldo atual: R$ %.2f\n",
               cad->contas[pos].saldo);
    } else {
        cad->contas[pos].saldo -= valor;
        printf("Saque de R$ %.2f realizado.\n", valor);
        printf("Novo saldo: R$ %.2f\n", cad->contas[pos].saldo);
    }
}

void exibir(Cadastro *cad, const char *tipo)
{
    int i;
    printf("\n=== Contas de %s ===\n", tipo);
    if (cad->qtd == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }
    printf("%-10s %-30s %-15s\n", "Numero", "Titular", "Telefone");
    printf("%-10s %-30s %-15s\n", "------", "-------", "--------");
    for (i = 0; i < cad->qtd; i++) {
        printf("%-10d %-30s %-15s\n",
               cad->contas[i].numero,
               cad->contas[i].nome,
               cad->contas[i].telefone);
    }
}

void menu(Cadastro *corrente, Cadastro *poupanca)
{
    int      opcao, tipo, numero;
    Cadastro *cad;
    char     nomeTipo[20];

    do {
        
        printf("1. Cadastrar conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Exibir todas as contas\n");
        printf("0. Sair\n");
        printf("----------------------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao >= 1 && opcao <= 5) {
            printf("Tipo de conta (1-Corrente / 2-Poupanca): ");
            scanf("%d", &tipo);
            if (tipo == 1) {
                cad = corrente;
                strcpy(nomeTipo, "Conta Corrente");
            } else if (tipo == 2) {
                cad = poupanca;
                strcpy(nomeTipo, "Conta Poupanca");
            } else {
                printf("Tipo invalido.\n");
                continue;
            }
        }

        switch (opcao) {
            case 1:
                printf("Numero da nova conta: ");
                scanf("%d", &numero);
                cadastrar(cad, numero);
                break;

            case 2:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                consultarSaldo(cad, numero);
                break;

            case 3:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                depositar(cad, numero);
                break;

            case 4:
                printf("Numero da conta: ");
                scanf("%d", &numero);
                sacar(cad, numero);
                break;

            case 5:
                exibir(cad, nomeTipo);
                break;

            case 0:
                printf("Sistema Fechado!\n");
                break;

            default:
                printf("Opcao invalida\n");
        }

    } while (opcao != 0);
}
