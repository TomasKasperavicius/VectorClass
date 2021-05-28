#ifndef STUDENTASFUNKCIJOS_HPP
#define STUDENTASFUNKCIJOS_HPP
#include "Vector.hpp"
#include <list>
#include <deque>
#include <fstream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::deque;
using std::endl;
using std::fixed;
using std::left;
using std::list;
using std::right;
using std::setprecision;
using std::setw;

class Zmogus
{
protected:

    std::string vardas/*! first name*/, pavarde;/*!< last name */
public:
    /*!
    * Zmogus class default constructor.
    */
    Zmogus() : vardas(""), pavarde(""){}
    /*!
    * Zmogus class constructor.
    * @param vardas - first name, type string 
    * @param pavarde - last name, type string 
    */
    Zmogus(std::string vardas,std::string pavarde) : vardas(vardas),pavarde(pavarde){}
    virtual void BaseClass() = 0;
    /*!
    * \return first name, type string
    */
    inline std::string getVardas() const { return vardas;}
    /*!
    * \return last name, type string 
    */
    inline std::string getPavarde() const { return pavarde;}
    ~Zmogus();
};
class Studentas : public Zmogus
{
private:
    double egzaminas/*! exam grade*/, galutinis;/*!< final grade */
    Vector<double> pazymiai;/*!< homework grades */

public:
    /*!
    * Function that is used to sort students by their name alphabetically
    * @param st - reference to a Studentas class object
    */
    bool operator<(const Studentas &st) const
    {
        return (vardas < st.vardas);
    }
    /*!
    * Studentas class default constructor.
    */
    Studentas() : egzaminas(0), galutinis(0), pazymiai(0,0) {}
    Studentas(std::string vardas, std::string pavarde, double egzaminas, double galutinis, Vector<double>& pazymiai);
    Studentas(std::string vardas, std::string pavarde, double egzaminas,char vid_med, Vector<double>& pazymiai);
    Studentas(const Studentas& st);
    void BaseClass(){cout << "Studentas klase\n";}
    /*!
    * \return exam grade, type double
    */
    inline double getEgzaminas() const { return egzaminas;}
    /*!
    * \return final grade, type double
    */
    inline double getGalutinisBalas() const { return galutinis;}
    /*!
    * \return a vector of type double
    */
    inline Vector<double> getPazymiai() const { return pazymiai;}
    /*!
    * A function that sets the final grade.
    * @param galutinis - final grade, type double
    */
    void setGalutinisBalas(double galutinis) { this->galutinis = galutinis;}
    Studentas& operator=(const Studentas& st);
    friend std::ostream& operator<<(std::ostream &out, const Studentas& st);
    friend std::istream& operator>>(std::istream &in, Studentas& st);
    friend std::ofstream& operator<<(std::ofstream &out, const Studentas& st);
    friend std::ifstream& operator>>(std::ifstream &in, Studentas& st);
    ~Studentas();
};
bool StudentuLyginimas(const Studentas &, const Studentas &);
bool Galutinis5(const Studentas &);
double Vidurkis(Vector<double>&);
double Mediana(Vector<double>&);
double GalutinisBalas(Vector<double> &pazymiai, double egzaminas, double (*funkcija)(Vector<double> &)=Vidurkis);
template <typename T>
void VargsiukuIsvedimas(T &, char, int, int, int);
template <typename T>
void GalvociuIsvedimas(T &, char, int, int, int);
template <typename T>
void FailoSkaitymas(T &, std::string, char, int &, int &);
void FailoGeneravimas(std::string, int);
void FailuGeneravimas(int failu_kiekis, int failu_dydis);
void FailoPadalinimas(Vector<Studentas> &, Vector<Studentas> &, Vector<Studentas> &);
void FailoPadalinimas(deque<Studentas> &, deque<Studentas> &, deque<Studentas> &);
void FailoPadalinimas(list<Studentas> &, list<Studentas> &, list<Studentas> &);
void FailoPadalinimas(Vector<Studentas> &, Vector<Studentas> &);
void FailoPadalinimas(deque<Studentas> &, deque<Studentas> &);
void FailoPadalinimas(list<Studentas> &, list<Studentas> &);
template <typename T>
void VargsiukuIsvedimas(T &vargsiukai, char vid_med, int failo_dydis, int ilgiausia_pavarde, int ilgiausias_vardas)
{
    std::string vid = "Galutinis (Vid.)", med = "Galutinis (Med.)";
    int v_plotis = ilgiausias_vardas + 2 < 6 ? 8 : ilgiausias_vardas + 2, pav_plotis = ilgiausia_pavarde + 1 < 7 ? 8 : ilgiausia_pavarde + 1;
    std::stringstream ss;
    char(tolower(vid_med)) == 'v' ? ss << left << setw(pav_plotis) << "Pavarde " << left << setw(v_plotis) << "Vardas " << left << setw(vid.size()) << vid << endl : ss << left << setw(pav_plotis) << "Pavarde " << left << setw(v_plotis) << "Vardas " << left << setw(med.size()) << med << endl;
    for (int i = 0; i < v_plotis + pav_plotis + int(vid.size()); i++)
    {
        ss << "-";
    }
    ss << endl;
    for (const auto& i : vargsiukai)
    {
        ss << left << setw(pav_plotis) << i.getPavarde() << left << setw(v_plotis) << i.getVardas() << left << setw(vid.size()) << fixed << setprecision(2) << i.getGalutinisBalas() << endl;
    }
    std::fstream f;
    f.open("Vargsiukai" + std::to_string(failo_dydis) + ".txt", std::ios::out);
    try
    {
        if (!f)
        {
            throw "Nepavyko sukurti failo!";
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << '\n';
        exit(1);
    }
    f << ss.rdbuf();
    f.close();
}
template <typename T>
void GalvociuIsvedimas(T &galvociai, char vid_med, int failo_dydis, int ilgiausia_pavarde, int ilgiausias_vardas)
{
    std::string vid = "Galutinis (Vid.)", med = "Galutinis (Med.)";
    int v_plotis = ilgiausias_vardas + 2 < 6 ? 8 : ilgiausias_vardas + 2, pav_plotis = ilgiausia_pavarde + 1 < 7 ? 8 : ilgiausia_pavarde + 1;
    std::stringstream ss;
    char(tolower(vid_med)) == 'v' ? ss << left << setw(pav_plotis) << "Pavarde " << left << setw(v_plotis) << "Vardas " << left << setw(vid.size()) << vid << endl : ss << left << setw(pav_plotis) << "Pavarde " << left << setw(v_plotis) << "Vardas " << left << setw(med.size()) << med << endl;
    for (int i = 0; i < v_plotis + pav_plotis + int(vid.size()); i++)
    {
        ss << "-";
    }
    ss << endl;
    for (const auto& i : galvociai)
    {
        ss << left << setw(pav_plotis) << i.getPavarde() << left << setw(v_plotis) << i.getVardas() << left << setw(vid.size()) << fixed << setprecision(2) << i.getGalutinisBalas() << endl;
    }
    std::fstream f;
    f.open("Galvociai" + std::to_string(failo_dydis) + ".txt", std::ios::out);
    try
    {
        if (!f)
        {
            throw "Nepavyko sukurti failo!";
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << '\n';
        exit(1);
    }
    f << ss.rdbuf();
    f.close();
}
template <typename T>
void FailoSkaitymas(T &st, std::string failas, char vid_med, int &ilgiausia_pavarde, int &ilgiausias_vardas)
{
    std::fstream f;
    f.open(failas, std::ios::in);
    try
    {
        if (!f)
        {
            throw "Nepavyko atidaryti failo!";
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << '\n';
        exit(1);
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    buffer.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    f.close();
    std::string line, vardas, pavarde;
    double pazymys,egzaminas;
    Vector<double> pazymiai;
    while (getline(buffer, line))
    {
        std::stringstream readLine(line);
        readLine >> vardas >> pavarde;
        while (readLine >> pazymys)
        {
            pazymiai.push_back(pazymys);
        }
        egzaminas = pazymiai[pazymiai.size() - 1];
        pazymiai.pop_back();
        if (char(tolower(vid_med)) == 'v')
        {
            Studentas stud{vardas,pavarde,egzaminas,GalutinisBalas(pazymiai,egzaminas),pazymiai};
            st.push_back(stud);
        }
        else
        {
            Studentas stud{vardas,pavarde,egzaminas,GalutinisBalas(pazymiai,egzaminas,Mediana),pazymiai};
            st.push_back(stud); 
        }
        if (int(vardas.size()) > ilgiausias_vardas)
        {
            ilgiausias_vardas = vardas.size();
        }
        if (int(pavarde.size()) > ilgiausia_pavarde)
        {
            ilgiausia_pavarde = pavarde.size();
        }
        pazymiai.clear();
    }
}
#endif
