#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "marks.h"

void getMarkStr(tMark mark, int maxSize, char *str) {
	snprintf(str,maxSize-1,"%u;%u;%f;", mark.stuId, mark.subId, mark.value);			
	str[maxSize-1]='\0';
}

tError getMarkObject(const char *str, tMark *mark) {

	sscanf(str, "%u;%u;%f", &mark->stuId, &mark->subId, &mark->value);

	return OK;
}

void mrkTable_init(tMarkTable *tabM) {
	tabM->size=0;
/******************** PR 3 - EX 4B ********************/
}

tBoolean mark_cmp(tMark m1, tMark m2) {
	
    tBoolean retVal = TRUE;
    
	if(m1.stuId!=m2.stuId) 
		retVal= FALSE;
	else if (m1.subId!=m2.subId) 
        retVal = FALSE;
	else if (m1.value!=m2.value) 
        retVal = FALSE;

	return retVal;
}

void mark_cpy(tMark *dst, tMark src) {
	dst->stuId = src.stuId; 
	dst->subId = src.subId;
	dst->value = src.value;
}

int mrkTable_findMark(tMarkTable tabM, unsigned int studentId, unsigned int subjectId) {
	unsigned int i;
	int idx = -1;
	
	i=0;
	while(i< tabM.size && idx==-1) {
		/* Check if the mark is the same */
		if(tabM.table[i].subId==subjectId && tabM.table[i].stuId==studentId) {
			/* Add to the result table */
			idx = i;
		}
		i++;
	}
	
	return idx;
}

tError mrkTable_add(tMarkTable *tabM, tMark mark) {

	tError retVal = OK;
	int idx;
	idx=mrkTable_findMark(*tabM,mark.stuId,mark.subId);
	
	/* Add new mark to end of table if it doesnt exist */
	if(idx==-1) {
/******************** PR 3 - EX 4C ********************/
		/* Check if there enough space for the new mark */
		if(tabM->size>=MAX_STUDENTS) {
			retVal=ERR_MEMORY;
		}
		
		mark_cpy(&(tabM->table[tabM->size]), mark);	
		tabM->size++;
	} else {
	/* Modify mark with new value if it exists */
		tabM->table[idx].value = mark.value;
	}
	
	return retVal;
}

void mrkTable_del(tMarkTable *tabMrk, tMark mark) {
	
	unsigned int i;
	int idx;
	idx=mrkTable_findMark(*tabMrk,mark.stuId,mark.subId);
	
	/******************** PR 3 - EX 4D ********************/
	if(idx!=-1) {
		/* If the student is found, all the rest of the elements are displaced one position */
		for(i=idx+1; i<tabMrk->size; i++) {		
				mark_cpy(&(tabMrk->table[i-1]), tabMrk->table[i]);			
		}

		tabMrk->size=tabMrk->size-1;	

	}
}

tError mrkTable_save(tMarkTable tabM, const char* filename) {
	FILE *fout=0;
	unsigned int i;
	char str[MAX_LINE];
	tError retVal = OK;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))!=0) {

		/* Save all marks to the file */
		for(i=0;i<tabM.size;i++) {
			getMarkStr(tabM.table[i], MAX_LINE, str);
			fprintf(fout, "%s\n", str);
		}
		
		/* Close the file */
		fclose(fout);
	} else {
		retVal = ERR_CANNOT_WRITE;
	}
	
	return retVal;
}

tError mrkTable_load(tMarkTable *tabM, const char* filename) {
	
	tError retVal = OK;
	FILE *fin=0;	
	char line[MAX_LINE];
	tMark newMark;
	
	/* Initialize the output table */
	mrkTable_init(tabM);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))==0) {
		retVal = ERR_FILE_NOT_FOUND;
	} else {
	
		/* Read all the marks */
		while(!feof(fin) && tabM->size<MAX_STUDENTS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getMarkObject(line, &newMark);
				/* Add the new mark to the output table */
				mrkTable_add(tabM, newMark);		
			}
		}
		/* Close the file */
		fclose(fin);	
	}	
	
	return retVal;
}

/******************** PR 3 - EX 4E ********************/
/* Release a marks table */
void mrkTable_release(tMarkTable *tabM) {

}


void mrkTable_filterBySubject(tMarkTable tabM, unsigned int subjectId, tMarkTable *result) {
	unsigned int i;
		
	/* Initialize the result table */
	mrkTable_init(result);
	
	for(i=0; i< tabM.size; i++) {
		/* Check if the subject is the same */
		if(tabM.table[i].subId==subjectId) {
			/* Add to the result table */
			mrkTable_add(result, tabM.table[i]);
		}
	}
}

void mrkTable_filterByStudent(tMarkTable tabM, unsigned int studentId, tMarkTable *result) {
	unsigned int i;
		
	/* Initialize the result table */
	mrkTable_init(result);
	
	for(i=0; i< tabM.size; i++) {
		/* Check if the subject is the same */
		if(tabM.table[i].stuId==studentId) {
			/* Add to the result table */
			mrkTable_add(result, tabM.table[i]);
		}
	}
}
