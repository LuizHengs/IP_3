#include "demitir_1.h"

void demitirFuncionario(tFuncionario **cabecaF, tFuncionario **tremF) {

    printf("\n0");
    encherCabeca(&(*cabecaF), &(*tremF));

    FILE *departamentoArqDat, *departamentoArqTexto_b, *departamentoArqTexto, *funcionariosArqDat, *funcionariosArq;
    int quantDepart, codFuncio, fechamento, quantColocar = 0, i = 0;

    printf("\n1");

    //funcionariosArq = fopen("funcionarios_b.txt", "rb+");

    printf("\n2");

    int quant = 0;

    for ((*tremF) = (*cabecaF) ; (*tremF) != NULL; (*tremF) = (*tremF)->proximo) {
        quantColocar++;
        quant++;
    }

    //quant = quantidadeArquivo(&funcionariosArq);
    tFuncionario funcionarios[quant];

    for ((*tremF) = (*cabecaF) ; (*tremF) != NULL; (*tremF) = (*tremF)->proximo) {
        funcionarios[i++] = *(*tremF);
    }

    //for (i = 0; i < quant; i++)
        //quantColocar += fread(&(funcionarios[i]), sizeof(tFuncionario), 1, funcionariosArq);
    
    /*printf("\n3");

    printf(" A quantidade lida foi de %d blocos", quantColocar);

    printf("\n\n Este é o arquivo inicial dos funcionários: \n\n");
    printf("\n\n Teste: vetor[2].linha: %u", funcionarios[2].linha);
    printf("\n\n Teste: vetor[2].nivll: %u", funcionarios[2].nivelSalarial);
    printf("\n\n Teste: vetor[2].departamento: %d", funcionarios[2].departamento);
    printf("\n\n Teste: vetor[2].proximo: %d", funcionarios[2].proximo);*/



    mostrarFuncionarios(funcionarios, quant);

    printf("\nQual é o Funcionário que você deseja excluir? Digite o código do funcionário: ");
    scanf(" %d", &codFuncio);

    retira(&(*cabecaF), codFuncio);
    quantColocar--;
    
    tFuncionario funcionariosAtualizados[quantColocar];

    i = 0;

    for ((*tremF) = (*cabecaF) ; (*tremF) != NULL; (*tremF) = (*tremF)->proximo)
        funcionariosAtualizados[i++] = *(*tremF);
    
    departamentoArqTexto_b = fopen("departamentos_b.txt", "rb+");

    fseek(departamentoArqTexto_b, 0, SEEK_END);
    quantDepart = ftell(departamentoArqTexto_b)/sizeof(tDepartamento);
    rewind(departamentoArqTexto_b);

    tDepartamento departamentos[quantDepart];

    for (i = 0; i < quantDepart; i++)
        fread(&(departamentos[i]), sizeof(tDepartamento), 1, departamentoArqTexto_b);

    fechamento = fclose(departamentoArqTexto_b);

    atualizarPonteiros(funcionariosAtualizados, departamentos, quantColocar);

    voltarPonteiros(funcionarios, funcionariosAtualizados, quant);

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

    printf("\n\nA operação foi de excluir funcionários demitidos no sistema!");

    printf("\n\nEsta é a tabela atualizada de departamentos: \n\n");

    mostrarDepartamentos(departamentos, quantDepart);

    printf("\n\n Este é o arquivo final dos funcionários: \n");
    mostrarFuncionarios(funcionariosAtualizados, quantColocar);



    

}