/* Uncomment the practice version you want to run */
#define SIMPLE_VERSION
/*#define COMPLETE_VERSION*/

/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise, this code is excluded. When the code is added, the constant is defined, therefore next time this file will be included it will be defined and no inclusion will be done. */

#define MAX_LINE 512
#define MAX_SUBJECTS 100
#define MAX_SUBJECT_NAME 101
#define MAX_STUDENT_ID_STRING 10
#define MAX_STUDENT_ID_DIGITS 8
#define MAX_STUDENTS 500
#define MAX_STUDENT_NAME 101
#define MAX_STUDENT_EMAIL 101
#define MAX_DESC 200
#define MAX_PATH 256
#define MODULE 23

/* Constant string for student ID verification */
static const char checkID[MODULE] = "TRWAGMYFPDXBNJZSQVHLCKE";

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_FILE_NOT_FOUND=-1, ERR_CANNOT_WRITE=-2, ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, ERR_ENTRY_NOT_FOUND=-6} tError;

/* Definition of a date */
typedef struct {
	unsigned char day;
	unsigned char month;
	unsigned short year;
} tDate;

/* Definition of the sex */
typedef enum {MALE,FEMALE} tSex;

/* Definition of a subject */
typedef struct {
	unsigned int id;
	char name[MAX_SUBJECT_NAME];
	unsigned short credits;
	char desc[MAX_DESC];
} tSubject;

/* Table of subjects */
typedef struct {
/******************** PR 3 - EX 4A ********************/
	tSubject *table;
	unsigned int size;
} tSubjectTable;

/* Definition of the student */
typedef struct {
	unsigned int id;
	char name[MAX_STUDENT_NAME];
	char email[MAX_STUDENT_EMAIL];
	tDate birthDate;
	tSex sex;
	tBoolean exchange;
} tStudent;

/* Table of students */
typedef struct {
/******************** PR 3 - EX 4A ********************/
	tStudent *table;
	unsigned int size;
} tStudentTable;

/* Definition of a mark */
typedef struct {
	unsigned int stuId;
	unsigned int subId;
	float value;
} tMark;

/* Table of marks */
typedef struct {
/******************** PR 3 - EX 4A ********************/
	tMark table[MAX_STUDENTS];
	unsigned int size;
} tMarkTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATH];
	
	/* subjects table */
	tSubjectTable subjects;
	
	/* Students table */
	tStudentTable students;
	
	/* Marks table */
	tMarkTable marks;
	
} tAppData;

/******************** PR 3 - EX 1 ********************/

typedef struct {
	unsigned long id;
    int numSubjects;
    tMarkTable tabM;
    tSubject *tabS[MAX_SUBJECTS];
	int totCredits;
	float avgMark;
} tStudentRecord;

#endif /*__DATA_H*/