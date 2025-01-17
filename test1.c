#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h> // Biblioteca para usar getch()

// Estruturas para armazenar informações do usuário
typedef struct {
    char nome[50];
    char email[80];
    char senha[20];
    float saldo;
} Usuario;

// Estrutura para informações do banco
typedef struct {
    Usuario *usuarios;
    int totalUsuarios;
} Banco;

// Declarações das Funções
void acessarMenuCadastrado(Banco *banco, int usuarioID); // Declaração da função menuUsuario
void menuNaoCadastrado(Banco *banco); // Declaração da função menuNaoCadastrado
void menuUsuario(Banco *banco, int usuarioID); // Declaração da função acessarMenuCadastrado
void exibirBoasVindas();
Banco* criarBanco();
int validarEmail(Banco *banco, const char *email, int indiceUsuarioAtual);
void capturarSenha(char *senha);
void cadastrarUsuario(Banco *banco);
void listarUsuarios(Banco *banco);
void editarUsuario(Banco *banco);
void excluirUsuario(Banco *banco);
void sair(Banco *banco);
int realizarLogin(Banco *banco);
void verificarSaldo(Banco *banco, int usuarioID);
void realizarDeposito(Banco *banco, int usuarioID);
void realizarSaque(Banco *banco, int usuarioID);
void alterarSenha(Banco *banco, int usuarioID);
void realizarTransferencia(Banco *banco, int usuarioID);
void menuPrincipal(Banco *banco);

// Função para exibir mensagem de boas-vindas
void exibirBoasVindas() {
    printf(" =================================\n");
    printf(" Bem-vindo ao Banco Digital CDBank\n");
    printf(" =================================\n");
}

// Função para criar um novo banco
Banco* criarBanco() {
    Banco *banco = (Banco*)malloc(sizeof(Banco));
    if(!banco) {
        printf("Erro ao alocar memória para o banco!\n");
        exit(1);
    }
    banco -> usuarios = NULL;
    banco -> totalUsuarios = 0;
    return banco;
}

// Função para validar o email
int validarEmail(Banco *banco, const char *email, int indiceUsuarioAtual) {
    // Verifica se o email contém '@'
    if(strchr(email, '@') == NULL) {
        printf("Erro: Email inválido, deve conter '@'!\n");
        return 0;
    }

    // Verifica se o email já está cadastrado, ignorando o próprio email do usuário atual
    for (int i = 0; i < banco -> totalUsuarios; i++) {
        if (i != indiceUsuarioAtual && strcmp(banco -> usuarios[i].email, email) == 0) {
            printf("Erro: Email já cadastrado!\n");
            return 0;
        }
    }
    return 1;
}

// Função para capturar senha com asteriscos
void capturarSenha(char *senha) {
    char ch;
    int i = 0;
    while(1) {
        ch = getch();
        if(ch == 13) { // Enter (fim da senha)
            senha[i] = '\0';
            break;
        } else if(ch == 8) { // Backspace
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        } else if(i < 19) {
            senha[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}

// Função para cadastrar um novo usuário
void cadastrarUsuario(Banco *banco) {
    Usuario novoUsuario;
    novoUsuario.saldo = 0.0f;

    // Solicitar o nome do usuário
    printf("Digite seu nome: ");
    getchar(); // Limpar o buffer do teclado
    fgets(novoUsuario.nome, 50, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0; // Remover o '\n' do final da string

    // Solicitar e validar o email
    do {
        printf("Digite seu email: ");
        scanf("%s", novoUsuario.email);
    } while (!validarEmail(banco, novoUsuario.email, -1)); // Uso do -1 para indicar que é um novo usuário

    // Solicitar a senha
    printf("Digite sua senha: ");
    capturarSenha(novoUsuario.senha);

    // Adicionar o novo usuário ao banco
    banco -> totalUsuarios++;
    banco -> usuarios = (Usuario*)realloc(banco -> usuarios, banco -> totalUsuarios * sizeof(Usuario));
    if(!banco -> usuarios) {
        printf("Erro ao alocar memória para os usuários!\n");
        exit(1);
    }
    banco -> usuarios[banco -> totalUsuarios - 1] = novoUsuario;
    printf("Usuário cadastrado com sucesso!\n\n");

    menuPrincipal(banco);
}

// Função para listar todos os usuários cadastrados
void listarUsuarios(Banco *banco) {
    printf("Usuários cadastrados:\n");
    for (int i = 0; i < banco -> totalUsuarios; i++) {
        printf("%d. Nome: %s | Email: %s | Saldo: R$ %.2f\n", i + 1, banco -> usuarios[i].nome, banco -> usuarios[i].email, banco -> usuarios[i].saldo);
    }
    printf("\n");
}

// Função para editar um usuário
void editarUsuario(Banco *banco) {
    int indice;
    listarUsuarios(banco);
    printf("Selecione o número do usuário que deseja editar: ");
    scanf("%d", &indice);
    indice--; // Ajustar para índice baseado em zero
    if(indice >= 0 && indice < banco -> totalUsuarios) {
        printf("Digite o novo nome: ");
        getchar();
        fgets(banco -> usuarios[indice].nome, 50, stdin);
        banco -> usuarios[indice].nome[strcspn(banco -> usuarios[indice].nome, "\n")] = 0;

        do {
            printf("Digite o novo email: ");
            scanf("%s", banco -> usuarios[indice].email);
        } while (!validarEmail(banco, banco -> usuarios[indice].email, indice));

        printf("Digite a nova senha: ");
        capturarSenha(banco -> usuarios[indice].senha);

        printf("Usuário editado com sucesso!\n\n");
    } else {
        printf("Erro: Índice inválido!\n\n");
    }
}

// Função para excluir um usuário
void excluirUsuario(Banco *banco) {
    int indice;
    listarUsuarios(banco);
    printf("Selecione o número do usuário que deseja excluir: ");
    scanf("%d", &indice);
    indice--; // Ajustar para o índice baseado em zero
    if(indice >= 0 && indice < banco -> totalUsuarios) {
        for(int i = indice; i < banco -> totalUsuarios - 1; i++) {
            banco -> usuarios[i] = banco -> usuarios[i + 1];
        }
        banco -> totalUsuarios--;
        banco -> usuarios = (Usuario*)realloc(banco -> usuarios, banco -> totalUsuarios * sizeof(Usuario));
        if(banco -> totalUsuarios > 0 && !banco -> usuarios) {
            printf("Erro ao realocar memória!\n");
            exit(1);
        }
        printf("Usuário excluído com sucesso!\n\n");
    } else {
        printf("Erro: Índice inválido!\n\n");
    }
}

// Função para sair do programa e liberar a memória alocada
void sair(Banco *banco) {
    // Liberar a memória alocada para os usuários
    if(banco -> usuarios != NULL) {
        free(banco -> usuarios);
    }

    // Liberar a memória alocada para o banco
    free(banco);

    printf("Obrigado por utilizar o Banco Digital CDBank. Até logo!\n");
    exit(0); // Encerra o programa
}

// Função para realizar login do usuário
int realizarLogin(Banco *banco) {
    char email[80];
    char senha[20];

    for (int tentativas = 3; tentativas > 0; tentativas--) {
        printf("Digite seu email: ");
        scanf("%s", email);
        printf("Digite sua senha: ");
        capturarSenha(senha);

        for(int i = 0; i < banco -> totalUsuarios; i++) {
            if(strcmp(banco -> usuarios[i].email, email) == 0 && strcmp(banco -> usuarios[i].senha, senha) == 0) {
                printf("Login realizado com sucesso! Bem-vindo, %s!\n\n", banco -> usuarios[i].nome);
                return i;
            }
        }
        printf("Email ou senha incorretos! Você tem %d tentativa(s) restante(s).\n\n", tentativas - 1);
    }
    return -1;
}

// Função para mostrar o menu de usuário
void menuUsuario(Banco *banco, int usuarioID) {
    int opcao;
    do {
        printf("Menu de Usuário:\n");
        printf("1. Verificar Saldo\n");
        printf("2. Realizar Depósito\n");
        printf("3. Realizar Saque\n");
        printf("4. Alterar Senha\n");
        printf("5. Realizar Transferência\n");
        printf("6. Sair para o Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                verificarSaldo(banco, usuarioID);
                break;
            case 2:
                realizarDeposito(banco, usuarioID);
                break;
            case 3:
                realizarSaque(banco, usuarioID);
                break;
            case 4:
                alterarSenha(banco, usuarioID);
                break;
            case 5:
                realizarTransferencia(banco, usuarioID);
                break;
            case 6:
                menuPrincipal(banco);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while(opcao != 6);
}

// Função para verificar o saldo do usuário
void verificarSaldo(Banco *banco, int usuarioID) {
    printf("Seu saldo atual é: R$ %.2f\n\n", banco -> usuarios[usuarioID].saldo);
}

// Função para realizar depósito
void realizarDeposito(Banco *banco, int usuarioID) {
    float valor;
    printf("Digite o valor do depósito: ");
    scanf("%f", &valor);
    if(valor > 0) {
        banco -> usuarios[usuarioID].saldo += valor;
        printf("Depósito realizado com sucesso! Novo saldo: R$ %.2f\n\n", banco -> usuarios[usuarioID].saldo);
    } else {
        printf("Valor inválido! O depósito deve ser maior que zero.\n\n");
    }
}

// Função para realizar saque
void realizarSaque(Banco *banco, int usuarioID) {
    float valor;
    printf("Digite o valor do saque: ");
    scanf("%f", &valor);
    if(valor > 0 && valor <= banco -> usuarios[usuarioID].saldo) {
        banco -> usuarios[usuarioID].saldo -= valor;
        printf("Saque realizado com sucesso! Novo saldo: R$ %.2f\n\n", banco -> usuarios[usuarioID].saldo);
    } else {
        printf("Valor inválido ou saldo insuficiente!\n\n");
    }
}

// Função para alterar a senha
void alterarSenha(Banco *banco, int usuarioID) {
    char novaSenha[20];
    printf("Digite a nova senha: ");
    capturarSenha(novaSenha);
    strcpy(banco -> usuarios[usuarioID].senha, novaSenha);
    printf("Senha alterada com sucesso!\n\n");
}

// Função para realizar transferência
void realizarTransferencia(Banco *banco, int usuarioID) {
    int destinatarioID;
    float valor;

    listarUsuarios(banco);
    printf("Selecione o número do usuário para transferir: ");
    scanf("%d", &destinatarioID);
    destinatarioID--; // Ajustar para o índice baseado em zero

    if(destinatarioID >= 0 && destinatarioID < banco -> totalUsuarios && destinatarioID != usuarioID) {
        printf("Digite o valor da transferência: ");
        scanf("%f", &valor);

        if(valor > 0 && valor <= banco -> usuarios[usuarioID].saldo) {
            banco -> usuarios[usuarioID].saldo -= valor;
            banco -> usuarios[destinatarioID].saldo += valor;
            printf("Transferência realizada com sucesso! Novo saldo: R$ %.2f\n\n", banco -> usuarios[usuarioID].saldo);
        } else {
            printf("Valor inválido ou saldo insuficiente!\n\n");
        }
    } else {
        printf("Destinatário inválido!\n\n");
    }
}

// Função para o menu quando não cadastrado
void menuNaoCadastrado(Banco *banco) {
    int opcao;
    do {
        printf("Menu Não Cadastrado:\n");
        printf("1. Cadastrar Usuário\n");
        printf("2. Listar Usuários\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarUsuario(banco);
                break;
            case 2:
                listarUsuarios(banco);
                break;
            case 3:
                sair(banco);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while(opcao != 3);
}

// Função para o menu principal
void menuPrincipal(Banco *banco) {
    int opcao;
    do {
        printf("Você já tem cadastro? (1 - Sim, 2 - Não): ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            int usuarioID = realizarLogin(banco);
            if(usuarioID != -1) {
                menuUsuario(banco, usuarioID);
            } else {   
                printf("Login falhou. Tente novamente mais tarde.\n");
                sair(banco);
            }
        } else if(opcao == 2) {
            menuNaoCadastrado(banco);
        } else {
            printf("Opção inválida!\n");    
        }
    } while(opcao != 3);
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    Banco *banco = criarBanco();
    menuPrincipal(banco);
    return 0;
}
