#ifndef LIST_H
#define LIST_H

/// @brief Person besitzt Vorname und Nachname
struct person{
    char vorname[20];
    char nachname[20];
};

/// @brief Doppeltverkettetes Listen Element
struct listElement{
    struct person personlist;
    struct listElement *vorgaenger;
    struct listElement *nachfolger;
};

/// @brief Doppeltverkette Liste
struct list{
    struct listElement *begin;
    struct listElement *end;
};

#endif