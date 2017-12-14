#include "data.h"

/* Get a textual representation of a concept */
void getConceptStr(tConcept concept, int maxSize, char *str);

/* Get a concept object from its textual representation */
tError getConceptObject(const char *str, tConcept *concept);

/* Compare two concepts */
int concept_cmp(tConcept c1, tConcept c2);


/* Initialize the table of concepts */
void conTable_init(tConceptTable *table);

/* Load the table of concepts from a file */
tError conTable_load(tConceptTable *table, const char* filename);

/* Save a table of concepts to a file */
tError conTable_save(tConceptTable table, const char* filename);

/* Add a new concept to the table of concepts */
tError conTable_add(tConceptTable *table, tConcept concept);

/* Remove the first occurence of a concept in the table */
void conTable_del(tConceptTable *table, tConcept concept);

/* Find the concepts in the table */
void conTable_find(tConceptTable table, tConceptTable *result);
