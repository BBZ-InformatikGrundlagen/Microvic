#include "MicroBit.h"

MicroBit uBit;

int main() {
    //Programmierung der einzelnen Leuchten um ein Kreuz beziehungsweise ein Kreis anzuzeigen
    MicroBitImage cross("255,0,0,0, 255\n0,255,0,255,0\n0,0,250,0,0\n0,255,0,255,0\n255,0,0,0,255\n");
    MicroBitImage circle("255,255,255,255,255\n255,0,0,0,255\n255,0,0,0,255\n255,0,0,0,255\n255,255,255,255,255\n");

    //Buzzer-Definiton
    MicroBitPin buzzer(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ANALOG);

    uBit.init();

    //Spielerpunktestand
    int scoreplayer1 = 0;
    int scoreplayer2 = 0;

    //Countdown für Spielerwechsel und Spielbeginn
    int c = 54321;

    //Zustände für den Spielerwechsel/Gewinnanzeige
    bool player1 = true;
    bool player2 = false;
    bool winner = false;
    //"winner" wird benötigt, damit Spieler 2 nachziehen kann wenn Spieler 1 fünf Punkte erreicht (Damit Spieler 2
    // die Chance auf ein unentschieden hat).

    while (1) {
        //Countdown läuft
        uBit.display.scroll(c);

        //Zufall generiert eine Zahl für Spieler 1
        int number = rand() % 2;

        //Durch die generierte Zahl wird Kreuz/Kreis angezeigt.
        if (number == 0) {
            uBit.display.print(cross);
        } else if (number == 1) {
            uBit.display.print(circle);
        }

        while (player1) {

            //Wenn Knopf A gedrückt wird, bekommt Spieler 1 einen Punkt. Spieler 2 ist dran mit dem Raten.
            if (uBit.buttonA.isPressed()) {
                scoreplayer1++;
                player1 = false;
                player2 = true;
                winner = false;

                //Wenn Knopf B gedrückt wird, werden keine Punkte verteilt. Spieler 2 ist dran mit dem Raten.
            } else if (uBit.buttonB.isPressed()) {
                player1 = false;
                player2 = true;
                winner = false;
            }
        }
        //Nach Knopfbetätigung läuft der Countdown (Spielerwechsel)
        uBit.display.scroll(c);

        //Zufall generiert eine Zahl für Spieler 2
        int number2 = rand() % 2;

        //Durch die generierte Zahl wird Kreuz/Kreis angezeigt
        if (number2 == 0) {
            uBit.display.print(cross);
        } else if (number2 == 1) {
            uBit.display.print(circle);
        }

        while (player2) {

            //Wenn Knopf A gedrückt wird, bekommt Spieler 2 einen Punkt. Spieler 1 ist wieder dran mit dem Raten.
            if (uBit.buttonA.isPressed()) {
                scoreplayer2++;
                player1 = false;
                player2 = false;
                winner = true;

                //Wenn Knopf B gedrückt wird, werden keine Punkte verteilt. Spieler 1 ist wieder dran mit dem Raten.
            } else if (uBit.buttonB.isPressed()) {
                player1 = true;
                player2 = false;
                winner = true;
            }
        }
        //Gewinnanzeige + Buzzer
        while (winner) {

            //Wenn beide Spieler fünf Punkte haben, ertönt der Buzzer und es wird "DRAW!" angezeigt.
            if (scoreplayer1 + scoreplayer2 == 10) {
                buzzer.setAnalogValue(512);
                uBit.sleep(1000);
                buzzer.setAnalogValue(0);
                uBit.display.scroll("DRAW!");
            }

                //Wenn Spieler 1 fünf Punkte erreicht hat, ertönt der Buzzer und es wird "PLAYER 1 WINS! angezeigt
            else if (scoreplayer1 >= 5) {
                buzzer.setAnalogValue(512);
                uBit.sleep(1000);
                buzzer.setAnalogValue(0);
                uBit.display.scroll("PLAYER 1 WINS!");
            }

                //Wenn Spieler 2 fünf Punkte erreicht hat, ertönt der Buzzer und es wird "PLAYER 1 WINS! angezeigt
            else if (scoreplayer2 >= 5) {
                buzzer.setAnalogValue(512);
                uBit.sleep(1000);
                buzzer.setAnalogValue(0);
                uBit.display.scroll("PLAYER 2 WINS!");
            }

            //Falls keiner der Spieler 5 Punkte erreicht hat, läuft das Spiel weiter.
            else {
                player1 = true;
                player2 = false;
                winner = false;
            }
        }
    }
}