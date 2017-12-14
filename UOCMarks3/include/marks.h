#include "data.h"

/* Get a textual representation of a mark */
void getMarkStr(tMark mark, int maxSize, char *str);
	
/* Get a mark object from its textual representation */
tError getMarkObject(const char *str, tMark *mark);

/* Initialize the table of marks */
void mrkTable_init(tMarkTable *table);

/* Load the table of marks from a file */
tError mrkTable_load(tMarkTable *table, const char* filename);

/* Save a table of marks to a file */
tError mrkTable_save(tMarkTable table, const char* filename);

/* Add a new mark to the table of marks */
tError mrkTable_add(tMarkTable *table, tMark mark);

/* Remove the occurence of a mark in the table */
void mrkTable_del(tMarkTable *table, tMark mark);

/* Find marks */
void mrkTable_find(tMarkTable table, tMarkTable *result);

/* Find marks of a given subject */
void mrkTable_filterBySubject(tMarkTable table, unsigned int subjectId, tMarkTable *result);

/* Find marks of a given student */
void mrkTable_filterByStudent(tMarkTable table, unsigned int studentId, tMarkTable *result);

/* Copy the mark data in src to dst*/
void mark_cpy(tMark *dst, tMark src);

/* Compare two marks */
tBoolean mark_cmp(tMark m1, tMark m2);

/* Exercice 4e */
/* Release a marks table */
void mrkTable_release(tMarkTable *table); 

/* Evaluate the average marks for a table of students */
float getStudentsAvgMark(tMarkTable table);

/* Evaluate the average mark of a subject for a table of students */
float getSubjectAvgMark(tMarkTable table, unsigned int subjectID);
