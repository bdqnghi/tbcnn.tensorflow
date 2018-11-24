#include "hmm.h"

HMM::HMM( string atributoBase )
{
    this->atributoBase = atributoBase;
}

HMM::~HMM()
{
    //dtor
}

Classificador *HMM::executarTreinamento( Corpus &corpus, int atributo )
{
    int atributo_base;
    if( ( atributo_base = corpus.pegarPosAtributo( atributoBase ) ) == -1 )
    {
        cout << "Erro: executarTreinamento!\nAtributo inexistente!" << endl;
        return NULL;
    }

    map< string, double > vetInicial;
    map< string, map< string, double > > matrizTransicao;
    map< string, map< string, double > > tabFreqObservacoes;
    int row = corpus.pegarQtdSentencas(), column, i, j;
    double total = 0.0;

    if ( atributo <= 0 || atributo >= ( int )corpus.pegarQtdAtributos() )
    {
        cout << "Erro:executarTreinamento!\nAtributo inexistente!" << endl;
    	return NULL;
    }

    for ( i = 0; i < row; ++i )
    {
        column = corpus.pegarQtdTokens( i );

        ++tabFreqObservacoes[corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo_base))];
        ++vetInicial[corpus.pegarSimbolo(corpus.pegarValor(i,0,atributo))];
        if( column != 1 )
        {
            for ( j = 1; j < (column - 1); ++j )
            {
                ++tabFreqObservacoes[corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo_base))];
                ++matrizTransicao[corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,j+1,atributo))];
            }
            ++tabFreqObservacoes[corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo))][corpus.pegarSimbolo(corpus.pegarValor(i,j,atributo_base))];
        }
    }

    ///Verificar depois at� onde o double mantem a precis�o
    map< string, map< string, double > >::iterator linha, linha_end;
    map< string, double >:: iterator coluna, coluna_end;
    //faz convers�o para matriz de probabilidades
    linha_end = matrizTransicao.end();
    for( linha = matrizTransicao.begin();  linha != linha_end; ++linha )
    {
        coluna_end = linha->second.end();
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            total += coluna->second;
        for( coluna = linha->second.begin(); coluna != coluna_end; ++coluna )
            matrizTransicao[linha->first][coluna->first] = ( coluna->second )/total; //pode haver um erro carregado aqui
        total = 0.0;
    }

    //A principio n�o precisa de Unknown, sera utilizado a melhor sequencia de estados
    //cout << "A, B e Pi criados" << endl;
    return new ClassificadorHMM( atributoBase, vetInicial, matrizTransicao, tabFreqObservacoes );
}
