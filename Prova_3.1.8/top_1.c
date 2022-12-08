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

    for (i = 0; i < 4; i++)
        fwrite(&(departamentos[i]), sizeof(tDepartamento), 1, departamentoArqTexto_b);

    i = fclose(departamentoArqTexto_b);
    verificarFechamento(i);


}

void escreverDepartamentos (tDepartamento vetor[], int quantidade) {

    FILE *departamentoArqTexto;
    int fechamento;

    departamentoArqTexto = fopen("departamentos.txt", "w+");

    fprintf(departamentoArqTexto, " codDepto\tnomeDepto\tInício");

     for (int i = 0; i < quantidade; i++) {
            if (i != 1)
                fprintf(departamentoArqTexto, "\n%u\t\t%s\t\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
            else
                fprintf(departamentoArqTexto, "\n%u\t\t%s\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
     }

    fechamento = fclose(departamentoArqTexto);

    departamentoArqTexto = fopen("departamentos.dat", "w+");

    fprintf(departamentoArqTexto, " codDepto\tnomeDepto\tInício");


     for (int i = 0; i < quantidade; i++) {
            if (i != 1)
                fprintf(departamentoArqTexto, "\n%u\t\t%s\t\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
            else
                fprintf(departamentoArqTexto, "\n%u\t\t%s\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
     }

    fechamento = fclose(departamentoArqTexto);
}

void escreverFuncionarios (tFuncionario vetor[], int quantidade) {

    FILE *funcionarios_textoArqDat, *funcionarios_textoArq;
    int fechamento;

    funcionarios_textoArq = fopen("funcionarios.txt", "w+");
    funcionarios_textoArqDat = fopen("funcionarios.dat", "w+");

    fprintf(funcionarios_textoArq, " linha\tnumFunc\tnívelSalarial\tdepartamento\tpróximo");
    fprintf(funcionarios_textoArqDat, " linha\tnumFunc\tnívelSalarial\tdepartamento\tpróximo");

    for (int i = 0; i < quantidade; i++) {
        if (vetor[i].proximo != NULL) {
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t\t%d\t\t%d", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento, vetor[i].proximo->linha);
            fprintf(funcionarios_textoArqDat, "\n%u\t%u\t%u\t\t%d\t\t%d", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento, vetor[i].proximo->linha);
        }else{
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t\t%d\t\t-1", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento);
            fprintf(funcionarios_textoArqDat, "\n%u\t%u\t%u\t\t%d\t\t-1", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento);
        }
    }

    fechamento = fclose(funcionarios_textoArqDat);
    fechamento = fclose(funcionarios_textoArq);

}

void mostrarFuncionarios(tFuncionario vetor[], int quantidade) {

    printf(" linha\tnumFunc\tnívelSalarial\tdepartamento\tpróximo");

    for (int i = 0; i < quantidade; i++) {
        if (vetor[i].proximo != NULL)
            printf("\n------------------------------------------------------------------\n %u\t%u\t%u\t\t%d\t\t%d", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento, vetor[i].proximo->linha);
        else
            printf("\n------------------------------------------------------------------\n %u\t%u\t%u\t\t%d\t\t-1", vetor[i].linha, vetor[i].codFuncio, vetor[i].nivelSalarial, vetor[i].departamento);
    }
}

void mostrarDepartamentos(tDepartamento vetor[], int quantidade) {

    printf(" codDepto.\tnomeDepto.\tInício");

    for (int i = 0; i < quantidade; i++) {
            if (i != 1)
                printf("\n------------------------------------------------------------------\n %u\t\t%s\t\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
            else
                printf("\n------------------------------------------------------------------\n %u\t\t%s\t%d", vetor[i].codDepto, vetor[i].nomeDepto, vetor[i].inicio);
    }
}

//////////////////////////////////////////////////////////////////// ORGANIZAR PONTEIROS ///////////////////////////////////////////////////////////////////////////////////

void atualizarPonteiros (tFuncionario funcionariosAtualizados[], tDepartamento departamentos[], int quantColocar) {

    tFuncionario *modificadorF, *modificanteF, *cabecaVendas, *cabecaContab, *cabecaEstoque, *cabecaEntrega;
    int i, qtdVendas = 0, qtdContab = 0, qtdEstoque = 0, qtdEntrega = 0;
    cabecaVendas = NULL;
    cabecaContab = NULL;
    cabecaEstoque = NULL;
    cabecaEntrega = NULL;

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].departamento == 2)
            qtdContab++;
        else if (funcionariosAtualizados[i].departamento == 3)
            qtdEstoque++;
        else if (funcionariosAtualizados[i].departamento == 4)
            qtdEntrega++;
        else
            qtdVendas++;
    }

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].departamento == 2 && qtdContab > 0){
        qtdContab--;
        if (cabecaContab == NULL) {
            cabecaContab = &(funcionariosAtualizados[i]);
            departamentos[1].inicio = cabecaContab->linha;
        }else{
            cabecaContab->proximo = &(funcionariosAtualizados[i]);
            cabecaContab = &(funcionariosAtualizados[i]);
        }
        } else if (funcionariosAtualizados[i].departamento == 3 && qtdEstoque > 0){
            qtdEstoque--;
            if (cabecaEstoque == NULL) {
                cabecaEstoque = &(funcionariosAtualizados[i]);
                departamentos[2].inicio = cabecaEstoque->linha;
            }else{
                cabecaEstoque->proximo = &(funcionariosAtualizados[i]);
                cabecaEstoque = &(funcionariosAtualizados[i]);
            }
        } else if (funcionariosAtualizados[i].departamento == 4 && qtdEntrega > 0){
            qtdEntrega--;
            if (cabecaEntrega == NULL) {
                cabecaEntrega = &(funcionariosAtualizados[i]);
                departamentos[3].inicio = cabecaEntrega->linha;
            }else{
                cabecaEntrega->proximo = &(funcionariosAtualizados[i]);
                cabecaEntrega = &(funcionariosAtualizados[i]);
            }
        } else if (qtdVendas > 0){
            qtdVendas--;
            if (cabecaVendas == NULL) {
                cabecaVendas = &(funcionariosAtualizados[i]);
                departamentos[0].inicio = cabecaVendas->linha;
            }else{
                cabecaVendas->proximo = &(funcionariosAtualizados[i]);
                cabecaVendas = &(funcionariosAtualizados[i]);
            }
        }

    }

    if (cabecaVendas != NULL)
        cabecaVendas->proximo = NULL;
    
    if (cabecaContab != NULL)
        cabecaContab->proximo = NULL;
    
    if (cabecaEstoque != NULL)
        cabecaEstoque->proximo = NULL;
    
    if (cabecaEntrega != NULL)
        cabecaEntrega->proximo = NULL;

};

///////////////////////////////////////////////////// PASSAR VALORES INICIAIS DE VOLTA //////////////////////////////////////////

void voltarPonteiros (tFuncionario funcionarios[], tFuncionario funcionariosAtualizados[], int quant) {

    struct tEmployer *proximoAtualizado[quant];
    struct tEmployer *proximoPrimeirosAtualizado[quant];
    int i, j, z;

    for (i = 0; i < quant; i++)
        funcionarios[i] = funcionariosAtualizados[i];


    for (i = 0; i < quant; i++) {

        z = 1;

        for (j = 0; j < quant; j++)
            if ((funcionarios[i].proximo) == &(funcionariosAtualizados[j])){
                z = 0;
                break;
            }
        if (z == 1)  // Se há um ponteiro igual ao do funcionarios[i].proximo, então funcionarios[i].proximo não será NULL
            funcionarios[i].proximo = NULL;
    }

}

///////////////////////////////////////////////////////////////////// ENCHER CABEÇA E TREM ///////////////////////////////////////////////////////////////////////////////////

void encherCabeca (tFuncionario **cabecaF, tFuncionario **tremF) {

    FILE *funcionariosArq;
    tFuncionario *novoFun;

    funcionariosArq = fopen("funcionarios_b.txt", "rb+");

    int fechamento, i;
    int quant = 0;
    quant = quantidadeArquivo(&funcionariosArq);
    int quantColocar = 0;
    tFuncionario funcionarios[quant];

    for (i = 0; i < quant; i++)
        quantColocar += fread(&(funcionarios[i]), sizeof(tFuncionario), 1, funcionariosArq);

    quantColocar = quantColocar > 0 ? 1: 0;

    if (quantColocar < quant) {
        (*cabecaF)->linha = funcionarios[0].linha;
        (*cabecaF)->codFuncio = funcionarios[0].codFuncio;
        (*cabecaF)->nivelSalarial = funcionarios[0].nivelSalarial;
        (*cabecaF)->departamento = funcionarios[0].departamento;
        (*cabecaF)->proximo = NULL;
    }

    for (; quantColocar < quant; quantColocar++) {
        *tremF = *cabecaF;

        while ((*tremF)->proximo != NULL)
            *tremF = (*tremF)->proximo;

        novoFun = (tFuncionario *) malloc (sizeof(tFuncionario));

        novoFun->linha = funcionarios[quantColocar].linha;
        novoFun->codFuncio = funcionarios[quantColocar].codFuncio;
        novoFun->nivelSalarial = funcionarios[quantColocar].nivelSalarial;
        novoFun->departamento = funcionarios[quantColocar].departamento;
        novoFun->proximo = NULL;
        (*tremF)->proximo = novoFun;
        funcionarios[quantColocar - 1] = *(*tremF);
    }

   fechamento = fclose(funcionariosArq);

}

void retira(tFuncionario **cabecaF, int v) {

    tFuncionario *anterior = NULL; /* ponteiro para elemento anterior */
    tFuncionario *p = *cabecaF; /* ponteiro para percorrer a lista*/
    tFuncionario *tremF;

    while (p != NULL && p->codFuncio != v) {/* procura elemento na lista, guardando anterior */
        anterior = p;
        p = p->proximo;
    }
    
    /* retira elemento */
    if (anterior == NULL) /* retira elemento do inicio */
     *cabecaF = p->proximo;
    else /* retira elemento do meio da lista */
        anterior->proximo = p->proximo;
    

    for (tremF = p; tremF != NULL; tremF = tremF->proximo) {
        tremF->linha -= 1;
    }

    free(p);

}

