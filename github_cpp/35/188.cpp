#include <iostream>
#include <string.h>

using namespace std;

int main(){

    setlocale(LC_ALL, "Portuguese");

    // Cria estrutura 'Pessoas'
    struct Pessoas {
        char Nome[60];
        int Idade;
        Pessoas *Proximo;
    };

    // Cria ponteiro 'ptr_alunos' e aloca 10 espaços na memória
    Pessoas *ptr_aluno = new Pessoas[10];

    // Cria ponteiro auxiliar, que irá passear pelos itens na memória
    Pessoas *ptr_aux = new Pessoas;


    int x = 0;
    char nome[60];

    // Prenchendo o vetor com dados do usuário
    while(nome[0] != '!' && x < 10){
        cout << "\nDigite o nome: ";
        cin.getline(nome, 60);
        if (nome[0] != '!'){
            strcpy(ptr_aluno[x].Nome, nome);
            ptr_aluno[x].Idade = 18+x;
            ptr_aluno[x].Proximo = NULL;

            // Aribui ao item anterior, caso exista, o endereço de meḿoria do item atual
            // criando então um vinculo/ligacao (link) entre eles
            if (x > 0){
                ptr_aluno[x-1].Proximo = &ptr_aluno[x];
            }
            x++;
        }
    };

    // Posiciona o ptr_aux no endereço de memória onde está o primeio item
    ptr_aux = &ptr_aluno[0];

    cout << "\n\nApresentando os dados: ------------- \n";

    // Se o item existir na memória
    while(ptr_aux != NULL ){

        // Exibe os dados do item que está no endereço de memória atual
        cout << "\nNome: " << ptr_aux->Nome;
        cout << "\nIdade: " << ptr_aux->Idade;
        cout << "\nEndereco: " << &ptr_aux;
        cout << "\nProximo Endereco: " << ptr_aux->Proximo;
        cout << endl << "-----" << endl;

        // Verifica e posiciona no endereço de memória do próximo item
        ptr_aux = ptr_aux->Proximo;
    }

    cout << endl << endl;

    return 0;
}
