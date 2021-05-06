#include<iostream>
#include<fstream>
#include<string.h>

#include"random.h"

using namespace std;

/**
 * Lunghezza massima dei valori who, what, why, e lunghezza massima della frase
 * numero di elementi che compongono una frase
 * Nome del file contenente i pezzi di frasi da attaccare
 * Nome del file contenente le frasi preferite
 */
const int lungwho=30, lungwhat=40, lungwhy=40, lungall=110;
const int numel=3;
const char FilePezzi[] = "ElencoPezzi.txt";
const char FilePreferiti[] = "FrasiPreferite.txt";

/**
 *  struttura usata per immagazzinare una terna di possibili valori
 *  un array di questo elemento contiene i vari pezzi ottenuti
 *  in input da un file
 */
struct pezzi
{
	char who[lungwho];
	char what[lungwhat];
	char why[lungwhy];
};

/**
 * struttura usata per immagazzinare una frase completa
 */
struct sfrasi
{
	char frase[lungall];
};



/**
 * Per prendere in Input FilePezzi, ed immagazzinarlo in un array di elementi di tipo "pezzi"
 */
pezzi* Riempimento(int &n)
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

/**
 * Stampa un biscotto, mettendo gli spazi prima di ogni maiuscola per migliorare la leggibilita'
 * bisogna passargli un array contenente gli indici da vedere nell'array di pezzi
 */
void StampaBiscotto(pezzi* elenco,int indice[])
{
	for(unsigned int i=0;i<strlen(elenco[indice[0]].who);i++)
	{
		if(static_cast<int>(elenco[indice[0]].who[i])<=90&&static_cast<int>(elenco[indice[0]].who[i])>=65)
			cout<<" ";
		cout<<elenco[indice[0]].who[i];
	}
	for(unsigned int i=0;i<strlen(elenco[indice[1]].what);i++)
	{
		if(static_cast<int>(elenco[indice[1]].what[i])<=90&&static_cast<int>(elenco[indice[1]].what[i])>=65)
			cout<<" ";
		cout<<elenco[indice[1]].what[i];
	}
	for(unsigned int i=0;i<strlen(elenco[indice[2]].why);i++)
	{
		if(static_cast<int>(elenco[indice[2]].why[i])<=90&&static_cast<int>(elenco[indice[2]].why[i])>=65)
			cout<<" ";
		cout<<elenco[indice[2]].why[i];
	}
	cout<<"\n\n";
}

/**
 * Crea un nuovo biscotto, di fatto inizializzando i valori di un array "indice" con il risultato
 * della funzione PaoloFox
 */
void NuovoBiscotto(pezzi* elenco,int indice[],int n)
{
	for(int i=0;i<numel;i++)
	{
		indice[i]=PaoloFox(n,i);
	}
}

/**
 * Stampa la frase n tra quelle immagazzinate in un array di "sfrasi"
 *
 */
void StampaFrase(sfrasi* copia,int n)
{
	for(unsigned int i=0;i<strlen(copia[n].frase);i++)
	{
		if(static_cast<int>(copia[n].frase[i])<=90&&static_cast<int>(copia[n].frase[i])>=65)
			cout<<" ";
		cout<<copia[n].frase[i];
	}
	cout<<"\n\n";
}

/**
 * Apre e salva il file delle frasi preferite, modificando i parametri passati
 */
void CaricaPref(int &numpref,sfrasi* &copia)
{
	ifstream s(FilePreferiti);
	s>>numpref;
	copia=new sfrasi[numpref];
	for(int i=0;i<numpref;i++)
		s>>copia[i].frase;
	s.close();
}

/**
 * Salva l'ultima frase (pezzi ed indici passati come parametri) nei preferiti
 */
void SalvaFrase(pezzi* elenco,int indice[])
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

/**
 * Svuota il file delle frasi preferite
 */
void Svuota()
{
	ofstream f(FilePreferiti);
	f<<"0\n";
	f.close();
}

/**
 * 	Apre Il File Delle Frasi Preferite, e ne scrive una a
 * 	caso in standard output
 */
void PreferitaRandom()
{
	int numpref;
	sfrasi* copia;
	CaricaPref(numpref,copia);
	if(numpref==0)
	{
		cout<<"Non sono presenti frasi preferite\n\n";
		return;
	}
	StampaFrase(copia,PaoloFox(numpref,0));
}

/**
 * main, con classica scelta tra varie opzioni gestita da uno switch
 */
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
				cout<<"E' stato bello creare biscotti con te\n";
				return 0;
		}
	}
}
