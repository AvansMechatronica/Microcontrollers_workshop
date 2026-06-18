# Opdracht 2: Kennismaken met de Arduino Uno en PlatformIO
 In deze opdracht maak je kennis met de Arduino Uno en de bijbehorende programmeeromgeving PlatformIO. Je leert hoe je een programma kunt schrijven in de programmeertaal C, hoe je dit programma kunt compileren en flashen naar de Arduino Uno, en hoe je de LED’s en schakelaars op het LED / switch shield van de Arduino Uno kunt aansturen en uitlezen.

:::{note}
Tijdens de uitvoering van deze opdracht houd je een rapportage bij. Je kunt hiervoor het document `Rapportage_Opdracht_2.docx` gebruiken welke in de map `opdracht2` van de microcontrollers workshop staat. Dit bestand lever je in op Brightspace.
:::

## Opdracht 2.1: Installatie Visual Studio Code en PlatformIO
:::{note}
Deze opdracht voer je in je eigen tijd uit voordat je aan de volgende opdrachten kunt beginnen. Je hoeft deze opdracht dus niet in het practicum uit te voeren, maar je moet deze opdracht wel hebben uitgevoerd voordat je aan de volgende opdrachten kunt beginnen. Als je de software nog niet hebt geïnstalleerd heb je geen toegang tot het practicum.
:::

Voor het programmeren van de Arduino Uno wordt gebruik gemaakt van Visual Studio Code in combinatie met de PlatformIO extension. Deze software is gratis te downloaden en te gebruiken. Volg de volgende stappen om deze software te installeren:
1.	Download en installeer Visual Studio Code van https://code.visualstudio.com/
2.	Open Visual Studio Code en ga naar de Extensions (Ctrl+Shift+X)	
3.	Zoek naar PlatformIO en installeer deze extension
4.	Na installatie van PlatformIO, herstart Visual Studio Code	


## Opdracht 2.2: Een programma uitvoeren op de Arduino Uno

De Arduino Uno wordt gebruikt in combinatie met een zgn. shield, dat nodig is voor communicatie met de PLC en dat de signaalzuil gaat aansturen. In het practicum worden de schakelaars en de LED’s op dit shield gebruikt. In figuur 1 zijn deze aangegeven.


![Image](../images/arduino_shield.png)


***Figuur 1.	Positie van schakelaars en LED’s***	


Om een programma op de Arduino Uno uit te voeren moet dit programma worden gedownload (‘geflasht’) van de PC naar de Arduino. We doen dit met behulp van PlatformIO. Volg de volgende stappen om een programma te flashen naar de Arduino Uno:

1. Open in VisualStudio Code het `FlashLeds`-project door de map `opdracht2/FlashLeds` te openen. Gebruik hiervoor in Visual Studio Code de optie `File > Open Folder` en selecteer de map `opdracht2/FlashLeds`. Je zou nu het volgende moeten zien in Visual Studio Code:

![image](../images/vsc_platformio.jpg)
**Figuur 2.	Visual Studio Code met PlatformIO extension**

2. Compileer het programma door in de beneden balk van Visual Studio Code te klikken op het vinkje (check) icoon, of door de sneltoets Ctrl+Alt+B te gebruiken. Controleer of er geen fouten zijn tijdens het compileren.
![image](../images/Compile.JPG)

3. Plaats het shield op de Arduino Uno en sluit de Arduino Uno aan op de PC met behulp van een USB-kabel. 

4. Flash het programma naar de Arduino door in de beneden balk van Visual Studio Code te klikken op het pijltje (upload) icoon, of door de sneltoets Ctrl+Alt+U te gebruiken. Controleer of de LED’s op het shield knipperen zoals verwacht.
![image](../images/Upload.JPG)

## Opdracht 2.3: Een eenvoudig programma in de taal C

Het programma van C-Programma 1 laat zien hoe de LED’s op het shield kunnen worden aangestuurd. In dit programma worden de LED’s steeds 500 ms aan en 500 ms uit gezet, waardoor ze knipperen.


```cpp
int main(void)
{
	initPorts();
	initTimer();

	while (true) // endless loop, flash the LED's on PORTD
	{
		PORTD = 255;
		delay(500);

		PORTD = 0;
		delay(500);
	}

	return 0;
}
```



**C-Programma 1.	Het programma FlashLeds**

Open het bestand door in Visual Studio Code te klikken op het bestand `main.c` in de map `opdracht2/FlashLeds/src`.


Pas het programma van C-Programma 1 zodanig aan, dat de LED’s 2 maal zo traag knipperen. Voeg hiervoor de programmaregels in zoals aangegeven in C-Programma 2. Save & compileer het programma en download het op de Arduino. Controleer uiteraard of de LED’s daadwerkelijk 2 maal zo traag knipperen!


```cpp
int main(void)
{
	initPorts();
	initTimer();

	while (true) // endless loop, flash the LED's on PORTD
	{
		PORTD = 255;
		delay(500);
		delay(500); // voeg deze regel toe

		PORTD = 0;
		delay(500);
		delay(500); // voeg deze regel toe
	}

	return 0;
}
```

**C-Programma 2.	Het aangepaste programma FlashLeds**

 
## Opdracht 2.4.	Onderzoek aansturen LED’s




Een LED kan in principe op de volgende manieren op een microcontroller worden aangesloten, zie figuur 3 en figuur 4. De vraag is nu: op welke van deze mogelijke 2 manieren zijn de LED’s nu daadwerkelijk aangesloten op het Arduino LED / switch shield? Onderzoek dit door:

1.	eerst een aanname te maken over het gedrag van de LED’s, en vervolgens

2.	deze aanname te controleren met een programma. Gebruik PORTD om de LED’s aan te sturen.


::::{grid} 2
:::{grid-item-card} 
![Image](../images/led_active_low.png)

**Figuur 3. Output / LED aangesloten
op voedingsspanning**	
:::
:::{grid-item-card}
![Image](../images/led_active_high.png)
**Figuur 4. Output / LED aangesloten
op ground**

Output / LED aangesloten
op ground

:::
::::

1. Open in VisualStudio Code het `LedTest`-project door de map `opdracht2/LedTest` te openen. Gebruik hiervoor in Visual Studio Code de optie `File > Open Folder` en selecteer de map `opdracht2/LedTest`.
2. Flash het programma naar de Arduino Uno.
3. Open het `main.c` bestand in Visual Studio Code en bestudeer dit programma. Probeer te begrijpen wat dit programma doet en hoe het werkt. Controleer of dit programma daadwerkelijk de LED’s aanstuurt zoals verwacht.

4.	Als een logische 1 op de output van de microcontroller wordt voorgesteld door +5 Volt, en een logische 0 door 0 volt, geef dan in de volgende tabel aan, wanneer 	en LED aan of uit is. Vul in deze tabel AAN of UIT in. Gebruik in het programma LedTest PORTD als output poort voor de LED’s.


|  | Output = 0 | Output = 1
| --- | --- | --- |
Figuur 3|	
Figuur 4| 


**Tabel 1.	Gedrag van LED’s op de uitgang van een microcontroller (invullen)**

5.	Op welke manier zijn nu de LED’s op het LED / switch shield van de Arduino Uno aangesloten, m.a.w.: gaat een LED branden bij een ‘0’ op de uitgang van de microcontroller, of juist bij een ‘1’? 

*Conclusie:*

- Een LED is AAN als de output een logische … is
- Een LED is UIT als de output een logische … is
 
## Opdracht 2.5: Onderzoek inlezen schakelaars 

1. Open in VisualStudio Code het `SwitchTest`-project door de map `opdracht2/SwitchTest` te openen. Gebruik hiervoor in Visual Studio Code de optie `File > Open Folder` en selecteer de map `opdracht2/SwitchTest`.
2. Flash het programma naar de Arduino Uno.
3. Open het `main.c` bestand in Visual Studio Code en bestudeer dit programma. Probeer te begrijpen wat dit programma doet en hoe het werkt.

Maak voor de uitvoering van deze opdracht gebruik van het programma en de kennis die je hebt gebruikt bij opdracht 3 (LedTest).

LET OP: omdat we slechts 4 schakelaars hebben (en 8 LED’s), kijken we bij deze opdracht UITSLUITEND naar het gedrag van de LED’s B3…B0, d.w.z de 4 meest RECHTSE LED’s op het shield. Kijk dus NIET naar de LED’s 7..4 links op het shield, deze hebben hier nl. een andere functie en kunnen aan of uit zijn.

Op 4 ingangen van poort B zijn 4 schakelaars aangesloten. Een schakelaar kan in principe op de volgende manieren op een microcontroller worden aangesloten, zie figuur 5 en figuur 6. In deze opdracht wordt bepaald op welke van deze mogelijke 2 manieren de schakelaars nu daadwerkelijk zijn geconfigureerd op het Arduino LED / switch shield.


 ::::{grid} 2
:::{grid-item-card} 
![Image](../images/switch_active_low.png)
**Figuur 5. Input / schakelaar aangesloten
op ground**	
:::
:::{grid-item-card}
![Image](../images/switch_active_high.png)
**Figuur 6. Input / schakelaar aangesloten
op voedingsspanning**

Input / schakelaar aangesloten
op voedingsspanning
:::
::::			 

4.	Als een logische 1 op de input van de microcontroller wordt voorgesteld door +5 Volt, en een logische 0 door 0 volt, geef dan in de volgende tabel aan, wanneer een schakelaar is ingedrukt of losgelaten. Vul in deze tabel IN of LOS in.

|  | Input = 0 | Input = 1
| --- | --- | --- |
Figuur 5 |	
Figuur 6| 



**Tabel 2. Gedrag van schakelaars op de ingang van een microcontroller**

5.	Op welke manier zijn nu de schakelaars aangesloten? M.a.w.: stelt een ingedrukte schakelaar een ‘0’ voor op de ingang van de microcontroller, of juist een ‘1’? Onderzoek dit door:

6.	een aanname te maken, en vervolgens

7.	deze aanname te controleren met een programma. 

Gebruik input poort B (PINB) om 4 schakelaars tegelijk in te lezen. Maak ook gebruik van de conclusies die getrokken zijn uit het gedrag van de LED's in de vorige opdracht. Lees vooral ook de volgende 2 aanwijzingen!

*Aanwijzingen:*

- maak een programma dat voortdurend de status van de schakelaars weergeeft op de LED’s (kijk dus alleen naar de 4 RECHTER LED’s, de 4 linker LED’s doen niet mee in deze opdracht)

- Bepaal nu of een ingedrukte schakelaar een ‘0’ geeft op de ingang of juist een ‘1’.


*Conclusie:*

- Een schakelaar die is ingedrukt genereert een logische … op de ingang van de microcontroller
- Een schakelaar die is losgelaten genereert een logische … op de ingang van de microcontroller
 
## Opdracht 2.6: Teller

1. Open in VisualStudio Code het `Teller`-project door de map `opdracht2/Teller` te openen. Gebruik hiervoor in Visual Studio Code de optie `File > Open Folder` en selecteer de map `opdracht2/Teller`.
2. Flash het programma naar de Arduino Uno.
3. Open het `main.c` bestand in Visual Studio Code en bestudeer dit programma. Probeer te begrijpen wat dit programma doet en hoe het werkt.

Pas dit programma zodanig aan, dat het programma op de LED’s van het LED / switch shield een (binaire) teller laat zien, die elke ½ seconde omhoog telt. De beginwaarde van de teller is 0. Maak, indien nodig, gebruik van een PSD in microAVR om dit vooraf te testen.

Het programma moet niet alleen het juiste telgedrag vertonen op de LED’s, het moet daarnaast ook een logische, leesbare, begrijpelijke en duidelijke structuur hebben: in dit geval (het programma moet omhoog tellen) betekent het, dat er dus 'ergens' in dit programma een opdracht moet staan met een '+' teken, zoals in:

teller = teller + 1

:::{note}
Het programma is verkeerd, als dit programma ergens een opdracht bevat van de vorm 

teller = teller - 1

waarbij er gebruik wordt gemaakt van een min-teken!
:::

## Opdracht 2.7: Inleveren van de opdrachten
Vergeet niet om je rapportage in te leveren op Brightspace. Gebruik hiervoor het document `Rapportage_Opdracht_2.docx` welke in de map `opdracht2` van de microcontrollers workshop staat. In dit document kun je de antwoorden op de vragen en de conclusies van de verschillende opdrachten invullen.