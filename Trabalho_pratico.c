#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include <string.h>

int i;
typedef struct Produto {
    char nome[40];
    int codigo;
    int quantidade;
    float preco;
} produto;

typedef struct Lista {
    int max;
    int n;
    produto *itens;
} t_lista;

t_lista *criarLista(int tam) {
    t_lista *lista = (t_lista *)malloc(sizeof(t_lista));
    lista->max = tam;
    lista->n = 0;
    lista->itens = (produto *)malloc(sizeof(produto) * tam);
    return lista;
}

int limparLista(lista);
int listaCheia(lista);
int listaVazia(lista);
int tamanho(lista);
int buscar_produto(lista,elem);
int verificarProdutoDuplicado(lista,cod);
int listaTodos(lista);
int removeIndex(lista,index);
int removeProduto(lista);
int removeUltimaPosicao(lista);
int insereFim(lista,prod);
void inserirIndice(lista,indice,prod);
int indiceInserir(lista,indice);
void atualizarProduto(lista);
void listaProdutoId(lista);
int cadastrarProduto(lista);
int menu_produto();
void gerenciador_produto(lista);
void imprimiProduto(p);
int menuprincipal();
void salva(lista) ;
void carrega(lista);
void menuArquivo(lista);
int main();



int limparLista(t_lista *lista){
    return lista->n = 0;
}
int listaCheia(t_lista *lista) {
    return lista->n == lista->max;
}

int listaVazia(t_lista *lista){
    return lista->n == 0;
}

int tamanhoLista(t_lista *lista){
    return lista->n;
}

int busca_produto(t_lista *lista, int elem){
   // printf("\n\t --- Buscando um produto no estoque ---\n");

    printf("Informe o codigo: \n");
    scanf("%d", &elem);

    if(!listaVazia(lista)){
        for( i = 0 ; lista-> n ; i++){
           if(lista->itens[i].codigo == elem){
           return i;
         }
       }
    }
   return -1;
}
void imprimiProduto(produto *p){


    printf("-----------Pruduto------------");
    printf("\nCodigo do produto:%d",p->codigo);
    printf("\nNome do produto: %s" ,p->nome);
    printf("\nQuantidade estoque: %d",p->quantidade);
    printf("\nPreco: %.2f \n\n",p->preco);


}
int verificaProdutoDuplicado(t_lista *lista, int cod){
    for( i = 0; i < lista->n ; i++){
        if(lista->itens[i].codigo ==  cod){
           return 1;
        }
    }
    return 0;

}

int listaTodos(t_lista *lista){
   if(!listaVazia(lista)){
        for( i = 0; i < lista->n; i++){
            imprimiProduto(&lista->itens[i]);
        }
        return 1;
   }
   return 0;
}

int removeIndex(t_lista *lista, int index){

   if(!listaVazia(lista) && index >= 0 && index < lista->n){
       for( i = index ; i < lista->n -1 ; i++){
          lista->itens[i]  =  lista->itens[i +1];
       }
       lista->n--;
       return 1;
   }
    return 0;
}


int removeUltimaPosicao(t_lista *lista){
    if(!listaVazia(lista)){
        lista->n --;
        return 1;
    }
    return 0;
}

int insereFim(t_lista *lista, produto prod){
    if(!listaCheia(lista)){
        lista->itens[lista->n] = prod;
        lista->n++;
        return 1;
    }
    return 0;

}

void inserirIndice(t_lista *lista, int indice,produto prod){
    if(indice >= 0 && indice <= lista->n){
        for( i = lista->n -1; i >= indice; i--){
            lista->itens[i +1] = lista->itens[ i];
        }
        lista->itens[indice] = prod;
        lista->n++;
        return 1;
    } 
    return 0;
}

int ordenacaoBolhaOtimizado(t_lista *lista ){
    int trocou = -1;
    produto  aux;
    int j;
   if(!listaVazia(lista)){
       for( i = lista->n -1; i >= 1 && trocou; i--){ 
            trocou = 0;
            for( j = 0; j < i ; j++){
                if(lista->itens[j].codigo > lista->itens[j +1].codigo){
                    aux =  lista->itens[j]; 
                    lista->itens[j]  = lista->itens[j +1];
                    lista->itens[j +1] = aux;
                    trocou =1;
                    
                }
                
            }
       }
    
       return 1;
   }
   return 0;
}

int removeProduto(t_lista *lista) {
    int index;
    printf("Informe o indice: ");
    scanf("%d", &index);

    if (removeIndex(lista, index)) {
        printf("Produto removido com sucesso.\n");
        return 1;
    } else {
        printf("Falha na remoção. Verifique o indice ou a lista vazia.\n");
        return 0;
    }
}

int indiceInserir(t_lista *lista, int indice){
  int duplicado;
  int cod;
  produto prod;

    printf("Informe o indice:");
    scanf("%d",&indice);

    if(listaCheia(lista)){
        printf("Lista cheia!\n\n");
        return 0;
    }
    if(indice >= 0 &&  indice <= lista->n){
        printf("\ncodigo produto:");
        scanf("%d",&cod);

        duplicado = verificaProdutoDuplicado(lista, cod);
      
      while (duplicado == 1) {
          printf("Produto ja cadastrado! Insira um codigo diferente: ");
          scanf("%d",&cod);
          duplicado = verificaProdutoDuplicado(lista, cod);
       }
        prod.codigo = cod;
        printf("\nNome do produto:");
        scanf("%s",&prod.nome);


        printf("\nQuantidade em estoque: ");
        scanf("%d",&prod.quantidade);

        printf("\nPreco:");
        scanf("%f",&prod.preco);

        inserirIndice(lista,indice,prod);

        printf("Inserido com sucesso\n");
        return 1;
    }
    printf("Falha na insercao. Não é possível inserir em indices maiores que %d.\n", lista->n);
    return 0;

}

void atualizarProduto(t_lista *lista){
    int elem;
    int buscar;

    buscar = busca_produto(lista,elem);

    if(buscar != -1){

       printf("Nome do produto:");
       scanf("%s",lista->itens[buscar].nome);

       printf("\nCodigo do produto:");
       scanf("%d",&lista->itens[buscar].codigo);

       printf("\nQuantidade em estoque: ");
       scanf("%d",&lista->itens[buscar].quantidade);

       printf("\nPreco:");
       scanf("%f",&lista->itens[buscar].preco);

       fflush(stdin);
      printf("\nProduto atualizado com sucesso!\n");

    }else{
        printf("Codigo do produto nao foi encontrado\n");
        printf("busca:%d\n",buscar);
    }
}



void listaProdutoId(t_lista *lista){
    int elem;
    int buscar;

    buscar = busca_produto(lista,elem);

    if(buscar != -1){

        printf("Nome do produto: %s" ,lista->itens[buscar].nome);
        printf("\nCodigo do produto:%d ",lista->itens[buscar].codigo);
        printf("\nQuantidade estoque: %d",lista->itens[buscar].quantidade);
        printf("\nPreco: %.2f ",lista->itens[buscar].preco);
        printf("\n");

    }else{
        printf("Codigo do produto nao foi encontrado\n");
        printf("busca:%d\n",buscar);
    }

}



int cadastrarProduto(t_lista *lista) {
    int cod;
    int duplicado;
    produto prod;

    printf("informeo  codigo:");
    scanf("%d",&cod);

   duplicado = verificaProdutoDuplicado(lista, cod);
    printf("duplicado: %d | %d\n",duplicado,cod);
    while (duplicado == 1) {
        printf("Produto ja cadastrado! Insira um codigo diferente: ");
        scanf("%d",&cod);
        duplicado = verificaProdutoDuplicado(lista, cod);
    }

    prod.codigo =cod;
    printf("\nNome do produto:");
    scanf("%s",&prod.nome);


    printf("\nQuantidade em estoque: ");
    scanf("%d", &prod.quantidade);

    printf("\nPreco:");
    scanf("%f",&prod.preco);

    insereFim(lista,prod);

    fflush(stdin);


}



int menu_produto() {
    int op;
   // system("cls");
    printf("--------------------------------------\n");
    printf("-----------Relatorio de estoque-------\n");
    printf("\t1. Inseri no fim\n");
    printf("\t2. Inserir item por posicao\n");
    printf("\t3. Consultar produto por Id\n");
    printf("\t4. Atulizar produto\n");
    printf("\t5. Lista todos os produtos\n");
    printf("\t6. Tamanho da lista\n");
    printf("\t7. Remove por posicao\n");
    printf("\t8. Remove o ultimo da lista\n");
    printf("\t9. Salvar\n");
    printf("\t10. Carregar\n");
    printf("\t11. Limpar lista\n");
     printf("\t12. Ordernar por codigo\n");
    printf("\t0. voltar\n");
    printf("--------------------------------------\n");
    scanf("%d", &op);
    return op;
    system("cls");
    system("pause");
}

void gerenciador_produto(t_lista *lista) {
    int i = 1;
    int menu;
    int flag;
    int indice;
    system("pause");
    while (i != 0) {

        int opcao = menu_produto();
        switch (opcao) {
        case 1:

            if (!listaCheia(lista)) {
                cadastrarProduto(lista);
                printf("\nProduto cadastrado com sucesso!\n");
            } else {
                printf("A lista esta cheia!\n");
            }

            break;
        case 2:
           //flag = indiceInserir(lista,indice);
             indiceInserir(lista,indice);

            break;
        case 3:
            listaProdutoId(lista);
            break;
        case 4:
            atualizarProduto(lista);
            break;
        case 5:

            if(listaTodos(lista) == 0){
                printf("lista vazia\n");
            }
            break;
        case 6:
            printf("Tamanho da lista: %d\n", tamanhoLista(lista));
            break;
        case 7:
           removeProduto(lista);
            break;;
        case 8:
            //flag = removeUltimaPosicao(lista);
            //printf("flag : %d",flag);
            if(removeUltimaPosicao(lista) == 1){
               printf("Produto removido\n");
            }else{
                printf(" Falha na remocao do prudto\n");
            }
            break;
        case 9:
            salva(lista);
            break;
        case 10:
          carrega(lista);
          break;
        case 11:
            if(!limparLista(lista)){
              printf("Lista vazia\n");
            }

          break;
        case 12:
         
           if(ordenacaoBolhaOtimizado(lista) == 1){
               printf("ordenado\n");
           }else{
              printf("falha\n");
           }
           
            break;
        case 0:
            i= 0;
            main();
            break;
        default:
          printf("Opcao invalida!!! Escolha novamente!\n");
            break;
        }
          system("pause");
    }
}



int menuprincipal(){
    int op;

    printf("---------------------------------------\n");
    printf("----------Nenu Principal---------------\n");
    printf("\t1.Produto\n");
    printf("\t0. Sair\n");
    printf("Escolha uma opcao:\n");
    printf("--------------------------------------\n");
    scanf("%d",&op);
    return op;
    system("cls");
}

void salva(t_lista *lista) {
    FILE *arquivo;
    arquivo = fopen("lista_produtos.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for ( i = 0; i < lista->n; i++) {
        fprintf(arquivo,  " %s, %d,  %d,  %.2f\n", lista->itens[i].nome, lista->itens[i].codigo, lista->itens[i].quantidade, lista->itens[i].preco);
    }

    printf("Dados salvos com sucesso em lista_produtos.csv.\n");

    fclose(arquivo);
}

void carrega(t_lista *lista) {
    FILE *arquivo;
    arquivo = fopen("lista_produtos.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    limparLista(lista);
      /*
           %39[^,]: Isso lê até 39 caracteres (ou até encontrar uma vírgula) e
           armazena no campo nome da estrutura prod.
           O [^,] indica que a leitura deve parar quando uma vírgula for encontrada.
           ,: Isso corresponde à própria vírgula no arquivo
       */
    produto prod;
    while (fscanf(arquivo, "%39[^,],%d,%d,%f\n", prod.nome, &prod.codigo, &prod.quantidade, &prod.preco) == 4) {
        if (insereFim(lista, prod)) {
        printf("Nome: %s\n", prod.nome);
        printf("Codigo: %d\n", prod.codigo);
        printf("Quantidade: %d\n", prod.quantidade);
        printf("Preco: %.2f\n", prod.preco);
        printf("------------------------------\n");

        }
    }

    fclose(arquivo);
}



void menuArquivo(t_lista *lista) {
    char resposta;

    printf("\nDeseja abrir o arquivo lista de produtos? (s/n)\n ");
    scanf(" %c", &resposta);

    if (resposta == 's' || resposta == 'S') {
        carrega(lista);
        printf("\nDados carregados do arquivo.\n");
    }
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    t_lista *lista = criarLista(10);
    produto p;
    int op =0;

    menuArquivo(lista);
    do{
        int op = menuprincipal();
        switch (op){
        case 1:
             gerenciador_produto(lista);
            break;

        default:
            break;
        }
    }while(op !=0);
    fflush(stdin);
   system("pause");
 

}
