# Opdracht 4: Oefenen met functies in C

## Inleiding

In dit practicum oefen je met functies in de programmeertaal C.

:::{note}
Tijdens de uitvoering van deze opdracht houd je een rapportage bij. Gebruik hiervoor het document `Rapportage_Opdracht_4.docx` in de map `opdracht4` van de microcontrollers workshop. Dit bestand lever je in op Brightspace.
:::

:::{tip}
- Het is niet verplicht om PSD's te maken, maar dit mag wel als je daarmee je uitwerking kunt verduidelijken.
- Gebruik bij deze opdrachten het project `Framework_4` als startpunt. Maak voor elke deelopdracht een aparte kopie, met een duidelijke naam die overeenkomt met de opdracht (bijvoorbeeld `Framework_4_1` voor opdracht 4.1).
:::

## Opdracht 4.1: Eenvoudige functie implementeren en gebruiken

1. Implementeer in de functie `main()` van je project `Framework_4_1` een knipperlicht met de LED's op output-poort D. Gebruik eventueel code uit eerdere opdrachten.
2. Maak vervolgens de volgende eenvoudige functies (elk met een body van een regel):

   - `void LedsOn(void)`: zet alle LED's op poort D aan.
   - `void LedsOff(void)`: zet alle LED's op poort D uit.

3. Vervang in `main()` de bestaande code voor LED aan/uit door aanroepen van `LedsOn()` en `LedsOff()`.
4. Controleer of het knipperlicht nog steeds correct werkt.

## Opdracht 4.2: Functie met returnwaarde implementeren en gebruiken

Maak een kopie van `Framework_4_1` en noem deze `Framework_4_2`. Open daarna de map van `Framework_4_2` in Visual Studio Code en open `main.c`.

In opdracht 3 is het gedrag van de LED's en drukknoppen op het shield bepaald. De LED's zijn aangesloten op output-poort D van de microcontroller, de drukknoppen op input-poort B.

Beantwoord eerst de volgende vragen als voorbereiding:

- Vraag 1: een uitgang van poort D wordt op logische `1` gezet. Is de bijbehorende LED dan aan of uit?
- Vraag 2: een ingang van poort B wordt uitgelezen als logische `1`. Is de bijbehorende drukknop dan ingedrukt of niet ingedrukt?

Werk daarna de volgende stappen uit:

1. Pas het knipperlicht uit opdracht 4.1 zo aan dat het alleen knippert als een of meer knoppen worden ingedrukt. Let op: voor de knoppen op poort B worden alleen bits `0..3` gebruikt. Gebruik een masker en een bitwise AND (`&`) om deze bits te selecteren.
2. Implementeer de functie `bool IsEenKnopIngedrukt(void)`. Deze geeft `true` terug als minimaal een knop is ingedrukt, anders `false`.
3. Gebruik `IsEenKnopIngedrukt()` in het hoofdprogramma, bijvoorbeeld:

```cpp
if (IsEenKnopIngedrukt() == true)
{
    // knipperlicht code
}
```

## Opdracht 4.3: Functie met parameter en returnwaarde

In opdracht 4.2 gaf `IsEenKnopIngedrukt()` aan of er minimaal een knop was ingedrukt. In deze opdracht maak je een nieuwe functie die controleert of een specifieke knop is ingedrukt. Het knopnummer (`0` t/m `3`, overeenkomend met D0 t/m D3 op het shield) wordt een parameter.

1. Implementeer de functie `bool IsKnopIngedrukt(uint8_t knopNummer)`. Deze geeft `true` terug als de knop met nummer `knopNummer` is ingedrukt, anders `false`. Zorg dat dit correct werkt voor alle waarden van `knopNummer` tussen `0` en `3`.
2. Gebruik `IsKnopIngedrukt(uint8_t knopNummer)` in het hoofdprogramma. Als het knipperlicht bijvoorbeeld alleen bij knop 2 mag knipperen:

```cpp
uint8_t knopNummer = 2;
if (IsKnopIngedrukt(knopNummer) == true)
{
    // knipperlicht code
}
```

## Opdracht 4.4: Inleveren

Lever je rapportage in op Brightspace. Gebruik hiervoor het document `Rapportage_Opdracht_4.docx` in de map `opdracht4` van de microcontrollers workshop. In dit document vul je de antwoorden op de vragen en je conclusies per opdracht in.