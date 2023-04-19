//AINDA COM ERROS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 100

// Definição da estrutura da pilha
typedef struct Node {
    char *dados; // Dado armazenado no nó
    struct Node *proximo; // Ponteiro para o próximo nó
} Node;

typedef struct {
    Node *topo; // Ponteiro para o topo da pilha
} Pilha;

// Função para inicializar a pilha
void inicializa_pilha(Pilha *p) {
    p->topo = NULL; // Define o topo como NULL para indicar pilha vazia
}

// Função para verificar se a pilha está vazia
bool is_vazia(Pilha *p) {
    return p->topo == NULL; // Retorna true se o topo for NULL, indicando pilha vazia
}

// Função para inserir uma string na pilha
void inserir_string(Pilha *p, char *str) {
    Node *novo_no = (Node *) malloc(sizeof(Node)); // Aloca memória para um novo nó
    if (novo_no == NULL) {
        printf("Erro: Memória insuficiente\n");
        exit(1);
    }
    novo_no->dados = strdup(str); // Aloca memória para a string e a insere no novo nó
    novo_no->proximo = p->topo; // O próximo do novo nó aponta para o antigo topo
    p->topo = novo_no; // Atualiza o topo para apontar para o novo nó
}

// Função para verificar se uma string é um número real (float) ou inteiro (int)
bool is_numero(char *str) {
    char *endptr;
    strtod(str, &endptr); // Converte a string para double e armazena o ponteiro para o próximo caractere em endptr
    return *endptr == '\0'; // Retorna true se o próximo caractere for o caractere nulo, indicando que a string é um número válido
}

// Função para converter uma string para número real (float) ou inteiro (int)
void converter_numero(char *str) {
    if (is_numero(str)) {
        int inteiro = strtol(str, NULL, 10); // Converte a string para inteiro
        printf("Número inteiro: %d\n", inteiro);
    } else {
        float real = strtof(str, NULL); // Converte a string para float
        printf("Número real: %.2f\n", real);
    }
}

// Função para remover o topo da pilha
void remover_topo(Pilha *p) {
    if (is_vazia(p)) {
        printf("Erro: Pilha vazia\n");
        return;
    }
    Node *no_removido = p->topo; // Guarda o ponteiro do nó que será removido
    p->topo = p->topo->proximo; // Atualiza o topo para apontar para o próximo nó
    free(no_removido->dados); // Libera a memória alocada para a string do nó removido
    free(no_removido); // Libera a memória alocada para o nó removido
}

// Função para verificar o topo da pilha
void ver_topo(Pilha *p) {
    if (is_vazia(p))
        printf("Erro: Pilha vazia\n");
        return;
    printf("Topo da pilha: %s\n", p->dados[p->topo]);
}

// Função para visualizar toda a pilha
void ver_pilha(Pilha *p) {
    if (is_vazia(p))
        printf("Pilha vazia\n");
        return;
    printf("Conteúdo da pilha:\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%s\n", p->dados[i]);
    }
}

int main() {
    Pilha pilha;
    inicializa_pilha(&pilha); // Inicializa a pilha
    int opcao;
    char entrada[100];
    while (1) {
        printf("0. Sair\n");
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir string\n");
        printf("2. Verificar se é número e converter\n");
        printf("3. Remover topo\n");
        printf("4. Ver topo\n");
        printf("5. Ver pilha toda\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                exit(0);
            break;
            
            case 1:
                printf("Digite a string a ser inserida: ");
                scanf("%s", entrada);
                inserir_string(&pilha, entrada);
                break;
        
            case 2:
        	    printf("Digite a string a ser verificada: ");
        	    scanf("%s", entrada);
            	if (is_numero(entrada)) {
            		converter_numero(entrada);
        	    	inserir_string(&pilha, entrada);
        	    } else {
        		    inserir_string(&pilha, entrada);
        	    }
        	break;
    
            case 3:
                remover_topo(&pilha);
                break;
    
            case 4:
                ver_topo(&pilha);
                break;
    
            case 5:
                ver_pilha(&pilha);
                break;
    
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }   
    }
    return 0;
}
