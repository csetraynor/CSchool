#include "data.h"

/* Get a textual representation of a subject */
void getSubjectStr(tSubject subject, int maxSize, char *str);

/* Get a subject object from its textual representation */
tError getSubjectObject(const char *str, tSubject *subject);

/* Compare two subjects */
int subject_cmp(tSubject s1, tSubject s2);

/* Copy the subject data in src to dst*/
void subject_cpy(tSubject *dst, tSubject src);

/* Initialize the table of subjects */
void subTable_init(tSubjectTable *tabSub);

/* Load the table of subjects from a file */
tError subTable_load(tSubjectTable *tabSub, const char* filename);

/* Save a table of subjects to a file */
tError subTable_save(tSubjectTable tabSub, const char* filename);

/* Add a new subject to the table of subjects */
tError subTable_add(tSubjectTable *tabSub, tSubject subject);

/* Add a new subject to the table of subjects (sorted) */
tError subTable_sortedAdd(tSubjectTable *tabSub, tSubject subject);

/* Find a subject in the table */
int subTable_find(tSubjectTable tabSub, unsigned int subjectId);

/* Remove the first occurence of a subject in the table */
void subTable_del(tSubjectTable *tabSub, tSubject subject);

/* Release a subjects table */
void subTable_release(tSubjectTable *tabSub); 
