#include "admitir_1.h"

    tDepartamento departamento1 = {1, "vendas", 0};
    tDepartamento departamento2 = {2, "contabilidade", 1};
    tDepartamento departamento3 = {3, "estoque", 2};
    tDepartamento departamento4 = {4, "entrega", 3};

void admitirFuncionario (tFuncionario **cabecaF, tFuncionario **tremF) {

    FILE *funcionariosArqDat, *funcionariosArq;
    FILE *funcionarios_textoArqDat, *funcionarios_textoArq;

    funcionariosArq = fopen("funcionarios_b.txt", "rb+");
    verificarAbertura(funcionariosArq);
    funcionarios_textoArqDat = fopen("funcionarios.dat", "r+");
    verificarAbertura(funcionarios_textoArqDat);
    funcionarios_textoArq = fopen("funcionarios.txt", "r+");
    verificarAbertura (funcionarios_textoArq);

    

    int fechamento;
    int quant = 0;
    quant = quantidadeArquivo(&funcionariosArq);
    int i, j, quantColocar = 0;
    tFuncionario funcionarios[quant];

    printf("\n---Quantidade de blocos no arquivo é %d---", quant);

    
    quantColocar = fread(funcionarios, sizeof(tFuncionario), quant, funcionariosArq);
    
    printf("\n----Quantidade a colocar eh %d----", quantColocar);
    printf("\n---Informações: %u %u %d", funcionarios[1].linha, funcionarios[1].nivelSalarial, funcionarios[1].proximo);
    printf("\n---Ponteiro do funcionários array de structs: %d", &(funcionarios[0]));
    quantColocar = quantColocar > 0 ? 1: 0;
    
    printf("\n----Quantidade a colocar eh %d----", quantColocar);



    ////////////////////////////////////////////////////// Lista Encadeada //////////////////////////////////////////////////////////////////////

    tFuncionario *novoFun;

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
            }

            *tremF = *cabecaF;

            while ((*tremF)->proximo != NULL)
                *tremF = (*tremF)->proximo;
            
            novoFun = (tFuncionario *) malloc (sizeof(tFuncionario));

            novoFun->linha = quantColocar++;

            printf("\n(trem)Qual é o número do funcionário? Digite: ");
            scanf(" %u", &(novoFun->codFuncio));
            limparBuffer();

            printf("\nQual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
            scanf(" %u", &(novoFun->nivelSalarial));
            limparBuffer();
            printf("\n%u", (novoFun->nivelSalarial));

            printf("Qual é o código do departamento ao qual o funcionário pertencerá? Digite: ");
            printf("\n\t1 - Vendas;");
            printf("\n\t2 - Contabilidade;");
            printf("\n\t3 - Estoque;");
            printf("\n\t4 - Entrega");
            printf("\n\tDigite: ");
            scanf(" %d", &(novoFun->departamento));
            limparBuffer();
            printf("\n%d", (novoFun->departamento));

            novoFun->proximo = NULL;
            (*tremF)->proximo = novoFun;

            printf("\nTremF é %d", (*tremF));
            printf("\nTremF proximo é %d", (*tremF)->proximo);

        }

        printf("Você deseja adicionar mais alguém? Se sim, digite 0. Se não, digite 1: ");
        scanf("%d", &fechamento);
        limparBuffer();

    } while (!(fechamento));

    fechamento = fclose(funcionariosArq);
    verificarFechamento(fechamento);

    /////////////////////////////////////////////////////////// Organizar tudo em uma bendita array de structs ///////////////////////////////////////////////////////////////////////

    *tremF = *cabecaF;

    //fseek(funcionariosArq, 0, SEEK_SET);
    tFuncionario funcionariosAtualizados[quantColocar];
    fechamento = 0;
    
    funcionariosAtualizados[fechamento++] = *(*tremF);

    printf("\n==Teste do cabeça: %u %d", funcionariosAtualizados[0].linha, funcionariosAtualizados[0].departamento);

    while ((*tremF)->proximo != NULL) {

        funcionariosAtualizados[fechamento++] = *((*tremF)->proximo);

        (*tremF) = (*tremF)->proximo;

    }

    printf("\n==Teste do cabeça: %u %d", funcionariosAtualizados[0].linha, funcionariosAtualizados[0].departamento);

    //////////////////////////////////////////////////////////////// Organizar a bendita da array de structs por departamentos//////////////////////////////////////////////////////////

    tFuncionario *modificadorF, *modificanteF, *cabecaVendas, *cabecaContab, *cabecaEstoque, *cabecaEntrega;
    int jaAchados = 1, qtdVendas = 0, qtdContab = 0, qtdEstoque = 0, qtdEntrega = 0;
    cabecaVendas = NULL;
    cabecaContab = NULL;
    cabecaEstoque = NULL;
    cabecaEntrega = NULL;

    printf("\n===Começou distribuição");

    for (i = 0; i < quantColocar; i++) {
        printf("\n===Começou Colocar quantidades");
        if (funcionariosAtualizados[i].departamento == 2)
            qtdContab++;
        else if (funcionariosAtualizados[i].departamento == 3)
            qtdEstoque++;
        else if (funcionariosAtualizados[i].departamento == 4)
            qtdEntrega++;
        else
            qtdVendas++;
        printf("\n===Terminou Colocar quantidades");
    }

    printf("\n==Quantidade de vendas: %d", qtdVendas);
    printf("\n==Quantidade de Contab.: %d", qtdContab);
    printf("\n==Quantidade de Estoque: %d", qtdEstoque);
    printf("\n==Quantidade de Entrega: %d", qtdEntrega);

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].departamento == 2 && qtdContab > 0){
        printf("\n===Começou ordenar Contab");
        qtdContab--;
        if (cabecaContab == NULL) {
            cabecaContab = &(funcionariosAtualizados[i]);
            printf("\n Ponteiro é: %d", cabecaContab);
        }else{
            cabecaContab->proximo = &(funcionariosAtualizados[i]);
            cabecaContab = &(funcionariosAtualizados[i]);
        }
        printf("\n===Terminou ordenar Contab");
        } else if (funcionariosAtualizados[i].departamento == 3 && qtdEstoque > 0){
            printf("\n===Começou ordenar Estoque");
            qtdEstoque--;
            if (cabecaEstoque == NULL) {
                cabecaEstoque = &(funcionariosAtualizados[i]);
                printf("\n Ponteiro é: %d", cabecaEstoque);
            }else{
                cabecaEstoque->proximo = &(funcionariosAtualizados[i]);
                cabecaEstoque = &(funcionariosAtualizados[i]);
            }
            printf("\n===Terminou ordenar Estoque");
        } else if (funcionariosAtualizados[i].departamento == 4 && qtdEntrega > 0){
            printf("\n===Começou ordenar Entrega");
            qtdEntrega--;
            if (cabecaEntrega == NULL) {
                cabecaEntrega = &(funcionariosAtualizados[i]);
                printf("\n Ponteiro é: %d", cabecaEntrega);
            }else{
                cabecaEntrega->proximo = &(funcionariosAtualizados[i]);
                cabecaEntrega = &(funcionariosAtualizados[i]);
            }
            printf("\n===Terminou ordenar Entrega");
        } else if (qtdVendas > 0){
            printf("\n===Começou ordenar vendas");
            qtdVendas--;
            if (cabecaVendas == NULL) {
                cabecaVendas = &(funcionariosAtualizados[i]);
                printf("\n Ponteiro é: %d", cabecaVendas);
            }else{
                cabecaVendas->proximo = &(funcionariosAtualizados[i]);
                cabecaVendas = &(funcionariosAtualizados[i]);
            }
            printf("\n===Terminou ordenar vendas");
        }
        
    }

    cabecaVendas->proximo = NULL;
    cabecaContab->proximo = NULL;
    cabecaEstoque->proximo = NULL;
    cabecaEntrega->proximo = NULL;


    //////////////////////////////////////////////////////////////// Escrever nos arquivos /////////////////////////////////////////////////////////////////////////////////////
    funcionariosArq = fopen("funcionarios_b.txt", "wb+");
    verificarAbertura(funcionariosArq);

    fwrite(funcionariosAtualizados, sizeof(tFuncionario), quantColocar, funcionariosArq);

    fechamento = fclose(funcionariosArq);
    verificarFechamento(fechamento);

    *tremF = *cabecaF;

    fprintf(funcionarios_textoArq, " linha\tnumFunc\tnível\tdepartamento\tpróximo");
    limparBuffer();

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].proximo != NULL)
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t%d", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento, funcionariosAtualizados[i].proximo->linha);
        else
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t-1", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento);
    }

    


    
    fechamento = fclose(funcionarios_textoArqDat);
    verificarFechamento(fechamento);
    fechamento = fclose(funcionarios_textoArq);
    verificarFechamento(fechamento);

}

