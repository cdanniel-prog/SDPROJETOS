#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<conio.h> //Biblioteca para usar getch()

//Estruturas para armazenas informa��es do usu�rio
typedef struct {
    char nome[50];
    char email[80];
    char senha[20];
    float saldo;
} Usuario;

//Estrutura para informa��es do banco
typedef struct {
    Usuario *usuarios;
    int totalUsuarios;
} Banco;

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

//Fun��o para criar um novo banco
Banco* criarBanco(){
    Banco *banco = (Banco*)malloc(sizeof(Banco));
    if(!banco){
        printf("Erro ao alocar mem�ria para o banco!\n");
        exit(1);
    }
    banco -> usuarios = NULL;
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
        if (i != indiceUsuarioAtual && strcmp (banco -> usuarios[i].email, email) == 0){
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
        if(ch == 13){ //Enter (fim da senha)
            senha[i] = '\0';
            break;
        } else if(ch == 8){ //Backspace
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

//Fun��o para cadastrar um novo usu�rio
void cadastrarUsuario(Banco *banco){
    Usuario novoUsuario;
    novoUsuario.saldo = 0.0f;

    //Solicitar o nome do usu�rio
    printf("Digite seu nome: ");
    getchar(); //Limpar o buffer do teclado
    fgets(novoUsuario.nome, 50, stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = 0; //Remover o '\n' do final da string

    //Solicitar e validar o email
    do {
        printf("Digite seu email: ");
        scanf("%s", novoUsuario.email);
    } while (!validarEmail(banco, novoUsuario.email, -1)); //Uso do -1 para indicar que � um novo usu�rio

    //Solicitar a senha
    printf("Digite sua senha: ");
    capturarSenha(novoUsuario.senha);

    //Adicionar o novo usu�rio ao banco
    banco -> totalUsuarios++;
    banco -> usuarios = (Usuario*)realloc(banco -> usuarios, banco -> totalUsuarios * sizeof(Usuario));
    if(!banco -> usuarios){
        printf("Erro ao alocar mem�ria para os usu�rios!\n");
        exit(1);
    }
    banco -> usuarios[banco -> totalUsuarios - 1] = novoUsuario;
    printf("Usu�rio cadastrado com sucesso!\n\n");

    acessarMenuCadastrado(banco, banco -> totalUsuarios - 1);
}

//Fun��o para listar todos os usu�rios cadastrados
void listarUsuarios(Banco *banco){
    printf("Usu�rios cadastrados:\n");
    for (int i = 0; i < banco -> totalUsuarios; i++){
        printf("%d. Nome: %s | Email: %s | Saldo: R$ %.2f\n", i + 1, banco -> usuarios[i].nome, banco -> usuarios[i].email, banco -> usuarios[i].saldo);
    }
    printf("\n");
}

//Fun��o para editar um usu�rio
void editarUsuario(Banco *banco){
    int indice;
    listarUsuarios(banco);
    printf("Selecione o n�mero do usu�rio que deseja editar: ");
    scanf("%d", &indice);
    indice--; //Ajustar para �ndice baseado em zero
    if(indice >= 0 && indice < banco -> totalUsuarios){
        printf("Digite o novo nome: ");
        getchar(); 
        fgets(banco -> usuarios[indice].nome, 50, stdin);
        banco -> usuarios[indice].nome[strcspn(banco -> usuarios[indice].nome, "\n")] = 0; 

        do{
            printf("Digite o novo email: ");
            scanf("%s", banco -> usuarios[indice].email);
        } while (!validarEmail(banco, banco -> usuarios[indice].email, indice));

        printf("Digite a nova senha: ");
        capturarSenha(banco -> usuarios[indice].senha);
       
        printf("Usu�rio editado com sucesso!\n\n");
    } else {
        printf("Erro: �ndice inv�lido!\n\n");
    }
}
    
//Fun��o para excluir um usu�rio
void excluirUsuario(Banco *banco){
    int indice;
    listarUsuarios(banco);
    printf("Selecione o n�mero do usu�rio que deseja excluir: ");
    scanf("%d", &indice);
    indice--; //Ajutar para o �ndice baseado em zero
    if(indice >= 0 && indice < banco -> totalUsuarios){
        for(int i = indice; i < banco -> totalUsuarios - 1; i++){
            banco -> usuarios[i] = banco -> usuarios[i + 1];
        }
        banco -> totalUsuarios--;
        banco -> usuarios = (Usuario*)realloc(banco -> usuarios, banco -> totalUsuarios * sizeof(Usuario));
        if(banco -> totalUsuarios > 0 && !banco -> usuarios){
            printf("Erro ao realocar mem�ria!\n");
            exit(1);
        }
        printf("Usu�rio exclu�do com sucesso!\n\n");
    } else {
        printf("Erro: �ndice inv�lido!\n\n");
    }
}

//Fun��o para sair do programa e liberar a mem�ria alocada
void sair(Banco *banco){
    //Liberar a mem�ria alocada para os usu�rios
    if(banco -> usuarios != NULL){
        free(banco -> usuarios);
    }

    //Liberar a mem�ria alocada para o banco
    free(banco);

    printf("Obrigado por utilizar o Banco Digital CDBank. At� logo!\n");
    exit(0); //Encerra o programa
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
            if(strcmp(banco -> usuarios[i].email, email) == 0 && strcmp(banco -> usuarios[i].senha, senha) == 0){
                printf("Login realizado com sucesso! Bem-vindo, %s!\n\n", banco -> usuarios[i].nome);
                return i;
            }
        }
        printf("Email ou senha incorretos! Voc� tem %d tentativa(s) restante(s).\n\n", tentativas -1);
    }
    return -1;
}

//Fun��o para acessar o menu de um usu�rio cadastrado
void acessarMenuCadastrado(Banco *banco, int usuarioID){
    menuUsuario(banco, usuarioID);
}

//Fun��o para verificar o saldo
void verificarSaldo(Banco *banco, int usuarioID){
    printf("Seu saldo �: R$ %.2f\n\n", banco->usuarios[usuarioID].saldo);
}

//Fun��o para realizar dep�sito
void realizarDeposito(Banco *banco, int usuarioID){
    float valor;
    printf("Digite o valor do dep�sito: R$ ");
    scanf("%f", &valor);
    banco -> usuarios[usuarioID].saldo += valor;
    printf("Dep�sito de R$ %.2f realizado com sucesso!\n\n", valor);
}
//Fun��o para realizar saque
void realizarSaque(Banco *banco, int usuarioID){
    float valor;
    printf("Digite o valor do saque: R$ ");
    scanf("%f", &valor);
    if(valor <= banco -> usuarios[usuarioID].saldo){
        banco -> usuarios[usuarioID].saldo -= valor;
        printf("Saque de R$ %.2f realizado com sucesso!\n\n", valor);
    } else {
        printf("Saldo insuficiente!\n\n");
    }
}

//Fun��o para alterar senha
void alterarSenha(Banco *banco, int usuarioID){
    printf("Digite sua nova senha: ");
    capturarSenha(banco -> usuarios[usuarioID].senha);
    printf("Senha alterada com sucesso!\n\n");
}

//Fun��o para transferir para outro usu�rio
void realizarTransferencia(Banco *banco, int usuarioID){
    int destinatarioID;
    float valor;
    listarUsuarios(banco);
    printf("Selecione o n�mero do usu�rio para quem deseja transferir: ");
    scanf("%d", &destinatarioID);
    destinatarioID--;
    if(destinatarioID >= 0 && destinatarioID < banco -> totalUsuarios && destinatarioID != usuarioID){
        printf("Digite o valor da transfer�ncia: R$ ");
        scanf("%f", &valor);
        if(valor <= banco -> usuarios[usuarioID].saldo){
            banco -> usuarios[usuarioID].saldo -=valor;
            banco -> usuarios[destinatarioID].saldo += valor;
            printf("Transfer�ncia de R$ %.2f realizada com sucesso para %s!\n\n", valor, banco -> usuarios[destinatarioID].email);
        } else{
            printf("Saldo Insuficiente!\n\n");
        }
    } else{
        printf("Erro: Usu�rio inv�lido!\n\n");
    }
}

//Menu para usu�rios n�o cadastrados
void menuNaoCadastrado(Banco *banco){
    int opcao;
    while(1){
        printf("Menu Principal\n");
        printf("1. Cadastrar usu�rio\n");
        printf("2. Listar usu�rios\n");
        printf("3.Editar usu�rio\n");
        printf("4. Excluir usu�rio\n");
        printf("5. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);
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
                sair(banco);
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
        printf("6. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

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
                sair(banco);
                break;
            default:
                printf("Op��o inv�lida! Tente novamente.\n\n");
        }
    } 
}

//Fun��o principal
int main(){
    setlocale(LC_ALL, "Portuguese");
    Banco *banco = criarBanco();
    int usuarioID;

    exibirBoasVindas();

    printf("Voc� j� tem cadastro? (1 - Sim, 2 - N�o): ");
    int resposta;
    scanf("%d", &resposta);
    if(resposta == 1){
        usuarioID = realizarLogin(banco);
        if (usuarioID != -1){
            acessarMenuCadastrado(banco, usuarioID);
        } else {
            printf("login falhou. Tente novamente mais tarde.\n");
            sair(banco);
        }
    } else if(resposta == 2){
        menuNaoCadastrado(banco);
    } else {
        printf("Op��o inv�lida!\n");
        sair(banco);
    }
    return 0;
}
