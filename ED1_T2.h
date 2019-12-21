#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Declarando Estruturas
typedef struct nodeDisciplina{
    char *nome, *mencao;
    struct nodeDisciplina *next;
}nodeDisciplina;

typedef struct listDisciplina{
    int size;
    nodeDisciplina *head;
}listDisciplina;

typedef struct nodeAluno{
    char *nome, *email;
    long int matricula;
    listDisciplina *head;
    struct nodeAluno *next;
}nodeAluno;

typedef struct listAluno{
    int size;
    nodeAluno *head;
}listAluno;

//Fun��es que criam as estruturas de n� e de lista
listDisciplina *criaListaDisc(){
    listDisciplina *list = (listDisciplina*)malloc(sizeof(listDisciplina));
    list->head = NULL;
    list->size = 0;
    return list;
}
listAluno *criaListaAluno(){
    listAluno *list = (listAluno*)malloc(sizeof(listAluno));
    list->head = NULL;
    list->size = 0;
    return list;
}
nodeAluno *criaNodeAluno(){
    nodeAluno *node = (nodeAluno*)malloc(sizeof(nodeAluno));
    node->nome = (char*)malloc(sizeof(char) * 50);
    node->email = (char*)malloc(sizeof(char) * 50);
    node->head = criaListaDisc();

    getchar();
    printf("Nome: ");
    scanf("%[^\n]", node->nome);
    getchar();
    printf("Email: ");
    scanf("%[^\n]", node->email);
    printf("Matricula: ");
    scanf("%ld", &node->matricula);

    char continuar;
    printf("\nAluno Cadastrado!\n");
    printf("Aperte ENTER para continuar.\n");
    getchar();
    scanf("%c", &continuar);
    system("clear");

    return node;
}
nodeDisciplina *criaNodeDisc(){
    nodeDisciplina *node = (nodeDisciplina*)malloc(sizeof(nodeDisciplina));
    node->nome = (char*)malloc(sizeof(char)*50);
    node->mencao = (char*)malloc(sizeof(char)*50);

    getchar();
    printf("\nNome da Disciplina: ");
    scanf("%[^\n]", node->nome);
    //Entrando num do-while para n�o permitir o cadastro de disciplinas com men��o invalida
    do{
        printf("Mencao Obtida: ");
        scanf("%s", node->mencao);

        if(strcmp(node->mencao,"SR")!=0&&strcmp(node->mencao,"TR")!=0&&strcmp(node->mencao,"II")!=0&&strcmp(node->mencao,"MI")!=0&&strcmp(node->mencao,"MM")!=0&&strcmp(node->mencao,"MS")!=0&&strcmp(node->mencao,"SS")!=0){
            printf("Mencao Invalida, Tente Novamente!\n");
        }

    }while(strcmp(node->mencao,"SR")!=0&&strcmp(node->mencao,"TR")!=0&&strcmp(node->mencao,"II")!=0&&strcmp(node->mencao,"MI")!=0&&strcmp(node->mencao,"MM")!=0&&strcmp(node->mencao,"MS")!=0&&strcmp(node->mencao,"SS")!=0);

    node->next = NULL;

    printf("\nDisciplina registrada! Aperte ENTER para continuar.\n");
    char continuar;
    getchar();
    scanf("%c", &continuar);
    system("clear");

    return node;
}

//Fun�oes de Push
void pushAluno(listAluno *list, nodeAluno *node){
    if(node){
        node->next = list->head;
        list->head = node;
        list->size++;
    }
}
void pushDisc(listDisciplina *list, nodeDisciplina *node){
    if(node){
        node->next = list->head;
        list->head = node;
        list->size++;
    }
}

//Fun�oes isEmty - retornam verdadeiro caso as listas estejam vazias
bool isEmptyAluno(listAluno *list){
    return (list->size == 0);
}
bool isEmptyDisc(listDisciplina *list){
    return (list->size == 0);
}

//Fun��es que printam as listas
void printaListaAlunos(listAluno *list){
    system("clear");
    if(isEmptyAluno(list)){
        printf("Sem alunos registrados.\n");
        return;
    }

    nodeAluno *aux = list->head;

    while(aux){
        printf("Nome: %s\nEmail: %s\nMatricula: %ld\n", aux->nome, aux->email, aux->matricula);
        if(aux->head->size == 0){
            printf("Aluno Sem Disciplinas.\n\n");
        }else{
            printf("Historico: %d disciplina(s).\n\n", aux->head->size);
        }
        aux = aux->next;
    }
}
void printaListaDisc(listDisciplina *list){
    system("clear");
    if(isEmptyDisc(list)){
        printf("\nAluno sem Disciplinas.\n");
        return;
    }

    nodeDisciplina *aux = list->head;

    while(aux){
        printf("Nome: %s\nMencao: %s\n\n", aux->nome, aux->mencao);
        aux = aux->next;
    }
}

//Fun��es pop - removem primeiro integrante das listas
void popAluno(listAluno *list){
    system("clear");
    if(list->size == 0){
        printf("Lista sem elementos para remover.");
        return;
    }

    nodeAluno *aux = list->head;
    list->head = aux->next; //Transforma segundo integrante em head da lista
    free(aux); //Limpa o espa�o de memoria referente ao head antigo
    list->size--;
}
void popDisciplina(listDisciplina *list){
    system("clear");
    if(list->size == 0){
        printf("Lista sem elementos para remover.");
        return;
    }

    nodeDisciplina *aux = list->head;
    list->head = aux->next; //Transforma segundo integrante em head da lista
    free(aux); //Limpa o espa�o de memoria referente ao head antigo
    list->size--;
}

//Fun��es atPos - retornam n� encontrado em indice especifico recebido do usuario
nodeAluno *alunoAtPos(listAluno *list, int index){
    if(isEmptyAluno(list)){
        printf("\nSem Alunos Cadastrados!\n");
        return NULL;
    }
    if(index > list->size || index < 0){
        printf("\nIndice Invalido!\n");
        return NULL;
    }
    int i = 0;
    nodeAluno *aux = list->head;

    while(aux){
        if(i == index){ //Compara o indice recebido ao numero da volta atual do while
            break;
        }
        i++;
        aux = aux->next;
    }

    return aux;
}

//Fun�oes de Busca - Retornam n� com atributo desejado
nodeAluno *buscaNomeAluno(listAluno *list, char *nome){
    if(isEmptyAluno(list)){ //Verificando se existem alunos cadastrados antes de iniciar pesquisa
        printf("\nSem Alunos Registrados\n");
        return NULL;
    }

    nodeAluno *aux = list->head;
    char *busca;
    int contador = 0, i = 0, op;

    while(aux){
        busca = strstr(aux->nome, nome); //compara nome recebido com nome do n� atual
        if(busca == NULL){ //retorno � null se n�o for encontrado n� com parte do nome igual ao nome pesquisado
        }else{
            contador++; //variavel responsavel por receber quantos alunos possuem parte do nome igual a pesquisa
        }
        aux = aux->next;
    }

    if(contador == 0){ // contador = 0 signfica 0 alunos com parte do nome igual a pesquisa
        printf("Aluno nao encontrado.\n");
        return NULL;
    }

     //Lista de alunos que ir� receber todos os alunos que possuem o nome pesquisado em pelo menos parte de seu nome
    nodeAluno **nomesRepetidos = (nodeAluno**)malloc(sizeof(nodeAluno*)*contador);
    aux = list->head;

    while(aux){
        busca = strstr(aux->nome, nome);
        if(busca == NULL){
        }else{
            nomesRepetidos[i] = aux;
            i++;
        }
        aux = aux->next;
    }

    i = 0;

    if(contador > 0){
        printf("Alunos Encontrados:\n");
        for(i = 0; i < contador; i++){
            printf("\nAluno %d\n", (i+1));
            printf("    Nome: %s\n", nomesRepetidos[i]->nome);
            printf("    Email: %s\n", nomesRepetidos[i]->email);
            printf("    Matricula: %ld\n", nomesRepetidos[i]->matricula);
        }

        printf("\nNumero do Aluno Escolhido:\n");
        scanf("%d", &op);
        return nomesRepetidos[op-1];
    }

    return NULL;
}
nodeAluno *buscaEmail(listAluno *list, char *email){
    if(isEmptyAluno(list)){ //Verificando se existem alunos cadastrados antes de iniciar pesquisa
        printf("\nSem Alunos Registrados\n");
        return NULL;
    }

    nodeAluno *aux = list->head;
    char *busca;
    int contador = 0, i = 0, op;

    while(aux){
        busca = strstr(aux->email, email);//compara nome recebido com email do n� atual
        if(busca == NULL){ //retorno � null se n�o for encontrado n� com parte do nome igual ao nome pesquisado
        }else{
            contador++;//variavel responsavel por receber quantos alunos possuem parte do nome igual a pesquisa
        }
        aux = aux->next;
    }

    if(contador == 0){// contador = 0 signfica 0 alunos com parte do nome igual a pesquisa
        printf("Aluno nao encontrado.\n");
        return NULL;
    }

    //Lista de alunos que ir� receber todos os alunos que possuem o nome pesquisado em pelo menos parte de seu email
    nodeAluno **nomesRepetidos = (nodeAluno**)malloc(sizeof(nodeAluno*)*contador);
    aux = list->head;

    while(aux){
        busca = strstr(aux->email, email);
        if(busca == NULL){
        }else{
            nomesRepetidos[i] = aux;
            i++;
        }
        aux = aux->next;
    }

    i = 0;

    if(contador > 0){
        printf("Alunos Encontrados:\n");
        for(i = 0; i < contador; i++){
            printf("\nAluno %d:\n", (i+1));
            printf("Nome: %s\n", nomesRepetidos[i]->nome);
            printf("Email: %s\n", nomesRepetidos[i]->email);
            printf("Matricula: %ld\n", nomesRepetidos[i]->matricula);
        }

        printf("\nNumero do Aluno Escolhido:\n");
        scanf("%d", &op);
        return nomesRepetidos[op-1];
    }

    return NULL;
}
nodeDisciplina *buscaDisciplina(listDisciplina *list, char *pesquisa){
    if(isEmptyDisc(list)){ //Verificando se aluno tem disciplinas antes de iniciar pesquisa
        printf("\nAluno sem Disciplinas!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        char continuar;
        scanf("%c", &continuar);
        system("clear");
        return NULL;
    }


    nodeDisciplina *aux = list->head;
    char *busca;
    int contador = 0, i = 0, op;

    while(aux){
        busca = strstr(aux->nome, pesquisa); //Compara nome pesquisado com nome da disciplina atual
        if(busca == NULL){//retorno � null se n�o for encontrado n� com parte do nome igual ao nome pesquisado
        }else{
            contador++; //Recebe quantas disciplinas possuem nome pesquisado em parte do seu nome
        }
        aux = aux->next;
    }

    if(contador == 0){ //contador = 0 significa que nenhuma disciplina possui nome pesquisado
        printf("Aluno nao encontrado.\n");
        return NULL;
    }

    //Lista de disciplinas que ira receber todas aquelas em que palavra pesquisada aparece em parte de seu nome
    nodeDisciplina **nomesRepetidos = (nodeDisciplina**)malloc(sizeof(nodeDisciplina*)*contador);
    aux = list->head;

    while(aux){
        busca = strstr(aux->nome, pesquisa);
        if(busca == NULL){
        }else{
            nomesRepetidos[i] = aux;
            i++;
        }
        aux = aux->next;
    }

    i = 0;

    if(contador > 0){
        printf("Disciplinas Encontradas:\n");
        for(i = 0; i < contador; i++){
            printf("\nDisciplina %d:\n", (i+1));
            printf("Nome: %s\n", nomesRepetidos[i]->nome);
            printf("Mencao: %s\n", nomesRepetidos[i]->mencao);
        }

        printf("\nNumero da Disciplina Escolhida:\n");
        scanf("%d", &op);
        return nomesRepetidos[op-1];
    }
    return NULL;
}

//Fun��es Edit - Editam todos os atributos de n� especifico
void editDisciplina(nodeDisciplina *busca){
    if(busca){
    system("clear");
    printf("Novo Nome: ");
    getchar();
    scanf("%[^\n]", busca->nome);
    //Inicia do-while que nao permite registro de men��es invalidas
    do{
        printf("Nova Mencao: ");
        scanf("%s", busca->mencao);

        if(strcmp(busca->mencao,"SR")!=0&&strcmp(busca->mencao,"TR")!=0&&strcmp(busca->mencao,"II")!=0&&strcmp(busca->mencao,"MI")!=0&&strcmp(busca->mencao,"MM")!=0&&strcmp(busca->mencao,"MS")!=0&&strcmp(busca->mencao,"SS")!=0){
            printf("Mencao Invalida, Tente Novamente!\n");
        }

    }while(strcmp(busca->mencao,"SR")!=0&&strcmp(busca->mencao,"TR")!=0&&strcmp(busca->mencao,"II")!=0&&strcmp(busca->mencao,"MI")!=0&&strcmp(busca->mencao,"MM")!=0&&strcmp(busca->mencao,"MS")!=0&&strcmp(busca->mencao,"SS")!=0);
    }
}
void editAluno(nodeAluno *node){
    if(node){
    system("clear");
    printf("Novo Nome: ");
    getchar();
    scanf("%[^\n]", node->nome);
    printf("Novo Email: ");
    getchar();
    scanf("%[^\n]", node->email);
    printf("Nova Matricula: ");
    scanf("%ld", &node->matricula);
    printf("\nAluno Editado!\n");
    }
}

//Fun��o indexOf - Retorna indice de n� na lista
int indexOfAluno(listAluno *list, nodeAluno *node){
    if(isEmptyAluno(list)){ //verificando se a lista esta vazia antes do processo
        char continuar;
        printf("Lista Sem Alunos!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        scanf("%c", &continuar);
        system("clear");
        return -1; //retorno negativo significar� n� nao encontrado
    }

    int index = -1;

    if(node){ //verificando se o n� � valido
        nodeAluno *aux = list->head;
        int i = 0;

        while(aux){
            if(aux->matricula == node->matricula){
                index = i;
                break;
            }
            i++;
            aux = aux->next;
        }
    }

    return index;
}
int indexOfDisciplina(listDisciplina *list, nodeDisciplina *node){
    if(isEmptyDisc(list)){
        char continuar;
        printf("Aluno Sem Disciplinas!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        scanf("%c", &continuar);
        system("clear");
        return -1;
    }

    int index = -1;

    if(node){
        nodeDisciplina *aux = list->head;
        int i = 0;

        while(aux){
            if(aux == node){
                index = i;
                break;
            }
            i++;
            aux = aux->next;
        }
    }

    return index;
}

//Fun��es Erase - removem n� especifico de listas
void eraseAluno(listAluno *list, nodeAluno *node){
    if(isEmptyAluno(list)){ //Verificando primeiramente se j� existem alunos cadastrados
        char continuar;
        printf("Lista Sem Alunos!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        scanf("%c", &continuar);
        system("clear");
        return;
    }
    if(node){

        nodeAluno *aux=list->head, *aux2;
        int contador = indexOfAluno(list, node), i = 0;

        if(contador == 0){
            popAluno(list);
            return;
        }

        if(contador >= 0){
            while(aux){
                if(i == (contador - 1)){
                    aux2 = aux->next;
                    aux->next = aux2->next;
                }
                i++;
                aux = aux->next;
            }
        }
        printf("Aluno Removido!\n");
        free(aux);
    }
}
void eraseDisciplina(listDisciplina *list, nodeDisciplina *node){
    if(isEmptyDisc(list)){ //verificando primeiramente se o aluno ja tem disciplinas cadastradas
        char continuar;
        printf("Aluno sem Disciplinas!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        scanf("%c", &continuar);
        system("clear");
        return;
    }

    if(node){

        nodeDisciplina *aux=list->head, *aux2;
        int contador = indexOfDisciplina(list, node), i = 0;

        if(contador == 0){
            popDisciplina(list);
            printf("Disciplina Removida!\n");
            return;
        }

        if(contador >= 0){
            while(aux){
                if(i == (contador - 1)){
                    aux2 = aux->next;
                    aux->next = aux2->next;
                }
                i++;
                aux = aux->next;
            }
        }
        printf("Disciplina Removida!\n");
        free(aux);
    }
}

//Fun��o Filtra Disciplina - Mostra todas as disciplinas que receberam men��o informada
void *filtraDisciplina(listDisciplina *list, char *pesquisa){
    if(isEmptyDisc(list)){ //Verificando primeiramente se o aluno tem disciplinas cadastradas
        printf("\nAluno sem Disciplinas!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        char continuar;
        scanf("%c", &continuar);
        system("clear");
        return NULL;
    }


    nodeDisciplina *aux = list->head;
    char *busca;
    int contador = 0, i = 0;

    while(aux){
        busca = strstr(aux->mencao, pesquisa);
        if(busca == NULL){
        }else{
            contador++; //contando todas as disciplinas que receberam a men��o pesquisada
        }
        aux = aux->next;
    }

    if(contador == 0){
        printf("Sem disciplinas com a referida mencao.\n");
        return NULL;
    }

    nodeDisciplina **nomesRepetidos = (nodeDisciplina**)malloc(sizeof(nodeDisciplina*)*contador);
    aux = list->head;

    while(aux){
        busca = strstr(aux->mencao, pesquisa);
        if(busca == NULL){
        }else{
            nomesRepetidos[i] = aux;
            i++;
        }
        aux = aux->next;
    }

    i = 0;

    if(contador > 0){
        system("clear");
        printf("Disciplinas Encontradas!\n");
        printf("Disciplinas com Mencao %s Obtida:\n", pesquisa);

        for(i = 0; i < contador; i++){
            printf("Nome: %s\n", nomesRepetidos[i]->nome);
        }
    }
    return NULL;
}

//Fun��o relatorioGeral - mostra relatorio do aluno como pedido (numero de disciplinas cursadas, de reprova�oes, aprova��es e trancamentos
void relatorioGeral(listDisciplina *list){
    if(isEmptyDisc(list)){ //Verificando se o aluno j� tem disciplinas cadastradas
        printf("Aluno sem Disciplinas Cursadas!\n");
        printf("Aperte ENTER para continuar.\n");
        getchar();
        char continuar;
        scanf("%c", &continuar);
        system("clear");
        return;
    }

    int aprovacoes = 0, reprovacoes = 0, trancamentos = 0; //contadores pra cada tipo de men��o

    nodeDisciplina *aux = list->head;

    while(aux){
        if(strcmp(aux->mencao, "SS") == 0){
            aprovacoes++;
        }else if(strcmp(aux->mencao, "MS") == 0){
            aprovacoes++;
        }else if(strcmp(aux->mencao, "MM") == 0){
            aprovacoes++;
        }else if(strcmp(aux->mencao, "MI") == 0){
            reprovacoes++;
        }else if(strcmp(aux->mencao, "II") == 0){
            reprovacoes++;
        }else if(strcmp(aux->mencao, "TR") == 0){
            trancamentos++;
        }else if(strcmp(aux->mencao, "SR") == 0){
            reprovacoes++;
        }
        aux = aux->next;
    }

    printf("Numero de Disciplinas Cursadas: %d\n", list->size);
    printf("Numero de Aprovacoes: %d\n", aprovacoes);
    printf("Numero de Reprovacoes: %d\n", reprovacoes);
    printf("Numero de Trancamentos: %d\n\n", trancamentos);

    printf("Aperte ENTER para continuar.\n");
    getchar();
    char continuar;
    scanf("%c", &continuar);
    system("clear");
}

//Limpa memoria
void freeDisciplinas(listDisciplina *list){
    //lista vazia nao precisa de free
    if(isEmptyDisc(list)){
        return;
    }
    //lista com size 1 so precisamos remover o head
    if(list->size == 1){
        nodeDisciplina *aux = list->head;
        free(aux);
        return;
    }
    nodeDisciplina *aux = list->head;
    nodeDisciplina *aux2 = aux->next;
    while(aux2){
        list->head = aux2;
        free(aux);
        aux = aux2;
        aux2 = aux2->next;
    }
}
void freeLista(listAluno *list){
    //lista vazia nao precisa de free
    if(isEmptyAluno(list)){
        return;
    }
    //Se a lista tiver apenas um n� so precisamos dar free no head
    if(list->size == 1){
        nodeAluno *aux = list->head;
        freeDisciplinas(aux->head);
        free(aux);
        return;
    }

    nodeAluno *aux = list->head;
    nodeAluno *aux2 = aux->next;
    while(aux2){
        list->head = aux2;
        freeDisciplinas(aux->head);
        free(aux);
        aux = aux2;
        aux2 = aux2->next;
    }
    /* Professor, ap�s colocar um contador dentro do while para verificar quantas voltas
    a estrutura de repeti��o faz, percebi que sempre faltava uma volta, ou seja por algum motivo
    o ultimo n� da lista n�o � excluido (n�o importa o tamanho da lista), por�m esse foi o melhor
    que consegui fazer, se puder me explicar onde est� meu erro depois, agrade�o.*/
}
