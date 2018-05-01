#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"

struct Student *LIST = NULL;

void
AddStudent (int p, char *Name, int MatrNr, int Etag, int Emon, int Ejahr, int B_P, char *pBew) {
	printf("Adding... MatrNr: %d...\n", MatrNr);
	struct Student * NewStudent = NULL;
	
	NewStudent = (struct Student *) (malloc(sizeof(struct Student)));
	if (NewStudent == NULL) {
		errno = EDOM;
		perror("Faild to allocate memory!!");
		return;
	}
	
	strcpy(NewStudent->Name, Name);
	NewStudent->MatrNr = MatrNr;
	NewStudent->Einschreibung.Tag = Etag;
	NewStudent->Einschreibung.Monat = Emon;
	NewStudent->Einschreibung.Jahr = Ejahr;
	NewStudent->Bew_Pkt = B_P;
	NewStudent->pBew = pBew;
	
	if (p == 0 || LIST == NULL) {
		NewStudent->next = LIST;
		LIST = NewStudent;
	
	} else if (p == 1){
		WHILENEXT(LIST, curr) {
			curr = curr->next;
		}
		curr->next = NewStudent;
		NewStudent->next = NULL;
	}
	
}

void
DelStudent(int MatrNr) {
	printf("Deleting MatrNr: %d...\n", MatrNr);
	struct Student *del = NULL;
	
	if (LIST == NULL) {
		perror("List is empty!!");
		return;
	} else if (LIST->MatrNr == MatrNr){
		del = LIST;
		LIST = LIST->next;
		free(del);
		return;
	}
	
	WHILENEXT(LIST, test) {
		if (test->next->MatrNr == MatrNr) {
			break;
		}
		test = test->next;
	}

	if (test->next == NULL) {
		errno = EOF;
		perror("Nicht Vorhanden!!");
		return;
	}

	del = test->next;
	test->next = test->next->next;
	
	free(del);
}

void
PrintStudents() {
	printf("Printing...\n");
	WHILE(LIST, curr){
		printf("| Name: %s MatrNr.: %d\
			  \n| Einschreibung: %d/%d/%d\
			  \n| Bew_Pkt.: %d\
			  \n| pBew.: %s\n\n" , curr->Name, curr->MatrNr\
												 , curr->Einschreibung.Tag, curr->Einschreibung.Monat, curr->Einschreibung.Jahr\
												 , curr->Bew_Pkt\
												 , curr->pBew);
		curr = curr->next;
	}
	printf("END\n\n");
}

void
AddPkt(int MatrNr, int BewPkt) {
	printf("Adding Pkt MatrNr: %d...\n", MatrNr);
	WHILE(LIST, test) {
		if (test->MatrNr == MatrNr) {
			break;
		}
		test = test->next;
	}

	test->Bew_Pkt += BewPkt;
}

int
BewStudent(char *pBew) {
	printf("BewStudent...\n");
	int bestMatrNr = -1;

	WHILE(LIST, curr) {
		if (curr->Bew_Pkt >= 1800) {
			curr->pBew = pBew;
			bestMatrNr = curr->MatrNr;
		}
		curr = curr->next;
	}
	
	return bestMatrNr;
}
