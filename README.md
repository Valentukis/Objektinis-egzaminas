# Teksto analizės programa (C++)

Ši programa analizuoja pateiktą teksto failą (`tekstas.txt`) ir atlieka šiuos veiksmus:

---

##  Funkcionalumas

1. **Žodžių dažnis (`output_count.txt`)**
   - Suskaičiuoja, kiek kartų kiekvienas žodis pasikartoja
   - Išveda tik tuos žodžius, kurie pasirodo **daugiau nei vieną kartą**
   - Atpažįsta lietuviškas raides ir ignoruoja skyrybos ženklus

![image](https://github.com/user-attachments/assets/b85abcaf-1993-4890-949f-2bd8b26a320d)

2. **Žodžių eilučių nuorodos (`cross_reference.txt`)**
   - Sukuria lentelę, kuri nurodo, kuriose teksto eilutėse (pagal eilutės numerį) daugiau nei kartą pasikartojantys žodžiai buvo paminėti

![image](https://github.com/user-attachments/assets/5531133c-11c8-4a11-bfe5-067aca1cbc2c)

3. **URL'ų surinkimas (`output_urls.txt`)**
   - Iš tekstinio failo išrenka visus galimus URL adresus
   - Patikrina, ar domeno galūnė (TLD) yra reali, naudodama `tlds_cleaned.txt` (TLD sąrašą)
   - Palaiko formatus: `https://`, `http://`, `www.`, trumpus domenus (`vu.lt`), su keliomis subdomenų dalimis ir keliais
   - Pašalina pasikartojančius URL 

![image](https://github.com/user-attachments/assets/b9a8a5a6-6330-437d-b22d-2b1992b2ce5f)
---

##  Reikalingi failai

- `tekstas.txt` – teksto failas, kurį reikia apdoroti
- `links.txt` – galimų domenų galūnių (TLD) sąrašas (pvz. `lt`, `com`, `org`, ...)

---

##  Paleidimas
- Paprastas paleidimas su Makefile
- `make` Sukuria paleidžiamąjį failą `programa.exe`
- `make clean` Ištrina paleidžiamąjį failą

![image](https://github.com/user-attachments/assets/62f9323a-bde2-4ec4-b515-01d26d24a654)

