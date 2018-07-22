#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <dirent.h>
#include "midias.h"

// função menu com as opções disponiveis
int menu(){
    int opc;

    printf("\tXxXxXxXxXx - Biblioteca Digital - XxXxXxXxXxX\n\n");
    printf("Lista de Opções:\n");
    printf("[1] - Adicionar um diretório.\n");
    printf("[2] - Mostrar as midias indexadas.\n");
    printf("[3] - Pesquisar Midia.\n");
    printf("[4] - Limpar Lista.\n");
    printf("[5] - Sair.\n");
    fflush(stdin);
    printf("O que Deseja realizar?: "); scanf("%d",&opc);
    return opc;
}
// recebe a opção escolhida no menu e realiza a o camando especifico
void opcao(int opc, node **head){

    switch(opc){
        case 1 :
            system("cls");
            opendiretorio(head);
            break;
        case 2 :
            system("cls");
            mostrar(*head);
            break;
        case 3 :
            system("cls");
            pesquisar(head);
            break;
        case 4 :
            system("cls");
            limpar(head);
            break;
        case 5 :
            system("cls");
            printf("\nPrograma encerrado... Até mais!\n");
            exit(1);
            break;
        default :
            system("cls");
            printf("ERROR!!! Comando não reconhecido\n\n");
    }
}
// aloca os espaços da lista
node *aloca ( ){

    node *novo = (node*)malloc(sizeof(node));
    if (!novo){
        printf("alocacao indisponivel!\n");
        exit(1);
    }
    novo->ptr = (struct dirent*)malloc(sizeof(struct dirent));
    // aponta para null para ser o ultimo da lista
    novo->prox = NULL;

    return novo;
}
// abre o diretorio informado
void opendiretorio(node **head){
    setlocale(LC_ALL, "Portuguese");
    // recebe o diretorio informado pelo usuario
    char dir_informado[100];
    //para testar a repetição
    char teste[200];
    FILE *file;
    DIR *diretorio;
    struct dirent *ptr = NULL;

    printf("Informe o diretório das midias:\n\n");
    fflush(stdin);
    gets(dir_informado);

     // aqui a abre o diretorio
    diretorio = opendir(dir_informado);
    // abre o aquivo que contem os diretorios salvos
    file = fopen("resgate.txt","a");
    // testa se foi um caminho de diretorio valido
    if (!diretorio){
        printf("\n\nDiretorio nn foi aberto...ops!\n");
        system("pause");
    }else{
        printf("\n\tX-x-x Diretorio adicionado com sucesso x-x-X\n\n");
        fprintf(file,"%s\n",dir_informado);
        system("pause");
    }
    // enquanto nn encontrar o null no final do diretorio
    while ( ( ptr = readdir(diretorio) ) != NULL ){
            //formatos possiveis de midia(musicas e videos)
            if (strstr(ptr->d_name,".3gp") ||
                strstr(ptr->d_name,".mp3") ||
                strstr(ptr->d_name,".mp4") ||
                strstr(ptr->d_name,".avi") ||
                strstr(ptr->d_name,".wma") ||
                strstr(ptr->d_name,".mkv") ||
                strstr(ptr->d_name,".rmvb")||
                strstr(ptr->d_name,".asf") ||
                strstr(ptr->d_name,".m4v") ||
                strstr(ptr->d_name,".mov") ||
                strstr(ptr->d_name,".mpg") ||
                strstr(ptr->d_name,".mpeg")||
                strstr(ptr->d_name,".swf") ||
                strstr(ptr->d_name,".aiff")||
                strstr(ptr->d_name,".au")  ||
                strstr(ptr->d_name,".mid") ||
                strstr(ptr->d_name,".midi")||
                strstr(ptr->d_name,".m4a") ||
                strstr(ptr->d_name,".wav") ||
                // formatos de foto
                strstr(ptr->d_name,".jpeg")||
                strstr(ptr->d_name,".jpg") ||
                strstr(ptr->d_name,".gif") ||
                strstr(ptr->d_name,".png") ||
                strstr(ptr->d_name,".bitmap")||
                strstr(ptr->d_name,".tiff")||
                strstr(ptr->d_name,".raw") ||
                strstr(ptr->d_name,".svg"))

    //chama a função comparar , para ver se a midia ja esta na lista
    comparar(head,ptr, dir_informado);
    }
    //fecha o diretorio
    closedir(diretorio);
    //fecha o arquivo de memoria
    fclose(file);
}
// printa na tela as midias da lista
void mostrar(node *head){

    //verifica se os elementos do diretorio foi indexado na lista
    if (head==NULL){
    printf("Nenhum arquivo disponivel ! \n\n");
        return;
    }
    node *tmp;
    tmp = head;
    // equanto não chegar no final da lista
    while(tmp!=NULL){
        printf("%s\n",tmp->ptr->d_name);
        tmp= tmp->prox;
    }
    printf("\n\nX--- Um backup da lista foi realizado em um documento de texto ---X\n\n");
}

// adiciona as midias nn repetidas na lista
void adiciona(char *diretorio,node **head,struct dirent *ptr){
    // o conteudo da cabeça é passado para a temporaria
    node *tmp = *head;
    node *novo;
    //chama a função aloca para criar o novo
    novo = aloca();
    // copia o nome do arquivo para a struct dirent
    strcpy(novo->ptr->d_name,ptr->d_name);
    strcpy(novo->diretorio,diretorio);

    // cabeça estiver vazia o primeiro elemento vai pra ela
    if (*head == NULL){
        *head = novo;
    }else{
        while(tmp->prox!=NULL)
            tmp = tmp->prox;
        tmp->prox = novo;
    }
}

// compara se existe midias repetidas
void comparar (node **head, struct dirent *ptr, char *diretorio){
    if (*head == NULL){
        adiciona(diretorio,head,ptr);
        return;
    }
    int resultado;
    node *tmp = *head;
    while(tmp!= NULL){
        resultado = strcmp(tmp->ptr->d_name,ptr->d_name);
        tmp = tmp->prox;
        if (resultado == 0){
                //informa sobre a repetição da midia
            printf("\n'%s' já tinha sido adicionada anteriormente\n", ptr->d_name);
            break;
        }

    }
    if (resultado ==0)
        return;
    else
        //chama a função para adicionar as midias nn repetidas na lista
        adiciona(diretorio,head,ptr);

}

// pesquisa a midia informada pelo usuario na lista
void pesquisar(node **head){
    setlocale(LC_ALL, "Portuguese");
    if (*head ==NULL){
        printf("Não há arquivo de midia ate o momento!\n\n");
        return;
    }
    char midia[20];
    int cont = 0;
    node *tmp;
    tmp = *head;
    printf("Informe nome ou parte do nome da midia a ser buscada:\n");
    fflush(stdin);
    gets(midia);
    fflush(stdin);

    while (tmp!=NULL) {
        if (strstr(tmp->ptr->d_name,midia)){
                while (strstr(tmp->ptr->d_name,midia) && tmp != NULL){
                printf("'%s' foi encontrada na pesquisa\n\n",tmp->ptr->d_name);
                cont = 1;
                tmp = tmp ->prox;
                }
            break;
        }
        if (strcmp(tmp->ptr->d_name,midia)==0){
            printf("Midia '%s' encontrado em %s\n", tmp->ptr->d_name, tmp->diretorio);
            cont = 1;
            break;
        }

    tmp = tmp->prox;
   }
   if (cont == 0)
    printf("A midia não foi localizada\n\n");
}

//implementação da função que limpa a lista
void limpar(node **head){
    FILE *reset;
    // limpa o arquivo onde fica salvos os caminhos dos diretorios.
    reset =fopen("resgate.txt","w");
    node *tmp;
    tmp = *head;
    while (tmp != NULL){
        tmp = (*head)->prox;
        free(*head);
        *head = tmp;
    }
    //fecha o arquivo agora limpo
    fclose(reset);
}

// ler os ultimos diretorios salvos.
void retorno(node **head){
    setlocale(LC_ALL, "Portuguese");
    char list_dir[200];
    FILE *resgate;
    DIR *diretorio;
    struct dirent *ptr = NULL;
    //abre o arquivo responsavel pela memoria do programa no formato de leitura
    resgate = fopen("resgate.txt","r");

    while(fgets(list_dir, 200, resgate)!= NULL){
        //adiciona o caractere \0 no lugar do \n
        list_dir[strlen(list_dir)-1] = '\0';
     // aqui a abre o diretorio listado no arquivo de memmoria
    diretorio = opendir(list_dir);
    // testa se um caminho valido de diretorio
    if (!diretorio){
        printf("\n\nDiretorio nn foi aberto...ops!\n");
    }else{
    // enquanto nn encontrar o null no final do diretorio
        while ( ( ptr = readdir(diretorio) ) != NULL ){
            //formatos possiveis de midia(musicas e videos)
            if (strstr(ptr->d_name,".3gp") ||
                strstr(ptr->d_name,".mp3") ||
                strstr(ptr->d_name,".mp4") ||
                strstr(ptr->d_name,".avi") ||
                strstr(ptr->d_name,".wma") ||
                strstr(ptr->d_name,".mkv") ||
                strstr(ptr->d_name,".rmvb")||
                strstr(ptr->d_name,".asf") ||
                strstr(ptr->d_name,".m4v") ||
                strstr(ptr->d_name,".mov") ||
                strstr(ptr->d_name,".mpg") ||
                strstr(ptr->d_name,".mpeg")||
                strstr(ptr->d_name,".swf") ||
                strstr(ptr->d_name,".aiff")||
                strstr(ptr->d_name,".au")  ||
                strstr(ptr->d_name,".mid") ||
                strstr(ptr->d_name,".midi")||
                strstr(ptr->d_name,".m4a") ||
                strstr(ptr->d_name,".wav") ||
                // formatos de foto
                strstr(ptr->d_name,".jpeg")||
                strstr(ptr->d_name,".jpg") ||
                strstr(ptr->d_name,".gif") ||
                strstr(ptr->d_name,".png") ||
                strstr(ptr->d_name,".bitmap")||
                strstr(ptr->d_name,".tiff")||
                strstr(ptr->d_name,".raw") ||
                strstr(ptr->d_name,".svg"))

    //chama a função comparar , para ver se a midia ja estão na lista
    cmp_memoria(head,ptr, list_dir);
        }
    }
}
    //fecha o diretorio
    closedir(diretorio);
    //fecha o arquivo de memoria
    fclose(resgate);
}

// impede que midias de diretoiros repetidos no arquivo de memoria sejam indexadas
void cmp_memoria(node **head, struct dirent *ptr, char *diretorio){
    if (*head == NULL){
        adiciona(diretorio,head,ptr);
        return;
    }
    int resultado;
    node *tmp = *head;
    while(tmp!= NULL){
        resultado = strcmp(tmp->ptr->d_name,ptr->d_name);
        tmp = tmp->prox;
        if (resultado == 0){
          return;
        }

    }
    if (resultado ==0)
        return;
    else
        adiciona(diretorio,head,ptr);

}



