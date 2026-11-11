#include <iostream>
#include <string>
using namespace std;
 
int main() {
    // a const que vai servir para todas variaveis
    const int MAX_CONTAS = 100;
    //todas variaveis obrigatorias
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];
 
    int quantidadeContas = 0;
 
    const int MAX_MOVIMENTACOES = 500;
 
    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];
 
    int quantidadeMovimentacoes = 0;
 
    int opcao, numero, numeroDestino, indice, indiceDestino;
    double valor;
 
    do {
        // começando o menu 
        cout << "\n=== BANCO ===\n";
        cout << "1 - Cadastrar conta\n";
        cout << "2 - Listar contas\n";
        cout << "3 - Consultar conta\n";
        cout << "4 - Depositar\n";
        cout << "5 - Sacar\n";
        cout << "6 - Transferir\n";
        cout << "7 - Extrato\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";
        cin >> opcao;
 
        switch (opcao) {
            case 1:
                //o if pra caso passe de 100 contas mesmo sendo improvavel
                if (quantidadeContas == MAX_CONTAS) {
                    cout << "Limite de contas atingido!" << endl;
                //começando o cadastro
                } else {
                    cout << "Numero da conta: ";
                    cin >> numero;
                    indice = -1;
                    // aqui vai ter o laço pra conferir se ja tem uma conta
                    // com o numero escolhido
                    for (int i = 0; i < quantidadeContas; i++) {
                        if (numeroConta[i] == numero) {
                            indice = i;
                        }
                    }
                    //se ja existir vai falar que ja existe
                    if (indice != -1) {
                        cout << "Ja existe uma conta com esse numero!" << endl;
                    } else {
                        //se nao tiver registra e continua
                        numeroConta[quantidadeContas] = numero;
                        //pra nao dar problema de buffer
                        cin.ignore();
                        //continuando com o simples registrando nome
                        cout << "Nome do cliente: ";
                        getline(cin, nomeCliente[quantidadeContas]);
                        // agora registrando cpf
                        cout << "CPF: ";
                        getline(cin, cpf[quantidadeContas]);
                        do {
                            cout << "Tipo da conta (1-Corrente, 2-Poupanca): ";
                            cin >> tipoConta[quantidadeContas];
                            if (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2) {
                                cout << "Tipo invalido! Digite 1 ou 2." << endl;
                            }
                            // esse do while é pra garantir que seja 1 ou 2
                        } while (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2);
                        do {
                            cout << "Saldo inicial: R$ ";
                            cin >> saldo[quantidadeContas];
                            if (saldo[quantidadeContas] < 0) {
                                cout << "Saldo inicial nao pode ser negativo!" << endl;
                            }
                            // ja esse do while é so pra garantir que o saldo nao seja negativo
                            
                        } while (saldo[quantidadeContas] < 0);
                        // vai ativar a conta no final e aumentar a quantidade de cotnas
                        contaAtiva[quantidadeContas] = true;
                        quantidadeContas++;
                        cout << "Conta cadastrada!" << endl;
                    }
                }
                break;
 
            case 2:
                // antes vai conferir se tem alguam conta
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada." << endl;
                } else {
                    // se tiver o laço vai se repetir mostrando todas as contas
                    cout << "\n--- CONTAS ---\n";
                    for (int i = 0; i < quantidadeContas; i++) {
                        cout << "Conta " << numeroConta[i]
                             << " | " << nomeCliente[i]
                             << " | CPF " << cpf[i]
                             << " | Tipo " << tipoConta[i]
                             << " | Saldo: R$ " << saldo[i] << endl;
                    }
                }
                break;
 
            case 3:
                // aqui vai conferir usando o numero de referencia
                cout << "Numero da conta: ";
                cin >> numero;
                indice = -1;
                // o laço vai ir ate encontrar o numero igual o pedido
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }
                // se nao tiver nenhuma correspondente so vai permanecer -1
                // ou seja so nao tem conta entao cancela e volta pro menu
                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else {
                //encontrou a conta vai mostrar tudo sobre ela:
                    cout << "\n--- CONTA " << numeroConta[indice] << " ---\n";
                    cout << "Cliente: " << nomeCliente[indice] << endl;
                    cout << "CPF: " << cpf[indice] << endl;
                    cout << "Tipo: " << tipoConta[indice] << endl;
                    cout << "Saldo: R$ " << saldo[indice] << endl;
                    if (contaAtiva[indice]) {
                        cout << "Situacao: ativa" << endl;
                    } else {
                        cout << "Situacao: inativa" << endl;
                    }
                }
                break;
 
            case 4:
                cout << "Numero da conta: ";
                cin >> numero;
                cout << "Valor do deposito: R$ ";
                cin >> valor;
                indice = -1;
                // de novo o laço pra encontrar essa conta
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }
                // se nao encontrou volta pro menu
                if (indice == -1 || !contaAtiva[indice]) {
                    cout << "Conta nao encontrada ou inativa!" << endl;
                // se colocou um saldo negativo pra depositar tambem cancela
                } else if (valor <= 0) {
                    cout << "Valor invalido!" << endl;
                // movimentou demais tambem cancela
                } else if (quantidadeMovimentacoes == MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!" << endl;
                } else {
                    // se deu tudo certo vai simplesmente adicionar o valor ao saldo
                    // tambem vai acrescentar ao numero de movimentações
                    // tudo usando o indice da conta encontrada
                    saldo[indice] = saldo[indice] + valor;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Deposito realizado!" << endl;
                }
                break;
 
            case 5:
                cout << "Numero da conta: ";
                cin >> numero;
                cout << "Valor do saque: R$ ";
                cin >> valor;
                indice = -1;
                // aqui é um processo bem parecido com sacar, primeiro vai encontrar a conta
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }
                if (indice == -1 || !contaAtiva[indice]) {
                    cout << "Conta nao encontrada ou inativa!" << endl;
                } else if (valor <= 0) {
                    cout << "Valor invalido!" << endl;
                // encontrou foi valido igual sacar
                // o que muda agora é que precisa conferir se tem o valor pra sacar
                } else if (valor > saldo[indice]) {
                    cout << "Saldo insuficiente!" << endl;
                } else if (quantidadeMovimentacoes == MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!" << endl;
                } else {
                    // conferiu deu tudo certo agora so vai subtrari do valor
                    // tambem aumentar as movimentações 
                    saldo[indice] = saldo[indice] - valor;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Saque realizado!" << endl;
                }
                break;
 
            case 6:
                cout << "Numero da conta de origem: ";
                cin >> numero;
                cout << "Numero da conta de destino: ";
                cin >> numeroDestino;
                cout << "Valor da transferencia: R$ ";
                cin >> valor;
                indice = -1;
                indiceDestino = -1;
                // parecido com os processos anteriores 
                // so que aqui vai conferir as duas contas que vai participar da transferencia
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                    if (numeroConta[i] == numeroDestino) {
                        indiceDestino = i;
                    }
                }
                if (indice == -1 || indiceDestino == -1) {
                    cout << "Conta de origem ou de destino nao encontrada!" << endl;
                } else if (!contaAtiva[indice] || !contaAtiva[indiceDestino]) {
                    cout << "Conta de origem ou de destino inativa!" << endl;
                } else if (valor <= 0) {
                    cout << "Valor invalido!" << endl;
                } else if (valor > saldo[indice]) {
                    cout << "Saldo insuficiente!" << endl;
                
                } else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!" << endl;
                // conferiu se todas condições tao certas ai continua
                // agora so vai subtrair de quem deu e aumentar quem recebeu
                // alem de aumentar a movimentação e registrar o tipo
                } else {
                    saldo[indice] = saldo[indice] - valor;
                    saldo[indiceDestino] = saldo[indiceDestino] + valor;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                    tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                    valorMovimentacao[quantidadeMovimentacoes] = valor;
                    quantidadeMovimentacoes++;
                    cout << "Transferencia realizada!" << endl;
                }
                break;
 
            case 7:
            // aqui é o mais simples, primeiro encontrar a conta
                cout << "Numero da conta: ";
                cin >> numero;
                indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numero) {
                        indice = i;
                    }
                }
                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else {
                    // aqui vai mostrar o extrato da conta encontrada
                    cout << "\n--- EXTRATO DA CONTA " << numero << " ---\n";
                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        // o laço vai mostrar o valor e o tipo de todas que teve
                        if (contaMovimentacao[i] == numero) {
                            if (tipoMovimentacao[i] == 'D') {
                                cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                            } else if (tipoMovimentacao[i] == 'S') {
                                cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                            }
                        }
                    }
                }
                break;
                // default basico 
            default:
                cout << "Opcao invalida!" << endl;
        }
        // while classico do menu pra fechar o codigo 
    } while (opcao != 0);
 
    return 0;
}