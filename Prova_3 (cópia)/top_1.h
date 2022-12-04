#ifndef TOP_1_H
#define TOP_1_H

////////////////////////////////////////////////////

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <malloc.h>

////////////////////////////////////////////////////

    #if defined(_WIN32) || defined(_WIN64)

        #define WINDOWS 1
        #include <windows.h>

    #else

        #define WINDOWS 0
        #include <unistd.h>

    #endif

///////////////////////////////////////////////////

    typedef struct tEmployer {

        unsigned int linha;
        unsigned int codFuncio;
        unsigned int nivelSalarial;
        struct tDepartment *departamento;
        struct tEmployer *proximo;
        
    } tFuncionario;



    typedef struct tDepartment {

        unsigned int codDepto;
        char nomeDepto[100];
        struct tEmployer *inicio;

    } tDepartamento;

///////////////////////////////////////////////////

    enum tiposDepartamentos {
        FIM,
        VENDAS,
        CONTABILIDADE,
        ESTOQUE,
        ENTREGA
    };

///////////////////////////////////////////////////

    void limparBuffer();
    void limparTela();
    void verificarAbertura();
    void verificarFechamento();
    void verificarErro();
    int quantidadeArquivo(FILE **a);

///////////////////////////////////////////////////

#endif