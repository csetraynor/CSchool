#include "uocmoney.h"

/* Read a movement object from keyboard */
tError readMovement(tAppData appData, tMovement *movement); 

/* Read a date from keyboard */
tError readDate(tDate *date);
	
/* Request an option to the user and check its validity */
unsigned int getOption(unsigned int numOptions);

/* Request the user for two dates and get all the movements between those dates */
tError getMovementsPeriod(tAppData appData, tMovementTable *result);

/* Print a table of movements */
void printMovementTable(tMovementTable table);

/* Print a table of concepts */
void printConceptsTable(tConceptTable table);



/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_MOVEMENTS, MAIN_MENU_CONCEPTS, MAIN_MENU_SOURCES, MAIN_MENU_STATUS, MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the movement management menu options type */
typedef enum {MOV_MNG_MENU_LIST, MOV_MNG_MENU_ADD, MOV_MNG_MENU_DEL, MOV_MNG_MENU_EXIT} tMovementMenuOptions;

/* Define the concept management menu options type */
typedef enum {CON_MNG_MENU_LIST, CON_MNG_MENU_ADD, CON_MNG_MENU_DEL, CON_MNG_MENU_EXIT} tConceptMenuOptions;

/* Define the status menu options type */
typedef enum {STAT_MENU_AMOUNT, STAT_MENU_EXIT} tStatusMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the movement management menu options */
void printMovementMenuOptions();

/* Get the option for the movement management menu */
tMovementMenuOptions getMovementsMenuOption();

/* Perform the actions for the movement management menu */
void movManMenu(tAppData *appData);

/* Print the concept management menu options */
void printConceptMenuOptions();

/* Get the option for the concept management menu */
tConceptMenuOptions getConceptMenuOption();

/* Perform the actions for the concept management menu */
void conManMenu(tAppData *appData);

/* Print the status menu options */
void printStatusMenuOptions();

/* Get the option for the status menu */
tStatusMenuOptions getStatusMenuOption();

/* Perform the actions for the status menu */
void statsMenu(tAppData appData);
