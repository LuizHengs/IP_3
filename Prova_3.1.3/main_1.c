#include "admitir_1.h"
#include "top_1.h"

int main () {

    #if WINDOWS

        u_int codigoConsolePadrao = GetConsoleOutputCP();
        u_int codigoConsole = 65001; // Código do padrão UTF-8

        SetConsoleOutputCP(codigoConsole); // Coloca o terminal no padrão UTF-8

    #endif

    setlocale(LC_ALL, "pt_BR.utf8");

    /////////////////////////////////////////////////////////////////////////////////


    int opcao;
    tFuncionario *cabecaF;
    tFuncionario *tremF;
    cabecaF = (tFuncionario *) malloc (sizeof(tFuncionario));

    do {

        printf("\n\n\tSeja bem vindo ao registro de funcionários!");
        printf("\n\n\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        printf("\n\t-=-=-=-=-=-=-=-=   MENU   -=-=-=-=-=-=-=-=-");
        printf("\n\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        printf("\n");
        printf("\n\t0 - Finalizar o programa");
        printf("\n\t1 - Admissão de um novo funcionário");
        printf("\n\t2 - Demissão de funcionário");
        printf("\n\t3 - Mudança de departamento por um funcionário");
        printf("\n\t4 - Consulta a todos os funcionários de um departamento");
        printf("\n\t5 - Consulta individual de um funcionário");
        printf("\n\n\tDigite a tua opção aqui: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

            case 0: printf("\nO programa será finalizado"); break;
            case 1: admitirFuncionario(&cabecaF, &tremF); break;
            /*case 2: demitirFuncionario(); break;
            case 3: mudarDepartamento(); break;
            case 4: consultarDepartamento(); break;
            case 5: consultarFuncionario(); break;
            */

            default: limparTela(); printf("\nVocê escolheu errado! Tente escolher uma das opções abaixo: ");
        }

    } while (opcao != 0);




    /////////////////////////////////////////////////////////////////////////////////
    getchar(); // Semelhante função aqui ao do system("pause");

    #if WINDOWS

        SetConsoleOutputCP(codigoConsolePadrao); // De volta ao padrão original

    #endif

    limparTela();

    return 0;
}