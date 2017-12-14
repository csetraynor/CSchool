#include <stdio.h>
#include <string.h>
#include "uocmoney.h"
#include "movements.h"
#include "concepts.h"

void appData_init(tAppData *object) {
	/* Set current folder as the default path */
	strcpy(object->path, "./");
	
	/* Initialize the movements table */
	movTable_init(&(object->movements));
	
	/* Initialize the concepts table */
	conTable_init(&(object->concepts));
}

tError appData_load(tAppData *object) {
	char path[512];
	tError err;
	
	/* Load the table of concepts */
	sprintf(path,"%sconcepts.csv", object->path);
	err=conTable_load(&(object->concepts), path);
	if(err!=OK) {
		printf("ERROR: Error reading the file of concepts\n");
		return err;
	}
	
	/* Load the table of movements */
	sprintf(path,"%smovements.csv", object->path);
	err=movTable_load(&(object->movements), path);
	if(err!=OK) {
		printf("ERROR: Error reading the file of movements\n");
		return err;
	}
	
	return OK;
}

tError appData_save(tAppData object)  {
	char path[512];
	tError err;
	
	/* Save the table of concepts */
	sprintf(path,"%sconcepts.csv", object.path);
	err=conTable_save(object.concepts, path);
	if(err!=OK) {
		printf("ERROR: Error saving the file of concepts\n");
		return err;
	}
	
	/* Save the table of movements */
	sprintf(path,"%smovements.csv", object.path);
	err=movTable_save(object.movements, path);
	if(err!=OK) {
		printf("ERROR: Error saving the file of movements\n");
		return err;
	}
	
	return OK;
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/
void getConcepts(tAppData object, tConceptTable *result) {
	/* Call the method from the concept table*/
	conTable_find(object.concepts, result);
}

tError getConcept(tAppData object, unsigned int conceptID, tConcept *concept) {
	unsigned int i;
		
	/* Check if there is another concept with this ID */
	for(i=0; i<object.concepts.size; i++) {
		if(object.concepts.table[i].id==conceptID) {
			concept->id=object.concepts.table[i].id;
			strcpy(concept->description, object.concepts.table[i].description);
			return OK;
		}
	}
	
	return ERR_ENTRY_NOT_FOUND;
}

tError addConcept(tAppData *object, tConcept concept) {
	tConcept tmp;
	
	/* Check if there is another concept with this ID */
	if(getConcept(*object, concept.id, &tmp)==OK) {
		return ERR_DUPLICATED_ENTRY;
	}
	
	/* Add the new concept using the concept table method */
	return conTable_add(&(object->concepts), concept);
}

void removeConcept(tAppData *object, tConcept concept) {
	tMovementTable movements;
	unsigned int i;
	
	/* Get the list of all movements related to this concept */
	movTable_findByConcept(object->movements, concept.id, &movements);
	
	/* Remove all the movements with this concept */
	for(i=0; i<movements.size; i++) {
		movTable_del(&(object->movements), movements.table[i]);
	}
	
	/* Call the method from the concept table*/
	conTable_del(&(object->concepts), concept);
}

tError addMovement(tAppData *object, tMovement movement) {
	tError err;
	tConcept concept;
	
	/* Check that the concept exists */
	if(getConcept(*object, movement.conceptID, &concept) == OK) {
		/* Call the method from the concept table*/
		err=movTable_add(&(object->movements), movement);	
	} else {
		err=ERR_INVALID_CONCEPT_ID;
	}
	
	return err;
}

void getMovements(tAppData object, tDate start, tDate end, tMovementTable *result) {
	/* Call the method from the movements table*/
	movTable_find(object.movements, start, end, result);	
}

void removeMovement(tAppData *object, tMovement movement) {
	/* Call the method from the movement table*/
	movTable_del(&(object->movements), movement);
}

float getAmount(tAppData object, tDate startDate, tDate endDate) {
	float totalAmount=0;
	unsigned int i=0;
	tMovementTable movements;
	
	for(i=0;i<object.movements.size; i++) {
		/* Get the movements generated by this movement in the given dates */
		getGenMovements(object.movements.table[i], startDate, endDate, &movements);
		
		/* Accumulate the amount */
		totalAmount+=getMovementsAmount(movements);
	}
		
	return totalAmount;
}
