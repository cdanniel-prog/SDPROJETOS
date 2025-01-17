#include<locale.h>
#include<string.h>
#include<conio.h> 

#ifndef BANCO_H
#define BANCO_H
#include "banco.h"

#define QUANTIDADE_USUARIOS 50

#ifndef USUARIO_H
#define USUARIO_H
#include<stdio.h>
#include<stdlib.h>

//Estruturas para armazenas informa��es do usu�rio
typedef struct {
    char nome[50];      
    char email[80];     
    char senha[20];
    float saldo;
} Usuario;

int validarEmail(Banco *banco, const char *email, int indiceUsuarioAtual);
void capturarSenha(char *senha);
void verificarSaldo(Banco *banco, int usuarioID);
void realizarDeposito(Banco *banco, int usuarioID);
void realizarSaque(Banco *banco, int usuarioID);
void alterarSenha(Banco *banco, int usuarioID);
void realizarTransferencia(Banco *banco, int usuarioID);

#endif

//Estrutura para informa��es do banco
typedef struct {
    Usuario *usuarios[QUANTIDADE_USUARIOS];
    int totalUsuarios;
} Banco;

Banco* criarBanco();
void carregarUsuarios(Banco *banco, const char *nomeArquivo);
void salvarUsuarios(Banco *banco, const char *nomeArquivo);
void listarUsuarios(Banco *banco);
void acessarMenuCadastrado(Banco *banco, int usuarioID);
void menuNaoCadastrado(Banco *banco);
void sair(Banco *banco);
void buscarUsuarioPorEmailComQuicksort(Banco *banco);

#endif

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "usuario.h"

void quicksortUsuariosPorEmail(Usuario *usuarios[], int baixo, int alto);
int buscaBinariaRecursiva(Banco *banco, const char *email, int inicio, int fim);

#endif

Banco* criarBanco();
void encerrarPrograma();
void listarUsuarios(Banco *banco);
void sair(Banco *banco);

//Declara��es das Fun��es 
void acessarMenuCadastrado(Banco *banco, int usuarioID); //Declara��o da fun��o menuUsuario
void menuNaoCadastrado(Banco *banco); //Declara��o da fun��o menuNaoCadastrado
void menuUsuario(Banco *banco, int usuarioID); //Declara��o da fun��o acessarMenuCadastrado

//Fun��o para exibir mensagem de boas-vindas
void exibirBoasVindas(){
    printf(" =================================\n");
    printf(" Bem-vindo ao Banco Digital CDBank\n");
    printf(" =================================\n");
}

//Fun��o para encerrar o progrmama
void encerrarPrograma(){
    printf("\n===========================================\n");
    printf("Obrigado por utilizar o Banco Digital CDBank!\n");
    printf("Esperamos v�-lo novamente em breve.\n");
    printf("===============================================");
    exit(0);
}

//Func�o para carregar usu�rios
void carregarUsuarios(Banco *banco, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Erro ao abrir arquivo de usu�rios.\n");
        return;
    }

    while (!feof(arquivo)){
        Usuario *novoUsuario = (Usuario*) malloc(sizeof(Usuario));
        if (fscanf(arquivo, "%[^,],%[^,],%[^,],%f\n", novoUsuario->nome, novoUsuario->email, novoUsuario->senha, &novoUsuario->saldo) == 4){
            banco->usuarios[banco->totalUsuarios] = novoUsuario;
            banco->totalUsuarios++;
        } else{
            free(novoUsuario);
        }
    }
    fclose(arquivo);
}

//Fun��o para salvar o novo usu�rio no arquivo
    FILE *arquivo = fopen(nomeArquivo, "a");
    if(arquivo != NULL){
        fprintf(arquivo, "%s, %s, %s, %.2f\n", usuario->nome, usuario->email, usuario->senha, usuario->saldo);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo para salvar o novo usu�rio.\n");
    }
    printf("Cadastro realizado com sucesso!\n");


//Fun��o para Ordenar usu�rios por Email
void ordenarUsuarioPorEmail(Banco *banco){
    for (int i = 0; i < banco->totalUusuarios - 1; i++){
        for (int j = 0; j < banco->totalUsuarios - i - 1; j++){
            if (strcmp(banco->usuarios[j]->email, banco->usuarios[j + 1]->email) > 0){
                Usuario *temp = banco->usuarios[j];
                banco->usuarios[j] = banco->usuarios[j + 1];
                banco->usuarios[j + 1] = temp;
            }
        }
    }
}

//Fun��o de Busca Bin�ria Recursiva
int buscaBinariaRecursiva(Banco *banco, const char *email, int inicio, int fim){
    if (inicio > fim){
        return -1; //N�o encontrou usu�rio
    }

    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(banco->usuarios[meio]-> email, email);

    if(comparacao == 0) {
        return meio; //Encontrou usu�rio
    } else if (comparacao < 0){
        return buscaBinariaRecursiva(banco, email, meio + 1, fim); //Procura na metade direita
    } else {
        return buscaBinariaRecursiva(banco, email, inicio, meio -1); //Procura na metade esquerda
    }
}

//Fun��o para Buscar um usu�rio por Email
void buscarUsuarioPorEmailComQuicksort(Banco *banco){
    if (banco->totalUsuarios == 0){
        print("Nenhum usu�rio cadastrado.\n");
        return;
    } 

    quicksortUsuariosPorEmail(banco->usuarios, 0, banco->totalUsuarios - 1);

    char email[80];
    printf("Digite o email do usu�rio que deseja buscar: ");
    scanf("%s", email);

    int indice = buscaBinariaRecursiva(banco, email, 0, banco->totalUsuarios - 1);

    if(indice != -1){
        Usuario *usuario = banco->usuarios[indice];
        printf("Usu�rio encontrado:\n");
        printf("Nome: %s\nEmail: %s\nSaldo: R$%.2f\n", usuario->nome, usuario->email, usuario->saldo);
    } else {
        printf("Usu�rio com o email %s nao encontrado.\n", email);
    }
}

//Fun��o de troca
void trocar(Usuario **a, Usuario **b){
    Usuario *temp = *a;
    *a = *b;
    *b = temp;
}

//Particiona o array para o Quicksort
int particionar(Usuario *usuario[], int baixo, int alto){
    Usuario *pivo = usuarios[alto];
    int i = baixo - 1;

    for(int j = baixo; j < alto; j++){
        //Se o email do usu�rio atual for menor que o piv�
        if (strcmp(usuario[j]->email, pivo->email) < 0){
            i++;
            trocar(&usuarios[i], &usuarios[j]);
        }
    }
    trocar(&usuarios[i + 1], &usuarios[alto]);
    return i + 1;
} 

//Fun��o Quicksort Recursiva
void quicksortUsuarioPorEmail(Usuario *usuario[], int baixo, int alto){
    if(baixo < alto){
        int pi = particionar(usuarios, baixo, alto);

        quicksortUsuariosPorEmail(usuarios, baixo, pi - 1);
        quicksortUsuariosPorEmail(usuarios, pi + 1, alto);
    }
}

//Fun��o para criar um novo banco
Banco* criarBanco(){
    Banco *banco = (Banco*)malloc(sizeof(Banco));
    if(!banco){
        printf("Erro ao alocar mem�ria para o banco!\n");
        exit(1);
    }
    banco -> totalUsuarios = 0;
    return banco;
}

//Fun��o para validar o email
int validarEmail(Banco *banco, const char *email, int indiceUsuarioAtual){
    
    //Verifica se o email cont�m '@'
    if(strchr(email, '@') == NULL){
        printf("Erro: Email inv�lido, deve conter '@'!\n");
        return 0;
    }

    //Verifica se o email j� est� cadastrado, ignorando o pr�prio email do usu�rio atual
    for (int i = 0; i < banco -> totalUsuarios; i++){
        if (i != indiceUsuarioAtual && strcmp (banco -> usuarios[i]->email, email) == 0){
            printf("Erro: Email j� cadastrado!\n");
            return 0;
        }
    }
    return 1;
}

//Fun��o para capturar senha com asteriscos
void capturarSenha(char *senha){
    char ch;
    int i = 0;
    while(1){
        ch = getch();
        if(ch == 13){ 
            senha[i] = '\0';
            break;
        } else if(ch == 8){ 
            if(i > 0){
                i--;
                printf("\b \b");
            }
        } else if(i < 19){
            senha[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}

//Fun��o para cadastrar um novo usu�rio (salvando no arquivo)
void cadastrarUsuario(Banco *banco, const char *nomeArquivo){
    if(banco -> totalUsuarios >= QUANTIDADE_USUARIOS){
        printf("Erro: Limite de usu�rios alcan�ado!\n");
        return;
    }
    Usuario *novoUsuario = (Usuario*)malloc(sizeof(Usuario));
    if(!novoUsuario){
        printf("Erro ao alocar mem�ria para o novo usu�rio!\n");
        return;
    }
    novoUsuario->saldo = 0.0f;

    //Solicitar o nome do usu�rio
    printf("Digite seu nome: ");
    getchar(); 
    fgets(novoUsuario->nome, 50, stdin);
    novoUsuario->nome[strcspn(novoUsuario->nome, "\n")] = 0; 

    //Solicitar e validar o email
    do {
        printf("Digite seu email: ");
        scanf("%s", novoUsuario->email);
    } while (!validarEmail(banco, novoUsuario->email, -1)); 

    //Solicitar a senha
    printf("Digite sua senha: ");
    capturarSenha(novoUsuario->senha);

    //Adicionar o novo usu�rio ao banco e salvar no arquivo
    banco ->usuarios[banco->totalUsuarios] = novoUsuario;
    banco -> totalUsuarios++;
    salvarUsuarios(banco, nomeArquivo);
    printf("Usu�rio cadastrado com sucesso!\n\n");
    if(!banco -> usuarios){
        printf("Erro ao alocar mem�ria para os usu�rios!\n");
        exit(1);
    }
    banco -> usuarios[banco -> totalUsuarios - 1] = novoUsuario;
    printf("Usu�rio cadastrado com sucesso!\n\n");

    acessarMenuCadastrado(banco, banco -> totalUsuarios - 1);
    fprintf("registro.txt", "%s %s %s %.2f \n", novoUsuario->nome, novoUsuario->email, novoUsuario->senha, 0.0);
}

//Fun��o para listar todos os usu�rios cadastrados
void listarUsuarios(Banco *banco){
    if(banco->totalUsuarios == 0){
        printf("Nenhum usu�rio cadastrado.\n");
        return;
    }

    printf("Lista de usu�rios cadastrados:\n");
    for(int i = 0; i < banco->totalUsuarios; i++){
        Usuario *usuario = banco->usuarios[i];
        printf("%d. Nome: %s | Email: %s | Saldo: R$ %.2f\n", i + 1, usuario->nome, usuario->email, usuario->saldo);
    }
    printf("\n");
}

//Fun��o para editar um usu�rio
void editarUsuario(Banco *banco, const char *nomeArquivo){
    listarUsuarios(banco);
    int indice;
    printf("Selecione o n�mero do usu�rio que deseja editar: ");
    scanf("%d", &indice);
    indice--; 
    if(indice >= 0 && indice < banco -> totalUsuarios){
        Usuario *usuario = banco->usuarios[indice];
        printf("Digite o novo nome: ");
        getchar(); 
        fgets(banco -> usuarios[indice]->nome, 50, stdin);
        usuario->nome[strcspn(usuario->nome, "\n")] = 0;
        
        do{
            printf("Digite o novo email: ");
            scanf("%s", usuario->email);
        } while (!validarEmail(banco, usuario->email, indice));

        printf("Digite a nova senha: ");
        capturarSenha(usuario->senha);

        salvarUsuarios(banco, nomeArquivo);
        printf("Usu�rio editado com sucesso!\n\n");
    } else {
        printf("Erro: �ndice inv�lido!\n\n");
    }
}
    
//Fun��o para excluir um usu�rio
void excluirUsuario(Banco *banco const char *nomeArquivo){
    int indice;
    listarUsuarios(banco);
    printf("Selecione o n�mero do usu�rio que deseja excluir: ");
    scanf("%d", &indice);
    indice--; 
    
    if(indice >= 0 && indice < banco -> totalUsuarios){
        free(banco -> usuarios[indice]);
        
        for(int i = indice; i < banco -> totalUsuarios - 1; i++){
            banco -> usuarios[i] = banco -> usuarios[i + 1];
        }
        
        banco -> totalUsuarios--;
        salvarUsuarios(banco, nomeArquivo);
        printf("Usu�rio exclu�do com sucesso!\n\n");
    } else {
        printf("Erro: �ndice inv�lido!\n\n");
    }
}

//Fun��o para sair do local
void sair(Banco *banco){
    for(int i = 0; i < banco -> totalUsuarios; i++){
        free(banco -> usuarios);
    }
    free(banco);
    exit(0); 
}

//Fun��o para realizar login do usu�rio
int realizarLogin(Banco *banco) {
    char email[79];
    char senha[20];
    for (int tentativas = 3; tentativas > 0; tentativas--){
        printf("Digite seu email: ");
        scanf("%s", email);
        printf("Digite sua senha: ");
        capturarSenha(senha);
        for(int i = 0; i < banco -> totalUsuarios; i++){
            if(strcmp(banco -> usuarios[i]->email, email) == 0 && strcmp(banco -> usuarios[i]->senha, senha) == 0){
                printf("Login realizado com sucesso! Bem-vindo, %s!\n\n", banco -> usuarios[i]->nome);
                return i;
            }
        }
        printf("Email ou senha incorretos! Voc� tem %d tentativa(s) restante(s).\n\n", tentativas -1);
    }
    printf("Login falhou. Retornando ao menu principal.\n");
    return -1;
}

//Fun��o para acessar o menu de um usu�rio cadastrado
void acessarMenuCadastrado(Banco *banco, int usuarioID){
    menuUsuario(banco, usuarioID);
}

//Fun��o para solicitar um n�mero float
float solicitarValorPositivo(){
    float valor;
    int resultado;
    while(1){
        resultado = scanf("%f", &valor);
        if(resultado != 1 || valor <= 0){
            printf("Erro: Valor inv�lido! Insira um valor positivo.\n");
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            return valor;
        }
    }
}

//Fun��o para verificar o saldo
void verificarSaldo(Banco *banco, int usuarioID){
    printf("Seu saldo �: R$ %.2f\n\n", banco->usuarios[usuarioID]->saldo);
}

//Fun��o para realizar dep�sito
void realizarDeposito(Banco *banco, int usuarioID){
    printf("Digite o valor do dep�sito: R$ ");
    float valor = solicitarValorPositivo();
    banco -> usuarios[usuarioID]->saldo += valor;
    printf("Dep�sito de R$ %.2f realizado com sucesso!\n\n", valor);

}

//Fun��o para realizar saque
void realizarSaque(Banco *banco, int usuarioID){
    printf("Digite o valor do saque: R$ ");
    float valor = solicitarValorPositivo();
    if(valor <= banco -> usuarios[usuarioID]->saldo){
        banco -> usuarios[usuarioID]->saldo -= valor;
        printf("Saque de R$ %.2f realizado com sucesso!\n\n", valor);
    } else {
        printf("Saldo insuficiente!\n\n");
    }
}

//Fun��o para alterar senha
void alterarSenha(Banco *banco, int usuarioID){
    printf("Digite sua nova senha: ");
    capturarSenha(banco -> usuarios[usuarioID]->senha);
    printf("Senha alterada com sucesso!\n\n");
}

//Fun��o para transferir para outro usu�rio
void realizarTransferencia(Banco *banco, int usuarioID){
    int destinatarioID;
    listarUsuarios(banco);
    printf("Selecione o n�mero do usu�rio para quem deseja transferir: ");
    scanf("%d", &destinatarioID);
    destinatarioID--; 
    if(destinatarioID >= 0 && destinatarioID < banco -> totalUsuarios && destinatarioID != usuarioID){     
        printf("Digite o valor da transfer�ncia: ");
        float valor = solicitarValorPositivo();
    if(valor <= banco -> usuarios[usuarioID]->saldo){
        banco -> usuarios[usuarioID]->saldo -=valor;
        banco -> usuarios[destinatarioID]->saldo += valor;
        printf("Transfer�ncia de R$ %.2f realizada com sucesso para %s!\n\n", valor, banco -> usuarios[destinatarioID]->email);
    } else{
        printf("Saldo Insuficiente!\n\n");
        }       
    } else{
        printf("Erro: Usu�rio inv�lido!\n\n");
    }
}

//Fun��o para solicitar apenas n�mero inteiro 
int solicitarOpcaoValida(int min, int max){
    int opcao;
    int resultado;
    while(1){
        resultado = scanf("%d", &opcao);
        if(resultado != 1 || opcao < min || opcao > max){
            printf("Erro: Op��o inv�lida! Insira um n�mero entre %d e %d.\n", min, max);
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            return opcao;
        }
    }
}

//Menu para usu�rios n�o cadastrados
void menuNaoCadastrado(Banco *banco){
    int opcao;
    while(1){
        printf("Menu Principal\n");
        printf("1. Cadastrar usu�rio\n");
        printf("2. Listar usu�rios\n");
        printf("3. Editar usu�rio\n");
        printf("4. Excluir usu�rio\n");
        printf("5. Tela Inicial\n");
        printf("6. Sair do Banco\n");
        printf("\nEscolha uma op��o: ");

        opcao = solicitarOpcaoValida(1, 6);

        switch (opcao){     
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
                return;
            case 6: 
                encerrarPrograma();
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } 
}


//Menu para usu�rios cadastrados
void menuUsuario(Banco *banco, int usuarioID){
    int opcao;
    while(1){
        printf("Menu do Usu�rio\n");
        printf("1. Verificar Saldo\n");
        printf("2. Realizar Dep�sito\n");
        printf("3. Realizar Saque\n");
        printf("4. Alterar Senha\n");
        printf("5. Realizar Transfer�ncias\n");
        printf("6. Acessar o Menu Principal\n");
        printf("\nEscolha uma op��o: ");

        opcao = solicitarOpcaoValida(1, 6);

        switch (opcao){
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
                return;
            default:
                printf("Op��o inv�lida! Tente novamente.\n\n");
        }
    } 
}

//Fun��o principal
int main(){
    setlocale(LC_ALL, "Portuguese");
    Banco *banco = criarBanco();
    const char *nomeArquivo = "usuarios.txt";

    //Carregar usu�rios do arquivo no in�cio
    carregarUsuarios(banco, nomeArquivo);

    exibirBoasVindas();
    int usuarioID;

    while (1){   
        printf("Voc� j� tem cadastro? (1 - Sim, 2 - N�o): ");
        int resposta;
        scanf("%d", &resposta);
        
        if(resposta == 1){
            usuarioID = realizarLogin(banco);
            if (usuarioID != -1){
                acessarMenuCadastrado(banco, usuarioID);
            } else {
                printf("login falhou. Tente novamente mais tarde.\n");
            }
        } else if(resposta == 2){
            menuNaoCadastrado(banco);
        } else {
            break;
        }
    }

    buscarUsuarioPorEmailComQuicksort(banco);

    //Salvar os dados ao sair
    salvarUsuarios(banco, nomeArquivo);
    sair(banco);

    return 0;
}