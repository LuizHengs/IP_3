#include "mudanca_departamento.h"

void mudarDepartamento(tFuncionario **cabecaF, tFuncionario **tremF ){

    //encherCabeca(&(*cabecaF), &(*tremF));

    //Fazer array Funcionarios lendo cada struct da lista encadeada que come�a j� com *cabe�aF;

    //atualizarPonteiros();

    //mostrarFuncionarios(funcionarios);

    encherCabeca(&(*cabecaF), &(*tremF));

    printf("\nCabe�aF departamento? %d", (*cabecaF)->departamento);
    printf("\nTremF departamento? %d", (*tremF)->departamento);

    int codFuncio, departamento, *novoDepartamento;
    printf("\tQual numero do funcionario? ");
    scanf("%d", &codFuncio);

    for((*tremF) = *cabecaF; (*tremF)!= NULL; *tremF = (*tremF)->proximo)
        if((*tremF)->codFuncio == codFuncio)
            break;
    departamento = (*tremF)->departamento;
    printf("\n\tO Funcionario escolhido se encontra no departamento %d.\n\tVoce deseja move-lo para qual departamento? ", departamento);
    scanf("%d", &novoDepartamento);

    (*tremF)->departamento = novoDepartamento;

    printf("TremF � %d", (*tremF)->departamento);

    if(novoDepartamento == departamento)
        printf("\n\tEle ja se encontra nesse departamento!");
    else
        printf("\n\tMudanca efetuada!");


    //atualizarPonteiros();

    //mostrarFuncionarios(funcionarios);
}




