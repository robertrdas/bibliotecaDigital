#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <dirent.h>

typedef struct node_{
    struct dirent *ptr;
    // ponteiro do tipo dirent
    struct node_ *prox;
    char diretorio[100];
}node;

//função menu
int menu();

//função que recebe a opção escolhida
void opcao(int opc, node **head);

// para criar estrutura do tipo node
node *aloca();

//funçãao para add um diretorio
void opendiretorio(node **head);

//função para mostrar as midias que estão salvas
void mostrar(node *head);

// para adicionar elementos do diretorio na lista interna
void adiciona(char *diretorio,node **head,struct dirent *ptr);

/*
função que compara se algum elemento ja esta na lista,
 se ja estiver ela não adiciona e informa o usuario
*/
void comparar (node **head, struct dirent *ptr, char *diretorio);

// para pesquisar se a midia esta na lista
void pesquisar(node **head);

//para zera a lista
void limpar(node **head);

// responsavel por recuperar os diretorios abertos anteriormente
void retorno(node **head);

// compara as midias dos diretorios salvos para que nn  haja repetição
void cmp_memoria(node **head, struct dirent *ptr, char *diretorio);




