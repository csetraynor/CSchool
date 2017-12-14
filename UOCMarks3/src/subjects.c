#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subjects.h"

void getSubjectStr(tSubject subject, int maxSize, char *str) {
	snprintf(str,maxSize-1,"%d;%s;%d;%s;", subject.id, subject.name, subject.credits, subject.desc);			
	str[maxSize-1]='\0';
}

tError getSubjectObject(const char *str, tSubject *subject) {
	int id, credits;
	char name[MAX_SUBJECT_NAME];
	char desc[MAX_DESC];
	
	sscanf(str, "%d;%[^;];%d;%[^;];", &id, name, &credits, desc);
	subject->id = id;
	strcpy(subject->name,name);
	subject->credits = credits;
	strcpy(subject->desc,desc);

	return OK;
}

int subject_cmp(tSubject s1, tSubject s2) {
	int ret = 0;
	
    if (s1.id > s2.id) {
        ret = 1;
	} else if (s1.id < s2.id) {
        ret = -1;
    } else {
		ret = strcmp(s1.name, s2.name);
    }
	
	return ret;
}

void subject_cpy(tSubject *dst, tSubject src) {

	dst->id = src.id; 
	strcpy(dst->name, src.name); 
	dst->credits = src.credits;
	strcpy(dst->desc, src.desc); 

}

void subTable_init(tSubjectTable *tabSub) {
	tabSub->size=0;
	/******************** PR 3 - EX 4B ********************/
    tabSub->table=NULL;
}

tError subTable_load(tSubjectTable *tabSub, const char* filename) {
	
	tError retVal = OK;
	FILE *fin=0;
	char line[MAX_LINE];
	tSubject newSubject;
	
	/* Initialize the output table */
	subTable_init(tabSub);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the subjects */
		while(!feof(fin) && tabSub->size<MAX_SUBJECTS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getSubjectObject(line, &newSubject);
				/* Add the new subject to the output table */
				subTable_add(tabSub, newSubject);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		retVal = ERR_FILE_NOT_FOUND;
	}
	

	return retVal;
}

tError subTable_save(tSubjectTable tabSub, const char* filename) {
	FILE *fout=0;
    tError retVal = OK;
	unsigned int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all subjects to the file */
        for(i=0;i<tabSub.size;i++) {
            getSubjectStr(tabSub.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}
    
	return retVal;
}

tError subTable_add(tSubjectTable *tabSub, tSubject subject) {

	tError retVal = OK;
	/******************** PR 3 - EX 4C ********************/

	/* Check if there enough space for the new subject */
	if(tabSub->table==NULL) {
		tabSub->table = (tSubject*) malloc (sizeof(tSubject));
	}else{
        tabSub->table = (tSubject*) realloc (tabSub, (tabSub->size+1)*sizeof(tSubject));
    }
    if(tabSub->table==NULL){
        retVal = ERR_MEMORY;
    }
	/* Add the new subject to the end of the table */
	subject_cpy(&tabSub->table[tabSub->size],subject);
	tabSub->size++;
	
	return retVal;
}

tError subTable_sortedAdd(tSubjectTable *tabSub, tSubject subject){
	tError retVal = OK;
	unsigned int i;
    int pos=-1;
	/******************** PR 3 - EX 4C ********************/

/******************** PR 3 - EX 4C ********************/

	/* Check if there enough space for the new subject */
	if(tabSub->table==NULL) {
		tabSub->table = (tSubject*) malloc (sizeof(tSubject));
	}else{
        tabSub->table = (tSubject*) realloc (tabSub, (tabSub->size+1)*sizeof(tSubject));
    }
    if(tabSub->table==NULL){
        retVal = ERR_MEMORY;
    }

        /* Add the new subject to the corresponding position of the table */
        i=0;
        while(i<tabSub->size && subject_cmp(tabSub->table[i],subject)<1){
            i++;
        }
        pos = i;
        /* Displace all elements to the right */
        i = tabSub->size;
        while(i>pos){
            subject_cpy(&tabSub->table[i],tabSub->table[i-1]);
            i--;
        }
        subject_cpy(&tabSub->table[pos],subject);
        tabSub->size++;
    
	return retVal;	
}

int subTable_find(tSubjectTable tabSub, unsigned int subjectId) {
	unsigned int i;
	int idx = -1;
	
	i=0;
	while(i< tabSub.size && idx==-1) {
		/* Check if the id is the same */
		if(tabSub.table[i].id==subjectId) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}


/******************** PR 2 - EX 2C ********************/
void subTable_del(tSubjectTable *tabSub, tSubject subject) {
	unsigned int i;
	tBoolean displace=FALSE;
	/******************** PR 3 - EX 4D ********************/

	/* If the student is found, all the rest of the elements are displaced one position */
		for(i=0;i<tabSub->size; i++){
            if(subject_cmp(tabSub->table[i], subject)){
                subject_cpy(&(tabSub->table[i]),tabSub->table[i-1]);
            }
        if(displace){
            tabSub->size--;
            if(tabSub->size==0){
                free(tabSub->table);
                tabSub->table=NULL;
            }else{
                tabSub->table=(tSubject*)realloc(tabSub->table, (tabSub->size+1)*sizeof(tSubject));
                }
            }
        }
}





/******************** PR 3 - EX 4E ********************/
/* Release a subjects table */
void subTable_release(tSubjectTable *table) {
    if(table->table != 0){
        free(table->table);
        table->table=NULL;
        table->size=0;
    }
}