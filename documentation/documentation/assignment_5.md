# Opdracht 5: Simulatie van signaallamp-besturing

## Inleiding

In dit practicum implementeer je functies die nodig zijn voor de simulatie van het volledige besturingsprogramma van de signaallampen:

- `bool IsSyncEdgeDetected(void)` (zie week 5)
- `uint8_t GetPLCData(void)`
- `uint8_t GetFunctionCode(uint8_t inputData)`
- `void ControlLamps(uint8_t functionCode)`
- `void SetAcknowledge(void)`
- `void WaitUntilSyncReleased(void)`
- `void ClearAcknowledge(void)`
- `void SetSyncLed(bool ledOn)`

Deze functies komen overeen met de functies in het PSD van het volledige programma (figuur 1).

*Figuur 1. PSD van het volledige besturingsprogramma*

:::{tip}
- Het is niet verplicht om PSD's te maken, maar dit mag wel als verduidelijking.
- Gebruik voor dit practicum het framework `FrameworkWeek8.zip` op Brightspace.
- Pak dit bestand uit in een geschikte map (bij voorkeur op je homedrive op het Avans-netwerk).
- Open daarna `FrameworkWeek8.atsln` in Microchip Studio.
- Voeg op de aangegeven plekken de uitwerkingen van onderstaande opdrachten toe.
- Demonstreer de uitwerking van de opdrachten aan de docent.
:::

## Opdrachten

Maak in onderstaande volgorde de C-code voor de volgende functies.

1. `void SetSyncLed(bool ledOn)`
	- LED B6 wordt gebruikt als indicatie voor het SYNC-bit.
	- `ledOn == true`: zet de SYNC-LED aan.
	- `ledOn == false`: zet de SYNC-LED uit.
	- Test deze functie door haar in `main()` aan te roepen en een knipperlicht te maken.

2. `bool IsSyncBitSet(void)`
	- Deze functie is nodig voor de implementatie van `IsSyncEdgeDetected()` in stap 3.
	- Als het SYNC-bit `1` is, retourneert de functie `true`; bij `0` retourneert de functie `false`.
	- Laat de functie bij simulatie reageren op drukknop D3, en niet op het echte SYNC-bit.

	N.B.: op het shield hebben knoppen een geinverteerde werking. Een ingedrukte knop levert logische `1`, een niet-ingedrukte knop logische `0`. Houd hiermee rekening in `IsSyncBitSet()` en in `GetPLCData()`.

	Breid de test uit stap 1 uit met `IsSyncBitSet()` en controleer of de functie correct reageert op het indrukken van knop D3 (simulatie van activeren van SYNC).

3. `bool IsSyncEdgeDetected(void)`
	- Zie ook de theorie van week 5 en het conceptuele PSD in figuur 2.
	- Deze functie wacht op een opgaande flank (rising edge) van het SYNC-signaal.
	- Zodra die optreedt, geeft de functie `true` terug.

	N.B.: deze functie geeft in de praktijk nooit `false` terug, omdat ze blijft wachten op een opgaande flank.

	Breid het testprogramma van stap 2 uit om te controleren of deze functie correct reageert op knop D3.

	*Figuur 2. Conceptueel PSD van `IsSyncEdgeDetected`*

4. `void WaitUntilSyncReleased(void)`
	- Deze functie wacht totdat het SYNC-bit in input-poort B niet meer actief is.
	- Zie ook het conceptuele PSD in figuur 3.
	- Laat de functie bij simulatie reageren op drukknop D3, en niet op het echte SYNC-bit.

	Breid het testprogramma van stap 3 uit met deze functie en controleer of de functie correct reageert op het loslaten van knop D3.

	*Figuur 3. PSD van `WaitUntilSyncReleased`*

5. `void ControlLamps(uint8_t functionCode)`
	- Stuur de signaallampen correct aan; `functionCode` bepaalt welke lampen aan moeten.
	- De signaallampen worden aangestuurd via `PORTD`.
	- Bits `3..0` worden gebruikt voor de lampen.
	- Bit `7` is het ACK-bit voor de handshake en moet logisch `0` blijven tijdens lampaansturing.

	De functie vertaalt de 3-bit functiecode naar een correcte waarde voor bits `3..0` van `PORTD`.

	Voor `functionCode` geldt: `0 <= functionCode <= 7`. Waarden buiten dit bereik moeten worden genegeerd (lampen blijven ongewijzigd).

	Breid het testprogramma van stap 4 uit. Test alle geldige waarden `0..7` en ook een ongeldige waarde (bijvoorbeeld `45`).

6. `uint8_t GetPLCData(void)`
	- Deze functie leest input-poort B en geeft de 4 bits `3..0` terug.
	- Bits `7..4` moeten worden gemaskeerd naar `0`.
	- De returnwaarde bevat dus de 3-bit functiecode (bits `2..0`) plus de status van SYNC in bit `3`.

	Laat de functie bij simulatie reageren op drukknoppen D2..D0 en niet op de echte bits van input-poort B.

	Test in twee stappen:
	- Roep `GetPLCData()` aan en sla de returnwaarde (`0..15`, oftewel `0x00..0x0F`) op in een variabele.
	- Geef deze variabele als parameter mee aan `ControlLamps()`.

	Voorbeeld: knop 0 en knop 1 ingedrukt geeft waarde `3`, dus groen en geel moeten aan gaan.

7. `uint8_t GetFunctionCode(uint8_t inputData)`
	- Input is de waarde van `GetPLCData()`.
	- De functie moet de 3 bits FC2..FC0 teruggeven.
	- Maskeer bits `7..4` en bit `3` (SYNC) naar `0`.
	- De returnwaarde ligt tussen `0` en `7` (`0x00..0x07`).

8. `void SetAcknowledge(void)`
	- Zet het ACK-bit in `PORTD` op `1`.
	- Alleen het ACK-bit mag worden aangepast.
	- Bits `3..0` (signaallampen) moeten ongewijzigd blijven.

9. `void ClearAcknowledge(void)`
	- Zet het ACK-bit in `PORTD` op `0`.
	- Alleen het ACK-bit mag worden aangepast.
	- Bits `3..0` (signaallampen) moeten ongewijzigd blijven.

## Uitvoeren simulatie met drukknoppen en LED's

In de theorieles is uitgelegd hoe de simulatie wordt uitgevoerd om de volledige code functioneel te testen:

1. Simuleer een functiecode tussen `0` en `7` door 0 of meer knoppen D2..D0 in te drukken. Houd deze knoppen ingedrukt.
2. Druk vervolgens op knop D3 om een opgaande flank van het SYNC-signaal te simuleren.
3. Bij correcte simulatie gaan LED's B3..B0 aan, evenals de SYNC-LED (B6).

	- LED B0 simuleert rood.
	- LED B1 simuleert geel.
	- LED B2 simuleert groen.
	- LED B3 simuleert blauw.

4. Bij correcte simulatie gaat ook LED B7 aan (meest rechter LED), omdat deze op het shield direct gekoppeld is aan ACK.
5. Laat de knoppen D2..D0 los.
6. Laat knop D3 los (simulatie van inactief worden van SYNC).
7. Bij correcte simulatie gaan SYNC (B6) en ACK (B7) uit. LED's B3..B0 houden hun waarde.

