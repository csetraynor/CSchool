#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "students.h"

int date_cmp(tDate d1, tDate d2) {
	int retVal=0;
	if(d1.year==d2.year) {
		if(d1.month==d2.month) {
			if(d1.day==d2.day) {
				retVal=0;
			} else {
				if(d1.day<d2.day) {
					retVal=-1;
				} else {
					retVal=1;
				}					
			}
		} else {
			if(d1.month<d2.month) {
				retVal=-1;
			} else {
				retVal=1;
			}		
		}		
	} else {
		if(d1.year<d2.year) {
			retVal=-1;
		} else {
			retVal=1;
		}		
	}
	return retVal;
}

void date_cpy(tDate *dst, tDate src){
	dst->day = src.day;
	dst->month = src.month;
	dst->year = src.year;
}

void getStudentStr(tStudent student, int maxSize, char *str) {
	snprintf(str,maxSize-1,"%d;%s;%s;%02d/%02d/%04d;%d;%d;", student.id, student.name, student.email, student.birthDate.day, student.birthDate.month, student.birthDate.year, student.sex, student.exchange);
	str[maxSize-1]='\0';
}

tError getStudentObject(const char *str, tStudent *student) {

	char tmpId[MAX_STUDENT_ID_STRING];
	char letter;
	int day, month, year, sex, exchange;
	tError retVal = OK;
	
	sscanf(str, "%[^;];%[^;];%[^;];%d/%d/%d;%d;%d;", tmpId, student->name, student->email, &day, &month, &year, &sex, &exchange);
	sscanf(tmpId,"%u%c",&(student->id),&letter);
	if(letter!=checkID[student->id % MODULE]) 
		retVal = ERR_INVALID_DATA;
		
	if(sex>1) {
		retVal = ERR_INVALID_DATA;		
	} else student->sex = (tSex)sex;
	
	if(exchange>1) {
		retVal = ERR_INVALID_DATA;		
	} else student->exchange = (tBoolean)exchange;
	
	if(day>31 || month>12) {
		retVal = ERR_INVALID_DATA;
	} else {
		student->birthDate.day = day;
		student->birthDate.month = month;
		student->birthDate.year = year;
	}

	return retVal;
}

void stuTable_init(tStudentTable *stuTable) {
	stuTable->size=0;
/******************** PR 3 - EX 4B ********************/
    stuTable->table=NULL;
}

tError stuTable_load(tStudentTable *stuTable, const char* filename) {
	FILE *fin=0;	
	char line[MAX_LINE];
	tStudent newStudent;
	
	/* Initialize the output table */
	stuTable_init(stuTable);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))==0) {
		return ERR_FILE_NOT_FOUND;
	}
	
	/* Read all the students */
	while(!feof(fin) && stuTable->size<MAX_STUDENTS) {
		/* Remove any content from the line */
		line[0] = '\0';
		/* Read one line and store it in "line" variable */
		fgets(line, MAX_LINE-1, fin);
		/* Ensure that the string is ended by 0*/
		line[MAX_LINE - 1]='\0';
		if(strlen(line)>0) {
			/* Obtain the object */
			getStudentObject(line, &newStudent);
			/* Add the new student to the output table */
			stuTable_add(stuTable, newStudent);		
		}
	}	
		
	/* Close the file */
	fclose(fin);
	
	return OK;
}

/******************** PR 2 - EX 1A ********************/
int student_cmp(tStudent s1, tStudent s2) {
	
	int retVal=0;
	
	retVal = strcmp(s1.name, s2.name);
	if(retVal==0) {
		/* If the names are equal, order by age */
		retVal=date_cmp(s2.birthDate, s1.birthDate);
		if(retVal==0) {
			/* If the dates are equal, order by ID */
			if (s1.id<s2.id) 
				retVal = -1;
			else if (s1.id>s2.id)
				retVal = 1;
			else retVal = 0;
		}
	}
	
	return retVal;
}

/******************** PR 2 - EX 1B ********************/
int student_cmpAge(tStudent s1, tStudent s2) {
	
	int retVal=0;
	
	retVal = date_cmp(s2.birthDate, s1.birthDate);
	if(retVal==0) {
		/* If the ages are equal, order by name */
		retVal=strcmp(s1.name, s2.name);
		if(retVal==0) {
			/* If the dates are equal, order by ID */
			if (s1.id<s2.id) 
				retVal = -1;
			else if (s1.id>s2.id)
				retVal = 1;
			else retVal = 0;
		}
	}
	
	return retVal;
}

/******************** PR 2 - EX 1C ********************/
void student_cpy(tStudent *dst, tStudent src) {
	dst->id = src.id; 
	strcpy(dst->name, src.name); 
	strcpy(dst->email, src.email); 
	date_cpy(&dst->birthDate,src.birthDate);
	dst->sex = src.sex;
	dst->exchange = src.exchange;
}

/******************** PR 2 - EX 2A ********************/
tError stuTable_add(tStudentTable *tabStu, tStudent student) {

    tError retVal;
    retVal = OK;
/******************** PR 3 - EX 4C ********************/
	/* Check if there enough space for the new student */
	if(tabStu->table==NULL) {
		tabStu->table=(tStudent*)malloc(sizeof(tStudent));
	}else{
        tabStu->table=(tStudent*)realloc(tabStu->table, (tabStu->size+1)*sizeof(tStudent));
    }
    if(tabStu->table==NULL){
        retVal =  ERR_MEMORY;
    }
	/* Add the new student to the end of the table */
	student_cpy(&(tabStu->table[tabStu->size]), student);	
	tabStu->size++;
    
	return retVal;
}


/******************** PR 2 - EX 2B ********************/
int stuTable_find(tStudentTable tabStu, unsigned int studentId) {
	unsigned int i;
	int idx = -1;
	
	i=0;
	while(i< tabStu.size && idx==-1) {
		/* Check if the id is the same */
		if(tabStu.table[i].id==studentId) {
			/* Get the position of the match */
			idx = i;
		}
		i++;
	}
	
	return idx;
}

/******************** PR 2 - EX 2C ********************/
void stuTable_del(tStudentTable *tabStu, tStudent student) {
	unsigned int i;
	tBoolean displace=FALSE;
	/******************** PR 3 - EX 4D ********************/

	/* If the student is found, all the rest of the elements are displaced one position */
		for(i=0;i<tabStu->size; i++){
            if(student_cmp(tabStu->table[i], student)){
                student_cpy(&(tabStu->table[i]),tabStu->table[i+1]);
            }
        if(displace){
            tabStu->size--;
            if(tabStu->size==0){
                free(tabStu->table);
                tabStu->table=NULL;
            }else{
                tabStu->table=(tStudent*)realloc(tabStu->table, (tabStu->size+1)*sizeof(tStudent));
            }
        }
        }
}

/******************** PR 2 - EX 3 ********************/
tError stuTable_save(tStudentTable tabStu, const char* filename) {
	FILE *fout=0;
	unsigned int i;
	char str[MAX_LINE];
	tError retVal = OK;
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))!=0) {

		/* Save all students to the file */
		for(i=0;i<tabStu.size;i++) {
			getStudentStr(tabStu.table[i], MAX_LINE, str);
			fprintf(fout, "%s\n", str);
		}
		
		/* Close the file */
		fclose(fout);
		retVal = OK;
	} else {
		retVal = ERR_CANNOT_WRITE;
	}
	
	return retVal;
}

/******************** PR 2 - EX4 ********************/
void stuTable_findByBirthYear(tStudentTable tabStu, unsigned int year, tStudentTable *result) {
	unsigned int i;
	
	stuTable_init(result);
	i=0;
	while(i< tabStu.size) {
		/* Check if the year is the same */
		if(tabStu.table[i].birthDate.year==year) {
			/* Add to the result table */
			stuTable_add(result,tabStu.table[i]);
		}
		i++;
	}
}

/******************** PR 2 - EX5 ********************/
int stuTable_getFemaleNumber(tStudentTable tabStu){
	unsigned int i;
	int numFemale=0;
	
	i=0;
	while(i< tabStu.size) {
		/* Check if the student is a female */
		if(tabStu.table[i].sex==FEMALE) {
			/* Add a unit to the total */
			numFemale++;
		}
		i++;
	}
	
	return numFemale;
}

/******************** PR 2 - EX6 ********************/
tError stuTable_sortedAdd(tStudentTable *tabStu, tStudent student){
	tError retVal = OK;
	unsigned int i;
	int pos=-1;
	/******************** PR 3 - EX 4C ********************/
	/* Check if there enough space for the new subject */
	/* Check if there enough space for the new student */
	if(tabStu->table==NULL) {
		tabStu->table=(tStudent*)malloc(sizeof(tStudent));
	}else{
        tabStu->table=(tStudent*)realloc(tabStu->table, (tabStu->size+1)*sizeof(tStudent));
    }
    if(tabStu->table==NULL){
        retVal =  ERR_MEMORY;
    }

        /* Add the new student to the corresponding position of the table */
        i=0;
        while(i<tabStu->size && student_cmpAge(tabStu->table[i],student)<1){
            i++;
        }
        pos = i;
        /* Displace all elements to the right */
        i = tabStu->size;
        while(i>pos){
            student_cpy(&tabStu->table[i],tabStu->table[i-1]);
            i--;
        }
        student_cpy(&tabStu->table[pos],student);
        tabStu->size++;

    
	return retVal;	
}

/******************** PR 2 - EX6 ********************/
void stuTable_sortByAge(tStudentTable tabStu, tStudentTable *result){

	unsigned int i;

	stuTable_init(result);
	for(i=0;i<tabStu.size;i++){
		/* Add (sorted) the each student to the result table */
		stuTable_sortedAdd(result, tabStu.table[i]);
	}
}

/******************** PR 3 - EX 4E ********************/
/* Release a students table */
void stuTable_release(tStudentTable *tabStu) {
    if(tabStu->table!=0){
        free(tabStu->table);
        tabStu->table=NULL;
        tabStu->size=0;
    }

}