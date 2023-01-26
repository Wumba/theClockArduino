// TM1637 Bibliothek von Avishay Orpaz

#include <TM1637Display.h>

#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)
#define numberOfMinutes(_time_) (((_time_ / 1000) / 60) % 60)

TM1637Display display(2, 3);
void setup()
{
    Serial.begin(115200);
    pinMode(startPin, INPUT_PULLUP);
    pinMode(zwischenzeitPin, INPUT_PULLUP);
    // Set brightness
    display.setBrightness(0x0c);
}
void showTime(long theTime)
{
    unsigned long myTime = theTime - startZeit;
    int seconds = numberOfSeconds(myTime);
    int minutes = numberOfMinutes(myTime);
    display.showNumberDecEx(seconds, 0, true, 2, 2);
    if (seconds % 2 == 0)
    {
        display.showNumberDecEx(minutes, 0b01000000, true, 2, 0);
    }
    else
    {
        display.showNumberDecEx(minutes, 0, true, 2, 0);
    }
}
void loop()
{
    stateStart = digitalRead(startPin);
    stateZwischenzeit = digitalRead(zwischenzeitPin);
    switch (programState)
    {
    case 0: // gestoppt
        startZeit = 0;
        display.showNumberDecEx(0, 0b01000000, true, 2, 2);
        display.showNumberDecEx(0, 0b01000000, true, 2, 0);
        // start
        if ((stateStart == LOW) && (stateStart != lastStateStart))
        {
            startZeit = millis();
            programState = 1;
        }
        break;
    case 1: // gestartet
        showTime(millis());
        // zwischenzeit
        if ((stateZwischenzeit == LOW) && (stateZwischenzeit != lastStateZwischenzeit))
        {
            zwischenzeit = millis();
            programState = 2;
        }
        // stop
        if ((stateStart == LOW) && (stateStart != lastStateStart))
        {
            zeitAngehalten = millis();
            programState = 3;
        }
        break;
    case 2: // zwischenzeit
        showTime(zwischenzeit);
        // zwischenzeit ausblenden
        if ((stateZwischenzeit == LOW) && (stateZwischenzeit != lastStateZwischenzeit))
        {
            programState = 1;
        }
        break;
    case 3: // gestoppt
        // weiter laufen lassen
        if ((stateZwischenzeit == LOW) && (stateZwischenzeit != lastStateZwischenzeit))
        {
            startZeit = startZeit + (millis() - zeitAngehalten);
            programState = 1;
        }
        // löschen
        if ((stateStart == LOW) && (stateStart != lastStateStart))
        {
            programState = 0;
        }
        break;
    }
    lastStateStart = stateStart;
    lastStateZwischenzeit = stateZwischenzeit;
}