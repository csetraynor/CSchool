#include "data.h"

/* Get a textual representation of a student */
void getStudentStr(tStudent student, int maxSize, char *str);
	
/* Get a student object from its textual representation */
tError getStudentObject(const char *str, tStudent *student);

/* Compare two students */
int student_cmp(tStudent t1, tStudent t2);

/* Compare two students by birth date */
int student_cmpAge(tStudent t1, tStudent t2);

/* Copy the student data in src to dst*/
void student_cpy(tStudent *dst, tStudent src);

/* Initialize the table of students */
void stuTable_init(tStudentTable *stuTable);

/* Load the table of students from a file */
tError stuTable_load(tStudentTable *table, const char* filename);

/* Save a table of students to a file */
tError stuTable_save(tStudentTable table, const char* filename);

/* Find a student in the table */
int stuTable_find(tStudentTable table, unsigned int studentId);

/* Add a new student to the table of students */
tError stuTable_add(tStudentTable *table, tStudent student);

/* Remove the first occurence of a student in the table */
void stuTable_del(tStudentTable *table, tStudent student);

void stuTable_findByBirthYear(tStudentTable tabStu, unsigned int year, tStudentTable *result);

int stuTable_getFemaleNumber(tStudentTable tabStu);

void stuTable_sortByAge(tStudentTable tabStu, tStudentTable *result);

/* Exercice 4e */
/* Release a students table */
void stuTable_release(tStudentTable *table); 
