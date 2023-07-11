#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

/* ------- OUTROS ------- */

void limparTela() { // limpar a tela
    #ifdef _WIN32 // verifica se está executando no Windows
        system("cls"); // comando para limpar tela no Windows
    #else
        system("clear"); // comando para limpar tela no Linux e macOS
    #endif
} // limpar a tela

void dormir() { // função para dar um pause
    #ifdef _WIN32 // verifica se está executando no Windows
        sleep(2000); // comando para dar pause na tela no Windows
    #else
        usleep(2000 *1000); // comando para dar pause na tela no Linux e macOS
    #endif
} // função para dar um pause

/* ------- MENU PRINCIPAL ------- */

int op_main_menu; // declaração de variável para o void puxaMenu

void puxaMenu(){ // void para o menu principal
    do{
    printf("(1). Menu Produtos\n");
    printf("(2). Menu Vendas\n");
    printf("(3). Sair\n"); 
    scanf("%d", &op_main_menu);
    getchar();
    limparTela();
    } while (op_main_menu >= 4);
    switch (op_main_menu){
        case 1:
            printf("Opção selecionada: Menu Produtos\n\n");
            menuProdutos();
            break;
        case 2:
            printf("Opção selecionada: Menu Vendas\n\n");
            menuVendas();
            break;
        case 3:
            printf("Encerrando programa...\n\n");
            dormir();
            exit (0);
            break;
    }
} // void para o menu principal

/* ------- MENU DE PRODUTOS E SUAS RESPECTIVAS FUNÇÕES ------- */

int op_menuProdutos; // declaração de variável para o void menuProdutos

void menuProdutos() {
    do {
        printf("\t\t===== SUBMENU DE PRODUTOS =====\n");
        printf("\tOPÇÕES: \n");
        printf("\t(1). Exibir\n");
        printf("\t(2). Cadastrar\n");
        printf("\t(3). Atualizar\n");
        printf("\t(4). Excluir\n");
        printf("\t(5). Salvar\n");
        printf("\t(6). Ler\n");
        printf("\t(0). Voltar\n");
        scanf("%d", &op_menuProdutos);
        getchar();

        limparTela();

        switch (op_menuProdutos) {
            case 1:
                printf("Opção selecionada: Exibir\n\n");
                puxaExibir();
                break;
            case 2:
                printf("Opção selecionada: Cadastrar\n\n");
                puxaCadastrar();
                break;
            case 3:
                printf("Opção selecionada: Atualizar\n\n");
                puxaAtualizar();
                break;
            case 4:
                printf("Opção selecionada: Excluir\n\n");
                puxaExcluir();
                break;
            case 5:
                printf("Opção selecionada: Salvar\n\n");
                puxaSalvar();
                break;
            case 6:
                printf("Opção selecionada: Ler\n\n");
                puxaLer();
                break;
            case 0:
                printf("Opção selecionada: Voltar\n\n");
                puxaVoltar();
                break;
            default:
                printf("Opção inválida\n\n");
                break;
        }
    } while (op_menuProdutos != 6);
} // submenu de produtos

typedef struct Produto {
    unsigned long long int codigo;
    char nome[26];
    float preco;
    int quantidade;
    struct Produto* proximo;
} Produto;

Produto* primeiroProduto = NULL; // Ponteiro para o primeiro produto na lista

void puxaExibir() { // exibe uma tabela com o estoque
    // Cabeçalho
    printf("|---------|------------------|------------|------------|\n");
    printf("| Código: |     Produto:     |   Valor:   |  Estoque:  |\n");
    printf("|---------|------------------|------------|------------|\n");
    // Corpo
    printf("|--18745--|--Pão-de-Forma----|--R$07,50---|-----00-----|\n");
    printf("|--45462--|--Pão-de-Centeio--|--R$08,69---|-----05-----|\n");
    printf("|--34654--|--Broa-de-Milho---|--R$05,00---|-----02-----|\n");
    printf("|--00040--|--Sonho-----------|--R$04,50---|-----03-----|\n");
    printf("|--05000--|--Tubaína---------|--R$03,25---|-----00-----|\n");
    // Rodapé
    printf("|---------|------------------|------------|------------|\n");
    printf("\n\n");
    
    dormir();
}

int verificaCodigoExistente(unsigned long long int codigo) {
    Produto* produtoAtual = primeiroProduto;
    while (produtoAtual != NULL) {
        if (produtoAtual->codigo == codigo) {
            return 1; // Código já existe
        }
        produtoAtual = produtoAtual->proximo;
    }
    return 0; // Código não existe
}

void puxaCadastrar() {
    unsigned long long int codigo;
    char nome[26];
    float preco;
    int quantidade;

    printf("Digite o código do produto: ");
    scanf("%llu", &codigo);
    getchar(); // Limpa o caractere de nova linha do buffer

    // Verificar se o código já existe
    if (verificaCodigoExistente(codigo)) {
        printf("O código do produto já existe no cadastro. Tente novamente.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite o valor do produto: ");
    scanf("%f", &preco);
    getchar(); // Limpa o caractere de nova linha do buffer

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &quantidade);
    getchar(); // Limpa o caractere de nova linha do buffer

    limparTela();

    // Validar se os dados atendem às condições
    if (codigo == 0 || strlen(nome) == 0 || preco < 0 || quantidade < 0) {
        printf("Os dados inseridos não atendem às condições. Tente novamente.\n");
        return;
    }

    // Criar um novo produto
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->codigo = codigo;
    strcpy(novoProduto->nome, nome);
    novoProduto->preco = preco;
    novoProduto->quantidade = quantidade;
    novoProduto->proximo = NULL;

    // Verificar se é o primeiro produto da lista
    if (primeiroProduto == NULL) {
        primeiroProduto = novoProduto;
    } else {
        // Encontrar o último produto na lista
        Produto* ultimoProduto = primeiroProduto;
        while (ultimoProduto->proximo != NULL) {
            ultimoProduto = ultimoProduto->proximo;
        }

        // Adicionar o novo produto ao final da lista
        ultimoProduto->proximo = novoProduto;
    }

    printf("Produto cadastrado com sucesso!\n");
}

void puxaAtualizar() { // atualiza um item que ja tem no estoque
    char codigo[20];

    printf("Digite o código do produto que deseja atualizar: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            printf("Produto encontrado. Informações atuais:\n");
            printf("Código: %s\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Valor: R$ %.2f\n", produtos[i].valor);
            printf("Estoque: %d\n", produtos[i].estoque);
            printf("Vendido: %d\n", produtos[i].quantidadeVendida);

            printf("Digite as novas informações:\n");
            printf("Digite o nome do produto: ");
            fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin);

            char valorStr[20];
            printf("Digite o valor do produto: ");
            fgets(valorStr, sizeof(valorStr), stdin);
            sscanf(valorStr, "%f", &produtos[i].valor);

            char estoqueStr[20];
            printf("Digite a quantidade em estoque: ");
            fgets(estoqueStr, sizeof(estoqueStr), stdin);
            sscanf(estoqueStr, "%d", &produtos[i].estoque);

            char quantidadeStr[20];
            printf("Digite a quantidade vendida: ");
            fgets(quantidadeStr, sizeof(quantidadeStr), stdin);
            sscanf(quantidadeStr, "%d", &produtos[i].quantidadeVendida);

            printf("Produto atualizado com sucesso.\n");
            return;
        }
    }

    printf("Produto não encontrado.\n");
} // atualiza um item que ja tem no estoque

void puxaExcluir() { // função para excluir um produto do estoque
    char codigo[20];

    printf("Digite o código do produto que deseja excluir: ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    for (int i = 0; i < numProdutos; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            printf("Produto encontrado. Informações do produto:\n");
            printf("Código: %s\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Valor: R$ %.2f\n", produtos[i].valor);
            printf("Estoque: %d\n", produtos[i].estoque);
            printf("Vendido: %d\n", produtos[i].quantidadeVendida);

            printf("Deseja realmente excluir o produto? (S/N): ");
            char resposta[2];
            fgets(resposta, sizeof(resposta), stdin);

            if (toupper(resposta[0]) == 'S') {
                for (int j = i; j < numProdutos - 1; j++) {
                    produtos[j] = produtos[j + 1];
                }
                numProdutos--;
                printf("Produto excluído com sucesso.\n");

                puxaMenu(); // retornar ao menu 
                } else {
                printf("Exclusão cancelada.\n");
            }

            puxaMenu();
        }
    }

    printf("Produto não encontrado.\n");
} // função para excluir um produto do estoque

void puxaSalvar() { // salva os itens cadastrados no arquivo do estoque
    FILE* arq = fopen("estoque.txt", "a");
    if (arq == NULL) {
        printf("ERRO: arquivo não encontrado\n");
        return;
    }

    for (int i = 0; i < numProdutos; i++) {
        fprintf(arq, "%s\n%s\n%.2f\n%d\n%d\n", produtos[i].codigo, produtos[i].nome, produtos[i].valor, produtos[i].estoque, produtos[i].quantidadeVendida);
    }

    fclose(arq);
} // salva os itens cadastrados no arquivo do estoque

void adicionarProduto(const char* codigo, const char* nome, int estoque, float valor, int quantidadeVendida) {
    strcpy(produtos[numProdutos].codigo, codigo);
    strcpy(produtos[numProdutos].nome, nome);
    produtos[numProdutos].estoque = estoque;
    produtos[numProdutos].valor = valor;
    produtos[numProdutos].quantidadeVendida = quantidadeVendida;
    
    numProdutos++;
}

void puxaLer() {
    // Verifica se já existe uma lista de produtos e apaga se existir
    if (numProdutos > 0) {
        free(produtos);
        numProdutos = 0;
    }

    // Abre o arquivo para leitura
    FILE* arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo de produtos.\n");
        return;
    }

    // Lê os produtos do arquivo e adiciona à lista
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char codigo[20];
        char nome[50];
        int estoque;
        float valor;
        int quantidadeVendida;

        sscanf(linha, "%s %s %d %f %d", codigo, nome, &estoque, &valor, &quantidadeVendida);

        // Adiciona o produto à lista
        adicionarProduto(codigo, nome, estoque, valor, quantidadeVendida);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Produtos lidos do arquivo com sucesso.\n");
} 

void puxaVoltar() { // retorna ao menu principal
    printf("Voltando para o menu principal...\n\n");
    dormir();
    puxaMenu();
} // retorna ao menu principal

/* ------- MENU DE VENDAS E SUAS RESPECTIVAS FUNÇÕES ------- */

void menuVendas() {
    int op_menuVendas;

    do {
        printf("\t\t===== SUBMENU DE VENDAS =====\n");
        printf("\tOPÇÕES: \n");
        printf("\t(1). Realizar venda\n");
        printf("\t(2). Relatório de vendas\n");
        printf("\t(0). Voltar\n");
        scanf("%d", &op_menuVendas);
        getchar();
        
        limparTela();

        switch (op_menuVendas) {
            case 1:
                printf("Opção selecionada: Realizar venda\n\n");
                puxaRealizarVenda();
                break;
            case 2:
                printf("Opção selecionada: Relatório de vendas\n\n");
                puxaRelatorioVendas();
                break;
            case 0:
                printf("Opção selecionada: Voltar\n\n");
                puxaVoltar();
                break;
            default:
                printf("Opção inválida\n\n");
                break;
        }

        printf("\n");

    } while (op_menuVendas != 2);
}

void puxaRealizarVenda() {
    int continuarVenda = 1;
    float totalVenda = 0.0;

    printf("===== Realizar Venda =====\n");

    while (continuarVenda) {
        // Exibir a lista de produtos disponíveis
        puxaExibir();

        char codigo[20];
        int quantidade;

        printf("Digite o código do produto: ");
        fgets(codigo, sizeof(codigo), stdin);
        codigo[strcspn(codigo, "\n")] = '\0';

        int index = -1;
        for (int i = 0; i < numProdutos; i++) {
            if (strcmp(produtos[i].codigo, codigo) == 0) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("Produto não encontrado.\n");
            continue;
        }

        printf("Produto encontrado. Informações:\n");
        printf("Código: %s\n", produtos[index].codigo);
        printf("Nome: %s\n", produtos[index].nome);
        printf("Valor: R$ %.2f\n", produtos[index].valor);
        printf("Estoque: %d\n", produtos[index].estoque);

        printf("Digite a quantidade desejada: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0 || quantidade > produtos[index].estoque) {
            printf("Quantidade inválida ou insuficiente.\n");
            continue;
        }

        float valorTotal = produtos[index].valor * quantidade;
        totalVenda += valorTotal;

        produtos[index].estoque -= quantidade;

        // Perguntar ao cliente o método de pagamento
        int opcaoPagamento;
        printf("Selecione o método de pagamento:\n");
        printf("1. À vista com desconto\n");
        printf("2. A prazo\n");
        scanf("%d", &opcaoPagamento);

        float valorRecebido;
        float troco = 0.0;

        switch (opcaoPagamento) {
            case 1:
                // À vista com desconto
                if (valorTotal <= 50.0) {
                    valorTotal *= 0.95; // Aplica desconto de 5%
                } else if (valorTotal > 50.0 && valorTotal < 100.0) {
                    valorTotal *= 0.9; // Aplica desconto de 10%
                } else {
                    valorTotal *= 0.82; // Aplica desconto de 18%
                }

                printf("Valor total com desconto: R$ %.2f\n", valorTotal);

                // Verificar se precisa de troco
                int precisaTroco;
                printf("Deseja troco? (1 - Sim, 0 - Não): ");
                scanf("%d", &precisaTroco);

                if (precisaTroco) {
                    do {
                        printf("Digite o valor recebido: ");
                        scanf("%f", &valorRecebido);

                        if (valorRecebido < valorTotal) {
                            printf("Valor insuficiente. Digite um valor igual ou maior que R$ %.2f\n", valorTotal);
                        }
                    } while (valorRecebido < valorTotal);

                    troco = valorRecebido - valorTotal;
                    printf("Troco: R$ %.2f\n", troco);
                }
                break;

            case 2:
                // A prazo
                int numParcelas;
                printf("Digite o número de parcelas: ");
                scanf("%d", &numParcelas);

                if (numParcelas <= 3) {
                    valorTotal *= 1.05; // Aplica acréscimo de 5%
                } else {
                    valorTotal *= 1.08; // Aplica acréscimo de 8%
                }

                printf("Valor total a prazo: R$ %.2f\n", valorTotal);
                break;

            default:
                printf("Opção de pagamento inválida.\n");
                continue;
        }

        // Perguntar se deseja realizar outra venda
        printf("Deseja realizar outra venda?\n");
        printf("1. Sim\n");
        printf("2. Não\n");
        scanf("%d", &continuarVenda);

        // Limpar o buffer de entrada
        getchar();
    }

    printf("===== Cupom Fiscal =====\n");
    printf("Produtos vendidos:\n");

    printf("Total da compra: R$ %.2f\n", totalVenda);
}

void puxaRelatorioVendas() {
    // Implementação da função "Relatório de vendas"
    printf("Em construção...\n");
}
