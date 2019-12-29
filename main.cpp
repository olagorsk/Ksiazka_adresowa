#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct AddressBook
{
    int id = 0;
    string name = "", surname = "", phone = "", mail = "", address = "";
};

int loadAddressBook(vector <AddressBook> &contacts, int &lastID);

char *strToChar(string line);

int addContact (vector <AddressBook> &contacts,int numberOfContacts, int &lastID);

void searchName (vector <AddressBook> contacts,int numberOfContacts);

void searchSurname (vector <AddressBook> contacts, int numberOfContacts);

void viewAllContacts (vector <AddressBook> contacts, int numberOfContacts);

int eraseContact(vector <AddressBook> &contacts, int numberOfContacts, int &lastID);

int editContact (vector <AddressBook> &contacts, int numberOfContacts);

void editTextFile (vector <AddressBook> contacts, int numberOfContacts);

void printContact (vector <AddressBook> contacts, int i);


int main()
{
    char choice;
    vector <AddressBook> contacts;
    int numberOfContacts=0;
    int lastID=0;

    numberOfContacts = loadAddressBook(contacts, lastID);

    while(1)
    {
        system("cls");
        cout<< "------KSIAZKA ADRESOWA------"<< endl<< endl;
        cout<< "1. Dodaj adresata"<< endl;
        cout<< "2. Wyszukaj po imieniu"<< endl;
        cout<< "3. Wyszukaj po nazwisku"<< endl;
        cout<< "4. Wyswietl wszystkich adresatow"<< endl;
        cout<< "5. Usun adresata"<< endl;
        cout<< "6. Edytuj adresata"<< endl;
        cout<< "9. Zakoncz program"<< endl;
        choice = getch();

        switch (choice)
        {
        case '1':
            numberOfContacts = addContact (contacts, numberOfContacts, lastID);
            break;

        case '2':
            searchName (contacts, numberOfContacts);
            break;

        case '3':
            searchSurname (contacts, numberOfContacts);
            break;

        case '4':
            viewAllContacts (contacts, numberOfContacts);
            break;

        case '5':
            numberOfContacts = eraseContact(contacts, numberOfContacts, lastID);
            break;

        case '6':
            editContact (contacts, numberOfContacts);
            break;

        case '9':
            exit(0);
        }
    }
    return 0;
}

int loadAddressBook (vector<AddressBook> &contacts, int &lastID)
{
    string line;
    int numberOfContacts = 0;

    AddressBook contact;

    string name = "", surname = "", phone = "", mail = "", address = "";
    int id;

    fstream file;
    file.open("ksiazka_adresowa.txt", ios::in);

    if (file.good() == true)
    {
        while (getline(file, line))
        {
            char space[] = "|";
            char *word;
            word = strtok (strToChar(line), space);
            while( word != NULL )
            {
                char wordToInt = *word;
                contact.id = wordToInt-'0';
                word = strtok( NULL, space );
                contact.name=word;
                word = strtok( NULL, space );
                contact.surname=word;
                word = strtok( NULL, space );
                contact.phone= word;
                word = strtok( NULL, space );
                contact.mail=word;
                word = strtok( NULL, space );
                contact.address = word;
                word = strtok( NULL, space );
            }
            contacts.push_back(contact);
            lastID = contact.id;
            numberOfContacts++;
        }
    }
    file.close();
    return numberOfContacts;
}

char *strToChar(string line)
{
    char *lineChar = new char[line.size() + 1];
    strcpy(lineChar, line.c_str() );
    return lineChar;
    delete [] lineChar;
}

int addContact (vector <AddressBook> &contacts, int numberOfContacts, int &lastID)
{
    AddressBook contact;
    string name = "", surname = "", phone = "", mail = "", address = "";

    cout<< "Podaj imie: ";
    cin>> name;

    cout<< "Podaj nazwisko: ";
    cin>> surname;

    cin.clear();
    cin.ignore( 1000, '\n' );
    cout<< "Podaj numer telefonu: ";
    getline (cin, phone);

    cout<< "Podaj adres email: ";
    cin>> mail;

    cin.clear();
    cin.ignore( 1000, '\n' );
    cout<< "Podaj adres: ";
    getline (cin, address);

    contact.id = lastID+1;
    contact.name = name;
    contact.surname = surname;
    contact.address = address;
    contact.phone = phone;
    contact.mail = mail;

    contacts.push_back(contact);
    lastID++;

    fstream file;
    file.open("ksiazka_adresowa.txt", ios::out|ios::app);
    if (file.good() == true)
    {
        file<< contact.id<<"|"<<contact.name<<"|"<<contact.surname<<"|"<<contact.phone<<"|"<<contact.mail<<"|"<<contact.address<<"|"<<endl;
        file.close();

        cout << "Utworzono nowy kontakt";
        Sleep(1500);
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }
    return numberOfContacts+1;
}

void searchName (vector <AddressBook> contacts, int numberOfContacts)
{
    system("cls");
    string name;
    cout<< "Podaj imie: ";
    cin>> name;
    int i = 0;
    int numberOfExistingName = 0;
    while (i < numberOfContacts)
    {
        if (contacts[i].name == name)
        {
            printContact (contacts, i);
            numberOfExistingName++;
        }
        i++;
    }
    if (numberOfExistingName==0)
        cout<< "Podane imie nie wystepuje w ksiazce adresowej" << endl;

    cout<< "Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

void searchSurname (vector <AddressBook> contacts, int numberOfContacts)
{
    system("cls");
    string surname;
    cout<< "Podaj nazwisko: ";
    cin>> surname;
    int i = 0;
    int numberOfExistingSurname = 0;
    while (i < numberOfContacts)
    {
        if (contacts[i].surname == surname)
        {
            printContact (contacts, i);
            numberOfExistingSurname++;
        }
        i++;
    }
    if (numberOfExistingSurname==0)
        cout<< "Podane nazwisko nie wystepuje w ksiazce adresowej"<< endl;

    cout<< "Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

void viewAllContacts (vector <AddressBook> contacts, int numberOfContacts)
{
    for (int i=0; i < numberOfContacts; i++)
    {
        printContact (contacts, i);
    }
    cout <<"Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

int eraseContact(vector <AddressBook> &contacts, int numberOfContacts, int &lastID)
{
    system("cls");
    cout<<"Podaj id adresata, ktorego chcesz usunac: ";
    int contactIDtoErase;
    cin>>contactIDtoErase;

    for (int i=0; i< numberOfContacts; i++)
    {
        if (contactIDtoErase == contacts[i].id)
        {
            cout<<"Czy na pewno usunac ten kontakt? (t)"<<endl;
            printContact (contacts, i);
            char sign;
            sign = getch();
            if (sign == 't')
            {
                contacts.erase(contacts.begin()+ i);
                numberOfContacts--;
                if (i = numberOfContacts)
                {
                    lastID = contacts[i-1].id;
                }
                editTextFile (contacts, numberOfContacts);
                cout<<"Kontakt usunieto";
                Sleep(1500);
            }
            else
                break;
        }
    }
    return numberOfContacts;
}

int editContact (vector <AddressBook> &contacts, int numberOfContacts)
{
    system("cls");
    cout<< "Wpisz ID adresata, ktorego dane chcesz zmienic: ";
    int contactToChange;
    cin>>contactToChange;

    int i=0;
    while (i<numberOfContacts)
    {
        if (contacts[i].id == contactToChange)
        {
            break;
        }
        i++;
        if (i==numberOfContacts)
        {
            cout<< "Podane dane (ID) nie wystepuje w ksiazce adresowej"<< endl;
            Sleep(1000);
            return i;
        }
    }
    cout<< "Edytuj: "<< endl;
    cout<< "1. Imie"<< endl;
    cout<< "2. Nazwisko"<< endl;
    cout<< "3. Numer telefonu"<< endl;
    cout<< "4. Email"<< endl;
    cout<< "5. Adres"<< endl;
    cout<< "6. Powrot do menu glownego"<< endl;

    string newData;
    char editMenuChoice;
    editMenuChoice = getch();

    switch (editMenuChoice)
    {
    case '1':
    {
        cout<<"Podaj nowe imie: ";
        cin>>newData;
        contacts[i].name = newData;
        editTextFile(contacts, numberOfContacts);
        cout<<"Imie zostalo zmienione na: "<<newData;
        Sleep(1000);
    }
    break;

    case '2':
    {
        cout<<"Podaj nowe nazwisko: ";
        cin>>newData;
        contacts[i].surname = newData;
        editTextFile(contacts, numberOfContacts);
        cout<<"Nazwisko zostalo zmienione na: "<<newData;
        Sleep(1000);
    }
    break;

    case '3':
    {
        cout<<"Podaj nowy numer telefonu: ";
        cin>>newData;
        contacts[i].phone = newData;
        editTextFile(contacts, numberOfContacts);
        cout<<"Numer telefonu zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '4':
    {
        cout<<"Podaj nowy mail: ";
        cin>>newData;
        contacts[i].mail = newData;
        editTextFile(contacts, numberOfContacts);
        cout<<"Adres mail zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '5':
    {
        cout<<"Podaj nowy adres: ";
        cin>>newData;
        contacts[i].address = newData;
        editTextFile(contacts, numberOfContacts);
        cout<<"Adres zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '6':
        break;
    }
}

void editTextFile (vector <AddressBook> contacts, int numberOfContacts)
{
    fstream file;
    file.open("ksiazka_adresowa.txt", ios::out| ios::trunc);
    file.clear();
    if (file.good() == true)
    {
        for (int i=0; i<numberOfContacts; i++ )
        {
            file<< contacts[i].id<<"|"<<contacts[i].name<<"|"<<contacts[i].surname<<"|"<<contacts[i].phone<<"|"<<contacts[i].mail<<"|"<<contacts[i].address<<"|"<<endl;
        }
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }
    file.close();
}

void printContact (vector <AddressBook> contacts, int i)
{
    cout<< contacts[i].name<< "   "<< contacts[i].surname<< endl;
    cout<< "Nr telefonu: "<< contacts[i].phone<< "  adres email: "<< contacts[i].mail;
    cout<< "  adres: "<< contacts[i].address<< "  ID: "<< contacts[i].id<< endl<< endl;
}
