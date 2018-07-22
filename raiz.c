#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <dirent.h>
#include <midias.h>


int main(){
    int opc;

    node *head = NULL;

    retorno(&head);
    // para poder usar acentos nas palavras
    setlocale(LC_ALL, "Portuguese");

    do {
    opc = menu();
    opcao(opc, &head);
    }while(opc);

    limpar(head);


}

