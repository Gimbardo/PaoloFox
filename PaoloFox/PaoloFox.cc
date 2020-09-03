#include<iostream>
#include<fstream>
#include<time.h>
#include<string.h>
using namespace std;

//Variabili Globali tutte const, cambiabili in caso di problemi allargando il programma
//Se desiderassi cambiare il numel, mi basterebbe cambiarlo qua, e non dovrei cercare ogni
//"3" presente nel programma
const int lungwho=30, lungwhat=40, lungwhy=40, lungall=110;
const int numel=3;
const char FilePezzi[] = "ElencoPezzi.txt";
const char FilePreferiti[] = "FrasiPreferite.txt";

struct pezzi //struttura usata per immagazzinare una terna di possibili valori
{
	char who[lungwho];
	char what[lungwhat];
	char why[lungwhy];
};

struct sfrasi
{
	char frase[lungall];
};
int PaoloFox(int n,int t)//Genera valori casuali con n massimo, e cambia il valore se 									cambia t. t è inserito per evitare che i numel (standard 3) 								valori inseriti non siano tutti e tre uguali, dato che chiamati 							nello stesso secondo (per maggiori info vedere il funzionamento 							della funzione srand, e della funzione time
{
	srand(time(0)+t);
	return (rand()%n);
}

pezzi* Riempimento(int &n) //Primo elemento del file txt: numero di elementi della struct
{
	ifstream f(FilePezzi);
	f>>n;
	pezzi* elenco = new pezzi[n];
	for(int i=0;i<n;i++)
	{
		f>>elenco[i].who;
		f>>elenco[i].what;
		f>>elenco[i].why;
	}
	f.close();
	return elenco;
}

void StampaBiscotto(pezzi* elenco,int indice[]) //Stampa Il Biscotto mettendo gli spazi 													prima delle Lettere Maiuscole
{
	for(int i=0;i<strlen(elenco[indice[0]].who);i++)
	{
		if(static_cast<int>(elenco[indice[0]].who[i])<=90&&static_cast<int>(elenco[indice[0]].who[i])>=65)
			cout<<" ";
		cout<<elenco[indice[0]].who[i];
	}
	for(int i=0;i<strlen(elenco[indice[1]].what);i++)
	{
		if(static_cast<int>(elenco[indice[1]].what[i])<=90&&static_cast<int>(elenco[indice[1]].what[i])>=65)
			cout<<" ";
		cout<<elenco[indice[1]].what[i];
	}
	for(int i=0;i<strlen(elenco[indice[2]].why);i++)
	{
		if(static_cast<int>(elenco[indice[2]].why[i])<=90&&static_cast<int>(elenco[indice[2]].why[i])>=65)
			cout<<" ";
		cout<<elenco[indice[2]].why[i];
	}
	cout<<"\n\n";
}
void NuovoBiscotto(pezzi* elenco,int indice[],int n)//Crea un nuovo biscotto, chiamando 															numel (standard 3) volte PaoloFox
{
	for(int i=0;i<numel;i++)
	{
		indice[i]=PaoloFox(n,i);
	}
}

void StampaFrasiRandom(sfrasi* copia,int n)//Stampa una frase random, e mette gli spazi 												prima dei caratteri maiuscoli
{
	for(int i=0;i<strlen(copia[n].frase);i++)
	{
		if(static_cast<int>(copia[n].frase[i])<=90&&static_cast<int>(copia[n].frase[i])>=65)
			cout<<" ";
		cout<<copia[n].frase[i];
	}
	cout<<"\n\n";
}
void CaricaPref(int &numpref,sfrasi* &copia)//Apre Il File DElle Frasi Preferite
{
	ifstream s(FilePreferiti);
	s>>numpref;
	copia=new sfrasi[numpref];
	for(int i=0;i<numpref;i++)
		s>>copia[i].frase;
	s.close();
}

void SalvaFrase(pezzi* elenco,int indice[]) //Salva L'Ultima Frase Nelle Preferite
{
	int numpref;
	sfrasi* copia;
	CaricaPref(numpref,copia);
	ofstream f(FilePreferiti);
	f<<numpref+1<<"\n";
	for(int i=0;i<numpref;i++)
	{
		f<<copia[i].frase;
		f<<"\n";
	}
	f<<elenco[indice[0]].who;
	f<<elenco[indice[1]].what;
	f<<elenco[indice[2]].why<<"\n";
	f.close();
}

void Svuota() //Svuota il File delle frasi preferite e ci mette uno 0 (numero di frasi 						preferite
{
	ofstream f(FilePreferiti);
	f<<"0\n";
	f.close();
}

void PreferitaRandom()//Apre Il File Delle Frasi Preferite, e ne scrive una a 										caso,Riutilizzando la funzione StampaFrasiRandom
{					  //Riutilizzando la funzione StampaFrasiRandom
	int numpref;
	sfrasi* copia;
	CaricaPref(numpref,copia);
	if(numpref==0)
	{
		cout<<"Non sono presenti frasi preferite\n\n";
		return;
	}
	StampaFrasiRandom(copia,PaoloFox(numpref,0));
}

int main()
{
	int n;//Numero di elementi
	pezzi* elenco=Riempimento(n);
	int indice[numel];
	const char menu[] =
		"1. Nuovo Biscotto\n"
		"2. Inserisci Frase nelle Preferite\n"
		"3. Svuota Le Frasi Preferite\n"
		"4. Fornisce una Frase Preferita randomica\n"
		"5. Esci\n";

	while (true)
	{
		cout<<menu<<endl;

		int scelta;
		cin>>scelta;
		cout<<"\n";
		switch (scelta)
		{
			case 1:
				NuovoBiscotto(elenco,indice,n);
				StampaBiscotto(elenco,indice);
				break;
			case 2:
				SalvaFrase(elenco,indice);
				break;
			case 3:
				Svuota();
				cout<<"Frasi Preferite Svuotate con Successo\n\n";
				break;
			case 4:
				PreferitaRandom();
				break;
			case 5:
				return 0;
		}
	}
}
