#include "admitir_1.h"

    tDepartamento departamento1 = {1, "vendas", 0};
    tDepartamento departamento2 = {2, "contabilidade", 8};
    tDepartamento departamento3 = {3, "estoque", 7};
    tDepartamento departamento4 = {4, "entrega", 2};

void admitirFuncionario (tFuncionario **cabecaF, tFuncionario **tremF) {

    FILE *funcionariosArqDat, *funcionariosArq;
    FILE *funcionarios_textoArqDat, *funcionarios_textoArq;

    funcionariosArqDat = fopen("funcionarios_b.dat", "rb+");
    verificarAbertura(funcionariosArqDat);
    funcionariosArq = fopen("funcionarios_b.txt", "rb+");
    verificarAbertura(funcionariosArq);
    funcionarios_textoArqDat = fopen("funcionarios.dat", "r+");
    verificarAbertura(funcionarios_textoArqDat);
    funcionarios_textoArq = fopen("funcionarios.txt", "r+");
    verificarAbertura (funcionarios_textoArq);



    int fechamento;
    int quant = 1;
    quant = quantidadeArquivo(funcionariosArq);
    int quantColocar = quant;

    
    int funcionarios[quant];
    fread(&funcionarios, sizeof(tFuncionario), quant, funcionariosArq);
    *cabecaF = funcionarios;
    



    ////////////////////////////////////////////////////// Lista Encadeada //////////////////////////////////////////////////////////////////////

    do {

        if (quantColocar == 0) {

            (*cabecaF)->linha = quantColocar++;

            printf("\n(Cabeça)Qual é o número do funcionário? Digite: ");
            scanf(" %u", &(*cabecaF)->codFuncio);
            limparBuffer();

            printf("Qual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
            scanf(" %u", &(*cabecaF)->nivelSalarial);
            limparBuffer();
            printf("\n%u", (*cabecaF)->nivelSalarial);

            printf("Qual é o código do departamento ao qual o funcionário pertencerá? Digite: ");
            printf("\n\t1 - Vendas;");
            printf("\n\t2 - Contabilidade;");
            printf("\n\t3 - Estoque;");
            printf("\n\t4 - Entrega");
            printf("\n\tDigite: ");
            scanf(" %d", &(*cabecaF)->departamento);
            limparBuffer();
            printf("\n%d", (*cabecaF)->departamento);

            (*cabecaF)->proximo = NULL;

            printf("\nCabeçaF é %d", (*cabecaF));

        }else{

            *tremF = *cabecaF;

            while ((*tremF)->proximo != NULL)
                *tremF = (*tremF)->proximo;
            
            ((*tremF)->proximo) = (tFuncionario *) malloc (sizeof(tFuncionario));

            ((*tremF)->proximo)->linha = quantColocar++;

            printf("\n(trem)Qual é o número do funcionário? Digite: ");
            scanf(" %u", &((*tremF)->proximo)->codFuncio);
            limparBuffer();

            printf("\nQual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
            scanf(" %u", &((*tremF)->proximo)->nivelSalarial);
            limparBuffer();
            printf("\n%u", ((*tremF)->proximo)->nivelSalarial);

            printf("Qual é o código do departamento ao qual o funcionário pertencerá? Digite: ");
            printf("\n\t1 - Vendas;");
            printf("\n\t2 - Contabilidade;");
            printf("\n\t3 - Estoque;");
            printf("\n\t4 - Entrega");
            printf("\n\tDigite: ");
            scanf(" %d", &((*tremF)->proximo)->departamento);
            limparBuffer();
            printf("\n%d", ((*tremF)->proximo)->departamento);

            (*tremF) = (*tremF)->proximo;
            (*tremF)->proximo = NULL;

            printf("\nTremF é %d", (*tremF));
            printf("\nTremF proximo é %d", (*tremF)->proximo);

        }

        printf("Você deseja adicionar mais alguém? Se sim, digite 0. Se não, digite 1: ");
        scanf("%d", &fechamento);
        limparBuffer();

    } while (!(fechamento));

    fechamento = fclose(funcionariosArq);
    verificarFechamento(fechamento);

    /////////////////////////////////////////////////////////// Passar tudo para os arquivos ///////////////////////////////////////////////////////////////////////

    *tremF = *cabecaF;


    fprintf(funcionarios_textoArq, " linha\tnumFunc\tnível\tdepartamento\tpróximo");
    limparBuffer();

    while ((*tremF) != NULL) {

        if (((*tremF)->proximo) != NULL)
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t%d", (*tremF)->linha, (*tremF)->codFuncio, (*tremF)->nivelSalarial, (*tremF)->departamento, ((*tremF)->proximo)->linha);
        else
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t-1", (*tremF)->linha, (*tremF)->codFuncio, (*tremF)->nivelSalarial, (*tremF)->departamento);

        (*tremF) = (*tremF)->proximo;
    }

    funcionariosArq = fopen("funcionarios_b.txt", "wb+");
    verificarAbertura(funcionariosArq);

    *tremF = *cabecaF;

    fseek(funcionariosArq, 0, SEEK_SET);

    while ((*tremF) != NULL) {

        fwrite(*tremF, sizeof(tFuncionario), 1, funcionariosArq);

        (*tremF) = (*tremF)->proximo;

    }


    fechamento = fclose(funcionariosArqDat);
    verificarFechamento(fechamento);
    fechamento = fclose(funcionariosArq);
    verificarFechamento(fechamento);
    fechamento = fclose(funcionarios_textoArqDat);
    verificarFechamento(fechamento);
    fechamento = fclose(funcionarios_textoArq);
    verificarFechamento(fechamento);

}

