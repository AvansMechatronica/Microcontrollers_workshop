# Opdracht 4: Oefenen met functies in C



## Inleiding

In dit practicum wordt geoefend met functies in de taal C.

:::{tip}

- Het is niet verplicht om PSD’s te maken, maar gebruik ervan is uiteraard wel toegestaan om zaken te verduidelijken.

- Maak voor dit practicum gebruik van het framework programma FrameworkWeek6.zip op Brightspace. Extract dit bestand in een geschikte directory, bij voorkeur op je homedrive op het Avans netwerk. Open hierna de file FrameworkWeek6.atsln met Microchip Studio. Voeg op de aangegeven plaatsen de uitwerkingen van onderstaande opdrachten in.

- Demonstreer de uitwerking van de opdrachten/ programma’s aan de docent.

- Maak gebruik van het bestand FrameworkWeek6.zip.
:::

## Opdracht 4.1: Implementatie en gebruik van een eenvoudige functie

1.	Implementeer in de functie main() van FrameworkWeek6.c een knipperlicht, waarbij de LED’s zijn aangesloten op output poort D. Maak gebruik van code (= kopieer) van vorige practica

2.	Maak vervolgens de (zéér eenvoudige, met een body van één regel!) functies:

- void LedsOn(void): aanroepen van deze functie zet alle LED’s op poort D AAN
- void LedsOff(void): aanroepen van deze functie zet alle LED’s op poort D UIT

3.	vervang nu in main() de code waarmee de LED’s worden aangezet en uitgezet, door de juiste aanroep van de functies LedsOn en LedsOff.

4.	Controleer vervolgens of het knipperlicht nog steeds correct functioneert.


## Opdracht 4.2: Implementatie en gebruik van functie met een returnwaarde

Maak voor de uitwerking van deze opdracht een nieuw Microchip Studio project aan, en maak gebruik van (= kopieer) de code en bijbehorende functies LedsOn en LedsOff uit opdracht 1.

In het practicum van week 4 is het gedrag van de LED’s en de drukknoppen bepaald op het shield. De LED’s zijn aangesloten is op output port D van de microcontroller, de drukknoppen zijn aangesloten op input port B van de microcontroller.

Beantwoord eerst de volgende vragen als voorbereiding op de volgende opdrachten:

- Vraag 1: een uitgang van port D wordt op logisch ‘1’ gezet. Is de bijbehorende LED dan AAN of is deze UIT?

- Vraag 2: een ingang van port B wordt uitgelezen als een logische ‘1’. Is de bijbehorende drukknop dan INGEDRUKT of NIET INGEDRUKT?


1.	Pas het programma met het knipperlicht van opdracht 1 zodanig aan, dat het knipperlicht uitsluitend knippert als er één of meer (willekeurige) knop(pen) is/zijn ingedrukt. De knoppen zijn aangesloten op poort B. Reminder: van poort B worden uitsluitend de bits 0..3 gebruikt voor de knoppen. Maak gebruik van een masker en een bitwise AND functie (&) om deze bits te selecteren.

2.	Implementeer vervolgens de functie bool IsEenKnopIngedrukt(void), die de waarde true teruggeeft als er minimaal één knop is ingedrukt, en de waarde false als er geen enkele knop is ingedrukt.

3.	Gebruik hierna de functie IsEenKnopIngedrukt in het hoofdprogramma op de volgende manier:

```cpp
if(IsKnopIngedrukt()== true)
{
    // knipperlicht code
}
```
 



 
Opdracht 3.	Implementatie en gebruik van functie met een parameter en een returnwaarde

In opdracht 2 geeft de functie IsEenKnopIngedrukt de waarde true terug als er minimaal één knop is ingedrukt. In opdracht 3 wordt een nieuwe functie gemaakt, die de waarde true teruggeeft als er een specifieke knop wordt ingedrukt met een knopnummer tussen 3 en 0 (komt overeen met de knoppen D3..D0 is op het shield). Het knopnummer wordt nu dus een parameter van die nieuwe functie.

1.	Implementeer de functie bool IsKnopIngedrukt(uint8_t knopNummer), die de waarde true teruggeeft als de knop met knopNummer is ingedrukt, en de waarde false als die knop niet is ingedrukt. De waarde van knopNummer moet hierbij liggen tussen 0 en 3. Gebruik hierbij als uitgangspunt de code van de vorige opdracht 2 van de functie IsEenKnopIngedrukt. N.B.: deze functie moet dus voor ELKE waarde van knopNummer tussen 0 en 3 correct functioneren!

2.	Gebruik nu de functie IsKnopIngedrukt(uint8_t knopNummer) in het hoofdprogramma. Stel dat het knipperlicht alleen moet knipperen als knop 3 is ingedrukt, dan gaat dit als volgt:

```cpp
knopNummer = 2;
if(IsKnopIngedrukt(knopNummer)== true)
{
    // knipperlicht code
}
```
 

