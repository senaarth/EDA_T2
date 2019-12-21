//Arthur Sena
//180030345

#include <stdio.h>
#include <stdlib.h>
#include "ED1_T2.h" //Biblioteca com as fun��es referentes as listas.

//Declara��o das Fun��es de Menu
void menuAluno(nodeAluno *node);
void menu(listAluno *list);

int main(){
    listAluno *listAluno = criaListaAluno();
    menu(listAluno);
    freeLista(listAluno); //Libera Espa�o de memoria referente a lista de alunos e da lista de disciplinas de cada um deles no final do uso
    return 0;
}

//Implementa��o das fun��es de menu.
void menuAluno(nodeAluno *node){
    char continuar, *pesquisa;
    pesquisa = (char*)malloc(sizeof(char)*50);
    printf("Aperte ENTER para continuar.\n");
    getchar();
    scanf("%c", &continuar);
    system("clear");

    int run = 1, op;

    //Estrutura de repeti��o respons�vel por rodar o menu.
    do{
        printf("Menu do Aluno: %s", node->nome);
        printf("\n1. Cadastrar Disciplina");
        printf("\n2. Listar Disciplinas do Aluno");
        printf("\n3. Editar Disciplina do Aluno");
        printf("\n4. Excluir Disciplina do Aluno");
        printf("\n5. Filtrar Disciplinas por Mencao");
        printf("\n6. Apresentar Relatorio Geral do Aluno");
        printf("\n0. Retornar ao Menu Principal");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op){
        //CADASTRO-------------------------------------------------------------------------------------------------------
        case 1:
            system("clear");
            nodeDisciplina *disciplina = criaNodeDisc(); //Chama fun��o que cria nova disciplina
            pushDisc(node->head, disciplina); // Insere n� na lista
        break;
        //LISTAGEM DE DISCIPLINAS-----------------------------------------------------------------------------------------
        case 2:
            printaListaDisc(node->head); // Chama fun��o que printa lista de disciplinas
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        //EDITAR DISCIPLINA-----------------------------------------------------------------------------------------
        case 3:

            system("clear");
            printf("Nome da Disciplina: ");
            getchar();
            scanf("%[^\n]", pesquisa);
            nodeDisciplina *busca = buscaDisciplina(node->head, pesquisa); //declarando variavel respons�vel por receber n� com nome pesquisado
            if(busca == NULL){
                printf("Disciplina nao encontrada.\n");
            }else{
                editDisciplina(busca);
            }
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        //APAGAR DISCIPLINA-----------------------------------------------------------------------------------------------------
        case 4:
            system("clear");
            printf("Nome da Disciplina: ");
            getchar();
            scanf("%[^\n]", pesquisa);
            nodeDisciplina *aux = buscaDisciplina(node->head, pesquisa); //Declarando variavel respons�vel por receber n� com nome pesquisado
            eraseDisciplina(node->head, aux);
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        //FILTRAR POR MENCAO----------------------------------------------------------------------------------------------
        case 5:
            system("clear");

             do{
                printf("Digite a mencao que deseja pesquisar: ");
                getchar();
                scanf("%[^\n]", pesquisa); //A fun��o de filtro ir� printar apenas as mat�rias cujas quais o aluno obteve esta men��o


                if(strcmp(pesquisa,"SR")!=0&&strcmp(pesquisa,"TR")!=0&&strcmp(pesquisa,"II")!=0&&strcmp(pesquisa,"MI")!=0&&strcmp(pesquisa,"MM")!=0&&strcmp(pesquisa,"MS")!=0&&strcmp(pesquisa,"SS")!=0){
                    printf("Mencao Invalida, Tente Novamente!\n");
                }

            }while(strcmp(pesquisa,"SR")!=0&&strcmp(pesquisa,"TR")!=0&&strcmp(pesquisa,"II")!=0&&strcmp(pesquisa,"MI")!=0&&strcmp(pesquisa,"MM")!=0&&strcmp(pesquisa,"MS")!=0&&strcmp(pesquisa,"SS")!=0);

            filtraDisciplina(node->head, pesquisa); //Chamando fun��o responsavel pelo filtro
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        //RELATORIO GERAL---------------------------------------------------------------------------------------------
        case 6:
            system("clear");
            relatorioGeral(node->head); //chama fun��o de relatorio geral
        break;
        //RETORNA AO MENU PRINCIPAL------------------------------------------------------------------------------------
        case 0:
        run = 0;
        break;
        //CASO DEFAULT-------------------------------------------------------------------------------------------------
        default:
            system("clear");
            printf("Opcao Invalida. Tente Novamente.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        }

    }while(run);
}

void menu(listAluno *list){

    nodeAluno *node;
    int run = 1; //Variavel que mantem o menu rodando.
    int pos, op;
    char *pesquisa, continuar;
    pesquisa = (char*)malloc(sizeof(char)*50);

    //Estrutura de repeti��o respons�vel por rodar o menu.
    do{

        printf("Menu - Gerenciamento de Alunos");
        printf("\n1. Cadastrar Aluno");
        printf("\n2. Listar Alunos");
        printf("\n3. Visualizar Aluno");
        printf("\n4. Editar Aluno");
        printf("\n5. Excluir Aluno");
        printf("\n0. Encerrar");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op){
        //CADASTRO----------------------------------------------------------------------------------------------
        case 1:
            system("clear");
            node = criaNodeAluno(); //Chama fun��o de cria��o de n� para aluno novo.
            pushAluno(list, node);  //Insere novo aluno na lista.
        break;
        //lISTAGEM----------------------------------------------------------------------------------------------
        case 2:
            printaListaAlunos(list); //Chama a fun��o que printa a lista de alunos j� cadastrados.
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        //VISUALIZA��O DE ALUNO----------------------------------------------------------------------------------------------
        case 3:
            if(isEmptyAluno(list)){ //Verificando se j� existem alunos cadastrados antes de iniciar busca.
                system("clear");
                printf("Sem Alunos Registrados!\n");
                printf("Aperte ENTER para continuar.\n");
                getchar();
                scanf("%c", &continuar);
                system("clear");
            }else{
                do{
                    system("clear");
                    printf("Buscar aluno por:\n");
                    printf("1. Nome\n");
                    printf("2. Email\n");
                    printf("3. Indice\n");
                    printf("Opcao: ");
                    scanf("%d", &op);

                    if(op != 1 && op != 2 && op != 3){
                        printf("Opcao invalida! Tente novamente.\n");
                        printf("Aperte ENTER para continuar.\n");
                        getchar();
                        scanf("%c", &continuar);
                        system("clear");
                    }else{
                        break;
                    }

                }while(op != 1 || op != 2 || op != 3);

                switch(op){
                case 1:
                    system("clear");
                    printf("Nome: ");
                    getchar();
                    scanf("%[^\n]", pesquisa);
                    node = buscaNomeAluno(list, pesquisa); //Declarando variavel respons�vel por receber n� com nome pesquisado
                    if(node == NULL){
                    }else{
                        menuAluno(node);
                    }
                break;
                case 2:
                    system("clear");
                    printf("Email: ");
                    getchar();
                    scanf("%[^\n]", pesquisa);
                    node = buscaEmail(list, pesquisa); //Declarando variavel respons�vel por receber n� com email pesquisado
                    if(node == NULL){
                    }else{
                        menuAluno(node);
                    }
                break;
                case 3:
                    system("clear");
                    printf("Lembre-se, o indice comeca a ser contado do 0.\n");
                    printf("Indice: ");
                    scanf("%d", &pos);
                    node = alunoAtPos(list, pos); //Declarando variavel respons�vel por receber n� com indice pesquisado
                    if(node == NULL){
                    }else{
                        menuAluno(node);
                    }
                break;
                }
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
            }
        break;
        //EDI��O DE ALUNO----------------------------------------------------------------------------------------------
        case 4:
        if(isEmptyAluno(list)){ //Verificando se j� existem alunos cadastrados antes de iniciar busca.
                system("clear");
                printf("Sem Alunos Registrados!\n");
                printf("Aperte ENTER para continuar.\n");
                getchar();
                scanf("%c", &continuar);
                system("clear");
        }else{
            do{
                system("clear");
                printf("Buscar aluno por:\n");
                printf("1. Nome\n");
                printf("2. Email\n");
                printf("3. Indice\n");
                printf("Opcao: ");
                scanf("%d", &op);

                if(op != 1 && op != 2 && op != 3){
                    printf("Opcao invalida! Tente novamente.\n");
                    printf("Aperte ENTER para continuar.\n");
                    getchar();
                    scanf("%c", &continuar);
                    system("clear");
                }else{
                    break;
                }

            }while(op != 1 || op != 2 || op != 3);

            switch(op){
            case 1:
                system("clear");
                printf("Nome: ");
                getchar();
                scanf("%[^\n]", pesquisa);
                node = buscaNomeAluno(list, pesquisa); //Declarando variavel respons�vel por receber n� com nome pesquisado
                if(node == NULL){
                }else{
                   editAluno(node);
                }
            break;
            case 2:
                system("clear");
                printf("Email: ");
                getchar();
                scanf("%[^\n]", pesquisa);
                node = buscaEmail(list, pesquisa); //Declarando variavel respons�vel por receber n� com email pesquisado
                if(node == NULL){
                }else{
                   editAluno(node);
                }
            break;
            case 3:
                system("clear");
                printf("Lembre-se, o indice comeca a ser contado do 0.\n");
                printf("Indice: ");
                getchar();
                scanf("%d", &pos);
                node = alunoAtPos(list, pos); //Declarando variavel respons�vel por receber n� com indice pesquisado
                if(node == NULL){
                    printf("\nAluno nao encontrado.\n");
                }else{
                   editAluno(node);
                }
            break;
            }
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        }
        break;
        //EXCLUS�O DE ALUNO----------------------------------------------------------------------------------------------
        case 5:
        if(isEmptyAluno(list)){ //Verificando se j� existem alunos cadastrados antes de iniciar busca.
            system("clear");
            printf("Sem Alunos Registrados!\n");
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        }else{
            do{
                system("clear");
                printf("Buscar aluno por:\n");
                printf("1. Nome\n");
                printf("2. Email\n");
                printf("3. Indice\n");
                printf("Opcao: ");
                scanf("%d", &op);

                if(op != 1 && op != 2 && op != 3){
                    printf("Opcao invalida! Tente novamente.\n");
                    printf("Aperte ENTER para continuar.\n");
                    getchar();
                    scanf("%c", &continuar);
                    system("clear");
                }else{
                    break;
                }

            }while(op != 1 || op != 2 || op != 3);

            switch(op){
            case 1:
                system("clear");
                printf("Nome: ");
                getchar();
                scanf("%[^\n]", pesquisa);
                node = buscaNomeAluno(list, pesquisa); //Declarando variavel respons�vel por receber n� com nome pesquisado
                if(node == NULL){
                }else{
                   eraseAluno(list, node);
                }
            break;
            case 2:
                system("clear");
                printf("Email: ");
                getchar();
                scanf("%[^\n]", pesquisa);
                node = buscaEmail(list, pesquisa); //Declarando variavel respons�vel por receber n� com email pesquisado
                if(node == NULL){
                }else{
                   eraseAluno(list, node);
                }
            break;
            case 3:
                system("clear");
                printf("Lembre-se, o indice comeca a ser contado do 0.\n");
                printf("Indice: ");
                getchar();
                scanf("%d", &pos);
                node = alunoAtPos(list, pos); //Declarando variavel respons�vel por receber n� com indice pesquisado
                char *nome = (char*)malloc(sizeof(char)*50);
                nome = node->nome; //Variavel que recebe nome do aluno a ser deletado para futuramente infomar qual aluno foi removido.
                if(node == NULL){
                    printf("\nAluno nao encontrado.\n"); //o retorno null significa que o n� nao foi encontrado
                }else{
                   eraseAluno(list, node);//Chamando fun��o de deletar
                   printf("Aluno %s removido.\n", nome);
                   //Senti a necessidade de utilizar essa variavel pois nesta parte do programa o nome do n� j� foi apagado
                   //e caso nao apresentasse o nome do aluno deletado o usuario nao saberia com certeza qual aluno foi removido.
                }
            break;
            }
            printf("Aperte ENTER para continuar.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        }
        break;
        //ENCERRA PROGRAMA----------------------------------------------------------------------------------------------
        case 0:
            system("clear");
            printf("Ok. Encerrando.\n");
            run = 0;
        break;
        //CASO DEFAULT----------------------------------------------------------------------------------------------
        default:
            system("clear");
            printf("Opcao Invalida. Tente Novamente.\n");
            getchar();
            scanf("%c", &continuar);
            system("clear");
        break;
        }

    }while(run);
}
