#include <random>
#include <sstream>
#include "Studentas.hpp"
/*!
 * Overloading operator >> of ifstream class for Studentas class.
 * @param in - reference to a ifstream class object
 * @param st - reference to a Studentas class object
 * \return reference to an ifstream class object 
 */
std::ifstream &operator>>(std::ifstream &in, Studentas &st)
{
    char vid_med;
    cout << "Galutiniam balui skaiciuoti naudoti vidurki ar mediana [v/m]: ";
    cin >> vid_med;
    st.pazymiai.clear();
    in >> st.vardas >> st.pavarde;
    try
    {
    double pazymys;
    while (in >> pazymys)
    {
        if (pazymys > 10 || pazymys < 1)
        {
            throw "Pazymio intervalas [1,10] pazeistas";
        }
        st.pazymiai.push_back(pazymys);
    }
    st.egzaminas = st.pazymiai[st.pazymiai.size() - 1];
    st.pazymiai.pop_back();
    }
    catch(const char* zinute)
    {
        std::cerr << zinute << '\n';
        exit(1);
    }
    if (char(tolower(vid_med)) == 'v')
    {
        st.galutinis = GalutinisBalas(st.pazymiai,st.egzaminas);
    }
    else
    {
        st.galutinis = GalutinisBalas(st.pazymiai,st.egzaminas,Mediana);
    }
    return in;
}
/*!
 * Overloading operator << of ofstream class for Studentas class.
 * @param out - reference to a ofstream class object
 * @param st - reference to a Studentas class object
 * \return reference to an ofstream class object
 */
std::ofstream &operator<<(std::ofstream &out, const Studentas &st)
{
    out << st.vardas << " " << st.pavarde<< " ";
    for (const auto &i : st.pazymiai)
    {
        out << i << " ";
    }
    out << st.egzaminas;
    return out;
}
/*!
 * Overloading operator << of ostream class for Studentas class.
 * @param out - reference to a ostream class object
 * @param st - reference to a Studentas class object
 * \return reference to an ostream class object
 */
std::ostream &operator<<(std::ostream &out, const Studentas &st)
{
    out << st.vardas << " " << st.pavarde<< " ";
    for (const auto &i : st.pazymiai)
    {
        out << i << " ";
    }
    out << st.egzaminas;
    return out;
}
/*!
 * Overloading operator << of istream class for Studentas class.
 * @param out - reference to a istream class object
 * @param st - reference to a Studentas class object
 * \return reference to an istream class object
 */
std::istream &operator>>(std::istream &in, Studentas &st)
{
    st.pazymiai.clear();
    cout << "Studento vardas: ";
    in >> st.vardas;
    cout << "Studento pavarde: ";
    in >> st.pavarde;
    cout << "Studento egzamino pazymys: ";
    in >> st.egzaminas;
    cout << "Studento namu darbu pazymiai (norint nustoti vesti, iveskite 0):" << endl;
    double pazymys;
    try
    {
        int i = 1;
        cout << i << " pazymys: ";
        i++;
        while (in >> pazymys && pazymys != 0)
        {
            cout << i << " pazymys: ";
            if (pazymys > 10 || pazymys < 1)
            {
                throw "Pazymio intervalas [1,10] pazeistas";
            }
            st.pazymiai.push_back(pazymys);
            i++;
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << '\n';
        exit(1);
    }
    char vid_med;
    cout << "Galutiniam balui skaiciuoti naudoti vidurki ar mediana [v/m]: ";
    cin >> vid_med;
    if (char(tolower(vid_med)) == 'v')
    {
        st.galutinis = GalutinisBalas(st.pazymiai,st.egzaminas);
    }
    else
    {
        st.galutinis = GalutinisBalas(st.pazymiai,st.egzaminas,Mediana);
    }
    return in;
}
/*!
 * Assignment operator.
 * @param st - reference to a Studentas class object
 * \return reference to a Studentas class object
 */
Studentas &Studentas::operator=(const Studentas &st)
{
    if (this != &st)
    {
        vardas = st.vardas;
        pavarde = st.pavarde;
        egzaminas = st.egzaminas;
        galutinis = st.galutinis;
        pazymiai = st.pazymiai;
    }
    return *this;
}
/*!
 * Studentas class copy constructor.
 * @param st - reference to a Studentas class object
 */
Studentas::Studentas(const Studentas &st)
{
    vardas = st.vardas;
    pavarde = st.pavarde;
    egzaminas = st.egzaminas;
    galutinis = st.galutinis;
    pazymiai = st.pazymiai;
}
/*!
 * Studentas class constructor.
 * @param vardas - first name, type string 
 * @param pavarde - last name, type string 
 * @param egzaminas - exam grade, type double
 * @param galutinis - final grade, type double
 * @param pazymiai - reference to a vector of type double
 */
Studentas::Studentas(std::string vardas, std::string pavarde, double egzaminas, double galutinis, Vector<double>& pazymiai)
{
    this->vardas = vardas;
    this->pavarde = pavarde;
    this->egzaminas = egzaminas;
    this->galutinis = galutinis;
    this->pazymiai = pazymiai;
}
/*!
 * Studentas class constructor.
 * @param vardas - first name, type string 
 * @param pavarde - last name, type string 
 * @param egzaminas - exam grade, type double
 * @param vid_med - character, which defines the final grade counting method, 'v' - using average, 'm' - using the median, type char
 * @param pazymiai - reference to a vector of type double
 */
Studentas::Studentas(std::string vardas, std::string pavarde, double egzaminas,char vid_med, Vector<double>& pazymiai)
{
    this->vardas = vardas;
    this->pavarde = pavarde;
    this->egzaminas = egzaminas;
    if (char(tolower(vid_med)) == 'v')
    {
    this->galutinis = GalutinisBalas(pazymiai,egzaminas);
    }
    else
    {
    this->galutinis = GalutinisBalas(pazymiai,egzaminas,Mediana);    
    }
    this->pazymiai = pazymiai;
}
/*!
 * Studentas class destructor.
 */
Studentas::~Studentas() {}
/*!
 * Zmogus class destructor.
 */
Zmogus::~Zmogus(){}
/*!
 * Function used to compare two students by their final grades.
 * @param st1 - reference to a Studentas class object 
 * @param st2 - reference to a Studentas class object
 * \return True if the first student has a lower final grade than the second student, otherwise False
 */
bool StudentuLyginimas(const Studentas &st1, const Studentas &st2)
{
    return st1.getGalutinisBalas() < st2.getGalutinisBalas();
}
/*!
 * Function used to divide students based on their final grade.
 * @param st1 - reference to a Studentas class object 
 * \return True if student's final grade is more or equal to 5, otherwise False
 */
bool Galutinis5(const Studentas &st1)
{
    return st1.getGalutinisBalas() >= 5;
}
/*!
 * Function that counts the average of homework grades.
 * @param pazymiai - reference to a vector of type double 
 * \return the average of homework grades, type double
 */
double Vidurkis(Vector<double> &pazymiai)
{
    try
    {
        if (pazymiai.size() == 0)
        {
            throw "Negalima skaičiuoti vidurkio, nes studentas neturi pažymių";
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << endl;
        exit(1);
    }
    double suma = 0;
    for (int i = 0; i < int(pazymiai.size()); i++)
    {
        suma += pazymiai[i];
    }
    return suma / pazymiai.size();
}
/*!
 * Function that counts the median of homework grades.
 * @param pazymiai - reference to a vector of type double 
 * \return the median of homework grades, type double
 */
double Mediana(Vector<double> &pazymiai)
{
    try
    {
        if (pazymiai.size() == 0)
        {
            throw "Negalima skaičiuoti medianos, nes studentas neturi pažymių";
        }
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << endl;
        exit(1);
    }
    std::sort(pazymiai.begin(), pazymiai.end());
    return pazymiai.size() % 2 == 0 ? (pazymiai[pazymiai.size() / 2 - 1] + pazymiai[pazymiai.size() / 2]) / 2.0 : pazymiai[pazymiai.size() / 2];
}
/*!
 * Function that counts the final grade.
 * @param pazymiai - reference to a vector of type double
 * @param egzaminas - reference to a vector of type double 
 * @param funkcija - function pointer (Mediana for median and Vidurkis for average) 
 * \return the final grade, type double
 */
double GalutinisBalas(Vector<double> &pazymiai, double egzaminas, double (*funkcija)(Vector<double> &))
{
    return funkcija(pazymiai) * 0.4 + egzaminas * 0.6;
}
/*!
 * Function that generates student files.
 * @param failas - file name, type string
 * @param dydis - size of records in the file, type int
 */
void FailoGeneravimas(std::string failas, int dydis)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    std::uniform_int_distribution<int> dist2(5, 30);
    std::string ilgVard = "Vardas" + std::to_string(dydis), ilgPav = "Pavarde" + std::to_string(dydis);
    int plotisVard = int(ilgVard.size())+1, plotisPav = int(ilgPav.size())+1, nd_kiekis = dist2(mt);
    std::stringstream ss;
    ss << setw(plotisVard) << left << "Vardas" << setw(plotisPav) << right << "Pavarde";
    for (int i = 1; i <= nd_kiekis; i++)
    {
        ss << setw(10) << right << "ND" + std::to_string(i) << " ";
    }
    ss << setw(10) << right << "Egz." << '\n';
    for (int i = 1; i <= dydis; i++)
    {
        ss << setw(plotisVard) << left << "Vardas" + std::to_string(i) << setw(plotisPav) << right << "Pavarde" + std::to_string(i);
        for (int j = 0; j < nd_kiekis; j++)
        {
            ss << setw(10) << right << dist(mt) << " ";
        }
        ss << '\n';
    }
    std::fstream f;
    f.open(failas, std::ios::out);
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
/*!
 * Function that assures that files are only generated once.
 * @param failu_kiekis - file count, type int
 * @param failo_dydis - size of records in the file, type int
 */
void FailuGeneravimas(int failu_kiekis, int failo_dydis)
{
    std::string failas;
    std::ifstream f;
    f.open("Studentai1000.txt");
    if (!f)
    {
        for (int i = 0; i < failu_kiekis; i++)
        {
            failas = "Studentai" + std::to_string(failo_dydis) + ".txt";
            FailoGeneravimas(failas, failo_dydis);
            failo_dydis *= 10;
        }
    }
    f.close();
}
/*!
 * Function that divides students into two vectors based on their final grade, using two additional containers.
 * @param st - reference to a vector of Studentas class objects
 * @param vargsiukai - reference to a vector of Studentas class objects
 * @param galvociai - reference to a vector of Studentas class objects
 */
void FailoPadalinimas(Vector<Studentas> &st, Vector<Studentas> &vargsiukai, Vector<Studentas> &galvociai)
{

    std::sort(st.begin(), st.end(), StudentuLyginimas);
    auto it = std::find_if(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(st.begin(), it);
    galvociai.assign(it, st.end());
    std::sort(vargsiukai.begin(), vargsiukai.end());
    std::sort(galvociai.begin(), galvociai.end());
    st.clear();
}
/*!
 * Function that divides students into two deques based on their final grade, using two additional containers.
 * @param st - reference to a deque of Studentas class objects
 * @param vargsiukai - reference to a deque of Studentas class objects
 * @param galvociai - reference to a deque of Studentas class objects
 */
void FailoPadalinimas(deque<Studentas> &st, deque<Studentas> &vargsiukai, deque<Studentas> &galvociai)
{
    std::sort(st.begin(), st.end(), StudentuLyginimas);
    auto it = std::find_if(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(st.begin(), it);
    galvociai.assign(it, st.end());
    std::sort(vargsiukai.begin(), vargsiukai.end());
    std::sort(galvociai.begin(), galvociai.end());
    st.clear();
}
/*!
 * Function that divides students into two lists based on their final grade, using two additional containers.
 * @param st - reference to a list of Studentas class objects
 * @param vargsiukai - reference to a list of Studentas class objects
 * @param galvociai - reference to a list of Studentas class objects
 */
void FailoPadalinimas(list<Studentas> &st, list<Studentas> &vargsiukai, list<Studentas> &galvociai)
{
    st.sort(StudentuLyginimas);
    auto it = std::find_if(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(st.begin(), it);
    galvociai.assign(it, st.end());
    vargsiukai.sort();
    galvociai.sort();
    st.clear();
}
/*!
 * Function that divides students into two vectors based on their final grade, using only one additional container.
 * @param st - reference to a vector of Studentas class objects
 * @param vargsiukai - reference to a vector of Studentas class objects
 * @param galvociai - reference to a vector of Studentas class objects
 */
void FailoPadalinimas(Vector<Studentas> &st, Vector<Studentas> &vargsiukai)
{
    auto it = std::partition(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(it, st.end());
    st.assign(st.begin(), it);
    std::sort(vargsiukai.begin(), vargsiukai.end());
    std::sort(st.begin(), st.end());
}
/*!
 * Function that divides students into deques based on their final grade, using only one additional container.
 * @param st - reference to a deque of Studentas class objects
 * @param vargsiukai - reference to a deque of Studentas class objects
 * @param galvociai - reference to a deque of Studentas class objects
 */
void FailoPadalinimas(deque<Studentas> &st, deque<Studentas> &vargsiukai)
{
    auto it = std::partition(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(it, st.end());
    st.assign(st.begin(), it);
    std::sort(vargsiukai.begin(), vargsiukai.end());
    std::sort(st.begin(), st.end());
}
/*!
 * Function that divides students into lists based on their final grade, using only one additional container.
 * @param st - reference to a list of Studentas class objects
 * @param vargsiukai - reference to a list of Studentas class objects
 * @param galvociai - reference to a list of Studentas class objects
 */
void FailoPadalinimas(list<Studentas> &st, list<Studentas> &vargsiukai)
{
    auto it = std::partition(st.begin(), st.end(), Galutinis5);
    vargsiukai.assign(it, st.end());
    st.assign(st.begin(), it);
    vargsiukai.sort();
    st.sort();
}
