# Opdracht 3: Programmeren in C op de Arduino Uno

In dit practicum oefen je met bitoperaties en met herhalings- en beslissingsstructuren in de taal C.

## Inleiding

Op de Arduino Uno zijn de 8 LED's op het shield aangesloten op output-poort D (`PORTD`) en de 4 schakelaars op input-poort B (`PINB`).

Input-poort B is een 8-bit poort, waarvan alleen bits `3..0` worden gebruikt voor de schakelaars. Bits `7..4` worden gebruikt voor andere functies van de microcontroller. De actuele waarde van bits `7..4` is onbekend. Je mag dus nooit aannemen dat deze bits altijd `0` of `1` zijn.

De waarde die van input-poort B wordt gelezen is dus:

![image](../images/opdracht3_figuur1.jpg)

*Figuur 1. Input-poort B*

Om alleen de waarde van schakelaars S3 t/m S0 in te lezen, moet je met een bitwise operatie bereiken dat bits `7..4` altijd als logische `0` worden geïnterpreteerd. Dit heet maskeren (zie figuur 2):

![image](../images/opdracht3_figuur2.jpg)

*Figuur 2. Maskeren van input-poort B*

:::{note}
Tijdens de uitvoering van deze opdracht houd je een rapportage bij. Gebruik hiervoor het document `Rapportage_Opdracht_3.docx` in de map `opdracht3` van de microcontrollers workshop. Dit bestand lever je in op Brightspace.
:::

Beantwoord eerst de volgende vraag voordat je aan de opdrachten begint. Na het beantwoorden van deze vraag kun je de onderstaande opdrachten correct uitvoeren.

Welke operatie en welk masker (de waarde van bits `m7..m0`) zijn nodig om het gewenste resultaat te krijgen volgens figuur 2?

## Opdracht 3.1: LED's knipperen bij ingedrukte schakelaar

1. Open in Visual Studio Code het project `Framework_3_1` door de map `opdracht3/Framework_3_1` te openen.
2. Open het bestand `main.c` in Visual Studio Code en bestudeer het programma.
3. Maak een `main.c`-programma dat de LED's laat knipperen zolang een of meer willekeurige schakelaars zijn ingedrukt. Als geen schakelaar is ingedrukt, zijn de LED's uit.
4. Pas het programma daarna zo aan dat alleen schakelaar 0 deze functie heeft. Het indrukken van een andere schakelaar mag geen effect hebben.

:::{tip}
- Laat je voor het knipperen van de LED's inspireren door het programma `FlashLeds` uit opdracht 2.
- Maak gebruik van een `if`-statement.
- Gebruik een bitwise AND-operatie om te controleren of schakelaar 0 is ingedrukt.
:::

## Opdracht 3.2: LED's knipperen met behoud van laatste stand

1. Open in Visual Studio Code het project `Framework_3_2` door de map `opdracht3/Framework_3_2` te openen.
2. Open het bestand `main.c` in Visual Studio Code en bestudeer het programma.
3. Maak een `main.c`-programma dat de LED's laat knipperen zolang een of meer willekeurige schakelaars zijn ingedrukt. Als geen schakelaar is ingedrukt, blijven de LED's in hun laatste stand.
4. Pas het programma daarna zo aan dat alleen schakelaar 1 deze functie heeft. Het indrukken van een andere schakelaar mag geen invloed hebben.

:::{tip}
Je kunt ook `main.c` uit opdracht 3.1 als startpunt gebruiken. Kopieer dit programma dan eerst naar `opdracht3/Framework_3_2/src` voordat je met de uitwerking begint.
:::

## Opdracht 3.3: LED's 1 seconde aan bij schakelaar-indruk

1. Open in Visual Studio Code het project `Framework_3_3` door de map `opdracht3/Framework_3_3` te openen.
2. Open het bestand `main.c` in Visual Studio Code en bestudeer het programma.
3. Maak een programma waarbij de LED's bij het indrukken van een willekeurige schakelaar 1 seconde branden. Het mag daarbij niet uitmaken hoe lang de schakelaar wordt ingedrukt.
4. Pas het programma daarna zo aan dat alleen schakelaar 2 deze functie heeft. Het indrukken van een andere schakelaar mag geen invloed hebben.

## Opdracht 3.4: LED's aan tijdens indrukken met 1 seconde nabranden

1. Open in Visual Studio Code het project `Framework_3_4` door de map `opdracht3/Framework_3_4` te openen.
2. Open het bestand `main.c` in Visual Studio Code en bestudeer het programma.
3. Maak een programma dat de LED's laat branden zolang een willekeurige schakelaar is ingedrukt. Na het loslaten van de schakelaar blijven de LED's nog 1 seconde branden.
4. Pas het programma daarna zo aan dat alleen schakelaar 3 deze functie heeft. Het indrukken van een andere schakelaar mag geen invloed hebben.

## Opdracht 3.5: LED's één voor één op- en afbouwen met bitwise operaties

1. Open in Visual Studio Code het project `Framework_3_5` door de map `opdracht3/Framework_3_5` te openen.
2. Open het bestand `main.c` in Visual Studio Code en bestudeer het programma.
3. Maak een programma met een oneindige herhaling waarin alle LED's één voor één worden aangezet, beginnend bij LED 0. Laat elke tussenstand 1 seconde zien. LED's die al aan zijn, blijven aan.
4. Zodra alle LED's aan zijn, zet je ze weer één voor één uit, beginnend bij LED 0. LED's die al uit zijn, blijven uit.

:::{tip}
- Gebruik een variabele met de naam `leds` van het type `uint8_t`.
- Gebruik herhalingen (`while`, `do/while` of `for`).
- Gebruik een bit set-operatie om LED's aan te zetten.
- Gebruik een bit clear-operatie om LED's uit te zetten.
- Gebruik een shift-operatie.
:::

## Opdracht 3.6: Inleveren van de opdrachten

Lever je rapportage in op Brightspace. Gebruik hiervoor het document `Rapportage_Opdracht_3.docx` in de map `opdracht3` van de microcontrollers workshop. In dit document vul je de antwoorden op de vragen en de conclusies van de verschillende opdrachten in.