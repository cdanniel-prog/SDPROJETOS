#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estruturas para armazenar informações do usuário
typedef struct {
    char email[80];
    char senha[20];
} Usuario;

// Estrutura para armazenar informações do banco
typedef struct {
    Usuario *usuarios;
    int totalUsuarios;
} Banco;

// Função para exibir mensagem de boas-vindas
void exibirBoasVindas() {
    printf(" =================================\n");
    printf(" Bem-vindo ao Banco Digital CDBank\n");
    printf(" =================================\n");
}

// Função para criar um novo banco
Banco* criarBanco() {
    Banco *banco = (Banco*)malloc(sizeof(Banco));
    banco->usuarios = NULL;
    banco->totalUsuarios = 0;
    return banco;
}

// Função para validar o email
int validarEmail(Banco *banco, const char *email) {
    // Verifica se o email já está cadastrado
    for (int i = 0; i < banco->totalUsuarios; i++) {
        if (strcmp(banco->usuarios[i].email, email) == 0) {
            printf("Erro: Email já cadastrado!\n");
            return 0;
        }
    }
    // Verifica se o email contém '@'
    if (strchr(email, '@') == NULL) {
        printf("Erro: Email inválido, deve conter '@'!\n");
        return 0;
    }
    return 1;
}

// Função para cadastrar um novo usuário
void cadastrarUsuario(Banco *banco) {
    Usuario novoUsuario;

    // Solicitar e validar o email
    do {
        printf("Digite seu email: ");
        scanf("%s", novoUsuario.email);
    } while (!validarEmail(banco, novoUsuario.email));

    // Solicitar a senha
    printf("Digite sua senha: ");
    scanf("%s", novoUsuario.senha);

    // Adicionar o novo usuário ao banco
    banco->totalUsuarios++;
    banco->usuarios = (Usuario*)realloc(banco->usuarios, banco->totalUsuarios * sizeof(Usuario));
    banco->usuarios[banco->totalUsuarios - 1] = novoUsuario;
    printf("Usuário cadastrado com sucesso!\n\n");
}

// Função para listar todos os usuários cadastrados
void listarUsuarios(Banco *banco) {
    printf("Usuários cadastrados:\n");
    for (int i = 0; i < banco->totalUsuarios; i++) {
        printf("%d. %s\n", i + 1, banco->usuarios[i].email);
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
    if (indice >= 0 && indice < banco->totalUsuarios) {
        printf("Digite o novo email: ");
        scanf("%s", banco->usuarios[indice].email);
        printf("Digite a nova senha: ");
        scanf("%s", banco->usuarios[indice].senha);
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
    if (indice >= 0 && indice < banco->totalUsuarios) {
        for (int i = indice; i < banco->totalUsuarios - 1; i++) {
            banco->usuarios[i] = banco->usuarios[i + 1];
        }
        banco->totalUsuarios--;
        banco->usuarios = (Usuario*)realloc(banco->usuarios, banco->totalUsuarios * sizeof(Usuario));
        printf("Usuário excluído com sucesso!\n\n");
    } else {
        printf("Erro: Índice inválido!\n\n");
    }
}

// Função para autenticar o usuário
void autenticarUsuario(Banco *banco) {
    char email[80];
    char senha[20];
    int autenticado = 0;
    while (!autenticado) {
        printf("Digite seu email: ");
        scanf("%s", email);
        printf("Digite sua senha: ");
        scanf("%s", senha);
        
        for (int i = 0; i < banco->totalUsuarios; i++) {
            if (strcmp(banco->usuarios[i].email, email) == 0 && strcmp(banco->usuarios[i].senha, senha) == 0) {
                printf("Autenticado com sucesso!\n\n");
                autenticado = 1;
                break;
            }
        }
        if (!autenticado) {
            printf("Email ou senha incorretos! Tente novamente.\n\n");
        }
    }
}

// Função principal para exibir o menu e gerenciar o fluxo do programa
void menu(Banco *banco) {
    int opcao;
    do {
        printf("1. Cadastrar Usuário\n");
        printf("2. Listar Usuários\n");
        printf("3. Editar Usuário\n");
        printf("4. Excluir Usuário\n");
        printf("5. Autenticar Usuário\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario(banco);
                break;
            case 2:
                listarUsuarios(banco);
                break;
            case 3:
                editarUsuario(banco);
                break;
            case 4:
                excluirUsuario(banco);
                break;
            case 5:
                autenticarUsuario(banco);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");
    exibirBoasVindas();

    Banco *banco = criarBanco();
    menu(banco);

    free(banco->usuarios);
    free(banco);
    return 0;
}
