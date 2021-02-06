#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#define TXT_LENGTH 256


void Wybor();
void zamiana_liter();
void free_ptr();

/*!
    Funkcja Sprawdz() przyjmuje jeden parametr, znak typu char;
    Zwraca 0 jeżeli znak jest mała literą;
    Zwraca 1 jeżeli znak jest wielką literą;
    Zwraca 2 jeżeli znak jest inny niz wielka lub mała litera;
*/
int Sprawdz(char znak)
{
    if(znak >= 'a' && znak <= 'z')
    {
        return 0;
    }
    if(znak >= 'A' && znak <= 'Z')
    {
        return 1;
	}
    return 2;
}

/*!
    Funkcja Szyfruj_Cezar() przyjmuje 2 parametry, pierwszy z nich to klucz typu int, drugi jest to tablica typu char;
    Funkcja nie zwraca żadnych wartości;
    Funkcja odpowiedzialna jest za wykonanie Szyfrowania i Deszyfrowania szyfrem Cezara;
    Aby wykorzystać funkcję do odszyfrowania wystarczy podać wartość przeciwną klucza użytego do kodowania;
*/
void Szyfruj_Cezar(int klucz, char *tab)
{
    if(!(klucz >= -26 && klucz <= 26))
    {
        return;
    }
    int tmp=0;
	char a, z;
	int dl = strlen(tab);

	for(int i = 0; i < dl; ++i)
	{
		tmp = Sprawdz(tab[i]);

		if(tmp < 2)
		{
			if(tmp == 0)
            {
				a = 'a', z = 'z';
            }
			else{
				a = 'A', z = 'Z';
			}

			if(klucz >= 0)
            {
                if(tab[i] + klucz <= z)
                {
					tab[i] += klucz;
                }else
                {
					tab[i] = tab[i] + klucz - 26;
                }
			}else
			{
			    if(tab[i] + klucz >= a)
                {
					tab[i] += klucz;
                }else
                {
                    tab[i] = tab[i] + klucz + 26;
                }
			}
		}
	}
}

/*!
    Funkcja Szyfr_Cezara() nie zwraca żadnej wartości;
    Służy do wybrania kodowania lub dekodowania szyfrem Cezara przez użytkownika;
*/
void Szyfr_Cezara()
{
    int wybor=0;
    char tab[100]={0};
    int klucz=0;
    char t;

    do{
    do{
    puts("Szyfr Cezara\n");
    puts("Wybierz opcje: \n\n1.Kodowanie\n2.Dekodowanie");
    puts("\nWprowadz wartosc: ");
    scanf("%d", &wybor);

    if(wybor<1 || wybor>2)
    {
        puts("\nPodano zla wartosc!!!\n");
    }
    }while(wybor<1 || wybor>2);

    if(wybor==1)
    {
        system("cls");
        puts("\nPodaj zdanie do zaszyfrowania: ");
        while(getchar()!='\n');
        scanf("%[^\n]", tab);

        puts("Podaj klucz z przedzialu <-26 do 26>: ");
        scanf("%d", &klucz);

        Szyfruj_Cezar(klucz,tab);

        printf("Po zaszyfrowaniu: %s", tab);
    }

    if(wybor==2)
    {
        system("cls");
        puts("\nPodaj zdanie do odszyfrowania: ");
        while(getchar()!='\n');
        scanf("%[^\n]", tab);

        puts("Podaj klucz z przedzialu <-26 do 26>: ");
        scanf("%d", &klucz);

        Szyfruj_Cezar(-klucz,tab);
        printf("\nPo rozszyfrowaniu: %s\n", tab);
    }
    printf("\nCzy chcesz dalej kontynuowac? (t=tak, esc=Menu)\n");
    t=getch();
    system("cls");
    }while(t=='t');

    if(t!='t')
    {
        system("cls");
        Wybor();
    }
}
/*!
    Funkcja usun_spacje() przyjmuje jeden parametr którym jest napis typu char*;
    Funkcja usuwa spacje z wprowadzonego tekstu;
*/
void usun_spacje(char* napis)
{
    char *i, *j;
    i = j = napis;
    while (*i) {
        if (*i != ' ') {
            *j = *i;
            j++;
        }
        i++;
    }
    *j = 0;
}

/*!
    Funkcja Szyfruj_Vigenere() przyjmuje dwa paramtery, pierwszy to tekst typu char*, drugi to klucz typu char*;
    Funkcja zwraca zaszyfrowany tekst typu char*;
    Służy do szyfrowania Szyfrem Vigenerea;
*/
char* Szyfruj_Vigenere (char* txt, char* key)
{
    int count_no_alpha=0;
    char* wynik = (char *)calloc((strlen(txt)+1),sizeof(char));
    wynik[strlen(txt)] = '\0';
    for(int i = 0; txt[i]; i++)
    {
        if(isalpha(txt[i]))
        {
            wynik[i] = ((txt[i] - 'a') + (key[(i-count_no_alpha) % strlen(key)] - 'a')) % 26 + 'a';
        }else
        {
            wynik[i]=txt[i];
            ++count_no_alpha;
        }
    }
    return wynik;
}

/*!
    Funkcja Odszyfruj_Vigenere() przyjumje dwa paramtery, pierwszy to tekst typu char*, drugi do klucz typu char*;
    Funkcja zwraca rozszyfrowany tekst typu char*;
    Służy do deszyfrowania Szyfrem Vigenerea;
*/
char* Odszyfruj_Vigenere (char* txt, char* key)
{
    int count_no_alpha=0;
    char* wynik = (char *)calloc((strlen(txt)+1),sizeof(char));
    wynik[strlen(txt)] = '\0';

    for(int i = 0; txt[i]; i++)
    {
        if(isalpha(txt[i]))
        {
            wynik[i] = ((txt[i] - 'a') - (key[(i-count_no_alpha)% strlen(key)] - 'a') + 26) % 26 + 'a';
        }
        else
        {
            wynik[i]=txt[i];
            ++count_no_alpha;
        }
    }
    return wynik;
}

/*!
    Funkcja Szyfr_Vigenere() nie przyjmuje parametrów oraz nie zwraca żadnej wartosci;
    Służy do wybrania kodowania lub dekodowania szyfrem Vigenerea przez użytkownika;
*/
void Szyfr_Vigenere()
{
    int wybor=0;
    char t;

    do{
    do{
    puts("Szyfr Vigenere\n");
    puts("Wybierz opcje: \n\n1.Kodowanie\n2.Dekodowanie");
    puts("\nWprowadz wartosc: ");
    scanf("%d", &wybor);

    if(wybor<1 || wybor>2)
    {
        puts("\nPodano zla wartosc!!!\n");
    }
    }while(wybor<1 || wybor>2);

    if(wybor==1)
    {
        system("cls");
        char* txt = (char *)calloc(TXT_LENGTH, sizeof(char));
        puts("Podaj tekst do zaszyfrowanie");
        while(getchar()!='\n');
        scanf("%[^\n]", txt);

        char* key = (char *)calloc(TXT_LENGTH, sizeof(char));
        puts("Podaj klucz: ");
        while(getchar()!='\n');
        scanf("%[^\n]", key);

        usun_spacje(key);
        zamiana_liter(txt, key);

        printf("\nTekst do zaszyfrowanie : %s\n", txt);
        printf("\nKlucz do zaszyfrowanie : %s\n", key);

        char* txtc = Szyfruj_Vigenere(txt, key);
        puts("\nPo zaszyfrowaniu: ");
        printf("%s", txtc);

        free_ptr (( void **) &txt) ;
        free_ptr (( void **) &key) ;
        free_ptr (( void **) &txtc) ;
    }

    if(wybor==2)
    {
        system("cls");
        char* txt = (char *)calloc(TXT_LENGTH, sizeof(char));
        puts("Podaj tekst do odszyfrowania");
        while(getchar()!='\n');
        scanf("%[^\n]", txt);

        char* key = (char *)calloc(TXT_LENGTH, sizeof(char));
        puts("Podaj klucz: ");
        while(getchar()!='\n');
        scanf("%[^\n]", key);

        usun_spacje(key);
        zamiana_liter(txt, key);

        puts("\n\nPo odszyfrowaniu:");
        char* txtd = Odszyfruj_Vigenere(txt, key);
        printf("%s", txtd);

        free_ptr (( void **) &txt) ;
        free_ptr (( void **) &key) ;
        free_ptr (( void **) &txtd) ;
    }

    printf("\nCzy chcesz dalej kontynuowac? (t=tak, esc=Menu)\n");
    t=getch();
    system("cls");
    }while(t=='t');

    if(t!='t')
    {
        system("cls");
        Wybor();
    }
}
/*!
    Funkcja free_ptr() przyjumje jeden parametr: jest to podwójny wskaźnik typu void;
    Funkcja nie zwraca zadnej wartosci;
    Służy do czyszczenia pamięci z dynamicznie alokowanej tablicy;
*/
void free_ptr ( void ** ptr)
{
    free (* ptr ) ;
    *ptr = NULL ;
}

/*!
    Funkcja zamiana_liter() przyjumje dwa paramtery, pierwszy to tekst typu char*, drugi do klucz typu char*;
    Funkcja nie zwraca żadnej wartości;
    Służy do zamiany dużych liter na małe;
*/
void zamiana_liter(char* txt, char* key)
{
    for(int i=0;i<100;++i)
    {
        if (txt[i]>='A'&&txt[i]<='Z')
        {
            txt[i]=txt[i]+32;
        }

        if(key[i]>='A'&&key[i]<='Z')
        {
            key[i]=key[i]+32;
        }
    }

}


/*!
    Funkcja Wybor() nie przyjmuje żadnych parametrów;
    Funkcja nie zwraca żadnej wartości;
    Służy jako Menu( użytkownik może wybrać szyfr);
*/
void Wybor()
{
    int wybor=0;

    do
    {
        puts("\nWybierz szyfr:\n\n1.Szyfr Cezara\n2.Szyfr Vigenerea");
        puts("\nWprowadz wartosc: ");
        scanf("%d", &wybor);
        if(wybor>2 || wybor<=0)
        {
            puts("Podano zla wartosc\nWpisz prawidlowo wartosc:\n ");
        }

    }while(wybor!=1 && wybor!=2);
    system("cls");

    if(wybor==1)
    {
        Szyfr_Cezara();

    }else if(wybor==2)
    {
        Szyfr_Vigenere();
    }
}

int main()
{
    Wybor();
    return 0;
}
