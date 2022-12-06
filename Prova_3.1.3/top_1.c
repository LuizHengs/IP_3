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

void criarDepartamentos (tDepartamento departamentos[]) {

    FILE *departamentoArqTexto_b;

    int i;
    // = sizeof(departamentos)/sizeof(departamentos[0]);
    //printf("\nO i é %d", i);

    departamentoArqTexto_b = fopen("departamentos_b.txt", "wb+");
    verificarAbertura(departamentoArqTexto_b);

    fwrite(departamentos, sizeof(tDepartamento), 4, departamentoArqTexto_b);

    i = fclose(departamentoArqTexto_b);
    verificarFechamento(i);


}

void mostrarFuncionarios(tFuncionario vetor[], int quantidade) {

    printf(" linha\tnumFunc\tnível\tdepartamento\tpróximo");

    for (int i = 0; i < quantidade; i++) {
        if (vetor[i].proximo != NULL)
            printf("\n------------------------------------------------------------------\n %u\t%u\t%u\t%d\t\t%d", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento, vetor[i].proximo->linha);
        else
            printf("\n------------------------------------------------------------------\n %u\t%u\t%u\t%d\t\t-1", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento);
    }
}

void mostrarDepartamentos(tDepartamento vetor[], int quantidade) {

    printf(" codDepto.\tnomeDepto.\tInício");

    for (int i = 0; i < quantidade; i++) {
            printf("\n------------------------------------------------------------------\n% u\t%s\t\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio->linha);
    }
} 

