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
#define VetorCliente 15

// Inicio structs de dados
typedef struct
{
  int id;
  float salario, telefone;
  char nome[Name], cargo[Position], cpf[CPF];
} Funcionario;

typedef struct
{
  int id;
  float telefone;
  char nome[Name], endereco[Endereco], cpf[CPF];
} Cliente;

typedef struct
{
  int dia;
  int mes;
  int ano;
} data;
typedef struct
{
  int id;
  char dataEntrada[Data], dataSaida[Data];
  int qtd_dias, idCliente, quarto;
} Estadia;
typedef struct
{
  int id;
  data dataEntrada;
  data dataSaida;
  int totalDiarias;
  int idCliente;
  int numeroQuarto;
} estadia;

typedef struct
{
  int numQuarto, status;
  float valorDiaria;
  int capacidade;
} Quarto;
// Fim structs de dados

/*


Funcoes: Cadastra cliente: 


*/

// Inicio Funcoes Gerais
float organizaTelefone(char telefone[]);
// Fim Funcoes Gerais

// Inicio Cadastro de clientes
void CadastraCliente(Cliente cliente, Cliente vetor_cliente[]);
// FIM Cadastro de clientes

// Inicio Cadastrar funcionario
void CadastraFuncionario(Funcionario funcionario, Funcionario vetor_funcionario[]);
// FIM Cadastrar funcionario

// Inicio cadastra estadia
int calculaDiarias(estadia estadia);
void verificaQuarto(estadia vetor_estadia[], estadia estadia, Quarto vetor_quartos[], int qntHospedes);
estadia cadastrarEstadia(estadia estadia, int *qntHospedes);
// FIM cadastra estadia

// Incio Funcoes Pesquisa cliente
void PesquisaCliente(Cliente vetor_cliente[]);

void ExibeCliente(Cliente vetor_cliente[], int Tamanho);
// FIM Funcoes Pesquisa cliente

// Inicio Funcoes Pesquisa funcionario
void PesquisaFuncionario(Funcionario vetor_funcionarios[]);

void ExibeFuncionario(Funcionario vetor_funcionarios[], int Tamanho);
// Fim Funcoes Pesquisa funcionario

// Inicio Funcoes Pesquisa estadias
void PesquisaEstadia();
// Fim Funcoes Pesquisa estadias

// Inicio Baixa estadia pontis de fidelidade
int calcularQuantidadePontosFidelidade(int idCliente);
int baixaEstadia();
int encontrarLinhaEValorDaDiaria(int codQuarto, float *valorDiaria);
void desocuparQuarto(int linha);
// FIM Baixa estadia pontis de fidelidade

void pause()
{
  char ch;
  printf("\n\nPressione ENTER\n");
  scanf("%c%*c", &ch);
}

// Inicio Funcoes Gerais
float organizaTelefone(char telefone[])
{
  char auxiliar[Phone];
  int temEspaco = 0;
  for (int i = 0; i < strlen(telefone); i++)
  {
    if (telefone[i] == ' ' || telefone[i] == '(' || telefone[i] == ')' || telefone[i] == '-' || telefone[i] == '+')
    {
      temEspaco = 1;
      int j = 0;
      for (int l = 0; l < strlen(telefone) - 1; l++)
        if (l != i)
        {
          auxiliar[j] = telefone[l];
          j++;
        }
    }
  }
  if (!temEspaco)
    return atof(telefone);
  else
    return atof(auxiliar);
}
// Fim Funcoes Gerais

// Inicio Cadastrar cliente
void CadastraCliente(Cliente cliente, Cliente vetor_cliente[])
{
  FILE *leTxt = fopen("cadastro_cliente.txt", "r");
  int IdNovo = 0, qntCadastrada = 0;
  char RecebeCliente[sizeof(Cliente)], *divideCli;
  while (!feof(leTxt))
  {
    // Lemos linha a linha o .txt
    fgets(RecebeCliente, sizeof(Cliente), leTxt);
    // Lemos linha a linha o .txt
    divideCli = strtok(RecebeCliente, ";");
    while (divideCli)
    {
      vetor_cliente[qntCadastrada].id = atoi(divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[qntCadastrada].nome, divideCli);
      divideCli = strtok(NULL, ";");
      char Recebetelefone[Phone];
      strcpy(Recebetelefone, divideCli);
      vetor_cliente[qntCadastrada].telefone = organizaTelefone(Recebetelefone);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[qntCadastrada].endereco, divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[qntCadastrada].cpf, divideCli);
      divideCli = strtok(NULL, ";");
      qntCadastrada++;
    }
  }
  fclose(leTxt);
  leTxt = NULL;

  cliente.id = vetor_cliente[qntCadastrada - 1].id + 1;
  printf("Qual nome do cliente que voce gostaria de cadastrar?\n");
  fflush(stdin);
  fgets(RecebeCliente, Name, stdin);
  RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];
  strcpy(cliente.nome, RecebeCliente);
  printf("Qual telefone do cliente(somente numeros, sem espaco com DD)?\n");
  fflush(stdin);
  fgets(RecebeCliente, Phone, stdin);
  RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];
  while (strlen(RecebeCliente) > 11)
  {
    printf("\nTelefone invalido!\n Coloque somente numeros, sem espaco com DD(Ex: 31991238970)?\n");
    fflush(stdin);
    fgets(RecebeCliente, Phone, stdin);
    RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];
  }
  cliente.telefone = organizaTelefone(RecebeCliente);
  printf("Qual o endereco?\n");
  fflush(stdin);
  fgets(RecebeCliente, Endereco, stdin);
  RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];
  strcpy(cliente.endereco, RecebeCliente);
  printf("Qual o CPF(somente numeros)?\n");
  fflush(stdin);
  fgets(RecebeCliente, CPF, stdin);
  RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];

  while (strlen(RecebeCliente) > 11)
  {
    printf("\nCPF invalido!\n Coloque somente numeros, sem espaco(Ex: 12345678935)?\n");
    fflush(stdin);
    fgets(RecebeCliente, CPF, stdin);
    RecebeCliente[strlen(RecebeCliente) - 1] = RecebeCliente[strlen(RecebeCliente)];
  }
  strcpy(cliente.cpf, RecebeCliente);
  for (int i = 0; i < qntCadastrada; i++)
    if (!strcmp(vetor_cliente[i].cpf, cliente.cpf))
    {
      printf("Esse cliente ja possui cadastro!\nVoltando...\n");
      return;
    }
  printf("--------------------------------\n");
  printf("\nCliente cadastro com sucesso\n!");
  printf("================================\n");
  printf("ID: %d\nNome: %s\nTelefone: %.0f\nEndereco: %s\nCPF: %s\n", cliente.id, cliente.nome, cliente.telefone, cliente.endereco, cliente.cpf);
  printf("================================\n");
  FILE *EscreveTxt = fopen("cadastro_cliente.txt", "a");
  fprintf(EscreveTxt, "\n%d;%s;%.0f;%s;%s", cliente.id, cliente.nome, cliente.telefone, cliente.endereco, cliente.cpf);
  fclose(EscreveTxt);
  EscreveTxt = NULL;
}
// FIM Cadastrar cliente

// Inicio Cadastrar funcionario
void CadastraFuncionario(Funcionario funcionario, Funcionario vetor_funcionario[])
{
  FILE *leTxt = fopen("cadastro_funcionarios.txt", "r");
  int qntCadastrada = 0;
  char RecebeFuncionario[sizeof(Funcionario)], *divideCli;
  while (!feof(leTxt))
  {
    // Lemos linha a linha o .txt
    fgets(RecebeFuncionario, sizeof(Cliente), leTxt);
    // Lemos linha a linha o .txt
    divideCli = strtok(RecebeFuncionario, ";");
    while (divideCli)
    {
      vetor_funcionario[qntCadastrada].id = atoi(divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_funcionario[qntCadastrada].nome, divideCli);
      divideCli = strtok(NULL, ";");
      char Recebetelefone[Phone];
      strcpy(Recebetelefone, divideCli);
      vetor_funcionario[qntCadastrada].telefone = organizaTelefone(Recebetelefone);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_funcionario[qntCadastrada].cargo, divideCli);
      divideCli = strtok(NULL, ";");
      vetor_funcionario[qntCadastrada].salario = atof(divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_funcionario[qntCadastrada].cpf, divideCli);
      divideCli = strtok(NULL, ";");
      qntCadastrada++;
    }
  }
  fclose(leTxt);
  leTxt = NULL;

  funcionario.id = vetor_funcionario[qntCadastrada - 1].id + 1;
  printf("Qual nome do funcionario que voce gostaria de cadastrar?\n");
  fflush(stdin);
  fgets(RecebeFuncionario, Name, stdin);
  RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];
  strcpy(funcionario.nome, RecebeFuncionario);
  printf("Qual telefone do funcionario(somente numeros, sem espaco com DD)?\n");
  fflush(stdin);
  fgets(RecebeFuncionario, Phone, stdin);
  RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];
  while (strlen(RecebeFuncionario) > 11)
  {
    printf("\nTelefone invalido!\n Coloque somente numeros, sem espaco com DD(Ex: 31991238970)?\n");
    fflush(stdin);
    fgets(RecebeFuncionario, Phone, stdin);
    RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];
  }
  funcionario.telefone = organizaTelefone(RecebeFuncionario);
  printf("Qual o cargo?\n");
  fflush(stdin);
  fgets(RecebeFuncionario, Position, stdin);
  RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];
  strcpy(funcionario.cargo, RecebeFuncionario);
  printf("Qual o salario(somente numeros)?\nR$ ");
  scanf("%f", &funcionario.salario);
  printf("Qual o CPF(somente numeros)?\n");
  fflush(stdin);
  fgets(RecebeFuncionario, CPF, stdin);
  RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];

  while (strlen(RecebeFuncionario) > 11)
  {
    printf("\nCPF invalido!\n Coloque somente numeros, sem espaco(Ex: 12345678935)?\n");
    fflush(stdin);
    fgets(RecebeFuncionario, CPF, stdin);
    RecebeFuncionario[strlen(RecebeFuncionario) - 1] = RecebeFuncionario[strlen(RecebeFuncionario)];
  }
  strcpy(funcionario.cpf, RecebeFuncionario);
  for (int i = 0; i < qntCadastrada; i++)
    if (!strcmp(vetor_funcionario[i].cpf, funcionario.cpf))
    {
      printf("Esse funcionario ja possui cadastro!\nVoltando...\n");
      return;
    }
  printf("--------------------------------\n");
  printf("\nFuncionario cadastro com sucesso!\n");
  printf("================================\n");
  printf("ID: %d\nNome: %s\nTelefone: %.0f\nCargo: %s\nSalario: R$ %.2f\nCPF: %s\n", funcionario.id, funcionario.nome, funcionario.telefone, funcionario.cargo, funcionario.salario, funcionario.cpf);
  printf("================================\n");
  FILE *EscreveTxt = fopen("cadastro_funcionarios.txt", "a");
  fprintf(EscreveTxt, "\n%d;%s;%.0f;%s;%.0f;%s", funcionario.id, funcionario.nome, funcionario.telefone, funcionario.cargo, funcionario.salario, funcionario.cpf);
  fclose(EscreveTxt);
  EscreveTxt = NULL;
}
// FIM Cadastrar funcionario

// Inicio Cadastrar estadia
estadia cadastrarEstadia(estadia estadia, int *qntHospedes)
{
  printf("\nDigite o ID do cliente: ");
  scanf("%i", &estadia.idCliente);
  Cliente vetor_cliente[VetorCliente];
  PesquisaCliente(vetor_cliente);
  int clienteEncontrado = 0;
  for (int i = 0; i < 15; i++)
    if (vetor_cliente[i].id == estadia.idCliente)
      clienteEncontrado = 1;
  if (!clienteEncontrado)
  {
    printf("Nao foi possivel localizar um cliente com esse ID\nFavor pesquisar pelo nome para ver seu ID\n");
    *qntHospedes = -1;
    return estadia;
  }
  printf("\nQuantidade de Hospedes: ");
  int quantidade;
  scanf("%i", &quantidade);
  *qntHospedes = quantidade;
  printf("\nData de Entrada(ex: 7/8/2021): ");
  scanf("%i/%i/%i", &estadia.dataEntrada.dia, &estadia.dataEntrada.mes, &estadia.dataEntrada.ano);
  printf("\nData de Saida(ex: 7/8/2021): ");
  scanf("%i/%i/%i", &estadia.dataSaida.dia, &estadia.dataSaida.mes, &estadia.dataSaida.ano);

  estadia.totalDiarias = calculaDiarias(estadia);

  return estadia;
}

// Função calcula as diarias e coloca na propriedade totalDiarias;
int calculaDiarias(estadia estadia)
{
  int diasEntrada = estadia.dataEntrada.dia + (estadia.dataEntrada.mes - 1) * 30 + (estadia.dataEntrada.ano - 1) * 365;
  int diasSaida = estadia.dataSaida.dia + (estadia.dataSaida.mes - 1) * 30 + (estadia.dataSaida.ano - 1) * 365;
  int totalDiarias = diasSaida - diasEntrada;
  return totalDiarias;
}

// Funcao busca no txt quartos e armazena no vetor quartos
void verificaQuarto(estadia vetor_estadia[], estadia estadias, Quarto vetor_quartos[], int qntHospedes)
{
  int qtdHospedes = qntHospedes;
  FILE *leTxt = fopen("quartos.txt", "r");
  char *divideStr, RecebeQuarto[sizeof(Quarto)];
  int index = 0;
  while (!feof(leTxt))
  {
    fgets(RecebeQuarto, sizeof(Quarto), leTxt);
    divideStr = strtok(RecebeQuarto, ";");
    while (divideStr)
    {
      vetor_quartos[index].numQuarto = atoi(divideStr);
      divideStr = strtok(NULL, ";");
      vetor_quartos[index].status = atoi(divideStr);
      divideStr = strtok(NULL, ";");
      vetor_quartos[index].capacidade = atoi(divideStr);
      divideStr = strtok(NULL, ";");
      vetor_quartos[index].valorDiaria = atof(divideStr);
      divideStr = strtok(NULL, ";");
      index++;
    }
  }
  fclose(leTxt);
  leTxt = NULL;
  // Verificando se a quantidade de vagas disponivies e suficiente para a quantidade de hospedes desejada
  int disponivel = 0;
  for (int i = 0; i < 10; i++)
  {
    if (!vetor_quartos[i].status && vetor_quartos[i].capacidade >= qtdHospedes)
    {
      disponivel = 1;
      estadias.numeroQuarto = vetor_quartos[i].numQuarto;
      printf("Temos disponibilidade para sua estadia!\n");
      printf("Quarto reservado: \n");
      printf("Quarto: %i\nCapacidade: %i\nValor da diaria: R$%.2f\n", vetor_quartos[i].numQuarto, vetor_quartos[i].capacidade, vetor_quartos[i].valorDiaria);
      vetor_quartos[i].status = 1;
      break;
    }
  }
  if (disponivel)
  {
    FILE *EscreveTxt = fopen("quartos.txt", "w");
    for (int i = 0; i < 10; i++)
    {
      if (!i)
        fprintf(EscreveTxt, "%d;%d;%d;%.0f", vetor_quartos[i].numQuarto, vetor_quartos[i].status, vetor_quartos[i].capacidade, vetor_quartos[i].valorDiaria);
      else
        fprintf(EscreveTxt, "\n%d;%d;%d;%.0f", vetor_quartos[i].numQuarto, vetor_quartos[i].status, vetor_quartos[i].capacidade, vetor_quartos[i].valorDiaria);
    }
    fclose(EscreveTxt);
    EscreveTxt = NULL;
    FILE *LendoTxt = fopen("estadias.txt", "r");
    char Recebe[sizeof(estadia)], *recebe;
    int j = 0;
    while (!feof(LendoTxt))
    {
      fflush(stdin);
      fgets(Recebe, sizeof(estadia), LendoTxt);
      recebe = strtok(Recebe, ";");
      while (recebe)
      {
        vetor_estadia[j].id = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataEntrada.dia = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataEntrada.mes = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataEntrada.ano = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataSaida.dia = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataSaida.mes = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].dataSaida.ano = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].totalDiarias = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].idCliente = atoi(recebe);
        recebe = strtok(NULL, ";");
        vetor_estadia[j].numeroQuarto = atoi(recebe);
        recebe = strtok(NULL, ";");
        j++;
      }
    }
    fclose(LendoTxt);
    int novaEstadia = vetor_estadia[j - 1].id + 1;
    FILE *Escrevetxt = fopen("estadias.txt", "a");
    fprintf(Escrevetxt, "\n%d;%d;%d;%d;%d;%d;%d;%d;%d;%d", novaEstadia, estadias.dataEntrada.dia, estadias.dataEntrada.mes, estadias.dataEntrada.ano, estadias.dataSaida.dia, estadias.dataSaida.mes, estadias.dataSaida.ano, estadias.totalDiarias, estadias.idCliente, estadias.numeroQuarto);
    fclose(Escrevetxt);
  }
  else
  {
    printf("Infelizmente nao temos quartos disponíveis para %i pessoas\n", qtdHospedes);
  }
}
// FIM Cadastrar estadia

// Incio Funcoes Pesquisa cliente
void PesquisaCliente(Cliente vetor_cliente[])
{
  FILE *leTxt = fopen("cadastro_cliente.txt", "r");
  char RecebeCliente[sizeof(Cliente)], *divideCli;
  int index = 0;
  while (!feof(leTxt))
  {
    // Lemos linha a linha o .txt
    fgets(RecebeCliente, sizeof(Cliente), leTxt);
    // Lemos linha a linha o .txt
    divideCli = strtok(RecebeCliente, ";");
    while (divideCli)
    {
      vetor_cliente[index].id = atoi(divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[index].nome, divideCli);
      divideCli = strtok(NULL, ";");
      char Recebetelefone[Phone];
      strcpy(Recebetelefone, divideCli);
      vetor_cliente[index].telefone = organizaTelefone(Recebetelefone);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[index].endereco, divideCli);
      divideCli = strtok(NULL, ";");
      strcpy(vetor_cliente[index].cpf, divideCli);
      divideCli = strtok(NULL, ";");
      index++;
    }
  }
}

void ExibeCliente(Cliente vetor_cliente[], int Tamanho)
{
  char NomeCiente[Name];
  printf("Qual o nome do cliente?");
  fflush(stdin);
  fgets(NomeCiente, Name, stdin);
  NomeCiente[strlen(NomeCiente) - 1] = NomeCiente[strlen(NomeCiente)];
  for (int i = 0; i < Tamanho; i++)
  {
    if (!strcmp(vetor_cliente[i].nome, NomeCiente))
    {
      printf("=========================================\n");
      printf("Dados do %s:\nId: %d\nTelefone: %.0f\nEndereco: %s\nCPF: %s\n", vetor_cliente[i].nome, vetor_cliente[i].id, vetor_cliente[i].telefone, vetor_cliente[i].endereco, vetor_cliente[i].cpf);
      printf("=========================================\n");
    }
  }
}
// Fim Funcoes Pesquisa cliente

// Inicio Funcoes Pesquisa funcionario
void PesquisaFuncionario(Funcionario vetor_funcionarios[])
{
  FILE *LeTxt = fopen("cadastro_funcionarios.txt", "r");
  char RecebeFuncionario[sizeof(Funcionario)];
  char *divideStr;
  int Index = 0;
  int correVetor = 0;
  while (!feof(LeTxt))
  {
    // Lemos uma linha do arquivo txt
    fgets(RecebeFuncionario, sizeof(Funcionario), LeTxt);
    // strtok retorna um ponteiro char
    divideStr = strtok(RecebeFuncionario, ";");
    // strtok retorna NULL quando chega ao final da string
    while (divideStr)
    {
      vetor_funcionarios[correVetor].id = atoi(divideStr);
      divideStr = strtok(NULL, ";");
      strcpy(vetor_funcionarios[correVetor].nome, divideStr);
      divideStr = strtok(NULL, ";");
      // printf("Telefone: %s\n", divideStr);
      // Funcao trata numero passado e retorna int
      char RecebeTelefone[Phone];
      strcpy(RecebeTelefone, divideStr);
      vetor_funcionarios[correVetor].telefone = organizaTelefone(RecebeTelefone);
      // printf("Telefone: %d\n", vetor_funcionarios[correVetor].telefone);
      divideStr = strtok(NULL, ";");
      strcpy(vetor_funcionarios[correVetor].cargo, divideStr);
      divideStr = strtok(NULL, ";");
      vetor_funcionarios[correVetor].salario = atof(divideStr);
      divideStr = strtok(NULL, ";");
      strcpy(vetor_funcionarios[correVetor].cpf, divideStr);
      divideStr = strtok(NULL, ";");
      correVetor++;
    }
  }
}

void ExibeFuncionario(Funcionario vetor_funcionarios[], int Tamanho)
{
  char nomeFuncionario[Name];
  int EncontreiFuncionario = 0;
  printf("Qual o nome do funcionario?\n");
  fflush(stdin);
  fgets(nomeFuncionario, Name, stdin);
  // \n sera substituido pelo \0
  nomeFuncionario[strlen(nomeFuncionario) - 1] = nomeFuncionario[strlen(nomeFuncionario)];
  int QuantidadeFuncionarios = 0;
  for (int i = 0; i < Tamanho; i++)
    if (!strcmp(nomeFuncionario, vetor_funcionarios[i].nome))
    {
      QuantidadeFuncionarios++;
    }
  if (QuantidadeFuncionarios)
  {
    printf("%d corrensondecia(s) para esse nome!", QuantidadeFuncionarios);
    for (int i = 0; i < Tamanho; i++)
      if (!strcmp(nomeFuncionario, vetor_funcionarios[i].nome))
      {
        printf("\n=========================================\n");
        printf("Dados do %s:\nId: %d\nTelefone: %.0f\nCargo: %s\nSalario: R$ %.2f\n", vetor_funcionarios[i].nome, vetor_funcionarios[i].id, vetor_funcionarios[i].telefone, vetor_funcionarios[i].cargo, vetor_funcionarios[i].salario);
        printf("=========================================\n");
      }
  }
  else
    printf("Funcionario nao encontrado!\nVoce digitou o nome corretamente?\nTente novamente da proxima vez.\n");

  printf("\nVoltando para o sub menu...\n");
}
// Fim Funcoes Pesquisa funcionario

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

int calcularQuantidadePontosFidelidade(int idCliente)
{
  estadia estadia;
  int pontosFidelidade = 0;
  FILE *arq;

  arq = fopen("estadias.txt", "r");
  if (arq == NULL)
  {
    // system("clear");
    printf("\n\aErro na abertura do arquivo.");
    pause();
  }
  else
  {
    do
    {
      fscanf(arq, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;\n",
             &estadia.id,
             &estadia.dataEntrada.dia, &estadia.dataEntrada.mes, &estadia.dataEntrada.ano,
             &estadia.dataSaida.dia, &estadia.dataSaida.mes, &estadia.dataSaida.ano,
             &estadia.totalDiarias, &estadia.idCliente, &estadia.numeroQuarto);
      if (estadia.idCliente == idCliente)
      {
        pontosFidelidade += 10;
      }
    } while (!feof(arq));
  }

  fclose(arq);
  return pontosFidelidade;
}

int encontrarLinhaEValorDaDiaria(int codQuarto, float *valorDiaria)
{
  Quarto quartos;
  int linha = 0;
  FILE *arq;
  arq = fopen("quartos.txt", "r+");
  if (arq == NULL)
  {
    // system("clear");
    printf("\n\aErro na abertura do arquivo.");
    pause();
  }
  else
  {
    do
    {
      fscanf(arq, "%d;%d;%d;%f", &quartos.numQuarto, &quartos.status, &quartos.capacidade, &quartos.valorDiaria);
      if (quartos.numQuarto == codQuarto)
      {
        *valorDiaria = quartos.valorDiaria;
        return linha;
      }
      linha++;
    } while (!feof(arq));
  }

  return -1;
}

void desocuparQuarto(int linha)
{
  Quarto quartos;
  int linhaAtual = 0;
  FILE *arq, *arqAux;
  arq = fopen("quartos.txt", "r");
  arqAux = fopen("quartosAux.txt", "w+");
  if (arq == NULL || arqAux == NULL)
  {
    // system("clear");
    printf("\n\aErro na abertura do arquivo.");
    pause();
  }
  else
  {
    do
    {
      fscanf(arq, "%d;%d;%d;%f\n", &quartos.numQuarto, &quartos.status, &quartos.capacidade, &quartos.valorDiaria);
      if (linha == linhaAtual)
        fprintf(arqAux, "%d;%d;%d;%.2f\n", quartos.numQuarto, 0, quartos.capacidade, quartos.valorDiaria);
      else
        fprintf(arqAux, "%d;%d;%d;%.2f\n", quartos.numQuarto, quartos.status, quartos.capacidade, quartos.valorDiaria);
      linhaAtual++;
    } while (!feof(arq));
  }
  fclose(arq);
  fclose(arqAux);

  remove("quartos.txt");
  rename("quartosAux.txt", "quartos.txt");
}

int baixaEstadia()
{
  int idEstadia, linha = 0, confirmar;
  float valorDiaria = 0.0;
  estadia estadia;
  // system("clear");
  printf("\tDar baixa na estadia");
  printf("\nDigite o id da estadia: ");
  scanf("%d", &idEstadia);

  FILE *arq;
  arq = fopen("estadias.txt", "r");
  if (arq == NULL)
  {
    // system("clear");
    printf("\n\aErro na abertura do arquivo.");
    pause();
  }
  else
  {
    do
    {
      fscanf(arq, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
             &estadia.id,
             &estadia.dataEntrada.dia, &estadia.dataEntrada.mes, &estadia.dataEntrada.ano,
             &estadia.dataSaida.dia, &estadia.dataSaida.mes, &estadia.dataSaida.ano,
             &estadia.totalDiarias, &estadia.idCliente, &estadia.numeroQuarto);

      if (estadia.id == idEstadia)
      {
        // system("clear");
        printf("\tDando baixa na estadia");
        int linha = encontrarLinhaEValorDaDiaria(estadia.numeroQuarto, &valorDiaria);
        printf("\nValor a ser pago: R$ %.2f", ((float)estadia.totalDiarias * valorDiaria));
        pause();
        fclose(arq);
        printf("\n\nConfirmar baixa? ");
        printf("\n1 - Sim");
        printf("\n2 - Nao");
        printf("\nEscolha: ");
        scanf("%d", &confirmar);
        // system("clear");
        if (confirmar != 1)
          return 2;
        desocuparQuarto(linha);
        return 0;
      }

      linha++;
    } while (!feof(arq));
  }
  fclose(arq);
  // system("clear");
  return 1;
}
