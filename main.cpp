#include <vector>
#include <chrono>
#include "Studentas.hpp"


const int failu_kiekis = 1;

int main()
{
    // unsigned int sz = 100000000;
    // std::vector<int> v1;
    // unsigned int r1 = 0;
    // for (int i = 1; i <= sz; ++i)
    // {
    //     if (v1.size()==v1.capacity())
    //     {
    //         r1++;
    //     }
    //     v1.push_back(i);
    // }
    // v1.clear();

    // Vector<int> v2;
    // unsigned int r2 = 0;
    // for (int i = 1; i <= sz; ++i)
    // {
    //     if (v2.size()==v2.capacity())
    //     {
    //         r2++;
    //     } 
    //     v2.push_back(i);
    // }
    // v2.clear();
    // std::cout << "konteinerio Vector ivykusiu atminties perskirstymu kiekis: "<<r2<<"\n";
    // std::cout << "konteinerio std::vector ivykusiu atminties perskirstymu kiekis: " << r1 <<"\n";
   
    // for(int j:{10000,100000,1000000,10000000,100000000})
    // {
    //     auto start = std::chrono::high_resolution_clock::now();
    //     for (int i = 1; i <= j; ++i)
    //     {
    //         v1.push_back(i);
    //     } 
    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double> diff =end-start;
    //     std::cout << j <<" int elementu i tuscia std::vector irasyti uztruko: " << diff.count() <<"\n";
    //     start = std::chrono::high_resolution_clock::now();
    //     for (int i = 1; i <= j; ++i)
    //     {
    //         v2.push_back(i);
    //     }
    //     end = std::chrono::high_resolution_clock::now();
    //     diff =end-start;
    //     std::cout << j <<" int elementu i tuscia Vector irasyti uztruko: " << diff.count() <<"\n";
    //     v1.clear();
    //     v2.clear();
    // }
  
    std::string failas;
    char vid_med = 'v';
    int failo_dydis = 100000, ilgiausia_pavarde = 0, ilgiausias_vardas = 0, n,strategija;
    FailuGeneravimas(failu_kiekis,failo_dydis);
    cout << "1 - 1 strategija" << '\n';
    cout << "2 - 2 strategija" << '\n';
    try
    {
        cin >> strategija;
        if (strategija!=1&&strategija!=2)
        {
            throw "tokia strategija neegzistuoja";
        }
        
    }
    catch (const char *zinute)
    {
        std::cerr << zinute << endl;
        exit(1);
    }
    cout << "1 - vector" << '\n';
    cout << "2 - list" << '\n';
    cout << "3 - deque" << '\n';
    cin >> n;
    switch (n)
    {
    case 1:
    {
        auto start = std::chrono::high_resolution_clock::now();
        Vector<Studentas> st, vargsiukai, galvociai;
        for (int i = 0; i < failu_kiekis; i++)
        {
            st.reserve(failo_dydis);
            failas = "Studentai" + std::to_string(failo_dydis) + ".txt";
            FailoSkaitymas(st, failas, vid_med, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? FailoPadalinimas(st, vargsiukai, galvociai):FailoPadalinimas(st, vargsiukai);
            VargsiukuIsvedimas(vargsiukai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? GalvociuIsvedimas(galvociai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas):GalvociuIsvedimas(st, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            vargsiukai.clear();
            galvociai.clear();
            st.clear();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end- start;
            cout << failo_dydis << " irasu failo testas uztruko: " << diff.count() << " s\n";
            ilgiausia_pavarde = 0, ilgiausias_vardas = 0;
            failo_dydis *= 10;
        }
        
    }
    break;
    case 2:
    {
        list<Studentas> st, vargsiukai, galvociai;
        for (int i = 0; i < failu_kiekis; i++)
        {
            
            failas = "Studentai" + std::to_string(failo_dydis) + ".txt";
            FailoSkaitymas(st, failas, vid_med, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? FailoPadalinimas(st, vargsiukai, galvociai):FailoPadalinimas(st, vargsiukai);
            VargsiukuIsvedimas(vargsiukai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? GalvociuIsvedimas(galvociai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas):GalvociuIsvedimas(st, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            vargsiukai.clear();
            galvociai.clear();
            st.clear();
            ilgiausia_pavarde = 0, ilgiausias_vardas = 0;
            failo_dydis *= 10;
        }
    }
    break;
    case 3:
    {
        deque<Studentas> st, vargsiukai, galvociai;
        for (int i = 0; i < failu_kiekis; i++)
        {
            failas = "Studentai" + std::to_string(failo_dydis) + ".txt";
            FailoSkaitymas(st, failas, vid_med, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? FailoPadalinimas(st, vargsiukai, galvociai):FailoPadalinimas(st, vargsiukai);
            VargsiukuIsvedimas(vargsiukai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            strategija == 1 ? GalvociuIsvedimas(galvociai, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas):GalvociuIsvedimas(st, vid_med, failo_dydis, ilgiausia_pavarde, ilgiausias_vardas);
            vargsiukai.clear();
            galvociai.clear();
            st.clear();
            ilgiausia_pavarde = 0, ilgiausias_vardas = 0;
            failo_dydis *= 10;
        }
    }
    break;
    default:
        break;
    }
    return 0;
}
