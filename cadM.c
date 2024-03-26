#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50

typedef struct no {
    char musica[TAM];
    char cantor[TAM];
    struct no *proximo;
} No;



//procedimento para inserir o nome do artista e musica
void inserir_ordenado(No **lista, const char *musica, const char *cantor) {
    No *aux, *novo = malloc(sizeof(No));//criar o no

    if (novo) {//verificar se o no foi alocado corretamente
        strncpy(novo->musica, musica, TAM - 1);//musica
        novo->musica[TAM - 1] = '\0';

        strncpy(novo->cantor, cantor, TAM - 1);//cantor
        novo->cantor[TAM - 1] = '\0';

        if (*lista == NULL || strcmp(novo->musica, (*lista)->musica) < 0) {
            novo->proximo = *lista;
            *lista = novo;
        } else {
            aux = *lista;
            while (aux->proximo && strcmp(novo->musica, aux->proximo->musica) > 0)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            aux->proximo = novo;
        }
    } else {
        printf("Erro ao cadastrar!\n");
    }
}


//procedimento para pesquisar o nome do artista e musica
No *buscar(No *lista, const char *musica, const char *cantor) {
    while (lista && (strcmp(lista->musica, musica) != 0 || strcmp(lista->cantor, cantor) != 0))
        lista = lista->proximo;

    return lista;
}

//procedimento para remover o nome do artista e musica

No *remover(No **lista, const char *musica, const char *cantor) {
    No *aux, *remover = NULL;

    if (*lista) {
        if (strcmp((*lista)->musica, musica) == 0 && strcmp((*lista)->cantor, cantor) == 0) {
            remover = *lista;
            *lista = remover->proximo;
        } else {
            aux = *lista;
            while (aux->proximo && (strcmp(aux->proximo->musica, musica) != 0 || strcmp(aux->proximo->cantor, cantor) != 0))
                aux = aux->proximo;

            if (aux->proximo) {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
        }
    }

    return remover;
}



//procedimento para imprimir o nome do artista e musica
void imprimir(No *no) {
    printf("\n\n\n\n\n\nLista de Musicas e Cantores:\n");
    
    while (no) {
    	printf("\n------------------------------------------------------------------------------------\n");
        printf("Musica - %s\n", no->musica);
        printf("Cantor - %s\n", no->cantor);
        printf("\n------------------------------------------------------------------------------------\n");
        printf("\n");
        no = no->proximo;
    }
    
}

int main() {
    int opcao;
    char musica[TAM];
    char cantor[TAM];
    No *lista = NULL;

    do {
        printf("1 - Cadastrar\n");
        printf("2 - Buscar\n");
        printf("3 - Imprimir\n");
        printf("4 - Remover\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a Musica: ");
                getchar();
                fgets(musica, TAM, stdin);

                int comprimento_musica = strlen(musica);
                if (comprimento_musica > 0 && musica[comprimento_musica - 1] == '\n') {
                    musica[comprimento_musica - 1] = '\0';
                }

                printf("Digite o Cantor: ");
                fgets(cantor, TAM, stdin);

                int comprimento_cantor = strlen(cantor);
                if (comprimento_cantor > 0 && cantor[comprimento_cantor - 1] == '\n') {
                    cantor[comprimento_cantor - 1] = '\0';
                }

                inserir_ordenado(&lista, musica, cantor);
                break;

            case 2:
                printf("Digite a Musica: ");
                getchar();
                fgets(musica, TAM, stdin);

                int comprimento_musica_busca = strlen(musica);
                if (comprimento_musica_busca > 0 && musica[comprimento_musica_busca - 1] == '\n') {
                    musica[comprimento_musica_busca - 1] = '\0';
                }

                printf("Digite o Cantor: ");
                fgets(cantor, TAM, stdin);

                int comprimento_cantor_busca = strlen(cantor);
                if (comprimento_cantor_busca > 0 && cantor[comprimento_cantor_busca - 1] == '\n') {
                    cantor[comprimento_cantor_busca - 1] = '\0';
                }

                No *resultado = buscar(lista, musica, cantor);
                if (resultado) {
                    printf("Encontrado:\n");
                    printf("Musica - %s\n", resultado->musica);
                    printf("Cantor - %s\n", resultado->cantor);
                } else {
                    printf("Nao encontrado.\n");
                }
                break;

            case 3:
                imprimir(lista);
                break;

            case 4:
                printf("Digite a Musica: ");
                getchar();
                fgets(musica, TAM, stdin);

                int comprimento_musica_remover = strlen(musica);
                if (comprimento_musica_remover > 0 && musica[comprimento_musica_remover - 1] == '\n') {
                    musica[comprimento_musica_remover - 1] = '\0';
                }

                printf("Digite o Cantor: ");
                fgets(cantor, TAM, stdin);

                int comprimento_cantor_remover = strlen(cantor);
                if (comprimento_cantor_remover > 0 && cantor[comprimento_cantor_remover - 1] == '\n') {
                    cantor[comprimento_cantor_remover - 1] = '\0';
                }

                No *removido = remover(&lista, musica, cantor);

                if (removido) {
                    printf("Removido:\n");
                    printf("Musica - %s\n", removido->musica);
                    printf("Cantor - %s\n", removido->cantor);
                    free(removido);
                } else {
                    printf("Inexistente!\n");
                }

                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}


