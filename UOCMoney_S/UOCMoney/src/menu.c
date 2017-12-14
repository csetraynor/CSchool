#include <stdio.h>
#include "menu.h"
#include "concepts.h"
#include "movements.h"

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

tError readMovement(tAppData appData, tMovement *movement) {	
	unsigned int tmpMovType;	
	unsigned int tmpMovIsPeriodic;
	unsigned int posConcept;
	tConceptTable concepts;
		
	/* Request information from user */
	printf("Plese enter the account movement information\n\n");
	printf("Movement type:\n(0 income, 1 expense) >> ");
	scanf("%u", &tmpMovType);
	getchar();
	if(tmpMovType<0 || tmpMovType>1) {
		printf("Invalid value\n");
		return ERR_INVALID_DATA;
	}
	movement->type=(tMovementType)tmpMovType;
	printf("Description:\n>> ");
	scanf("%[^\n]", movement->description);
	getchar();
	printf("Amount:\n>> ");
	scanf("%f", &(movement->amount));
	getchar();
	printf("Is periodic?:\n(1 yes, 0 no) >> ");
	scanf("%u", &tmpMovIsPeriodic);
	getchar();
	if(tmpMovIsPeriodic<0 || tmpMovIsPeriodic>1) {
		printf("Invalid value\n");
		return ERR_INVALID_DATA;
	}
	movement->isPeriodic=(tBoolean)tmpMovIsPeriodic;
	if(movement->isPeriodic) {
		printf("Start date:");
		if(readDate(&(movement->date))!=OK) {
			printf("Invalid start date\n");
			return ERR_INVALID_DATA;
		}		
		printf("End date:");
		if(readDate(&(movement->endDate))!=OK) {
			printf("Invalid end date\n");
			return ERR_INVALID_DATA;
		}			
	} else {
		printf("Date:");
		if(readDate(&(movement->date))!=OK) {
			printf("Invalid date\n");
			return ERR_INVALID_DATA;
		}		
	}
	
	printf("Select the concept: \n");
	getConcepts(appData, &concepts);
	printConceptsTable(concepts);
	posConcept=getOption(concepts.size);	
	movement->conceptID=concepts.table[posConcept-1].id;
	
	return OK;
}

tError readDate(tDate *date) {	
	unsigned int day, month, year;
	
	printf("[dd/mm/yyyy]>> ");
	scanf("%u/%u/%u", &day, &month, &year);	
	
	if(day>31 || month>12) {
		return ERR_INVALID_DATA;
	}
	
	if(!(day==0 && month==0 && year==0) && (day==0 || month==0)) {
		return ERR_INVALID_DATA;		
	}	
	
	date->day=(unsigned char)day;
	date->month=(unsigned char)month;
	date->year=(unsigned short)year;
	
	return OK;
}

tError getPeriodDates(tDate *startDate, tDate *endDate) {
	printf("Enter the first date of the period. Use 0/0/0 for empty date.\n");
	if(readDate(startDate)!=OK) {
		printf("Invalid date\n");
		return ERR_INVALID_DATA;
	}
	printf("Enter the last date of the period. Use 0/0/0 for empty date.\n");
	if(readDate(endDate)!=OK) {
		printf("Invalid date\n");
		return ERR_INVALID_DATA;
	}
	
	return OK;
}
tError getMovementsPeriod(tAppData appData, tMovementTable *result) { 
	tDate startDate;
	tDate endDate;
	
	if(getPeriodDates(&startDate, &endDate)==OK) {	
		/* If the dates are correct, get the result */
		getMovements(appData, startDate, endDate, result);
	
		return OK;		
	}
	
	return ERROR;
}

tError readConcept(tConcept *concept) {	
	unsigned int tmpMovConceptID;
	
	printf("ID:\n>> ");
	scanf("%u", &tmpMovConceptID);
	getchar();
	printf("Description:\n>> ");
	scanf("%[^\n]", concept->description);
	getchar();
	
	concept->id=(unsigned char) tmpMovConceptID;
		
	return OK;
}

void printConceptsTable(tConceptTable table) {
	unsigned int i;	
	char movStr[512];
	
	if(table.size==0) {
		printf("No movements.\n");
	} else {
		for(i=0;i<table.size;i++) {
			getConceptStr(table.table[i], 512, movStr);
			printf("[%d] - %s\n", i+1, movStr);
		}		
	}
}

void printMovementTable(tMovementTable table) {
	unsigned int i;	
	char movStr[512];
	
	if(table.size==0) {
		printf("No movements.\n");
	} else {
		for(i=0;i<table.size;i++) {
			getMovementStr(table.table[i], 512, movStr);
			printf("[%d] - %s\n", i+1, movStr);
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
	printf("3) Manage account movements\n");
	printf("4) Manage concepts\n");
	printf("5) Manage account sources\n");
	printf("6) View status\n");
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
	appData_setPath(appData,"./data/");
		
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
		case MAIN_MENU_MOVEMENTS:
			movManMenu(appData);
			break;
		case MAIN_MENU_CONCEPTS:
			conManMenu(appData);
			break;
		case MAIN_MENU_SOURCES:
			printf("Option 5 (Manage account sources) has been selected\n");
			break;
		case MAIN_MENU_STATUS:
			statsMenu(*appData);
			break;		
		case MAIN_MENU_EXIT:
			break;
		}	
	} while(option!=MAIN_MENU_EXIT);
}

/*********************************
 **   MOVEMENTS MANAGEMENT MENU **
*********************************/
void printMovementMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Account Movements\n");
	printf("=======================\n");
	printf("1) List movements\n");	
	printf("2) Add movement\n");
	printf("3) Delete movement\n");	
	printf("4) Exit\n");	
}

tMovementMenuOptions getMovementsMenuOption() {
	/* Convert to the correct type */
	return (tMovementMenuOptions)(getOption(4)-1);
}

void movManMenu(tAppData *appData) {
	tMovementMenuOptions option;
	tMovement movement;
	tMovementTable movTable;
	unsigned int pos=0;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printMovementMenuOptions();
		option=getMovementsMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case MOV_MNG_MENU_LIST:
			/* Get the movements between two dates*/
			if(getMovementsPeriod(*appData, &movTable)==OK) {			
				/* Print the movements */			
				printMovementTable(movTable);				
			}
			break;
		case MOV_MNG_MENU_ADD:
			printf("Enter the information for the new movement:\n");
			if(readMovement(*appData, &movement)==OK) {
				addMovement(appData, movement);
			}
			break;
		case MOV_MNG_MENU_DEL:
			if(getMovementsPeriod(*appData, &movTable)==OK) {			
				/* Print the movements */			
				printMovementTable(movTable);				
				/* Ask the number of the register to be removed */
				pos=getOption(movTable.size);
				/* Remove the selected movement */				
				removeMovement(appData, movTable.table[pos-1]);
			}
			break;		
		case MOV_MNG_MENU_EXIT:
			break;
		}	
	} while(option!=MOV_MNG_MENU_EXIT);
}

/********************************
 **   CONCEPTS MANAGEMENT MENU **
********************************/
void printConceptMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Manage Concepts\n");
	printf("=======================\n");
	printf("1) List concepts\n");	
	printf("2) Add concept\n");
	printf("3) Delete concept\n");	
	printf("4) Exit\n");	
}

tConceptMenuOptions getConceptMenuOption() {
	/* Convert to the correct type */
	return (tConceptMenuOptions)(getOption(4)-1);
}

void conManMenu(tAppData *appData) {
	tConceptMenuOptions option;
	tConceptTable concepts;
	tConcept newConcept;
	tError err;
	unsigned int pos;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printConceptMenuOptions();
		option=getConceptMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case CON_MNG_MENU_LIST:
			getConcepts(*appData, &concepts);
			printConceptsTable(concepts);
			break;
		case CON_MNG_MENU_ADD:
			if(readConcept(&newConcept)==OK) {
				err=addConcept(appData, newConcept);
				if(err==ERR_DUPLICATED_ENTRY) {
					printf("ERROR: A concept with the same ID already exists\n");
				}
			}			
			break;
		case CON_MNG_MENU_DEL:
			/* Select the concept to be removed. All movements with this concept will be removed */
			/* Print the concepts */			
			getConcepts(*appData, &concepts);
			printConceptsTable(concepts);				
			/* Ask the number of the register to be removed */
			pos=getOption(concepts.size);
			/* Remove the selected concept */				
			removeConcept(appData, concepts.table[pos-1]);
			break;		
		case CON_MNG_MENU_EXIT:
			break;
		}	
	} while(option!=CON_MNG_MENU_EXIT);	
}

/******************
 **   STAUS MENU **
******************/
void printStatusMenuOptions() {
	/* Show menu options */
	printf("=======================\n");
	printf(" Status \n");
	printf("=======================\n");
	printf("1) Get total amount\n");	
	printf("2) Exit\n");	
}


tStatusMenuOptions getStatusMenuOption() {
	/* Convert to the correct type */
	return (tStatusMenuOptions)(getOption(3)-1);
}

void statsMenu(tAppData appData) {
	tStatusMenuOptions option;
	tDate startDate, endDate;
	float amount=0;
			
	/* Start the menu */
	do {
		/* Show list of options and ask the user for an option */
		printStatusMenuOptions();
		option=getStatusMenuOption();
		
		/* Do the action for the given option */
		switch(option) {
		case STAT_MENU_AMOUNT:
			/* Get the dates of the period */
			if(getPeriodDates(&startDate, &endDate)==OK) {			
				/* Get the total amount between two dates*/
				amount=getAmount(appData, startDate, endDate);
				printf("The total amount for this period is %02f\n", amount);
			}
			break;	
		case STAT_MENU_EXIT:
			break;	
		}	
	} while(option!=STAT_MENU_EXIT);	
}
