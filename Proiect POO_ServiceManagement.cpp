#include <string>
#include <fstream>
#include<conio.h>
#include <iostream>
#include<stdio.h>
#include <vector>
#pragma warning(disable:4996)
using namespace std;

class iAfisabil {
public:
    virtual void genereazaRaport() = 0; //scriereInFisier
    virtual void citesteRaport() = 0; //citireDinFisier
    virtual void serializare(ofstream& fisier) = 0; //scriereInFisier
    virtual void deserializare(ifstream& fisier) = 0; //citireDinFisier
};

class Produs : iAfisabil {
private:
    string denumire;
    float pret;
    string unitateMasura;
    float cantitate;

public:
    static int nrProduse;

    void serializare(ofstream& f) override
    {
        int length = denumire.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(denumire.c_str(), length);

        float v = pret;
        f.write((char*)&v, sizeof(v));

        length = unitateMasura.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(unitateMasura.c_str(), length);

        v = cantitate;
        f.write((char*)&v, sizeof(v));
    }
    void deserializare(ifstream& f) override
    {
        int length = 0, x = 0;
        f.read((char*)&length, sizeof(length));
        char* aux = new char[length];
        f.read(aux, length);
        setDenumire(aux);
        if (aux != nullptr)
            delete[] aux;

        float y = 0;
        f.read((char*)&y, sizeof(y));
        setPret(y);

        length = 0;
        f.read((char*)&length, sizeof(length));
        aux = new char[length];
        f.read(aux, length);
        setUnitateMasura(aux);

        f.read((char*)&y, sizeof(y));
        setCantitate(y);
    }
    void citesteRaport() override {
        cout << "Produsul nu are nevoie de raport." << endl;
    }
    void genereazaRaport() override {
        cout << "Produsul nu are nevoie de raport." << endl;
    }
    string getDenumire() {
        return denumire;
    }
    void setDenumire(string denumire) {
        if (denumire != "")
            this->denumire = denumire;
    }
    float getPret() {
        return pret;
    }
    void setPret(float pret) {
        if (pret > 0) this->pret = pret;
    }
    string getUnitateMasura() {
        return unitateMasura;
    }
    void setUnitateMasura(string unitateMasura) {
        if (unitateMasura != "")
            this->unitateMasura = unitateMasura;
    }
    float getCantitate() {
        return cantitate;
    }
    void setCantitate(float cantitate) {
        if (pret > 0) this->cantitate = cantitate;
    }

    Produs() {
        ++nrProduse;
        this->denumire = "";
        this->cantitate = 0;
        this->pret = 0;
        this->unitateMasura = "";
    }
    Produs(string denumire, float pret, string unitateMasura, float cantitate) : Produs() {
        if (denumire != "")
            this->denumire = denumire;
        if (pret > 0)
            this->pret = pret;
        if (cantitate > 0)
            this->cantitate = cantitate;
        if (unitateMasura != "")
            this->unitateMasura = unitateMasura;
    }
    Produs(const Produs& p) : Produs() {
        if (p.denumire != "")
            this->denumire = p.denumire;
        if (p.pret > 0)
            this->pret = p.pret;
        if (p.cantitate > 0)
            this->cantitate = p.cantitate;
        if (p.unitateMasura != "")
            this->unitateMasura = p.unitateMasura;
    }
    ~Produs() {
        nrProduse--;
    }
    Produs& operator=(const Produs& p) {
        nrProduse--;
        if (p.denumire != "")
            this->denumire = p.denumire;
        if (p.pret > 0)
            this->pret = p.pret;
        if (p.cantitate > 0)
            this->cantitate = p.cantitate;
        if (p.unitateMasura != "")
            this->unitateMasura = p.unitateMasura;
        return *this;
    }
    // alti operatori 
    bool operator ==(Produs p) {
        return p.pret == pret && p.denumire == denumire && p.unitateMasura == unitateMasura && p.cantitate == cantitate;
    }
    explicit operator float() {
        return this->pret;
    }
    Produs operator+(float pret) {
        if (pret > 0)
            this->pret += pret;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Produs& m) {
        out << "Denumire: " << m.denumire << endl;
        out << "Pret: " << m.pret << endl;
        out << "Cantitate: " << m.cantitate << " " << m.unitateMasura << ". " << endl;
        return out;
    }
    friend istream& operator>>(istream& in, Produs& m) {

        cout << "Denumire: ";
        in >> ws;
        getline(in, m.denumire);
        cout << "Pret: ";
        in >> m.pret;
        cout << "Cantitate: ";
        in >> ws;
        in >> m.cantitate;
        cout << "Unitate de masura: " << endl;
        in >> ws;
        getline(in, m.unitateMasura);
        return in;
    }

};
int Produs::nrProduse = 0;


class Client : iAfisabil {
private:
    string numeComplet;
    string adresa;
    string telefon;
public:
    Client() {
        numeComplet = "";
        adresa = "";
        telefon = "";
    }
    Client(const Client& c) {
        setNumeComplet(c.numeComplet);
        setAdresa(c.adresa);
        setTelefon(c.telefon);
    }
    Client(string numeComplet, string adresa, string telefon) {
        setNumeComplet(numeComplet);
        setAdresa(adresa);
        setTelefon(telefon);
    }
    Client operator=(const Client& c) {
        setNumeComplet(c.numeComplet);
        setAdresa(c.adresa);
        setTelefon(c.telefon);
        return *this;
    }
    ~Client() {}

    string getNumeComplet() {
        return this->numeComplet;
    }
    string getAdresa() {
        return this->adresa;
    }
    string getTelefon() {
        return this->telefon;
    }
    void setNumeComplet(string nume) {
        if (nume != "") this->numeComplet = nume;
    }
    void setAdresa(string adresa) {
        if (adresa != "") this->adresa = adresa;
    }
    void setTelefon(string telefon) {
        if (telefon != "") this->telefon = telefon;
    }
    void citesteRaport() override {
        cout << "Client" << endl;
    }
    void genereazaRaport() override {
        cout << "Client" << endl;
    }
    // serializez doar datele
    void serializare(ofstream& f) override
    {
        int length = numeComplet.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(numeComplet.c_str(), length);

        length = adresa.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(adresa.c_str(), length);

        length = telefon.length();
        length++;
        f.write((char*)&length, sizeof(length));
        f.write(telefon.c_str(), length);
    }
    void deserializare(ifstream& f) override
    {
        int length = 0, x = 0;
        f.read((char*)&length, sizeof(length));
        char* aux = new char[length];
        f.read(aux, length);
        setNumeComplet(aux);
        if (aux != nullptr)
            delete[] aux;

        length = 0;
        f.read((char*)&length, sizeof(length));
        aux = new char[length];
        f.read(aux, length);
        setAdresa(aux);

        length = 0;
        f.read((char*)&length, sizeof(length));
        aux = new char[length];
        f.read(aux, length);
        setTelefon(aux);

    }
    friend ostream& operator<<(ostream& out, const Client& m) {
        out << "Nume: " << m.numeComplet << endl;
        out << "Adresa: " << m.adresa << endl;
        out << "Telefon: " << m.telefon << endl;
        return out;
    }
    friend istream& operator>>(istream& in, Client& m) {
        cout << "Nume: ";
        in >> ws;
        getline(in, m.numeComplet);
        cout << "Telefon: ";
        in >> ws;
        getline(in, m.telefon);
        cout << "Adresa: ";
        in >> ws;
        in >> m.adresa;
        return in;
    }
};

// clientul are un cos, pune produse. cand da finalizare, se face comanda: cos + date client.
// se face raport pe comanda
// magazinul are produse, are comenzi.

// preluare -> generare
// raport pe ele
class Comanda : iAfisabil {
private:
    Produs* produse;
    int nrProduse;
    Client client;
public:
    void setProduse(int nr, Produs* prod) {
        if (nr > 0 && prod != nullptr) {
            if (this->produse != nullptr)
                delete[] this->produse;
            this->produse = new Produs[nr];
            this->nrProduse = nr;
            for (int i = 0; i < nr; i++) {
                this->produse[i] = prod[i];
            }
        }
    }
    Produs* getProduse(int& nr) {
        Produs* copy = nullptr;
        if (produse != nullptr && nrProduse > 0) {
            copy = new Produs[nrProduse];
            nr = nrProduse;
            for (int i = 0; i < nr; i++) {
                copy[i] = produse[i];
            }
        }
        return copy;
    }
    void setClient(Client client) {
        this->client = client;
    }
    Client getclient() {
        return  this->client;
    }
    Comanda() {
        this->produse = nullptr; nrProduse = 0;
    }
    Comanda(const Comanda& m) : Comanda() {
        setProduse(m.nrProduse, m.produse);
        this->client = m.client;
    }
    Comanda& operator=(const Comanda& m) {
        setProduse(m.nrProduse, m.produse);
        this->client = m.client;
        return *this;
    }
    ~Comanda() {
        if (this->produse != nullptr) {
            delete[] produse;
            produse = nullptr;
        }
    }
    void citesteRaport() override {
        string nrProd = to_string(nrProduse);
        ifstream f; f.open("comanda" + client.getNumeComplet() + nrProd + ".txt", ios::in);
        string tp = "";
        while (getline(f, tp)) {
            cout << tp << endl;
        }
        f.close();
    }
    void genereazaRaport() override {
        string nrProd = to_string(nrProduse);
        string fileName = "comanda" + client.getNumeComplet() + nrProd + ".txt";
        ofstream f;
        f.open(fileName, ios::out);
        f << *this;
        f.close();
        cout << endl << "Raport comanda in " << fileName << endl;
    }
    void serializare(ofstream& f) override
    {
        int length = nrProduse;
        if (nrProduse > 0 && produse != nullptr) {
            f.write((char*)&length, sizeof(length));
            for (int i = 0; i < nrProduse; i++) {
                produse[i].serializare(f);
            }
        }
        else {
            length = 0;
            f.write((char*)&length, sizeof(length));
        }
        client.serializare(f);
    }
    void deserializare(ifstream& f) override
    {
        int length = 0;
        f.read((char*)&length, sizeof(length));
        if (length > 0) {
            Produs* prod = new Produs[length];
            for (int i = 0; i < length; i++) {
                Produs citit;
                prod[i] = citit;
                prod[i].deserializare(f);
            }
            this->nrProduse = length;
            this->produse = prod;
        }
        Client clientCitit;
        clientCitit.deserializare(f);
        this->client = clientCitit;
    }
    friend ostream& operator<<(ostream& out, const Comanda& m) {
        for (int i = 0; i < m.nrProduse; i++)
            out << m.produse[i] << endl;
        out << m.client << endl;
        return out;
    }
};


class Meniu {
public:
    virtual void afiseazaMeniu(string& opt) = 0;
    virtual void afiseazaProduse() = 0;
    virtual void afiseazaComenzi() = 0;
    virtual void serializare() = 0;
    virtual void deserializare() = 0;
    virtual void executaOptiune(string& opt) = 0;
};


class MeniuMagazin : public Meniu {
private:
    Produs* produse;
    int nrProduse;
    Comanda* comenzi;
    int nrComenzi;

public:
    int getNrProduse() {
        return nrProduse;
    }
    void setProduse(int nr, Produs* prod) {
        if (nr > 0 && prod != nullptr) {
            if (this->produse != nullptr)
                delete[] this->produse;
            this->produse = new Produs[nr];
            this->nrProduse = nr;
            for (int i = 0; i < nr; i++) {
                this->produse[i] = prod[i];
            }
        }
    }
    Produs* getProduse(int& nr) {
        Produs* copy = nullptr;
        if (produse != nullptr && nrProduse > 0) {
            copy = new Produs[nrProduse];
            nr = nrProduse;
            for (int i = 0; i < nr; i++) {
                copy[i] = produse[i];
            }
        }
        return copy;
    }
    void setComenzi(int nr, Comanda* com) {
        if (nr > 0 && com != nullptr) {
            if (this->comenzi != nullptr)
                delete[] this->comenzi;
            this->comenzi = new Comanda[nr];
            this->nrComenzi = nr;
            for (int i = 0; i < nr; i++) {
                this->comenzi[i] = com[i];
            }
        }
    }
    void afiseazaMeniu(string& opt) override {
        cout << endl << "Bine ai venit!" << endl;
        cout << "Alegeti o optiune:" << endl;
        cout << "1. Afiseaza produse." << endl;
        cout << "2. Adauga produs." << endl;
        cout << "3. Sterge produs." << endl;
        cout << "4. Editeaza produs." << endl;
        cout << "5. Afiseaza comenzi." << endl;
        cout << "6. Raport comenzi in txt." << endl;
        executaOptiune(opt);
    }
    void executaOptiune(string& type) override {
        cout << endl << "Decizia ta:";
        cin >> type;
        while (type != "exit" && type != "1" && type != "2" && type != "3" && type != "4" && type != "5" && type != "6") {
            afiseazaMeniu(type);
            cout << "Decizia ta:";
            cin >> type;

        }
        if (type == "1") afiseazaProduse();
        else if (type == "2") adaugaProdus();
        else if (type == "3") stergeProdus();
        else if (type == "4") editeazaProdus();
        else if (type == "5") afiseazaComenzi();
        else if (type == "6") raport();
    }
    void raport() {
        ofstream f; f.open("comenzi.txt");
        for (int i = 0; i < nrComenzi; i++) {
            f << comenzi[i];
        }
        f.close();
    }
    void adaugaProdus() {
        Produs p;
        cin >> p;
        adaugaInVector(p);
        serializare();
        cout << endl << "Ati adaugat: " << endl << p;
        afiseazaProduse();

    }
    void stergeProdus() {
        afiseazaProduse();
        string type = ""; bool ok = false; int nr = 0;

        while (!ok) {
            cout << "Alegeti nr produsului:" << endl;
            cin >> type;
            try {
                nr = std::stoi(type);
                if (nr <= getNrProduse() && nr > 0)
                    ok = true;
            }
            catch (std::exception const& e)
            {
                ok = false;
            }
        }
        int i = nr - 1;

        Produs* newVector = new Produs[nrProduse - 1];
        for (int j = 0; j < nrProduse; j++) {
            if (j != i) {
                newVector[j] = produse[j];
            }
        }
        setProduse(nrProduse - 1, newVector);
        afiseazaProduse();
        serializare();
    }
    void editeazaProdus() {
        afiseazaProduse();
        string type = ""; bool ok = false; int nr = 0;

        while (!ok) {
            cout << "Alegeti nr produsului:" << endl;
            cin >> type;
            try {
                nr = std::stoi(type);
                if (nr <= getNrProduse() && nr > 0)
                    ok = true;
            }
            catch (std::exception const& e)
            {
                ok = false;
            }
        }
        int i = nr - 1;
        Produs editabil = produse[i];
        cout << "Editati produsul:" << endl;
        cin >> editabil;
        produse[i] = editabil;
        afiseazaProduse();
        serializare();
    }
    void afiseazaProduse() override {
        cout << endl << endl << "Produsele din magazin:" << endl << endl;
        if (nrProduse > 0 && produse != nullptr) {
            for (int i = 0; i < nrProduse; i++) {
                cout << i + 1 << ". " << produse[i];
            }
        }
        else cout << "Nu sunt produse in magazin momentan." << endl;
        cout << endl << endl;
    }
    void afiseazaComenzi() override {
        cout << endl << endl << "Comenzile din magazin:" << endl << endl;
        if (nrComenzi > 0 && comenzi != nullptr) {
            for (int i = 0; i < nrComenzi; i++) {
                cout << i + 1 << ". " << comenzi[i];
            }
        }
        else cout << "Nu sunt produse in magazin momentan." << endl;
        cout << endl << endl;
    }
    void serializare() override {
        ofstream f;
        f.open("produse.bin", ios::binary | ios::out);
        if (f.is_open()) {
            int length = nrProduse;
            if (nrProduse > 0 && produse != nullptr) {
                f.write((char*)&length, sizeof(length));
                for (int i = 0; i < nrProduse; i++) {
                    produse[i].serializare(f);
                }
            }
            else {
                f.write((char*)&length, sizeof(length));
            }
            length = nrComenzi;
            if (nrComenzi > 0 && comenzi != nullptr) {
                f.write((char*)&length, sizeof(length));
                for (int i = 0; i < nrComenzi; i++) {
                    comenzi[i].serializare(f);
                }
            }
            else {
                f.write((char*)&length, sizeof(length));
            }

        }
        f.close();
        cout << endl << "Date salvate in fisier binar!" << endl << endl;
    }
    void deserializare() override {
        ifstream f;
        f.open("produse.bin", ios::binary | ios::in);
        if (f.is_open()) {
            int length = 0;
            f.read((char*)&length, sizeof(length));
            if (length > 0) {
                Produs* prod = new Produs[length];
                for (int i = 0; i < length; i++) {
                    Produs citit;
                    prod[i] = citit;
                    prod[i].deserializare(f);
                }
                setProduse(length, prod);
            }
            f.read((char*)&length, sizeof(length));
            if (length > 0) {
                Comanda* comenziCitite = new Comanda[length];
                for (int i = 0; i < length; i++) {
                    Comanda citit;
                    comenziCitite[i] = citit;
                    comenziCitite[i].deserializare(f);
                }
                setComenzi(length, comenziCitite);
            }

        }
        f.close();
    }
    void adaugaInVector(Produs nou) {
        Produs* copy = nullptr;
        if (produse != nullptr && nrProduse > 0) {
            copy = new Produs[nrProduse + 1];
            for (int i = 0; i < nrProduse; i++) {
                copy[i] = produse[i];
            }
            copy[nrProduse] = nou;
            setProduse(nrProduse + 1, copy);
        }
        else {
            copy = new Produs[1];
            copy[0] = nou;
            setProduse(1, copy);
        }

    }
    void adaugaComanda(Comanda noua) {
        Comanda* copy = nullptr;
        if (comenzi != nullptr && nrComenzi > 0) {
            copy = new Comanda[nrComenzi + 1];
            for (int i = 0; i < nrComenzi; i++) {
                copy[i] = comenzi[i];
            }
            copy[nrComenzi] = noua;
            setComenzi(nrComenzi + 1, copy);
        }
        else {
            copy = new Comanda[1];
            copy[0] = noua;
            setComenzi(1, copy);
        }
        serializare();
    }
    MeniuMagazin() {
        this->produse = nullptr;
        this->comenzi = nullptr;
        nrComenzi = nrProduse = 0;
    }
    MeniuMagazin(const MeniuMagazin& m) : MeniuMagazin() {
        setProduse(m.nrProduse, m.produse);
        setComenzi(m.nrComenzi, m.comenzi);
    }
    MeniuMagazin& operator=(const MeniuMagazin& m) {
        setProduse(m.nrProduse, m.produse);
        setComenzi(m.nrComenzi, m.comenzi);
        return *this;
    }
    ~MeniuMagazin() {
        if (this->comenzi != nullptr) {
            delete[] comenzi;
            comenzi = nullptr;
        }
        if (this->produse != nullptr) {
            delete[] produse;
            produse = nullptr;
        }
    }
};


class MeniuClient : public Meniu {
private:
    MeniuMagazin magazin;
    Comanda* comenzi;
    int nrComenzi;
    string numeClient;
public:
    void afiseazaMeniu(string& opt) override {
        cout << endl << "Bine ai venit!" << endl;
        cout << "Alegeti o optiune:" << endl;
        cout << "1. Afiseaza produse." << endl;
        cout << "2. Comanda." << endl;
        executaOptiune(opt);
    }
    void executaOptiune(string& type) override {
        cout << endl << "Decizia ta:";
        cin >> type;
        while (type != "exit" && type != "1" && type != "2") {
            afiseazaMeniu(type);
            cout << "Decizia ta:";
            cin >> type;
        }
        if (type == "1") afiseazaProduse();
        else if (type == "2") comanda(type);
    }
    void comanda(string& type) {
        bool ok = false; int nr = 0;
        Comanda comanda;
        while (!ok) {
            afiseazaProduse();
            cout << "Alegeti numarul de produse pe care doriti sa il comandati:" << endl;
            cin >> type;
            try {
                nr = std::stoi(type);
                if (nr <= magazin.getNrProduse())
                    ok = true;
            }
            catch (std::exception const& e)
            {
                ok = false;
            }
        }

        Produs* cos = new Produs[nr];
        int nrTotale = 0;
        Produs* totale = magazin.getProduse(nrTotale);
        cout << "Dati numarul produsului, cu virgula (ex: 1,4,5):";
        string alegeriProduse = "";
        cin >> ws;
        getline(cin, alegeriProduse);
        char* alegeri = strtok((char*)alegeriProduse.c_str(), ",");
        int contor = 0;
        while (alegeri != NULL)
        {
            int x = atoi(alegeri);
            for (int i = 0; i < nrTotale; i++) {
                if (x - 1 == i)
                    cos[contor++] = totale[i];
            }
            alegeri = strtok(NULL, ",");

        }
        cout << "Cosul dvs:" << endl;
        for (int i = 0; i < nr; i++) {
            cout << cos[i];
        }
        cout << "Dati date:";
        Client client;
        cin >> client;
        comanda.setClient(client);
        comanda.setProduse(atoi(type.c_str()), cos);
        cout << endl << "Comanda a fost trimisa:" << endl << comanda << endl;
        magazin.adaugaComanda(comanda); comanda.genereazaRaport(); comanda.citesteRaport();
    }
    void afiseazaProduse() override {
        magazin.afiseazaProduse();
    }
    void serializare() override {
        ofstream f;
        f.open("comenziClient.bin", ios::binary | ios::out);
        if (f.is_open()) {
            int length = nrComenzi;
            if (nrComenzi > 0 && comenzi != nullptr) {
                f.write((char*)&length, sizeof(length));
                for (int i = 0; i < nrComenzi; i++) {


                }
            }
            else {
                f.write((char*)&length, sizeof(length));
            }

        }
        f.close();
    }
    void deserializare() override {

    }
    void afiseazaComenzi() override {
        cout << endl << endl << "Comenzile clientului:" << endl << endl;
        if (nrComenzi > 0 && comenzi != nullptr) {
            for (int i = 0; i < nrComenzi; i++) {
                cout << i + 1 << ". " << comenzi[i];
            }
        }
        else cout << "Nu sunt produse in magazin momentan." << endl;
        cout << endl << endl;
    }
    void setComenzi(int nr, Comanda* com) {
        if (nr > 0 && com != nullptr) {
            if (this->comenzi != nullptr)
                delete[] this->comenzi;
            this->comenzi = new Comanda[nr];
            this->nrComenzi = nr;
            for (int i = 0; i < nr; i++) {
                this->comenzi[i] = com[i];
            }
        }
    }
    MeniuClient(MeniuMagazin m) {
        this->magazin = m;
        this->comenzi = nullptr;
        nrComenzi = 0;
        numeClient = "";
    }
    MeniuClient(const MeniuClient& m) {
        setComenzi(m.nrComenzi, m.comenzi);
        if (m.numeClient != "")
            numeClient = m.numeClient;
        magazin = m.magazin;
    }
    MeniuClient& operator=(const MeniuClient& m) {
        setComenzi(m.nrComenzi, m.comenzi);
        if (m.numeClient != "")
            numeClient = m.numeClient;
        magazin = m.magazin;
        return *this;
    }
    ~MeniuClient() {
        if (this->comenzi != nullptr) {
            delete[] comenzi;
            comenzi = nullptr;
        }
    }
};


int main() {

    Meniu* meniu = nullptr;

    string option = "";
    MeniuMagazin mag;
    mag.deserializare();
    if (mag.getNrProduse() < 1) {
        Produs* prod = new Produs[6];
        prod[0] = Produs("Lapte", 6, "L", 33);
        prod[1] = Produs("Mere", 4.2, "kg", 21);
        prod[2] = Produs("Paine", 2.3, "buc", 34);
        prod[3] = Produs("Apa", 2.2, "L", 121);
        prod[4] = Produs("Servetele", 5.5, "pachete", 87);
        prod[5] = Produs("Cartofi", 22.2, "saci", 71);

        mag.setProduse(6, prod);
        mag.serializare();
    }
    MeniuClient m(mag);
    cout << "Intrati ca si client (1) sau magazin (0)? ";
    while (option != "1" && option != "0" && option != "exit") {
        cin >> option;
        if (option == "1") {
            cout << "Ati ales client." << endl;

            meniu = &m;
        }
        else if (option == "0") {
            cout << "Ati ales magazin." << endl;
            meniu = &mag;
        }
        else if (option == "exit")
            break;

    }
    if (meniu != nullptr) {
        meniu->afiseazaProduse();
        while (option != "exit")
            meniu->afiseazaMeniu(option);
    }
    return 0;
}