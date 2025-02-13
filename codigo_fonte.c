#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Pessoa{
    int id;
    char nome[200];
    int idade;
}Pessoa;

typedef struct Produto{
    int id;
    char nome[200];
    float preco;
}Produto;

//Struct que estabelece um relacionamento entre a pessoa e o produto
typedef struct Compra{
    int idCompra;
    Pessoa cliente;
    Produto produtos[10];//Será uma lista de até 10 produtos
    int quantidade;
}Compra;

//-------------------------------------- 1 --------------------------------------
int adicionarCliente(Pessoa *pessoa, int numClientes, int numClientesExistentes){
    int i;
    if(pessoa == NULL){//Verificando se a alocação realmente deu certo
        return 1;
    }

    for (i = 0; i < numClientes; i++){
        printf("\n====Pessoa %d====\n", numClientesExistentes+i + 1);
        printf("Nome do Cliente: ");
        fgets(pessoa[i].nome, 200, stdin);
        // Remover o '\n' que pode ser capturado pelo fgets()
        pessoa[i].nome[strcspn(pessoa[i].nome, "\n")] = '\0';

        printf("Qual a idade do cliente: ");
        scanf("%d", &pessoa[i].idade);
        getchar();

        pessoa[i].id = (rand() % 100) + 1;
        printf("ID do cliente[%d] eh: %d\n", i+ 1, pessoa[i].id);//Por ser como chave primária para buscas não pode haver risco de duplicação.
        printf("------------------\n");
    }
    
    return 0;
}

//-------------------------------------- 2 --------------------------------------
int adicionarProduto(Produto *produto, int numProdutos, int numProdutosExistentes){
    int i;
    if(produto == NULL){//Re-verifica a alocacao
        return 1;
    }

    for(i = 0; i < numProdutos; i++){
        printf("====Produto %d====\n", numProdutosExistentes+i + 1);
        printf("Nome do produto: ");
        getchar();
        fgets(produto[i].nome, 200, stdin);

        printf("Qual eh seu valor: ");
        scanf("%f", &produto[i].preco);
        getchar();

        produto[i].id = numProdutosExistentes+i + 1;
        printf("ID do produto[%d] eh: %d\n", produto[i].id, produto[i].id);
    }
    return 0;
}

//-------------------------------------- 3 --------------------------------------
int removerCliente(Pessoa **cliente, int *numClientes){
    int i,j;
    int removidos = 0;
    char nomeBuscar[200];

    if(*numClientes == 0){
        printf("Nenhum cliente cadastrado. \n");
        return 0;
    }

    printf("Qual o nome do cliente para remocao: ");
    fgets(nomeBuscar, 200, stdin);

    // Remover o '\n' que pode ser capturado pelo fgets()
    nomeBuscar[strcspn(nomeBuscar, "\n")] = 0;

    /*"strcmp " compara duas strings, caso sejam iguais retorna 0, 
    caso a primeira seja menor que a segundo retorna um numero negativo, e caso a primeira for maior que a segundo 
    retorna um numero positivo*/
    for(i = 0; i < *numClientes; i++){
        if(strcmp((*cliente)[i].nome, nomeBuscar) == 0){
            //"Removerá o cliente encontrado, substituindo os dados da posição a frente nele"
            for(j = i; j < *numClientes -1; j++){
                (*cliente)[j] = (*cliente)[j + 1];
            }

            (*numClientes)--;//atualiza o n° de clientes
            i--;// para verificar a mesma posição, ja que os dados foram substituídos pelo da frente
            removidos++;//contador de remoção
        }
    }

    if(removidos > 0){//caso há remocao realocamos o vetor de struct
            
        if(*numClientes > 0){//E também caso o numero de clientes for maior que 0, se não o vetor de struct poderá estar vazio e com vazamento de memória
        *cliente = realloc(*cliente, (*numClientes) * sizeof(Pessoa));
        }else{
            free(*cliente);
            *cliente = NULL;
        }
        printf("%d clientes removidos! \n", removidos);

    }else{
        printf("\n============================================ \n");
        printf("Nenhum cliente com esse nome foi encontrado! \n");
        printf("============================================ \n");
        return 1;
    }
    return 0;
}


void listarClientes(Pessoa *cliente, int numClientes) {
    if (numClientes == 0) {
        printf("\nNenhum cliente cadastrado.\n");
        return;
    }
    printf("\n----- Lista de Clientes -----\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", cliente[i].nome);
        printf("Idade: %d\n", cliente[i].idade);
        printf("ID: %d\n", cliente[i].id);
        printf("-----------------------------\n");
    }
}


int menu(){
    int opcao;

    printf("\n 1)Adicionar Cliente");
    printf("\n 2)Adicionar Produto");
    printf("\n 3)Remover Cliente");
    printf("\n 4)Remover Produto");
    printf("\n 5)Listar todos os Clientes");
    printf("\n 6)Listar todos os Produtos");
    printf("\n 7)Buscar Cliente");
    printf("\n 8)Buscar Produto");
    printf("\n 9)Buscar Compra");
    printf("\n 10)Atualizar todos os dados");
    printf("\n 0)Sair");

    printf("\n O que deseja fazer? \n");
    scanf("%d", &opcao);
    getchar();
    
    return opcao;
}

int main(){
    srand(time(NULL)); // Inicializa a seed do rand() com o tempo atual, para nunca haver repetições.

    Pessoa *cliente = NULL;
    Produto *produto = NULL;
    int numClientes = 0;
    int numProdutos = 0;
    int opcao, novosClientes, novosProdutos;

    printf("=====Bem Vindo=====");

    do{
        opcao = menu();

        switch (opcao){

        case 1:
            printf("Quantos cliente serao adicionados: ");
            scanf("%d", &novosClientes);
            getchar();
            cliente = realloc(cliente , (numClientes+ novosClientes) * sizeof(Pessoa));
            if(cliente == NULL){
                printf("Erro na alocacao de memoria. \n");
                return 1;
            }

            adicionarCliente(&cliente[numClientes], novosClientes, numClientes);
            numClientes += novosClientes;//Mesma coisa que: numClientes = novosClientes + numClientes;
            //Feito para atualizar o numero max de clientes depois de add.
        break;
        
        case 2:
            printf("Quantos produtos serao adicionados: ");
            scanf("%d", &novosProdutos);
            getchar();

            produto = realloc(produto, (numProdutos + novosProdutos) * sizeof(Produto));
            if(produto == NULL){
                printf("Erro na alocacao de memoria. \n");
                return 1;
            }

            adicionarProduto(&produto[numProdutos], novosProdutos, numProdutos);
            numProdutos += novosProdutos;
        break;

        case 3:
            removerCliente(&cliente, &numClientes);
        break;

        case 4:
        break;

        case 5:
            listarClientes(cliente, numClientes); 
        break;

        default:
            break;
        }

    } while (opcao != 0);
    printf("Encerrando o programa!");

    free(cliente);
    free(produto);

    return 0;
}