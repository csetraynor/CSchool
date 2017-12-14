#include "data.h"
#include "api.h"

/* Request an option to the user and check its validity */
unsigned int getOption(unsigned int numOptions);

/* Define the main menu options type */
typedef enum {MAIN_MENU_LOAD, MAIN_MENU_SAVE, MAIN_MENU_STUDENTS, MAIN_MENU_SUBJECTS, MAIN_MENU_MARKS, MAIN_MENU_STATS, MAIN_MENU_EXIT} tMainMenuOptions;

/* Define the student management menu options type */
typedef enum {STU_MNG_MENU_LIST, STU_MNG_MENU_ADD, STU_MNG_MENU_DEL, STU_MNG_MENU_EXIT} tStudentMenuOptions;

/* Define the subject management menu options type */
typedef enum {SUB_MNG_MENU_LIST, SUB_MNG_MENU_ADD, SUB_MNG_MENU_EXIT} tSubjectMenuOptions;

/* Define the mark management menu options type */
typedef enum {MRK_MNG_MENU_LIST, MRK_MNG_MENU_ADD, MRK_MNG_MENU_DEL, MRK_MNG_MENU_EXIT} tMarkMenuOptions;

/* Define the status menu options type */
typedef enum {STAT_MENU_FEMALE, STAT_MENU_BIRTHYEAR, STAT_MENU_EXIT} tStatsMenuOptions;

/* Print the main menu options */
void printMainMenuOptions();

/* Get the option for the main menu */
tMainMenuOptions getMenuOption();

/* Perform the actions for the main menu */
void mainMenu(tAppData *appData);

/* Print the student management menu options */
void printStudentMenuOptions();

/* Get the option for the student management menu */
tStudentMenuOptions getStudentsMenuOption();

/* Perform the actions for the student management menu */
void stuManMenu(tAppData *appData);

/* Print the subject management menu options */
void printSubjectMenuOptions();

/* Get the option for the subject management menu */
tSubjectMenuOptions getSubjectMenuOption();

/* Perform the actions for the subject management menu */
void subManMenu(tAppData *appData);

/* Print the mark management menu options */
void printMarkMenuOptions();

/* Get the option for the mark management menu */
tMarkMenuOptions getMarkMenuOption();

/* Perform the actions for the student management menu */
void mrkManMenu(tAppData *appData);

/* Print the stats menu options */
void printStatsMenuOptions();

/* Get the option for the status menu */
tStatsMenuOptions getStatsMenuOption();

/* Perform the actions for the status menu */
void statsMenu(tAppData appData);
