#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define Phone 18
#define Name 40
#define Position 30
#define FuncioSize 200
#define ClientSize 200
#define EstadiaSize 200
#define Endereco 150
#define CPF 15
#define Data 8

// Inicio structs de dados
typedef struct
{
    int id;
    char dataEntrada[Data], dataSaida[Data];
    int qtd_dias, idCliente, quarto;
} Estadia;

typedef struct
{
    int id;
    float telefone;
    char nome[Name], endereco[Endereco], cpf[CPF];
} Cliente;

void PesquisaEstadia();

void PesquisaEstadia()
{

    Estadia vetor_Estadias[50];
    Cliente vetor_clientes[50];
    float telefoneProcurado;
    int idProcurado;
    printf("\nDigite o telefone do cliente: ");
    scanf("%f", &telefoneProcurado);

    // procura cliente pelo nome
    FILE *arqCLientes = fopen("cadastro_cliente.txt", "r");
    char RecebeCliente[ClientSize], *substr;
    int i = 0;
    int clienteEncontrado = 0;
    while (!feof(arqCLientes))
    {

        fgets(RecebeCliente, sizeof(Cliente), arqCLientes);

        substr = strtok(RecebeCliente, ";");

        vetor_clientes[i].id = atoi(substr);

        substr = strtok(NULL, ";");

        strcpy(vetor_clientes[i].nome, substr);

        substr = strtok(NULL, ";");

        strcpy(vetor_clientes[i].endereco, substr);

        substr = strtok(NULL, ";");

        vetor_clientes[i].telefone = atof(substr);
        substr = strtok(NULL, ";");

        strcpy(vetor_clientes[i].cpf, substr);

        if (vetor_clientes[i].telefone == telefoneProcurado)
        {
            idProcurado = vetor_clientes[i].id;
            clienteEncontrado = 1;
            break;
        }
    }
    fclose(arqCLientes);

    if (clienteEncontrado == 0)
    {
        printf("\nCliente não encontrado!!");
        return;
    }

    FILE *arqEstadias = fopen("estadias.txt", "r");
    char RecebeEstadia[EstadiaSize];
    char *divideStr;
    int correVetor = 0;

    while (!feof(arqEstadias))
    {
        // Lemos uma linha do arquivo txt
        fflush(stdin);
        fgets(RecebeEstadia, EstadiaSize, arqEstadias);
        // strtok retorna um ponteiro char
        divideStr = strtok(RecebeEstadia, ";");
        // strtok retorna NULL quando chega ao final da string

        vetor_Estadias[correVetor].id = atoi(divideStr);
        divideStr = strtok(NULL, ";");
        strcpy(vetor_Estadias[correVetor].dataEntrada, divideStr);
        divideStr = strtok(NULL, ";");
        strcpy(vetor_Estadias[correVetor].dataSaida, divideStr);
        divideStr = strtok(NULL, ";");
        vetor_Estadias[correVetor].qtd_dias = atoi(divideStr);

        divideStr = strtok(NULL, ";");
        vetor_Estadias[correVetor].idCliente = atoi(divideStr);
        divideStr = strtok(NULL, ";");
        vetor_Estadias[correVetor].quarto = atof(divideStr);

        correVetor = correVetor + 1;
        if (feof(arqEstadias))
        {
            break;
        }
    }

    fclose(arqEstadias);

    int estadiasImpressas = 0;

    for (i = 0; i < correVetor; i++)
    {

        if (idProcurado == vetor_Estadias[i].idCliente)
        {
            printf("ID Estadia:  %d\tData de entrada:  %s\tData de saida:  %s\tQuantidade de dias:  %d\tID Cliente: %d\tNumero do quarto:  %d\n", vetor_Estadias[i].id, vetor_Estadias[i].dataEntrada, vetor_Estadias[i].dataSaida, vetor_Estadias[i].qtd_dias, vetor_Estadias[i].idCliente, vetor_Estadias[i].quarto);
            estadiasImpressas++;
        }
    }
    if (estadiasImpressas == 0)
    {
        printf("\nEsse cliente nao possui nenhuma estadia cadastrada!!");
    }
}

int main()
{

    PesquisaEstadia();

    return 0;
}