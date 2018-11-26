#include "ReverseTraduction.hpp"

using namespace std;

ReverseTraduction::ReverseTraduction() : QThread()
{
	loadReverseTrad();
}

ReverseTraduction::~ReverseTraduction()
{
}

/* \brief chargement du tableau des conversion
 * */
void ReverseTraduction::loadReverseTrad()
{
	_reverseTraducter.insert(pair<string, string>("PHE","TTT"));
	_reverseTraducter.insert(pair<string, string>("PHE","TTC"));
	_reverseTraducter.insert(pair<string, string>("LEU","TTA"));
	_reverseTraducter.insert(pair<string, string>("LEU","TTG"));
	_reverseTraducter.insert(pair<string, string>("SER","TCT"));
	_reverseTraducter.insert(pair<string, string>("SER","TCC"));
	_reverseTraducter.insert(pair<string, string>("SER","TCA"));
	_reverseTraducter.insert(pair<string, string>("SER","TCG"));
	_reverseTraducter.insert(pair<string, string>("TYR","TAT"));
	_reverseTraducter.insert(pair<string, string>("TYR","TAC"));
	_reverseTraducter.insert(pair<string, string>("STOP","TAA"));
	_reverseTraducter.insert(pair<string, string>("STOP","TAG"));
	_reverseTraducter.insert(pair<string, string>("CYS","TGT"));
	_reverseTraducter.insert(pair<string, string>("CYS","TGC"));
	_reverseTraducter.insert(pair<string, string>("STOP","TGA"));
	_reverseTraducter.insert(pair<string, string>("TRP","TGG"));
	
	_reverseTraducter.insert(pair<string, string>("LEU","CTT"));
	_reverseTraducter.insert(pair<string, string>("LEU","CTC"));
	_reverseTraducter.insert(pair<string, string>("LEU","CTA"));
	_reverseTraducter.insert(pair<string, string>("LEU","CTG"));
	_reverseTraducter.insert(pair<string, string>("PRO","CCT"));
	_reverseTraducter.insert(pair<string, string>("PRO","CCC"));
	_reverseTraducter.insert(pair<string, string>("PRO","CCA"));
	_reverseTraducter.insert(pair<string, string>("PRO","CCG"));
	_reverseTraducter.insert(pair<string, string>("HIS","CAT"));
	_reverseTraducter.insert(pair<string, string>("HIS","CAC"));
	_reverseTraducter.insert(pair<string, string>("GLN","CAA"));
	_reverseTraducter.insert(pair<string, string>("GLN","CAG"));
	_reverseTraducter.insert(pair<string, string>("ARG","CGT"));
	_reverseTraducter.insert(pair<string, string>("ARG","CGC"));
	_reverseTraducter.insert(pair<string, string>("ARG","CGA"));
	_reverseTraducter.insert(pair<string, string>("ARG","CGG"));

	_reverseTraducter.insert(pair<string, string>("ILE","ATT"));
	_reverseTraducter.insert(pair<string, string>("ILE","ATC"));
	_reverseTraducter.insert(pair<string, string>("ILE","ATA"));
	_reverseTraducter.insert(pair<string, string>("MET","ATG"));
	_reverseTraducter.insert(pair<string, string>("THR","ACT"));
	_reverseTraducter.insert(pair<string, string>("THR","ACC"));
	_reverseTraducter.insert(pair<string, string>("THR","ACA"));
	_reverseTraducter.insert(pair<string, string>("THR","ACG"));
	_reverseTraducter.insert(pair<string, string>("ASN","AAT"));
	_reverseTraducter.insert(pair<string, string>("ASN","AAC"));
	_reverseTraducter.insert(pair<string, string>("LYS","AAA"));
	_reverseTraducter.insert(pair<string, string>("LYS","AAG"));
	_reverseTraducter.insert(pair<string, string>("SER","AGT"));
	_reverseTraducter.insert(pair<string, string>("SER","AGC"));
	_reverseTraducter.insert(pair<string, string>("ARG","AGA"));
	_reverseTraducter.insert(pair<string, string>("ARG","AGG"));

	_reverseTraducter.insert(pair<string, string>("VAL","GTT"));
	_reverseTraducter.insert(pair<string, string>("VAL","GTC"));
	_reverseTraducter.insert(pair<string, string>("VAL","GTA"));
	_reverseTraducter.insert(pair<string, string>("VAL","GTG"));
	_reverseTraducter.insert(pair<string, string>("ALA","GCT"));
	_reverseTraducter.insert(pair<string, string>("ALA","GCC"));
	_reverseTraducter.insert(pair<string, string>("ALA","GCA"));
	_reverseTraducter.insert(pair<string, string>("ALA","GCG"));
	_reverseTraducter.insert(pair<string, string>("ASP","GAT"));
	_reverseTraducter.insert(pair<string, string>("ASP","GAC"));
	_reverseTraducter.insert(pair<string, string>("GLU","GAA"));
	_reverseTraducter.insert(pair<string, string>("GLU","GAG"));
	_reverseTraducter.insert(pair<string, string>("GLY","GGT"));
	_reverseTraducter.insert(pair<string, string>("GLY","GGC"));
	_reverseTraducter.insert(pair<string, string>("GLY","GGA"));
	_reverseTraducter.insert(pair<string, string>("GLY","GGG"));

}

void ReverseTraduction::loadFicAndTranslate(FileManager *file)
{
    QString chaine;
    if(file)
    {
        chaine=file->read();
        reverseTranslate(chaine.toStdString().c_str());
    }
}

void ReverseTraduction::reverseTranslate(const char * aa)
{
	int current=0;
	char c_tmp[6];

    _resultChains.clear();
    _tableCount.clear();
	
	while(aa[current] != '*')
	{
		if(aa[current]==' ') {++current;continue;}
	
		strncpy(c_tmp,aa+current,4);
		c_tmp[4]='\0';
		string tmp(c_tmp);
		
		if(tmp == "STOP")
			current+=4;
		else
		{
			strncpy(c_tmp,aa+current,3);
			c_tmp[3]='\0';
			tmp=string(c_tmp);
			current+=3;
		}
		
		multimap<string,string>::iterator it=_reverseTraducter.find(tmp);
		vector<string> tmpVect;
		
		for(;it != _reverseTraducter.end() && strcmp(it->first.c_str(),c_tmp) == 0;++it)
		{
			tmpVect.push_back(it->second);
		}
		
		_resultChains.push_back(tmpVect);
	}
}

void ReverseTraduction::parcours(FileManager * file)
{
    QString ss;
    unsigned long counter=1;

    if(file)
        emit consoleChanged("Ouverture des fichiers<BR/>");
    for(int i=0;i<_resultChains.size();++i)
        _tableCount.push_back(0);
    emit consoleChanged("Parcours en cours...<BR/>");
    do
    {
        for(int i=0;i<_resultChains.size();i++)
            ss.append((_resultChains[i][_tableCount[i]]).c_str());

        ss.append("*");
        if(file)
            file->write(ss);
        else
        {
            ss.append("<BR/>");
            emit chainDecrypted(ss);
        }
        ss.clear();

    }while(!incremente());

    emit consoleChanged("Fin de parcours");
    if(file)
        emit consoleChanged("Fermeture des fichiers<BR/>");

}

/* Renvoie true si fin
 * */
bool ReverseTraduction::incremente()
{
	bool ret=true;
	int j=_resultChains.size()-1;
	
	while(_tableCount[j] == _resultChains[j].size()-1)
	{
		_tableCount[j]=0;
		--j;
	}
	if(j >= 0)
	{
		ret=false;
		++_tableCount[j];
	}
	
	return ret;
}

void ReverseTraduction::displayChains()
{
	long nbPoss=1;
	for(vector< vector<string> >::iterator it=_resultChains.begin();it != _resultChains.end();++it)
	{	
		nbPoss*=it->size();
		for(vector<string>::iterator iit=it->begin();iit != it->end();++iit)
		{
			cout << *iit << " / ";
		}
		cout << endl;
	}
	
	cout << endl << "Nb Chains: "<< nbPoss<<endl;
}

 void ReverseTraduction::start(ReverseMethod_t type,const char * param1,const char * fileName)
 {
     _type=type;
     _param1=QString(param1);
     _fileName=!fileName? QString() : QString(fileName);
     start(QThread::HighestPriority);
 }

void ReverseTraduction::run()
{
    emit startTimer();
    FileManager * file = NULL;

    switch(_type)
    {
    case reverseTranslateM:
        if(!_fileName.isEmpty())
            file= new FileManager(_fileName);
        reverseTranslate(_param1.toStdString().c_str());break;
    case loadFileAndTranslate:
        file= new FileManager(_param1,_fileName);
        loadFicAndTranslate(file);break;
    }

    parcours(file);

    emit stopTimer();
}
