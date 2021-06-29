#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcoes.c"
// #include "dar_baixa_estadia.c"
#define TamVetFun 15
#define TamVetCli 15
#define TamVetEsta 30
#define QntQuartos 10
void main()
{
    char opcaoMenu, subOpcao = '1';
    Cliente vetor_cliente[TamVetCli];
    Funcionario vetor_funcionarios[TamVetFun], funcionario;
    estadia vetor_estadia[TamVetEsta], estadia;
    int responseBaixaEstadia, codigoCliente;
    // LeEstadia vetor_leEstadia[TamVetEsta];
    Quarto vetor_quartos[QntQuartos];
    do
    {
        printf("\n----------------------------------------\n");
        printf("BEM VINDA/O AO 'Hotel Descanso Garantido!'\nGostariamos de proportcionar a melhor\nexperiencia de sua vida em nosso Hotel!\n\nMENU DO HOTEL:\n1) Cadastrar um cliente\n2) Cadastrar um funcionario\n3) Cadastrar uma estadia\n4) Dar baixa na estadia\n5) Pesquisar um cliente\n6) Pesquisar um funcionario\n7) Mostrar estadias de um cliente\n8) Verificar ponto de fidelidade do cliente\n0) Para Sair!");
        printf("\n----------------------------------------\n");
        scanf(" %c", &opcaoMenu);
        switch (opcaoMenu)
        {
        case '1':
            printf("--------------------------------\n");
            printf("Sub Menu (Cadastrar Cliente):\n");
            Cliente cliente;
            CadastraCliente(cliente, vetor_cliente);
            printf("--------------------------------\n");
            printf("1) Cadastrar outro cliente?\n0) Voltar ao menu principal");
            printf("\n--------------------------------\n");
            scanf(" %c", &subOpcao);
            do
            {
                switch (subOpcao)
                {
                case '1':
                    CadastraCliente(cliente, vetor_cliente);
                    break;
                case '0':
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("\nOpcao invalida\n");
                    break;
                }
            } while (subOpcao != '0');
            break;
        case '2':
            printf("--------------------------------\n");
            printf("Sub Menu (Cadastrar Funcionario):\n");
            CadastraFuncionario(funcionario, vetor_funcionarios);
            printf("--------------------------------\n");
            printf("1) Cadastrar outro Funcionario?\n0) Voltar ao menu principal");
            printf("\n--------------------------------\n");
            scanf(" %c", &subOpcao);
            do
            {
                switch (subOpcao)
                {
                case '1':
                    CadastraFuncionario(funcionario, vetor_funcionarios);
                    break;
                case '0':
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("\nOpcao invalida\n");
                    break;
                }
            } while (subOpcao != '0');
            break;
        case '3':
            printf("--------------------------------\n");
            int qntHospedes;
            printf("Sub Menu (Cadastrar Estadia):\n");
            estadia = cadastrarEstadia(estadia, &qntHospedes);
            if (qntHospedes == -1)
                break;
            verificaQuarto(vetor_estadia, estadia, vetor_quartos, qntHospedes);
            break;
        case '4':
            responseBaixaEstadia = baixaEstadia();
            if (responseBaixaEstadia == 0)
            {
                printf("\tSucesso");
                printf("\nBaixa Realizada com sucesso!");
                pause();
            }
            else if (responseBaixaEstadia == 1)
            {
                printf("\tErro");
                printf("\nEstadia nao encontrada!");
                printf("\nCertifique-se que o id passado esta correto.");
                pause();
            }
            else if (responseBaixaEstadia == 2)
            {
                printf("\tCancelado");
                printf("\nBaixa na estadia foi cancelada!");
                pause();
            }
            break;
        case '5':
            printf("--------------------------------\n");
            printf("Sub Menu (Pesquisa Cliente):\n");
            do
            {
                printf("1) Pesquisar cliente\n0) Voltar ao menu principal\n");
                printf("--------------------------------\n");
                scanf(" %c", &subOpcao);
                switch (subOpcao)
                {
                case '1':
                    printf("---------------------------\n");
                    PesquisaCliente(vetor_cliente);
                    ExibeCliente(vetor_cliente, TamVetCli);
                    printf("---------------------------\n");
                    break;
                case '0':
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
                }
            } while (subOpcao != '0');
            break;
        case '6':
            printf("--------------------------------\n");
            printf("Sub Menu (Pesquisa Funcionario):\n");
            do
            {
                printf("1) Pesquisar funcionario\n0) Voltar ao menu principal\n");
                printf("--------------------------------\n");
                fflush(stdin);
                scanf(" %c", &subOpcao);
                switch (subOpcao)
                {
                case '1':
                    printf("---------------------------\n");
                    PesquisaFuncionario(vetor_funcionarios);
                    ExibeFuncionario(vetor_funcionarios, TamVetFun);
                    printf("---------------------------\n");
                    break;
                case '0':
                    printf("\nVoltando ao menu principal...\n");
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
                }
            } while (subOpcao != '0');
            break;
        case '7':
            PesquisaEstadia();
            break;
        case '8':
            printf("\tPesquisar pontos de fidelidade");
            printf("\n\nDigite o codigo do cliente: ");
            scanf("%d", &codigoCliente);
            printf("\tPontos de fidelidade\n");
            printf("\n\nO cliente %d possui %d pontos de fidelidade.", codigoCliente, calcularQuantidadePontosFidelidade(codigoCliente));
            pause();
            break;
        case '0':
            printf("Voce apertou 0, saindo....\n");
            break;

        default:
            printf("Opcao invalida! Favor escolher uma opcao do menu!\n");
            break;
        }
    } while (opcaoMenu != '0');
}
