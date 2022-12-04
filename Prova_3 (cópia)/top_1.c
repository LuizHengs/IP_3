#include "top_1.h"

void limparBuffer () {

    while(getchar() != '\n');

}

void limparTela () {

    #if WINDOWS

        system("cls");

    #else

        system("clear");

    #endif

}

////////////////////////////////////////////////////////////////

void verificarAbertura(FILE *a) {

    if (a == NULL)
        printf("\nERRO. O arquivo não abriu!");
    else
        printf("\nO arquivo abriu sem problemas");

}

void verificarFechamento (int fechamento) {

    if (fechamento == 0)
        printf("\nO arquivo fechou corretamente");
    else
        printf("\nO arquivo não fechou corretamente");

}

void verificarErro (FILE *a) {

    if (ferror(a))
        printf("Erro na operação com o arquivo");

}

int quantidadeArquivo (FILE **a) {

    int quantidade;
    fseek(*a, 0, SEEK_END);
    quantidade = ftell(*a)/sizeof(tFuncionario);
    rewind(*a);

    return quantidade;


}

////////////////////////////////////////////////////////////////

