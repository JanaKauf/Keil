/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
  *          	Labor f�r technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "linkedlist.h"


#include "TI_Lib.h"

/**
  * @brief  Main program
  * @param  None
  */
int main(void)
{	
	Init_TI_Board();
	
	char* pBew[] = {"Mittel", "Hoch", "Ausgezeichnet"};
	
	AddStudent(1, "Kaufmann", 23098, 8, 7, 2002, 0, pBew[0]);
	PrintStudents();
	AddStudent(1, "Tekes", 29348, 2, 1, 2012, 0, pBew[0]);
	PrintStudents();
	AddStudent(0, "Napier", 33094, 1, 3, 2003, 0, pBew[0]);
	PrintStudents();
	AddStudent(0, "Quinzel", 20008, 12, 2, 2006, 0, pBew[0]);
	PrintStudents();
	AddStudent(1, "Isley", 23000, 27, 5, 2007, 0, pBew[0]);
	PrintStudents();
	AddStudent(1, "Dent", 19098, 30, 9, 2014, 0, pBew[0]);
	PrintStudents();
	AddStudent(1, "Nigma", 33033, 22, 10, 2009, 0, pBew[0]);
	PrintStudents();
	AddStudent(1, "Cobblepot", 13548, 11, 4, 2010, 0, pBew[0]);
	PrintStudents();
	
	AddPkt(33094, 1800);
	PrintStudents();
	AddPkt(20008, 1800);
	PrintStudents();
	AddPkt(23098, 1800);
	PrintStudents();
	AddPkt(33033, 1800);
	PrintStudents();
	AddPkt(33033, 100);
	PrintStudents();
	AddPkt(19098, 300);
	PrintStudents();
	
	setzeBew();
	PrintStudents();
	
	delUnder100();
	PrintStudents();
	
	DelStudent(23098);
	PrintStudents();
	DelStudent(23000);
	PrintStudents();
	DelStudent(33033);
	PrintStudents();
	DelStudent(20008);
	PrintStudents();
	DelStudent(29348);
	PrintStudents();
	DelStudent(19098);
	PrintStudents();
	DelStudent(33094);
	PrintStudents();
	DelStudent(33033);
	PrintStudents();
	DelStudent(13548);
	PrintStudents();
	
	
  return 0;

}
// EOF
