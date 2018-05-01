#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

struct Datum {
	int Tag;
	int Monat;
	int Jahr;
};

struct Student {
	char Name[20]; // Nachname
	int MatrNr;
	struct Datum Einschreibung;
	int Bew_Pkt; // Summe der Klausurpunkte, max. 2000
	char * pBew; // Kommentar zur Bewertung
	struct Student *next;
};

extern void AddStudent(int p, char *Name, int MatrNr, int Etag, int Emon, int Ejahr, int B_P, char *pBew);
extern void DelStudent(int MatrNr);
extern void PrintStudents(void);
extern void AddPkt(int MatrNr, int BewPkt);
extern int BewStudent(char *pBew);

//#define LIST_FOREACH(list, curr) struct Student * curr = NULL;for(curr = list; curr != NULL; curr = curr->next)
#define WHILE(LIST, NODE) struct Student * NODE = LIST;while(NODE != NULL)
#define WHILENEXT(LIST, NODE) struct Student * NODE = LIST;while(NODE->next != NULL)

#endif
