#include "admitir_1.h"

void admitirFuncionario (tFuncionario **cabecaF, tFuncionario **tremF) {

    FILE *funcionariosArqDat, *funcionariosArq;

    int i, j;

    tDepartamento departamentosIni[4];

    for (i = 0; i < 4; i++) {
        departamentosIni[i].codDepto = i + 1;
        departamentosIni[i].inicio = -1;
    }

    strcpy(departamentosIni[0].nomeDepto, "vendas");
    strcpy(departamentosIni[1].nomeDepto, "contabilidade");
    strcpy(departamentosIni[2].nomeDepto, "estoque");
    strcpy(departamentosIni[3].nomeDepto, "entrega");


    criarDepartamentos(departamentosIni);


    funcionariosArq = fopen("funcionarios_b.txt", "rb+");

    int fechamento;
    int quant = 0;

    quant = quantidadeArquivo(&funcionariosArq);
    int quantColocar = 0;
    tFuncionario funcionarios[quant];


    quantColocar = fread(funcionarios, sizeof(tFuncionario), quant, funcionariosArq);

    quantColocar = quantColocar > 0 ? 1: 0;

    ////////////////////////////////////////////////////// Lista Encadeada //////////////////////////////////////////////////////////////////////

    tFuncionario *novoFun;
    tFuncionario *compararCod;
    int g;
    unsigned int codFuncio;

    do {

        if (quant == 0) {

            (*cabecaF)->linha = quantColocar++;

            printf("\nQual é o número do funcionário? Digite: ");
            scanf(" %u", &(*cabecaF)->codFuncio);
            limparBuffer();

            printf("Qual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
            scanf(" %u", &(*cabecaF)->nivelSalarial);
            limparBuffer();
            
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

            (*cabecaF)->proximo = NULL;

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

            if (quantColocar <= 19) {

                *tremF = *cabecaF;

                while ((*tremF)->proximo != NULL)
                    *tremF = (*tremF)->proximo;

                novoFun = (tFuncionario *) malloc (sizeof(tFuncionario));

                novoFun->linha = quantColocar++;

                printf("\nQual é o número do funcionário? Digite: ");
                scanf(" %u", &codFuncio);
                limparBuffer();

                do {

                    if (g) {
                        printf("\nERRO! CÓDIGO REPETIDO! DE NOVO: Qual é o número do funcionário? Digite: ");
                        scanf(" %u", &codFuncio);
                        limparBuffer();
                    } 

                    g = 0;

                    for (compararCod = *cabecaF; compararCod != NULL; compararCod = compararCod->proximo) {

                        if (compararCod->codFuncio == codFuncio)
                            g = 1;
                    }   

                } while (g);

                (novoFun->codFuncio) = codFuncio;

                printf("\nQual é o nível salarial do funcionário? Digite um número inteiro positivo representando a casa dos milhares: ");
                scanf(" %u", &(novoFun->nivelSalarial));
                limparBuffer();

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

                novoFun->proximo = NULL;
                (*tremF)->proximo = novoFun;

            }
        }

        if (quantColocar < 20 && quant < 20) {
            printf("\tVocê dessa adicionar mais alguém? No máximo até 20 funcionários! Se sim, digite 0. Se não, digite 1: ");
            scanf("%d", &fechamento);
            limparBuffer();
        }

        if (quantColocar == 20) {
            printf("\n\t Só pode adicionar até 20 funcionários! Não pode mais!\n");
        }

    } while (!(fechamento) && !(quantColocar > 19));

    fechamento = fclose(funcionariosArq);

    /////////////////////////////////////////////////////////// Organizar tudo em uma bendita array de structs ///////////////////////////////////////////////////////////////////////

    *tremF = *cabecaF;

    tFuncionario funcionariosAtualizados[quantColocar];
    fechamento = 0;

    funcionariosAtualizados[fechamento++] = *(*tremF);

    while ((*tremF)->proximo != NULL) {

        funcionariosAtualizados[fechamento++] = *((*tremF)->proximo);

        (*tremF) = (*tremF)->proximo;

    }

    //////////////////////////////////////////////////////////////// Organizar a array de struct de departamento //////////////////////////////////////////////////////////////

    FILE *departamentoArqDat, *departamentoArqTexto_b, *departamentoArqTexto;
    int quantDepart;

    departamentoArqTexto_b = fopen("departamentos_b.txt", "rb+");

    fseek(departamentoArqTexto_b, 0, SEEK_END);
    quantDepart = ftell(departamentoArqTexto_b)/sizeof(tDepartamento);
    rewind(departamentoArqTexto_b);

    tDepartamento departamentos[quantDepart];

    for (i = 0; i < quantDepart; i++)
        fread(&(departamentos[i]), sizeof(tDepartamento), 1, departamentoArqTexto_b);

    fechamento = fclose(departamentoArqTexto_b);

    //////////////////////////////////////////////////////////////// Organizar a bendita da array de structs por departamentos//////////////////////////////////////////////////////////

    atualizarPonteiros(funcionariosAtualizados, departamentos, quantColocar);

    /////////////////////////////////////////////////////////////// Passar os valores iniciais de volta (com ponteiros corretos) //////////////////////////////////////////////

    voltarPonteiros(funcionarios, funcionariosAtualizados, quant);

    //////////////////////////////////////////////////////////////// Escrever nos arquivos /////////////////////////////////////////////////////////////////////////////////////
    funcionariosArq = fopen("funcionarios_b.txt", "wb+");

    for (i = 0; i < quantColocar; i++)
        fwrite(&(funcionariosAtualizados[i]), sizeof(tFuncionario), 1, funcionariosArq);

    fechamento = fclose(funcionariosArq);

    printf("\n\nEsta é a tabela lida de departamentos: \n\n");

    mostrarDepartamentos(departamentos, quantDepart);
    limparBuffer();

    departamentoArqTexto_b = fopen("departamentos_b.txt", "wb+");
    for (i = 0; i < quantDepart; i++)
        fwrite(&(departamentos[i]), sizeof(tDepartamento), 1, departamentoArqTexto_b);
    fechamento = fclose(departamentoArqTexto_b);

    escreverFuncionarios(funcionariosAtualizados, quantColocar);
    escreverDepartamentos(departamentos, quantDepart);

    /////////////////////////////////////////////////////////////// Mostrar no Programa ////////////////////////////////////////////////////////////////////////////////////

    printf("\n\n Este é o arquivo inicial dos funcionários: \n\n");
    mostrarFuncionarios(funcionarios, quant);

    printf("\n\nA operação foi de adicionar funcionários admitidos no sistema!");

    printf("\n\nEsta é a tabela atualizada de departamentos: \n\n");

    mostrarDepartamentos(departamentos, quantDepart);

    printf("\n\n Este é o arquivo final dos funcionários: \n");
    mostrarFuncionarios(funcionariosAtualizados, quantColocar);

}
