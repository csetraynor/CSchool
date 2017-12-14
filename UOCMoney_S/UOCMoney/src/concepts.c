#include <stdio.h>
#include <string.h>
#include "concepts.h"

void getConceptStr(tConcept concept, int maxSize, char *str) {
	snprintf(str,maxSize-1,"%u;%s;", (unsigned int)concept.id, concept.description);			
	str[maxSize-1]='\0';
}

tError getConceptObject(const char *str, tConcept *concept) {
	unsigned int tmpConceptID;	
	sscanf(str, "%u;%[^;];", &tmpConceptID, concept->description);
	if(tmpConceptID<0) {
		return ERR_INVALID_DATA;
	}
	concept->id=(unsigned char) tmpConceptID;
	
	return OK;
}

int concept_cmp(tConcept c1, tConcept c2) {
	if(c1.id==c2.id && strcmp(c1.description, c2.description)==0) {
		/* Are equals*/
		return 0;
	}
	
	if(c1.id==c2.id) {
		/* The order depends of the order of the descriptions */
		return strcmp(c1.description, c2.description);
	} 
	
	if(c1.id<c2.id) {
		/* c1 < c2 */
		return -1;
	} 
	
	/* c1 > c2*/
	return 1;
}

void conTable_init(tConceptTable *table) {
	table->size=0;
}

tError conTable_load(tConceptTable *table, const char* filename) {
	FILE *fin=0;
	char line[512];
	tConcept newConcept;
	
	/* Initialize the output table */
	conTable_init(table);
		
	/* Open the input file */
	if((fin=fopen(filename, "r"))==0) {
		return ERR_FILE_NOT_FOUND;
	}
	
	/* Read all the concepts */
	while(!feof(fin) && table->size<MAX_CONCEPTS) {
		/* Remove any content from the line */
		line[0] = '\0';
		/* Read one line (maximum 255 chars) and store it in "line" variable */
		fgets(line, 512, fin);
		/* Ensure that the string is ended by 0*/
		line[511]='\0';
		if(strlen(line)>0) {
			/* Obtain the object */
			getConceptObject(line, &newConcept);
			/* Add the new concept to the output table */
			conTable_add(table, newConcept);		
		}
	}	
	
	/* Close the file */
	fclose(fin);
	
	return OK;
}

tError conTable_save(tConceptTable table, const char* filename) {
	FILE *fout=0;
	unsigned int i;
	char str[512];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		return ERR_CANNOT_WRITE;
	}
	
	/* Save all concepts to the file */
	for(i=0;i<table.size;i++) {
		getConceptStr(table.table[i], 512, str);
		fprintf(fout, "%s\n", str);
	}
		
	/* Close the file */
	fclose(fout);
	
	return OK;
}

tError conTable_add(tConceptTable *table, tConcept concept) {
	/* Check if there enough space for the new concept */
	if(table->size>=MAX_CONCEPTS) {
		return ERR_MEMORY;
	}
	
	/* Add the new concept to the end of the table */
	table->table[table->size].id=concept.id;
	strcpy(table->table[table->size].description, concept.description);
	table->size++;
	
	return OK;
}

void conTable_del(tConceptTable *table, tConcept concept) {
	unsigned int i;
	tBoolean displace=FALSE;
	
	/* If the concept is found, all the rest of the elements are displaced one position */
	for(i=0; i<table->size; i++) {		
		if(concept_cmp(table->table[i], concept)==0) {						
			displace=TRUE;
		}
		if(displace) {			
			table->table[i].id=table->table[i+1].id;
			strcpy(table->table[i].description, table->table[i+1].description);
		}
	}
	if(displace) {
		table->size=table->size-1;			
	}
}

void conTable_find(tConceptTable table, tConceptTable *result) {
	unsigned int i;
	
	/* Initialize the output table */
	conTable_init(result);
	
	/* Copy all the concepts to the output table */
	for(i=0;i<table.size;i++) {
		result->table[i].id=table.table[i].id;
		strcpy(result->table[i].description, table.table[i].description);
	}
	result->size=table.size;
}
