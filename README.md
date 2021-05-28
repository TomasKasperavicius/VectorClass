# VectorClass
## Funkcijos push_back() testavimas su originaliu std::vector ir mano sukurtu Vector:
Elementų skaičius | std::vector      | Mano Vector | 
-------------  | ------------- | ------------- | 
10000        | 0.0001071 | 0.0000761 | 
100000       | 0.0010502 | 0.00096 | 
1000000        | 0.0095187 | 0.0081679 |
10000000       | 0.0878503 | 0.0768063 | 
100000000        | 0.853105 | 0.761467 |
* Mano sukurtas Vector veikia sparčiau nei originalus std::vector.
## Programos veikimo laikas su std::vector ir mano sukurtu Vector:
Studentų skaičius | std::vector      | Mano Vector | 
-------------  | ------------- | ------------- | 
100000        | 0.69175 s | 0.407146 s |
* Mano sukurtas Vector veikia sparčiau nei originalus std::vector.
## Mano Vector ir std::vector atminties perskirstymų kartai, užpildant 100000000 elementų:
![image](https://user-images.githubusercontent.com/78591148/119956188-806df480-bfa9-11eb-8fff-7097c5a1df9e.png)
* Mano sukurtas Vector atlieka tiek pat atminties perskirstymų kaip ir originalus std::vector.

## Mano sukurto Vector funkcionalumo tikrinimas, lyginant su std::vector:
* Funkcija push_back():

![image](https://user-images.githubusercontent.com/78591148/119957785-15252200-bfab-11eb-8274-a53868d76d62.png)
![image](https://user-images.githubusercontent.com/78591148/119957853-21a97a80-bfab-11eb-88ba-11c18066eac4.png)
* Funkcija at():

![image](https://user-images.githubusercontent.com/78591148/119958226-849b1180-bfab-11eb-8313-b17753e6412c.png)
![image](https://user-images.githubusercontent.com/78591148/119958299-941a5a80-bfab-11eb-9063-abadfcb0829b.png)
* Funkcija pop_back():

![image](https://user-images.githubusercontent.com/78591148/119958707-f3786a80-bfab-11eb-8f5f-0676401e5633.png)
![image](https://user-images.githubusercontent.com/78591148/119958755-01c68680-bfac-11eb-86e9-b158921cbed9.png)
* Funkcija swap():

![image](https://user-images.githubusercontent.com/78591148/119959341-98934300-bfac-11eb-8da6-11a1cb0366bb.png)

![image](https://user-images.githubusercontent.com/78591148/119959543-c4162d80-bfac-11eb-9057-ad1690358004.png)
* Funkcija resize():

![image](https://user-images.githubusercontent.com/78591148/119960066-4272cf80-bfad-11eb-9cd5-3130cf73e688.png)
![image](https://user-images.githubusercontent.com/78591148/119960125-4dc5fb00-bfad-11eb-99ac-735fc877887f.png)


