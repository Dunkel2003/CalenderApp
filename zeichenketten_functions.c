#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "zeichenketten_functions.h"
#define ONEDAY 86400

struct appointment{
    struct tm date;
    unsigned int dur;
    char titel[20];
};

/*struct person{
    char forename[20];
    char surname[20];
};*/

int size = 0;
int addsize = 0;
//dynamisches Array appointmentseries
struct appointment *appointmentseries = NULL;


int getUserInputMainMenu(){
    int input=0;

    printf("Termin anlegen: 1\n"
           "Terminserie anlegen: 2 \n"
           "Alle Termine anzeigen: 3 \n"
           "Kalenderausgabe: 4 \n"
           "Programm beenden: 9\n\n"
           "Geben Sie ein was Sie machen wollen.\n");

    scanf("%d", &input);

    return input;
}

int realdate(int day, int month, int year, int hour, int min, int sec)
{
    int check = 0;

    if(year < 70 || year > 137)
    {
        printf("Das Datum muss zwischen 1970 und 2037 sein.\n");
        return check;
    }
    else if(month < 0 || month > 11)
    {
        printf("Ein Jahr hat 12 Monate\n");
        return check;
    }
    else if(month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)
    {
        if(day > 31 || day < 1) {
            printf("DDieser Monat hat 31 Tage\n");
            return check;
        }
    }
    else if(month == 3 || month == 5 || month == 8 || month == 10)
    {
        if(day > 30 || day < 1)
        {
            printf("Dieser Monat hat 31 Tage\n");
            return check;
        }
    }
    else if (month == 1) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            // Schaltjahr: Februar hat 29 Tage
            if (day > 29 || day < 1) {
                printf("Dieser Monat hat 29 Tage");
                return 0;
            }
        } else {
            // Kein Schaltjahr: Februar hat 28 Tage
            if (day > 28 || day < 1) {
                printf("Dieser Monat hat 28 Tage");
                return 0;
            }
        }
    }
    else if(hour < 0 || hour > 23)
    {
        printf("Ein Tag hat 24 Stunden\n");
        return check;
    }
    else if(min < 0 || min > 59)
    {
        printf("Eine Stunde hat 60 Minuten\n");
        return check;
    }
    else if(sec < 0 || sec > 60)  // 60 = Schaltsekunde
    {
        printf("Eine Minute hat 60 Sekunden\n");
        return check;
    }
    else
    {
        return check = 1;
    }
}

//unixtime zu Struct tm
struct tm unixtimeToStruct(long long timeStamp){
    //Struktur für Jahr, Monat, Tag, Stunde, Minute, Sekunde
    struct tm *date;
    struct tm newdate;
    //long long zu time_t konvertieren
    time_t t_stamp = (time_t)timeStamp;
    //konvertierte Werte in date speichern
    date = localtime(&t_stamp);
    newdate = *date;

    return newdate;
}
//struct tm von appointmentseries in Unix Time, Intervall von Terminserie mitübergeben
struct tm toUnixtime(struct tm *date, int intervall) {

    struct tm newdate;

    time_t unixTime = mktime(date); // mktime verwendet die timeinfo-Struktur, um Unix-Zeit zu generieren
    unixTime = unixTime + intervall * ONEDAY; //Intervall zu der Unixtime zufügen

    newdate = unixtimeToStruct(unixTime); //Unixtime zu Struct tm
    return newdate; // Struct zurück geben
}

//Termin erstellen
void addAppointment()
{
    //hinzugefügte Größe
    addsize = 1;

    //dynamisches Array erweitern
    appointmentseries = (struct appointment *)realloc(appointmentseries, (size + addsize) * sizeof(struct appointment));

    int i = size;

    size += addsize;

    printf("Geben Sie den Termintitel an (max. 20 Zeichen):\n");
    scanf("%s",&appointmentseries[i].titel);
    while(appointmentseries[i].dur < 1 || appointmentseries[i].dur > 8)
    {
        printf("Geben Sie in Stunden an wie lange der Termin dauer (max. 8 Stunden):\n");
        scanf("%d",&appointmentseries[i].dur);
    }

    int valid = 0;
    //Eingabe & Überprüfung des Datums
    while (!valid) {
        printf("Geben Sie das Termindatum ein\n");
        scanf("%d%*c%d%*c%d%*c%d%*c%d%*c%d",
              &appointmentseries[i].date.tm_mday,
              &appointmentseries[i].date.tm_mon,
              &appointmentseries[i].date.tm_year,
              &appointmentseries[i].date.tm_hour,
              &appointmentseries[i].date.tm_min,
              &appointmentseries[i].date.tm_sec);

        appointmentseries[i].date.tm_year -= 1900; // Benutzereingabe vom Jahr und Monat korrigieren
        appointmentseries[i].date.tm_mon -= 1;

        //Checke Datum
        valid = realdate(appointmentseries[i].date.tm_mday, appointmentseries[i].date.tm_mon, appointmentseries[i].date.tm_year, appointmentseries[i].date.tm_hour, appointmentseries[i].date.tm_min, appointmentseries[i].date.tm_sec);

        if (!valid) {
            printf("Unguetige Eingabe. Bitte geben Sie ein gültiges Datum ein.\n");
            // Hier können Sie weitere Benutzerhinweise hinzufügen, wenn andere Eingaben ungültig sind.
        }
        appointmentseries[i].date = toUnixtime(&appointmentseries[i].date, 0);
    }

}

// Terminserie erstellen
void  addAppointmentSeries()
{
    int intervall;

    //hinzuzufügende speichergröße ermitteln
    printf("Geben Sie ein wie viele Termine Sie anlegen wollen:\n");
    scanf("%d", &addsize);

    //dynamisches Array erweitern
    appointmentseries = (struct appointment *)realloc(appointmentseries, (size + addsize) * sizeof(struct appointment));

    addsize = addsize + size;

        int i = size;

    printf("Geben sie an in welchen Intervall Sie die Termine haben möchten(1 Täglich/ 7 Wöchentlich/ 14 alle zwei Wochen)\n");
    scanf("%d", &intervall);

    printf("Geben Sie den Titel ein:\n");
    scanf_s("%s", &appointmentseries[i].titel);

    while(appointmentseries[i].dur < 1 || appointmentseries[i].dur > 8)
    {
        printf("Geben Sie in Stunden an wie lange der Termin dauer (max. 8 Stunden):\n");
        scanf("%d",&appointmentseries[i].dur);
    }

        int valid = 0;
        //Eingabe des Datums
        while (!valid) {
            printf("Geben Sie das Termindatum ein\n");
            scanf("%d%*c%d%*c%d%*c%d%*c%d%*c%d",
                  &appointmentseries[i].date.tm_mday,
                  &appointmentseries[i].date.tm_mon,
                  &appointmentseries[i].date.tm_year,
                  &appointmentseries[i].date.tm_hour,
                  &appointmentseries[i].date.tm_min,
                  &appointmentseries[i].date.tm_sec);

            appointmentseries[i].date.tm_year -= 1900; // Benutzereingabe vom Jahr und Monat korrigieren
            appointmentseries[i].date.tm_mon -= 1;

            //Checke Datum
            valid = realdate(appointmentseries[i].date.tm_mday, appointmentseries[i].date.tm_mon,
                             appointmentseries[i].date.tm_year, appointmentseries[i].date.tm_hour,
                             appointmentseries[i].date.tm_min, appointmentseries[i].date.tm_sec);

            if (!valid) {
                printf("Ungültige Eingabe. Bitte geben Sie ein gültiges Datum ein.\n");
                // Hier können Sie weitere Benutzerhinweise hinzufügen, wenn andere Eingaben ungültig sind.
            }

            appointmentseries[i].date = toUnixtime(&appointmentseries[i].date, 0);

            printf("%d",appointmentseries->date.tm_wday);

            //Weitere Termine der Terminserie erstellen
            for(i=size+1;i<addsize;i++)
            {
                appointmentseries[i] = appointmentseries[i - 1];
                appointmentseries[i].date = toUnixtime(&appointmentseries[i].date, intervall);
            }
            //Größe von size anpassen
            size = addsize;
    }
}

//Termine anzeigen
void showappointment()
{
    char output[20];
    for (int i = 0; i<size;)
    {
        i--;
        printf("Termin %d:\n", i+1);
        printf("Titel: %s\n", appointmentseries[i].titel);
        strftime(output, sizeof(output),"%d.%m.%Y %H:%M:%S", &appointmentseries[i].date); //Formatierung in einen String
        printf("%s\n",output);
        printf("Dauer: %u Stunden\n\n", appointmentseries[i].dur);
    }
}

void gettime(void)
{
    time_t now;  //Datentyp zum Speichern von Sekunden
    struct tm lt;  // Struct für die Angabe in ein Kalender
    char output[80]; //string für den Output

    time(&now);  //übergabe der Sekunden seit dem 01.01.1970 00:00:00
    lt = *localtime(&now); //übergabe der Sekunden in den struct
    strftime(output, sizeof(output),"%d.%m.%Y %H:%M:%S", &lt); //Formatierung in einen String
    printf("%s\n",output);
}

void timediff(void)
{
    struct tm userDate1 = {0,0,1,1,0,70};
    struct tm userDate2 = {0,0,1,1,0,70};

    printf("Gib das erste Datum ein.\n");
    scanf("%d %d %d %d %d %d", &userDate1.tm_sec, &userDate1.tm_min, &userDate1.tm_hour, &userDate1.tm_mday, &userDate1.tm_mon, &userDate1.tm_year);
    userDate1.tm_year -= 1900; // Benutzereingabe vom Jahr und Monat korrigieren
    userDate1.tm_mon -= 1;
    //fflush(stdin);

    printf("Gib das zweite Datum ein.\n");
    scanf("%d %d %d %d %d %d", &userDate2.tm_sec, &userDate2.tm_min, &userDate2.tm_hour, &userDate2.tm_mday, &userDate2.tm_mon, &userDate2.tm_year);
    userDate2.tm_year -= 1900; // Benutzereingabe vom Jahr und Monat korrigieren
    userDate2.tm_mon -= 1;
    //fflush(stdin);

    /*
        mktime() considers the localtimezone
        It calculates minus 1 hour in wintertime of Germany.
        !!! BE AWARE OF THAT !!!
    */
    time_t t_userDate1 = mktime(&userDate1);
    time_t t_userDate2 = mktime(&userDate2);
    double diffrence = difftime(t_userDate2, t_userDate1);
    if(diffrence < 0){diffrence = diffrence * (-1);}
    printf("The diffrence is : %f", diffrence);

}

void freememory()
{
    free(appointmentseries);
}