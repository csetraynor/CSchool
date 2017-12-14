#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
tError appData_load(tAppData *object);

/* Save the application data to a file */
tError appData_save(tAppData object);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);


/* 
 * API
 */

/* Return a table with the movements between the two dates (incuded) */
void getMovements(tAppData object, tDate start, tDate end, tMovementTable *result);

/* Add a new movement */
tError addMovement(tAppData *object, tMovement movement);

/* Remove all copies of a certain movement */
void removeMovement(tAppData *object, tMovement movement);

/* Return the table of concepts */
void getConcepts(tAppData object, tConceptTable *result);

/* Get the concept information */
tError getConcept(tAppData object, unsigned int conceptID, tConcept *concept);

/* Add a new concept */
tError addConcept(tAppData *object, tConcept concept);

/* Remove a concept and all movements with this concept */
void removeConcept(tAppData *object, tConcept concept);

/* Evaluate the total amount for the movements between two dates */
float getAmount(tAppData object, tDate startDate, tDate endDate);

