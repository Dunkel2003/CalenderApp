#include <string.h>
#include <stdio.h>

void StringCopy(){
    char src[] = "Hello, World!";
    char dest[10];
    
    printf("Vor dem Kopieren:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n\n", dest);  // Destination enthält zufällige Daten
    
    strcpy(dest, src);  // Buffer Overflow: Ziel-Puffer ist zu klein.
    
    printf("Nach dem Kopieren:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);  // Hier kann es zu undefiniertem Verhalten kommen
}

void AnzahlCopy(){
    char src[] = "Hello, World!";
    char dest[10];

    printf("Vor dem Kopieren:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n\n", dest);

    strncpy(dest, src, sizeof(dest) - 1);  // Sicher: Nur 9 Zeichen kopiert.
    dest[(sizeof(dest) - 1)] = '\0';  // Nullzeichen manuell hinzufügen.

    printf("Nach dem Kopieren:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);
}

void main(void){
    StringCopy();
    printf("\nAnzahlCopy: \n");
    AnzahlCopy();
}
/*
Die Funktion strcpy gilt als unsicher, da nicht sicher gestellt werden kann das die Funktion ohne Fehler läuft bei falscher Konfiguration 
der Variablen. 
z.B.: Wenn die Source einen größeren Inhalt hat als die Destination so kann es vorkommen das nicht alle Inhalte kopiert 
werden bzw. Inhalte der dahinter stehenden Programm überschrieben werden. 
--> Buffer-Overflow

strncpy kopiert die max. Anzahl an Zeichen die ihr übergeben werden. Die Funktion kann dann so konfiguriert werden, dass sie nicht mehr als
die Ziel Variable platz hat kopiert.
Dadurch kann es zu keinem Buffer-Overflow führen.
*/