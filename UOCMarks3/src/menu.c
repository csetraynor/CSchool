#include <stdio.h>
#include "menu.h"
#include "subjects.h"
#include "students.h"
#include "marks.h"

tError readDate(tDate *date);
tError readStudent(tStudent *student);

unsigned int getOption(unsigned int numOptions) {
	unsigned int option=0;
	
	while(option<1 || option>numOptions) {
		/* Read the input */
		printf(">> ");
		scanf("%u", &option);
		getchar();
		
		/* Check the user input */
		if(option<1 || option>numOptions) {
			printf("Incorrect option.\n");
		}
	}
	 return option;
}

tError readStudent(tStudent *student) {	

	tError retVal = OK;
	char letter;
	unsigned int tmpSex, tmpExchange;

	/* Request information from user */

	printf("ID:\n>> ");
	scanf("%u%c", &student->id,&letter);
	if(letter!=checkID[student->id % MODULE]) {
		printf("Invalid ID\n");
		retVal = ERR_INVALID_DATA;
	} else {
		getchar();
	
		printf("Name:\n>> ");
		scanf("%[^\n]", student->name);
		getchar();
		
		printf("Email:\n>> ");
		scanf("%s", student->email);
		getchar();

		printf("Date:\n");
		if(readDate(&(student->birthDate))!=OK) {
			printf("Invalid date\n");
			retVal = ERR_INVALID_DATA;
		} else {
			getchar();
			
			printf("Sex:\n(0 male, 1 female) >> ");
			scanf("%u", &tmpSex);
			getchar();
			if(tmpSex>1) {
				printf("Invalid value\n");
				retVal = ERR_INVALID_DATA;
			} else {
				student->sex=(tSex)tmpSex;
				
				printf("Is a exchange student?:\n(1 yes, 0 no) >> ");
				scanf("%u", &tmpExchange);
				getchar();
				if(tmpExchange>1) {
					printf("Invalid value\n");
					retVal = ERR_INVALID_DATA;
				} else {
					student->exchange=(tBoolean)tmpExchange;
				
				}
			}
		}
	}
	return retVal;
}

tError readDate(tDate *date) {
	
	tError retVal = OK;
	unsigned int day, month, year;
	
	printf("[dd/mm/yyyy]>> ");
	scanf("%u/%u/%u", &day, &month, &year);	
	
	if(day>31 || month>12) {
		retVal = ERR_INVALID_DATA;
	}
	
	if(!(day==0 && month==0 && year==0) && (day==0 || month==0)) {
		retVal = ERR_INVALID_DATA;		
	}	
	
	date->day=(unsigned char)day;
	date->month=(unsigned char)month;
	date->year=(unsigned short)year;
	
	return retVal;
}

tError readSubject(tSubject *subject) {	

	tError retVal = OK;
		
	printf("ID:\n>> ");
	scanf("%u", &subject->id);
	getchar();
	
	printf("Name:\n>> ");
	scanf("%[^\n]", subject->name);
	getchar();
	
	printf("Number of credits:\n>> ");
	scanf("%hu", &subject->credits);
	getchar();
	
	printf("Description:\n>> ");
	scanf("%[^\n]", subject->desc);
	getchar();
	
	return retVal;
}

tError readMark(tMark *mark) {	

	tError retVal = OK;
		
	printf("Student ID:\n>> ");
	scanf("%u", &mark->stuId);
	getchar();
	
	printf("Subject ID:\n>> ");
	scanf("%u", &mark->subId);
	getchar();
	
	printf("Mark:\n>> ");
	scanf("%f", &mark->value);
	getchar();
	
	return retVal;
}

void printSubjectsTable(tSubjectTable table) {
	unsigned int i;	
	char stuStr[MAX_LINE];
	
	if(table.size==0) {
		printf("No subjects.\n");
	} else {
		for(i=0;i<table.size;i++) {
			getSubjectStr((table.table[i]), MAX_LINE, stuStr);
			printf("[%d] - %s\n", i+1, stuStr);
		}		
	}
}

void printStudentTable(tStudentTable table) {
	unsigned int i;	
	char stuStr[MAX_LINE];
	
	if(table.size==0) {
		printf("No students.\n");
	} else {
		for(i=0;i<table.size;i++) {
			getStudentStr(table.table[i], MAX_LINE, stuStr);
			printf("[%d] - %s\n", i+1, stuStr);
		}		
	}
}

void printMarkTable(tMarkTable tabMrk) {
	unsigned int i;	
	char mrkStr[MAX_LINE];
	
	if(tabMrk.size==0) {
		printf("No marks.\n");
	} else {
		for(i=0;i<tabMrk.size;i++) {
            getMarkStr(tabMrk.table[i], MAX_LINE, mrkStr);
			printf("[%d] - %s\n", i+1, mrkStr);
		}		
	}
}

/*****************
 **   MAIN MENU **
*****************/
void printMainMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Main Menu \n");
	printf("=======================\n");
	printf("1) Load data from file\n");
	printf("2) Save data to file\n");
	printf("3) Manage students\n");
	printf("4) Manage subjects\n");
	printf("5) Manage marks\n");
	printf("6) View statistics\n");
	printf("7) Exit\n");	
}

tMainMenuOptions getMainMenuOption() {
	/* Convert to the correct type */
	return (tMainMenuOptions)(getOption(7)-1);
}

void mainMenu(tAppData *appData) 
{
	tMainMenuOptions option;
		
	/* Assign the data path */
	appData_setPath(appData,"../");
		
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMainMenuOptions();
		option=getMainMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case MAIN_MENU_LOAD:
			if(appData_load(appData)==OK) {
				printf("Data loaded\n");
			} else {	
				printf("No previous data loaded\n");
			}
			break;
		case MAIN_MENU_SAVE:
			if(appData_save(*appData)==OK) {
				printf("Data saved\n");
			} else {	
				printf("Cannot save the data\n");
			}
			break;
		case MAIN_MENU_STUDENTS:
			stuManMenu(appData);
			break;
		case MAIN_MENU_SUBJECTS:
			subManMenu(appData);
			break;
		case MAIN_MENU_MARKS:
			mrkManMenu(appData);
			break;
		case MAIN_MENU_STATS:
			statsMenu(*appData);
			break;		
		case MAIN_MENU_EXIT:
			break;
		}	
	} while(option!=MAIN_MENU_EXIT);
}

/*********************************
 **   STUDENTS MANAGEMENT MENU **
*********************************/
void printStudentMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Students\n");
	printf("=======================\n");
	printf("1) List students\n");	
	printf("2) Add student\n");
	printf("3) Delete student\n");	
	printf("4) Exit\n");	
}

tStudentMenuOptions getStudentsMenuOption() {
	/* Convert to the correct type */
	return (tStudentMenuOptions)(getOption(4)-1);
}

void stuManMenu(tAppData *appData) {
	tStudentMenuOptions option;
	tStudent newStudent;
	tStudentTable stuTable;
	unsigned int pos=0;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStudentMenuOptions();
		option=getStudentsMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case STU_MNG_MENU_LIST:
			/* Get the students between two dates*/
			
			if(getStudents(*appData, &stuTable)==OK) {			
				/* Print the students */			
				printStudentTable(stuTable);				
			}
			break;
		case STU_MNG_MENU_ADD:
			printf("Enter the information for the new student:\n");
			if(readStudent(&newStudent)==OK) {
				addStudent(appData, newStudent);
			}
			break;
		case STU_MNG_MENU_DEL:
			if(getStudents(*appData, &stuTable)==OK) {			
				/* Print the students */			
				printStudentTable(stuTable);				
				/* Ask the number of the register to be removed */
				pos=getOption(stuTable.size);
				/* Remove the selected student */				
				removeStudent(appData, stuTable.table[pos-1]);
			}
			break;		
		case STU_MNG_MENU_EXIT:
			break;
		}	
	} while(option!=STU_MNG_MENU_EXIT);
}

/********************************
 **   SUBJECT MANAGEMENT MENU **
********************************/
void printSubjectMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage subjects\n");
	printf("=======================\n");
	printf("1) List subjects\n");	
	printf("2) Add subject\n");
	printf("3) Exit\n");	
}

tSubjectMenuOptions getSubjectMenuOption() {
	/* Convert to the correct type */
	return (tSubjectMenuOptions)(getOption(3)-1);
}

void subManMenu(tAppData *appData) {
	tSubjectMenuOptions option;
	tSubjectTable subjects;
	tSubject newSubject;
	tError retVal = OK;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printSubjectMenuOptions();
		option=getSubjectMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case SUB_MNG_MENU_LIST:
			getSubjects(*appData, &subjects);
			printSubjectsTable(subjects);
			break;
		case SUB_MNG_MENU_ADD:
			if(readSubject(&newSubject)==OK) {
				retVal=addSubject(appData, newSubject);
				if(retVal==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A subject with the same ID already exists\n");
				}
			}			
			break;
		case SUB_MNG_MENU_EXIT:
			break;
		}	
	} while(option!=SUB_MNG_MENU_EXIT);	
}

/*********************************
 **   MARKS MANAGEMENT MENU **
*********************************/
void printMarkMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Marks\n");
	printf("=======================\n");
	printf("1) List marks\n");	
	printf("2) Add mark\n");
	printf("3) Delete mark\n");	
	printf("4) Exit\n");	
}

tMarkMenuOptions getMarkMenuOption() {
	/* Convert to the correct type */
	return (tMarkMenuOptions)(getOption(4)-1);
}

void mrkManMenu(tAppData *appData) {
	tMarkMenuOptions option;
	tMark newMark;
	tMarkTable mrkTable;
	unsigned int pos=0;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMarkMenuOptions();
		option=getMarkMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case MRK_MNG_MENU_LIST:
			/* Get the marks*/
			
			if(getMarks(*appData, &mrkTable)==OK) {			
				/* Print the students */			
				printMarkTable(mrkTable);				
			}
			break;
		case MRK_MNG_MENU_ADD:
			printf("Enter the information for the new student:\n");
			if(readMark(&newMark)==OK) {
				addMark(appData, newMark);
			}
			break;
		case MRK_MNG_MENU_DEL:
			if(getMarks(*appData, &mrkTable)==OK) {			
				/* Print the students */			
				printMarkTable(mrkTable);				
				/* Ask the number of the register to be removed */
				pos=getOption(mrkTable.size);
				/* Remove the selected student */				
				removeMark(appData, mrkTable.table[pos-1]);
			}
			break;		
		case MRK_MNG_MENU_EXIT:
			break;
		}	
	} while(option!=MRK_MNG_MENU_EXIT);
}

/******************
 **   STATS MENU **
******************/
void printStatsMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Stats \n");
	printf("=======================\n");
	printf("1) Get number of females\n");	
	printf("2) Get number of students given a birth year\n");	
	printf("3) Exit\n");	
}


tStatsMenuOptions getStatusMenuOption() {
	/* Convert to the correct type */
	return (tStatsMenuOptions)(getOption(3)-1);
}

void statsMenu(tAppData appData) {
	tStatsMenuOptions option;
	tStudentTable stuTable;
	tStudentTable stuTableFilt;
	unsigned int year;
	
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStatsMenuOptions();
		option=getStatusMenuOption();
		
		getStudents(appData, &stuTable);

		/* Do the action for the given option */
		switch(option) {
		case STAT_MENU_FEMALE:
			printf("Number of females: %d\n", stuTable_getFemaleNumber(stuTable));
			break;
		case STAT_MENU_BIRTHYEAR:
			printf("Introduce birth year:\n >> ");
			scanf("%u",&year);
			stuTable_findByBirthYear(stuTable, year, &stuTableFilt);
			printf("Number of students born on %d: %d\n", year, stuTableFilt.size);
			break;
		case STAT_MENU_EXIT:
			break;	
		}	
	} while(option!=STAT_MENU_EXIT);	
}
