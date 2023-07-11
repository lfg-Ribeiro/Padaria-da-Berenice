#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* ------- OUTROS ------- */

void limparTela(); // cls e clear
void dormir(); // sleep e usleep

/* ------- MENU PRINCIPAL ------- */

void puxaMenu(); // menu principal

/* ------- MENU DE PRODUTOS E SUAS RESPECTIVAS FUNÇÕES ------- */

void menuProdutos(); // menu de produtos
void puxaExibir(); // exibe o estoque
void puxaCadastrar(); // cadsatra um item novo no estoque
void puxaAtualizar(); // atualiza um item ja existente no estoque
void puxaExcluir(); // exclui um item do estoque
void puxaSalvar(); // salva o estoque após alguma alteração (exclusão, atualização ou cadastro)
void puxaLer(); // lê o estoque 
void puxaVoltar(); // volta ao menu principal

/* ------- MENU DE VENDAS E SUAS RESPECTIVAS FUNÇÕES ------- */

void menuVendas(); // menu de vendas
void puxaRealizarVenda(); // função de realizar venda
void puxaRelatorioVendas(); // relatório das vendas

#endif // FUNCTIONS_H_INCLUDED