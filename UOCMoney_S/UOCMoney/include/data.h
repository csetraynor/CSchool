/* This code ensures that this file is included only once */
#ifndef DATA_H
#define DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise, this code is excluded. When the code is added, the constant is defined, therefore next time this file will be included it will be defined and no inclusion will be done. */

#define MAX_CONCEPTS 15
#define MAX_CONCEPT_DESC 100
#define MAX_MOVEMENTS 50


/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_FILE_NOT_FOUND=-1, ERR_CANNOT_WRITE=-2, ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, ERR_ENTRY_NOT_FOUND=-6, ERR_INVALID_CONCEPT_ID=-7} tError;

/* Definition of a concept */
typedef struct {
	unsigned char id;
	char description[MAX_CONCEPT_DESC];
} tConcept;

/* Table of concepts */
typedef struct {
	tConcept table[MAX_CONCEPTS];
	unsigned int size;
} tConceptTable;

/* Definition of movement type */
typedef enum {INCOME, EXPENSE} tMovementType;

/* Definition of a date */
typedef struct {
	unsigned char day;
	unsigned char month;
	unsigned short year;
} tDate;

/* Definition of the movement */
typedef struct {
	tMovementType type;	
	char description[128];
	float amount;
	tBoolean isPeriodic;	
	tDate date;
	tDate endDate;
	unsigned char conceptID;	
} tMovement;

/* Table of movements */
typedef struct {
	tMovement table[MAX_MOVEMENTS];
	unsigned int size;
} tMovementTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[256];
	
	/* Concepts table */
	tConceptTable concepts;
	
	/* Movements table */
	tMovementTable movements;
} tAppData;

#endif /*DATA_H*/