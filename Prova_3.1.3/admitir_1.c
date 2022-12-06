#include "admitir_1.h"

    
    

void admitirFuncionario (tFuncionario **cabecaF, tFuncionario **tremF) {

    FILE *funcionariosArqDat, *funcionariosArq;
    FILE *funcionarios_textoArqDat, *funcionarios_textoArq;
    int i, j;

    tDepartamento departamentosIni[4];

    for (i = 0; i < 4; i++) {
        departamentosIni[i].codDepto = i;
        departamentosIni[i].inicio = i;
    }

    strcpy(departamentosIni[0].nomeDepto, "vendas");
    strcpy(departamentosIni[1].nomeDepto, "contabilidade");
    strcpy(departamentosIni[2].nomeDepto, "estoque");
    strcpy(departamentosIni[3].nomeDepto, "entrega");

    //printf("Teste: departamento1[0].nomeDepto = %s", departamentosIni[0].nomeDepto);
    //printf("Teste: departamento1[2].nomeDepto = %s", departamentosIni[2].nomeDepto);

    criarDepartamentos(departamentosIni);

    funcionariosArq = fopen("funcionarios_b.txt", "rb+");
    //verificarAbertura(funcionariosArq);
    funcionarios_textoArqDat = fopen("funcionarios.dat", "r+");
    //verificarAbertura(funcionarios_textoArqDat);
    funcionarios_textoArq = fopen("funcionarios.txt", "r+");
    //verificarAbertura (funcionarios_textoArq);

    

    int fechamento;
    int quant = 0;
    quant = quantidadeArquivo(&funcionariosArq);
    int quantColocar = 0;
    tFuncionario funcionarios[quant];

    //printf("\n---Quantidade de blocos no arquivo é %d---", quant);

    
    quantColocar = fread(funcionarios, sizeof(tFuncionario), quant, funcionariosArq);
    
    //printf("\n----Quantidade a colocar eh %d----", quantColocar);
    //printf("\n---Informações: %u %u %d", funcionarios[1].linha, funcionarios[1].nivelSalarial, funcionarios[1].proximo);
    //printf("\n---Ponteiro do funcionários array de structs: %d", &(funcionarios[0]));
    quantColocar = quantColocar > 0 ? 1: 0;
    
    //printf("\n----Quantidade a colocar eh %d----", quantColocar);



    ////////////////////////////////////////////////////// Lista Encadeada //////////////////////////////////////////////////////////////////////

    tFuncionario *novoFun;

    do {

        if (quantColocar == 0) {

            (*cabecaF)->linha = quantColocar++;

            printf("\nQual é o número do funcionário? Digite: ");
            scanf(" %u", &(*cabecaF)->codFuncio);
            limparBuffer();

            printf("Qual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
            scanf(" %u", &(*cabecaF)->nivelSalarial);
            limparBuffer();
            //printf("\n%u", (*cabecaF)->nivelSalarial);
            do {
                int d;
                printf("\nQual é o código do departamento ao qual o funcionário pertencerá? Digite: ");
                printf("\n\t1 - Vendas;");
                printf("\n\t2 - Contabilidade;");
                printf("\n\t3 - Estoque;");
                printf("\n\t4 - Entrega");
                printf("\n\tDigite: ");
                scanf(" %d", &d);
                limparBuffer();

                (*cabecaF)->departamento = d;

                if (((*cabecaF)->departamento < 1) || ((*cabecaF)->departamento > 4))
                    printf("\nERRO! Só pode digitar entre 1 e 4. Tente novamente!");

            } while (((*cabecaF)->departamento < 1) || ((*cabecaF)->departamento > 4));
            //printf("\n%d", (*cabecaF)->departamento);

            (*cabecaF)->proximo = NULL;

            printf("\nCabeçaF é %d", (*cabecaF));

        }else {
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

            if (quant <= 20) {

                *tremF = *cabecaF;

                while ((*tremF)->proximo != NULL)
                    *tremF = (*tremF)->proximo;
                
                novoFun = (tFuncionario *) malloc (sizeof(tFuncionario));

                novoFun->linha = quantColocar++;

                printf("\nQual é o número do funcionário? Digite: ");
                scanf(" %u", &(novoFun->codFuncio));
                limparBuffer();

                printf("\nQual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
                scanf(" %u", &(novoFun->nivelSalarial));
                limparBuffer();
                //printf("\n%u", (novoFun->nivelSalarial));

                do {
                    int d;
                    printf("\nQual é o código do departamento ao qual o funcionário pertencerá? Digite: ");
                    printf("\n\t1 - Vendas;");
                    printf("\n\t2 - Contabilidade;");
                    printf("\n\t3 - Estoque;");
                    printf("\n\t4 - Entrega");
                    printf("\n\tDigite: ");
                    scanf(" %d", &d);
                    limparBuffer();

                    (novoFun)->departamento = d;

                    if ((novoFun)->departamento < 1 || (novoFun)->departamento > 4)
                        printf("\nERRO! Só pode digitar entre 1 e 4. Tente novamente!");

                } while ((novoFun)->departamento < 1 || (novoFun)->departamento > 4);
                //printf("\n%d", (novoFun->departamento));

                novoFun->proximo = NULL;
                (*tremF)->proximo = novoFun;

                //printf("\nTremF é %d", (*tremF));
                //printf("\nTremF proximo é %d", (*tremF)->proximo);
            }
        }

        if (quantColocar < 20 && quant < 20) {
            printf("\tVocê dessa adicionar mais alguém? No máximo até 20 funcionários! Se sim, digite 0. Se não, digite 1: ");
            scanf("%d", &fechamento);
            limparBuffer();
        }

        if (quantColocar == 20) {
            printf("\n\t Só pode adicionar até 20 funcionários! Não pode mais!");
        }

    } while (!(fechamento) && !(quantColocar > 20));

    fechamento = fclose(funcionariosArq);
    //verificarFechamento(fechamento);

    /////////////////////////////////////////////////////////// Organizar tudo em uma bendita array de structs ///////////////////////////////////////////////////////////////////////

    *tremF = *cabecaF;

    //fseek(funcionariosArq, 0, SEEK_SET);
    tFuncionario funcionariosAtualizados[quantColocar];
    fechamento = 0;
    
    funcionariosAtualizados[fechamento++] = *(*tremF);

    //printf("\n==Teste do cabeça: %u %d", funcionariosAtualizados[0].linha, funcionariosAtualizados[0].departamento);

    while ((*tremF)->proximo != NULL) {

        funcionariosAtualizados[fechamento++] = *((*tremF)->proximo);

        (*tremF) = (*tremF)->proximo;

    }

    //printf("\n==Teste do cabeça: %u %d", funcionariosAtualizados[0].linha, funcionariosAtualizados[0].departamento);

    //////////////////////////////////////////////////////////////// Organizar a array de struct de departamento //////////////////////////////////////////////////////////////

    FILE *departamentoArqDat, *departamentoArqTexto_b, *departamentoArqTexto;
    int quantDepart;

    
    departamentoArqTexto_b = fopen("departamentos_b.txt", "rb+");
    //verificarAbertura(departamentoArqTexto_b);
    

    fseek(departamentoArqTexto_b, 0, SEEK_END);
    quantDepart = ftell(departamentoArqTexto_b)/sizeof(tDepartamento);
    rewind(departamentoArqTexto_b);

    tDepartamento departamentos[quantDepart];
    fread(departamentos, sizeof(tDepartamento), quantDepart, departamentoArqTexto_b);

    fechamento = fclose(departamentoArqTexto_b);
    //verificarFechamento(fechamento);

    //////////////////////////////////////////////////////////////// Organizar a bendita da array de structs por departamentos//////////////////////////////////////////////////////////

    tFuncionario *modificadorF, *modificanteF, *cabecaVendas, *cabecaContab, *cabecaEstoque, *cabecaEntrega;
    int jaAchados = 1, qtdVendas = 0, qtdContab = 0, qtdEstoque = 0, qtdEntrega = 0;
    cabecaVendas = NULL;
    cabecaContab = NULL;
    cabecaEstoque = NULL;
    cabecaEntrega = NULL;

    //printf("\n===Começou distribuição");

    for (i = 0; i < quantColocar; i++) {
        //printf("\n===Começou Colocar quantidades");
        if (funcionariosAtualizados[i].departamento == 2)
            qtdContab++;
        else if (funcionariosAtualizados[i].departamento == 3)
            qtdEstoque++;
        else if (funcionariosAtualizados[i].departamento == 4)
            qtdEntrega++;
        else
            qtdVendas++;
        //printf("\n===Terminou Colocar quantidades");
    }

    //printf("\n==Quantidade de vendas: %d", qtdVendas);
    //printf("\n==Quantidade de Contab.: %d", qtdContab);
    //printf("\n==Quantidade de Estoque: %d", qtdEstoque);
    //printf("\n==Quantidade de Entrega: %d", qtdEntrega);

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].departamento == 2 && qtdContab > 0){
        //printf("\n===Começou ordenar Contab");
        qtdContab--;
        if (cabecaContab == NULL) {
            cabecaContab = &(funcionariosAtualizados[i]);
            departamentos[1].inicio = cabecaContab;
            //printf("\n Ponteiro é: %d", cabecaContab);
        }else{
            cabecaContab->proximo = &(funcionariosAtualizados[i]);
            cabecaContab = &(funcionariosAtualizados[i]);
        }
        //printf("\n===Terminou ordenar Contab");
        } else if (funcionariosAtualizados[i].departamento == 3 && qtdEstoque > 0){
            //printf("\n===Começou ordenar Estoque");
            qtdEstoque--;
            if (cabecaEstoque == NULL) {
                cabecaEstoque = &(funcionariosAtualizados[i]);
                departamentos[2].inicio = cabecaEstoque;
                //printf("\n Ponteiro é: %d", cabecaEstoque);
            }else{
                cabecaEstoque->proximo = &(funcionariosAtualizados[i]);
                cabecaEstoque = &(funcionariosAtualizados[i]);
            }
            //printf("\n===Terminou ordenar Estoque");
        } else if (funcionariosAtualizados[i].departamento == 4 && qtdEntrega > 0){
            //printf("\n===Começou ordenar Entrega");
            qtdEntrega--;
            if (cabecaEntrega == NULL) {
                cabecaEntrega = &(funcionariosAtualizados[i]);
                departamentos[3].inicio = cabecaEntrega;
               // printf("\n Ponteiro é: %d", cabecaEntrega);
            }else{
                cabecaEntrega->proximo = &(funcionariosAtualizados[i]);
                cabecaEntrega = &(funcionariosAtualizados[i]);
            }
            //printf("\n===Terminou ordenar Entrega");
        } else if (qtdVendas > 0){
            //printf("\n===Começou ordenar vendas");
            qtdVendas--;
            if (cabecaVendas == NULL) {
                cabecaVendas = &(funcionariosAtualizados[i]);
                departamentos[0].inicio = cabecaVendas;
                //printf("\n Ponteiro é: %d", cabecaVendas);
            }else{
                cabecaVendas->proximo = &(funcionariosAtualizados[i]);
                cabecaVendas = &(funcionariosAtualizados[i]);
            }
            //printf("\n===Terminou ordenar vendas");
        }
        
    }

    cabecaVendas->proximo = NULL;
    cabecaContab->proximo = NULL;
    cabecaEstoque->proximo = NULL;
    cabecaEntrega->proximo = NULL;

    /////////////////////////////////////////////////////////////// Passar os valores iniciais de volta (com ponteiros corretos) //////////////////////////////////////////////
    
    struct tEmployer *proximoAtualizado[quant];
    struct tEmployer *proximoPrimeirosAtualizado[quant];
    int z; 
    // Não continuar

    for (i = 0; i < quant; i++)
        funcionarios[i] = funcionariosAtualizados[i];
    
    //mostrarFuncionarios(funcionarios, quant);

    for (i = 0; i < quant; i++) {

        z = 1;

        for (j = 0; j < quant; j++) {
            if ((funcionarios[i].proximo) == &(funcionariosAtualizados[j])){
                z = 0;
                break;
            }
        }

        //printf("\nz eh %d\n", z);
        

        if (z == 1) { // Se há um ponteiro igual ao do funcionarios[i].proximo, então funcionarios[i].proximo não será NULL
            funcionarios[i].proximo = NULL;
        }
        
    }

    
    //////////////////////////////////////////////////////////////// Escrever nos arquivos /////////////////////////////////////////////////////////////////////////////////////
    funcionariosArq = fopen("funcionarios_b.txt", "wb+");
    //verificarAbertura(funcionariosArq);

    fwrite(funcionariosAtualizados, sizeof(tFuncionario), quantColocar, funcionariosArq);

    fechamento = fclose(funcionariosArq);
    //verificarFechamento(fechamento);

    departamentoArqTexto_b = fopen("departamentos_b.txt", "wb+");
    //verificarAbertura(departamentoArqTexto_b);
    fwrite(departamentos, sizeof(tDepartamento), quantDepart, departamentoArqTexto_b);

    fechamento = fclose(departamentoArqTexto_b);
    //verificarFechamento(fechamento);


    *tremF = *cabecaF;

    fprintf(funcionarios_textoArq, " linha\tnumFunc\tnível\tdepartamento\tpróximo");
    fprintf(funcionarios_textoArqDat, " linha\tnumFunc\tnível\tdepartamento\tpróximo");
    limparBuffer();

    for (i = 0; i < quantColocar; i++) {
        if (funcionariosAtualizados[i].proximo != NULL) {
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t%d", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento, funcionariosAtualizados[i].proximo->linha);
            fprintf(funcionarios_textoArqDat, "\n%u\t%u\t%u\t%d\t\t%d", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento, funcionariosAtualizados[i].proximo->linha);
        }else{
            fprintf(funcionarios_textoArq, "\n%u\t%u\t%u\t%d\t\t-1", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento);
            fprintf(funcionarios_textoArqDat, "\n%u\t%u\t%u\t%d\t\t-1", funcionariosAtualizados[i].linha, funcionariosAtualizados[i].codFuncio, funcionariosAtualizados[i].nivelSalarial, funcionariosAtualizados[i].departamento);
        }
    }

    fechamento = fclose(funcionarios_textoArqDat);
    //verificarFechamento(fechamento);
    fechamento = fclose(funcionarios_textoArq);
    //verificarFechamento(fechamento);

    //printf("\nTeste: quantidade de departamentos: %d", quantDepart);

    departamentoArqDat = fopen("departamentos.dat", "w+");
    //verificarAbertura(departamentoArqDat);
    departamentoArqTexto = fopen("departamentos.txt", "w+");
    //verificarAbertura (departamentoArqTexto);

    fprintf(departamentoArqTexto, " codDepto\tnomeDepto\tInício");
    limparBuffer();

    
    fprintf(departamentoArqTexto, "\n%u\t\t%s\t\t%d", departamentos[0].codDepto, departamentos[0].nomeDepto, departamentos[0].inicio->linha);
    fprintf(departamentoArqTexto, "\n%u\t\t%s\t%d", departamentos[1].codDepto, departamentos[1].nomeDepto, departamentos[1].inicio->linha);
    fprintf(departamentoArqTexto, "\n%u\t\t%s\t\t%d", departamentos[2].codDepto, departamentos[2].nomeDepto, departamentos[2].inicio->linha);
    fprintf(departamentoArqTexto, "\n%u\t\t%s\t\t%d", departamentos[3].codDepto, departamentos[3].nomeDepto, departamentos[3].inicio->linha);

    fprintf(departamentoArqDat, "\n%u\t\t%s\t\t%d", departamentos[0].codDepto, departamentos[0].nomeDepto, departamentos[0].inicio->linha);
    fprintf(departamentoArqDat, "\n%u\t\t%s\t%d", departamentos[1].codDepto, departamentos[1].nomeDepto, departamentos[1].inicio->linha);
    fprintf(departamentoArqDat, "\n%u\t\t%s\t\t%d", departamentos[2].codDepto, departamentos[2].nomeDepto, departamentos[2].inicio->linha);
    fprintf(departamentoArqDat, "\n%u\t\t%s\t\t%d", departamentos[3].codDepto, departamentos[3].nomeDepto, departamentos[3].inicio->linha);
    

    fechamento = fclose(departamentoArqTexto);
    //verificarFechamento(fechamento);

    fechamento = fclose(departamentoArqDat);
    //verificarFechamento(fechamento);

    /////////////////////////////////////////////////////////////// Mostrar no Programa ////////////////////////////////////////////////////////////////////////////////////

    printf("\n\n Este é o arquivo inicial dos funcionários: \n\n");
    mostrarFuncionarios(funcionarios, quant);

    printf("\n\nA operação foi de adicionar funcionários admitidos no sistema!");

    printf("\n\n Este é o arquivo final dos funcionários: \n");
    mostrarFuncionarios(funcionariosAtualizados, quantColocar);

}