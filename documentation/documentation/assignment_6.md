# Opdracht 6: Testen en simuleren van de signaallamp-besturing



## 6.1 Inleiding

In dit practicum wordt het programma van de signaallamp-besturing getest. Het PSD van het volledige programma is gegeven in figuur 1.

![image](../images/psd_volledige_besturing.png)

*Figuur 1. PSD van het volledige besturingsprogramma*

 :::{tip}

- *MAAK GEBRUIK VAN DE UITWERKINGEN VAN DE PRACTICA VAN WEEK 8: DEZE BEVATTEN NU IMMERS ALLE FUNCTIONELE EN BENODIGDE CODE!*

- Het is niet verplicht om PSD’s te maken, maar gebruik ervan is uiteraard wel toegestaan om zaken te verduidelijken.

- Maak voor dit practicum gebruik van het framework programma FrameworkWeek8.zip op Brightspace. Extract dit bestand in een geschikte directory, bij voorkeur op je homedrive op het Avans netwerk. Open hierna de file FrameworkWeek8.atsln met Microchip Studio. Voeg op de aangegeven plaatsen de uitwerkingen van onderstaande opdrachten in.

- Demonstreer de uitwerking van de opdrachten/ programma’s aan de docent.
:::

## 6.2 Integratie en simulatietesten van de geïmplementeerde functies

Alle tot dusver gemaakte code moet eerst worden getest, voordat de Arduino + shield wordt aangesloten op de level shifter en de PLC van de besturing van de lopende band. Het testen is als volgt gefaseerd:

1. Testen en simuleren van de functionaliteit met behulp van uitsluitend de Arduino + shield
2. Testen van de Arduino + shield in combinatie met de PLC Simulator
3. Test van de Arduino + shield in combinatie met de PLC (dit is feitelijk onderdeel van de de SAT: Site Acceptance Test)

In dit practicum wordt de functionaliteit met behulp van de knoppen op het shield gesimuleerd (simulatie 1). 


## 6.3 Test 1: Arduino + shield

In deze test wordt de code getest en gesimuleerd met de drukknoppen (= simulatie van het SYNC signaal en de functiecode) en de LED’s op het shield.

Deze simulatie wijkt enigszins af van de testen 2 en 3, omdat de knoppen op het shield een `GEÏNVERTEERDE` werking hebben: een ingedrukte knop levert een logische ‘1’, een niet-ingedrukte knop een logische ‘0’. Dit is afhankelijk van de hardware. Dit kan worden opgelost door de code die nodig is voor de simulatie minimaal aan te passen. De plaats waar dit moet worden aangepast is in de functie IsSyncBitSet, waar de waarde wordt bepaald van het SYNC-bit. Zie ook het practicum van week 7.

N.B.: voor de hierna volgende testen 2 en 3 moet weer gebruik worden gemaakt van de “gewone” (niet-aangepaste) code van IsSyncBitSet.

 
De simulatie met de drukknoppen en de LED’s gaat als volgt:

1. simuleer een functiecode met een waarde tussen 0 en 7 door het indrukken van 0 of meer van de drukknoppen D2..D0 (maximaal 3 vingers nodig…). Houd deze knoppen ingedrukt.

2. Druk vervolgens op drukknop D3 om een opgaande flank van het SYNC signaal te simuleren.

3. Bij een correcte simulatie gaan de bijbehorende LED’s B3..B0 aan, evenals de SYNC LED (LED B6).

4. Bij een correcte simulatie gaat ook LED B7 aan (meest rechter LED): op het shield is deze nl. rechtstreeks gekoppeld aan het ACK (acknowledge) signaal.

5. Laat de drukknoppen D2..D0 los.

6. Laat drukknop D3 los, dit simuleert het inactief worden van het SYNC signaal.

7. Bij een correcte simulatie gaat zowel de SYNC LED (LED B7) als de ACK LED (LED B6) uit.


## 6.4 Test 2: Arduino + shield + signaalzuil simulator

Wanneer test 1 succesvol is uitgevoerd, kan de LED-bar met kleuren-LEDS worden aangesloten, als simulatie van de signaalzuil. Controleer op identieke wijze als bij test 1, of de juiste kleuren-LED’s worden aangestuurd.

Sluit het Arduino shield en de LED-bar aan zoals aangegeven in tabel 1 en figuur 1.

|Arduino shield	|LED-bar|
|-------------------------|-------------------------|
|+24V	|+24V|
|L0	|R (red)|
|L1	|Y (yellow)|
|L2	|G (green)|
|L3	|N (blue)|

*Tabel 1. Aansluitingen Arduino shield en LED-bar*

 
![image](../images/arduino-shield-led-bar.png)
*Figuur 1. Aansluitingen Arduino shield en LED-bar*


## 6.5 Test 3: Arduino + shield + level shifter + PLC-simulator

Wanneer test 2 met succes is afgerond, kan de functionaliteit van de drukknoppen voor de besturing van de handshakesignalen worden “vervangen” door besturing via de PLC inputs. Hiervoor wordt gebruik gemaakt van een PLC-simulator, die via de level shifter wordt aangesloten op het Arduino-shield. De PLC-simulator genereert signalen die qua timing en signaalniveaus identiek zijn aan de daadwerkelijk toegepaste PLC.

N.B.: de level shifter moet uiteraard zijn voorzien van de juiste weerstanden, zoals die zijn uitgerekend bij het practicum Netwerken! Daarnaast moeten in dat practicum ook de spanningen zijn getest van de level shifter en goed zijn bevonden!

Sluit de PLC-simulator en de  level-shifter aan zoals aangegeven in tabel 2 en figuur 2.

PLC-simulator	Level shifter
|-------------------------|-------------------------|
|+24V OUT	|+24VDC IN|
|ACK IN	|PLC ACK OUT|
|SYNC OUT	|PLC SYNC IN|
|FC2 OUT	|PLC IN 2|
|FC1 OUT	|PLC IN 1|
|FC0 OUT	|PLC IN 0|

*Tabel 2. Aansluitingen PLC-simulator en level shifter*

 
![image](../images/plc-simulator-level-shifter.png)
*Figuur 2. Aansluitingen PLC-simulator en level shifter*


Sluit de level-shifter en het Arduino shield aan zoals aangegeven in tabel 3 en figuur 3.


|Level shifter	|Arduino shield|
|-------------------------|-------------------------|
|ACK IN	|ACK OUT|
|SYNC OUT	|SYNC IN|
|OUT0	|IN0|
|OUT1	|IN1|
|OUT2	|IN2|
|GND	|GND|

*Tabel 3. Aansluitingen level shifter en Arduino shield*
![image](../images/level-shifter-arduino-shield.png)

 
*Figuur 3.  Aansluitingen level shifter en Arduino shield*

 
Op de PLC-simulator zijn een aantal standaard programma’s beschikbaar die de signaalzuil aansturen, zie tabel 4. 

|simulatie-programma | functie|
|-------------------------|-------------------------|
|0	|PLC simulator staat uit en genereert geen handshake signalen|
|1	|stuur permanent function code 0 uit (groen)|
|2	|stuur permanent function code 1 uit (geel)|
|3	|stuur permanent function code 2 uit (rood)|
|4	|stuur permanent function code 3 uit (groen + geel)|
|5	|stuur permanent function code 4 uit (rood + geel)|
|6	|stuur permanent function code 5 uit (blauw)|
|7	|stuur permanent function code 6 uit (blauw)|
|8	|stuur permanent function code 7 uit (blauw)|
|9	|stuur permanent achtereenvolgens de functiecodes 0 t/m 7 uit met tussenpauzes van een halve seconde.|

*Tabel 4. PLC simulatieprogramma’s*


Met de draaiknop PROGRAM SELECT kan het gewenste simulatieprogramma worden geselecteerd. Op het OLED-scherm wordt deze keuze weergegeven, evenals de functiecode.

Bij de simulatieprogramma’s 1 t/m 9 moet altijd een volledige handshake worden uitgevoerd met het SYNC- en het ACK-signaal! De status van deze signalen is te zien op de PLC-simulator met de SYNC-LED (oranje) en de ACK-LED (groen). Daarnaast zijn de status en eventuele foutmeldingen te zien op het OLED-scherm. Wanneer de handshake niet volledig wordt uitgevoerd, zullen de LED’s niet correct reageren.

Controleer of alle simulatieprogramma’s uit tabel 1 correct functioneren. Zo niet, controleer dan eerst de bedrading en de aansluitingen. Als het probleem niet is opgelost, zoek dan de fout in de code en pas de code aan voor de Arduino. 


## 6.6 Test 4: Arduino + shield + LED bar + level shifter + besturings-PLC

Wanneer test 3 met succes is afgerond, kan de integratietest worden uitgevoerd, waarbij de PLC van de transportband, de level shifter en de Arduino functioneel wordt getest. Sluit hiervoor de level shifter aan op de PLC i.p.v. op de PLC-simulator. Voer vervolgens het testprogramma uit op de PLC, zodanig dat deze de juiste signalen genereert (dit PLC-programma wordt kant-en-klaar aangeleverd).


 
## 6.7 Test 5: Arduino + shield + signaalzuil + level shifter + besturings-PLC

Wanneer test 4 met succes is afgerond, kan de LED bar met de kleuren-LED’s worden vervangen door de signaalzuil. Controleer uiteraard of de juiste kleuren op de LED’s worden weergegeven!

