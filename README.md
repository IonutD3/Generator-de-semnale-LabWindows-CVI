# Generator de semnale – LabWindows/CVI

## 🇷🇴 Română

### Descriere

Acest proiect este o aplicație realizată în **National Instruments LabWindows/CVI** pentru generarea și afișarea în timp real a patru tipuri de semnale de referință:

1. **Treaptă**
2. **Rampă**
3. **Sinusoidal**
4. **Triunghiular**

Semnalul este generat la fiecare perioadă de eșantionare și este afișat pe graficul aplicației.

### Funcționarea semnalelor

#### 1. Semnal treaptă

Valoarea semnalului este preluată direct din controlul **REFERINTA** al interfeței. Semnalul rămâne constant la valoarea aleasă până când utilizatorul o modifică.

#### 2. Semnal rampă

Rampa pornește de la valoarea curentă a semnalului în momentul selectării și evoluează cu panta introdusă în controlul **M PANTA**.

La schimbarea către rampă, valoarea inițială este memorată în `Refk0`, astfel încât rampa să înceapă din valoarea existentă și să nu producă un salt artificial la comutare.

#### 3. Semnal sinusoidal

Sinusul este definit prin:

- **A SINUS** – amplitudinea;
- **T SINUS** – perioada.

Semnalul este calculat în jurul valorii `Refk0`. La comutările între sinusuri, programul poate aștepta trecerea prin valoarea de bază pentru a evita o schimbare bruscă de fază.

#### 4. Semnal triunghiular

Semnalul triunghiular este definit prin:

- **INALTIME** – diferența dintre valoarea de bază și vârful triunghiului;
- **PERIOADA** – durata unui ciclu complet.

La selectarea triunghiului, valoarea curentă este memorată ca `Refk0`. Triunghiul urcă de la `Refk0` la `Refk0 + INALTIME` în prima jumătate a perioadei și revine la `Refk0` în a doua jumătate.

Formula este parametrizată în funcție de înălțime și perioadă, astfel încât nu este limitată la valori precum `INALTIME = 1` și `PERIOADA = 1 s`.

### Comutarea între semnale

Pentru semnalele continue, la selectarea unui nou tip de semnal se memorează valoarea curentă în `Refk0`. Astfel:

- Treaptă → Rampă: rampa pornește din valoarea curentă;
- Treaptă → Sinus: sinusul pornește din valoarea curentă;
- Treaptă → Triunghi: triunghiul pornește din valoarea curentă;
- Rampă → Triunghi: triunghiul pornește din valoarea curentă;
- Sinus → Triunghi: triunghiul pornește din valoarea curentă;
- Triunghi → Rampă: rampa pornește din valoarea curentă;
- Triunghi → Sinus: sinusul pornește din valoarea curentă.

O trecere către un semnal treaptă cu o valoare diferită poate produce în mod normal o discontinuitate, deoarece o treaptă schimbă instantaneu valoarea de referință. Aceasta este proprietatea semnalului treaptă și nu un defect al generatorului triunghiular.

### Parametri de eșantionare

Aplicația folosește:

- `Te = 0,01 s` – perioada de eșantionare;
- actualizarea graficului se face la fiecare eveniment al timerului.

Pentru o reprezentare cât mai precisă a unui semnal triunghiular discret, este recomandat ca perioada triunghiului să fie compatibilă cu perioada de eșantionare.

### Structura proiectului

```text
Generator-de-semnale–LabWindows-CVI/
│
├── src/
│   ├── semnale_T_R_S.c
│   ├── semnale_T_R_S.h
│   ├── 00_Declaratii_Variabile_S.h
│   ├── 01_Functionare_A_M_S.h
│   ├── 02_Functii_Utilitare_S.h
│   └── 03_Generare_Semnale_S.h
│
├── ui/
│   └── semnale_T_R_S.uir
│
├── project/
│   ├── Task01.prj
│   └── Task01.cws
│
└── README.md
```

### Compilare

Proiectul necesită **National Instruments LabWindows/CVI**. Fișierele de build generate automat și executabilele nu sunt incluse în versiunea curată a repository-ului.

---

## 🇬🇧 English

### Description

This project is an application developed in **National Instruments LabWindows/CVI** for real-time generation and display of four reference signal types:

1. **Step**
2. **Ramp**
3. **Sinusoidal**
4. **Triangular**

The signal is generated at every sampling period and displayed on the application graph.

### Signal operation

#### 1. Step signal

The signal value is read directly from the **REFERINTA** control on the user interface. The signal remains constant at the selected value until the user changes it.

#### 2. Ramp signal

The ramp starts from the current signal value when it is selected and evolves with the slope entered in the **M PANTA** control.

When switching to the ramp, the initial value is stored in `Refk0`, allowing the ramp to start from the current value instead of creating an artificial jump at the switching instant.

#### 3. Sinusoidal signal

The sinusoidal signal is defined by:

- **A SINUS** – amplitude;
- **T SINUS** – period.

The signal is generated around the `Refk0` base value. During sinusoidal switching, the program can wait for a crossing of the base value in order to avoid an abrupt phase change.

#### 4. Triangular signal

The triangular signal is defined by:

- **INALTIME** – the difference between the base value and the triangle peak;
- **PERIOADA** – the duration of one complete cycle.

When the triangular signal is selected, the current value is stored as `Refk0`. The triangle rises from `Refk0` to `Refk0 + INALTIME` during the first half of the period and returns to `Refk0` during the second half.

The formula is parameterized by both height and period, so it is not limited to values such as `INALTIME = 1` and `PERIOADA = 1 s`.

### Switching between signals

For continuous signals, the current value is stored in `Refk0` when a new signal type is selected. Therefore:

- Step → Ramp: the ramp starts from the current value;
- Step → Sinusoidal: the sinusoidal signal starts from the current value;
- Step → Triangular: the triangular signal starts from the current value;
- Ramp → Triangular: the triangular signal starts from the current value;
- Sinusoidal → Triangular: the triangular signal starts from the current value;
- Triangular → Ramp: the ramp starts from the current value;
- Triangular → Sinusoidal: the sinusoidal signal starts from the current value.

Switching to a step signal with a different target value can naturally create a discontinuity because a step signal changes its reference value instantaneously. This is a property of the step signal, not a defect of the triangular generator.

### Sampling parameters

The application uses:

- `Te = 0.01 s` – sampling period;
- the graph is updated at every timer event.

For the most accurate representation of a discrete triangular signal, it is recommended that the triangular period be compatible with the sampling period.

### Project structure

```text
Generator-de-semnale–LabWindows-CVI/
│
├── src/
│   ├── semnale_T_R_S.c
│   ├── semnale_T_R_S.h
│   ├── 00_Declaratii_Variabile_S.h
│   ├── 01_Functionare_A_M_S.h
│   ├── 02_Functii_Utilitare_S.h
│   └── 03_Generare_Semnale_S.h
│
├── ui/
│   └── semnale_T_R_S.uir
│
├── project/
│   ├── Task01.prj
│   └── Task01.cws
│
└── README.md
```

### Build

The project requires **National Instruments LabWindows/CVI**. Automatically generated build files and executables are not included in the clean repository version.


---

## Autor / Author

**IonutD**