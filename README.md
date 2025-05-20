# Teksto analizės programa (C++)

Ši programa analizuoja pateiktą teksto failą (`tekstas.txt`) ir atlieka šiuos veiksmus:

---

##  Funkcionalumas

1. **Žodžių dažnis (`output_count.txt`)**
   - Suskaičiuoja, kiek kartų kiekvienas žodis pasikartoja
   - Išveda tik tuos žodžius, kurie pasirodo **daugiau nei vieną kartą**
   - Atpažįsta lietuviškas raides ir ignoruoja skyrybos ženklus

2. **Žodžių eilučių nuorodos (`cross_reference.txt`)**
   - Sukuria lentelę, kuri nurodo, kuriose teksto eilutėse (pagal eilutės numerį) daugiau nei kartą pasikartojantys žodžiai buvo paminėti

3. **URL'ų surinkimas (`output_urls.txt`)**
   - Iš tekstinio failo išrenka visus galimus URL adresus
   - Patikrina, ar domeno galūnė (TLD) yra reali, naudodama `tlds_cleaned.txt` (TLD sąrašą)
   - Palaiko formatus: `https://`, `http://`, `www.`, trumpus domenus (`vu.lt`), su keliomis subdomenų dalimis ir keliais
   - Pašalina pasikartojančius URL

---

##  Reikalingi failai

- `tekstas.txt` – teksto failas, kurį reikia apdoroti
- `tlds_cleaned.txt` – galimų domenų galūnių (TLD) sąrašas (pvz. `lt`, `com`, `org`, ...)

---

