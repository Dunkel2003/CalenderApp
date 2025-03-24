#ifndef ZEICHENKETTEN_FUNCTIONS_H
#define ZEICHENKETTEN_FUNCTIONS_H

/// @brief Eingabe vom Benutzer
/// @return 1, 2, 3, 4, 9
int getUserInputMainMenu();

/// @brief Checken des Datums
/// @param day Eingegebener Tag
/// @param month Eingegebener Monat
/// @param year Eingegebenes Jahr
/// @param hour Eingegebener Stunde
/// @param min Eingegebener Minute
/// @param sec Eingegebenes Sekunde
/// @return Entweder Datum ist Gültig(1), oder Datum ist ungültig (0)
int realdate(int day, int month, int year, int hour, int min, int sec);

/// @brief UnixTime zu Struct tm
/// @param  timeStamp UnixTime
struct tm unixtimeToStruct(long long timeStamp);

/// @brief
struct tm newStruct(struct tm *date, int intervall);

time_t toUnixTime(struct tm *date, int intervall);

/// @brief Einzeltermin erstellen
void addAppointment();

/// @brief Terminserie erstellen
void addAppointmentSeries();

/// @brief Zeigen der Termine
void showappointment();

void showWeek();

/// @brief Ausgeben der lokalen Uhrzeit
void gettime(void);

/// @brief Ausgeben der differenz von zwei Daten
void timediff(void);


void freememory();

#endif