#include <stdio.h>
#include <string.h>
#include "movements.h"

tBoolean date_null(tDate date) {
	return (tBoolean)(date.day==0 && date.month==0 && date.year==0);
}

tDate date_add(tDate date, unsigned int months) {
	tDate retVal;
	
	retVal.day=date.day;
	retVal.month=date.month+(months%12);
	retVal.year=date.year+(months/12);
	
	return retVal;
}

int date_cmp(tDate d1, tDate d2) {
	int retVal=0;
	if(d1.year==d2.year) {
		if(d1.month==d2.month) {
			if(d1.day==d2.day) {
				/* d1 == d2 */
				retVal=0;
			} else {
				if(d1.day<d2.day) {
					/* d1 < d2 */
					retVal=-1;
				} else {
					/* d1 > d2 */
					retVal=1;
				}					
			}
		} else {
			if(d1.month<d2.month) {
				/* d1 < d2 */
				retVal=-1;
			} else {
				/* d1 > d2 */
				retVal=1;
			}		
		}		
	} else {
		if(d1.year<d2.year) {
			/* d1 < d2 */
			retVal=-1;
		} else {
			/* d1 > d2 */
			retVal=1;
		}		
	}
	return retVal;
}

tBoolean date_between(tDate date, tDate startDate, tDate endDate) {
	tBoolean retVal;
	
	/* Check the start date */
	if(date_null(startDate)) {
		retVal=TRUE;
	} else {
		if(date_cmp(startDate, date)<=0) {
			retVal=TRUE;
		} else {
			retVal=FALSE;
		}
	}
	
	/* Check the end date (only if date is after startDate */
	if(retVal==TRUE) {
		if(date_null(endDate)) {
			retVal=TRUE;
		} else {
			if(date_cmp(endDate, date)>=0) {
				retVal=TRUE;
			} else {
				retVal=FALSE;
			}
		}
	}
		
	return retVal;
}

void getMovementStr(tMovement movement, int maxSize, char *str) {
	snprintf(str,maxSize-1,"%u;%s;%f;%u;%02d/%02d/%04d;%02d/%02d/%04d;%u;", (unsigned int)movement.type, movement.description, movement.amount, (unsigned int)movement.isPeriodic, 
		movement.date.day, movement.date.month, movement.date.year, movement.endDate.day, movement.endDate.month, movement.endDate.year, (unsigned int)movement.conceptID);			
	str[maxSize-1]='\0';
}

tError getMovementObject(const char *str, tMovement *movement) {
	unsigned int tmpMovType;	
	unsigned int tmpMovIsPeriodic;	
	unsigned int tmpMovConceptID;
	unsigned int day1,month1,year1,day2,month2,year2;
	sscanf(str, "%u;%[^;];%f;%u;%u/%u/%u;%u/%u/%u;%u;", &tmpMovType, movement->description, &(movement->amount), &tmpMovIsPeriodic, &day1, &month1, &year1, &day2, &month2, &year2, &tmpMovConceptID);

	if(tmpMovConceptID<0) {
		return ERR_INVALID_DATA;
	}
	if(tmpMovIsPeriodic<0 || tmpMovIsPeriodic>1) {
		return ERR_INVALID_DATA;		
	}
	
	if(!(day1==0 && month1==0 && year1==0) && (day1<1 || month1<1 || year1<1)) {
		return ERR_INVALID_DATA;
	}
	
	if(!(day2==0 && month2==0 && year2==0) && (day2<1 || month2<1 || year2<1)) {
		return ERR_INVALID_DATA;
	}
	
	if(day1>31 || month1>12 || day2>31 || month2>12) {
		return ERR_INVALID_DATA;
	}
	
	movement->date.day=(unsigned char)day1;
	movement->date.month=(unsigned char)month1;
	movement->date.year=(unsigned short)year1;
	movement->endDate.day=(unsigned char)day2;
	movement->endDate.month=(unsigned char)month2;
	movement->endDate.year=(unsigned short)year2;	
	movement->type=(tMovementType)tmpMovType;
	movement->isPeriodic=(tBoolean)tmpMovIsPeriodic;
	movement->conceptID=(unsigned char)tmpMovConceptID;

	return OK;
}

void getGenMovements(tMovement movement, tDate startDate, tDate endDate, tMovementTable *result) {
	tDate date;
	tMovement newMovement;
	
	/* Initialize the result table */
	movTable_init(result);
	
	/* If the movement is not periodic, use the date */
	if(movement.isPeriodic==FALSE) {
		if(date_between(movement.date, startDate, endDate)) {
			/* Add to the result table */
			movTable_add(result, movement);
		}
	} else {
		/* Put the dates of the movement according to the time period */
		
		/* Start date */		
		if(date_null(startDate)==FALSE) {			
			if(date_cmp(startDate, movement.date)>0) {
				movement.date.year=startDate.year;
				if(startDate.day>movement.date.day) {
					movement.date.month++;
				}
			}
		}
		
		/* End date */
		if(!date_null(endDate)) {			
			if(date_null(movement.endDate)) {
				movement.endDate=endDate;				
			} else {			
				/* Get the minimum date*/
				if(date_cmp(movement.endDate, endDate)>0) {
					movement.endDate=endDate;
				}
			}			
		}
		
		/* Make a copy of the movement */
		movement_cpy(&newMovement, movement);
		
		/* Convert to a non periodic movement */
		newMovement.isPeriodic=FALSE;
		newMovement.endDate.day=0;
		newMovement.endDate.month=0;
		newMovement.endDate.year=0;		
		
		/* Generate the movements */
		date=movement.date;
		while((date_cmp(date, movement.endDate)<=0 || date_null(movement.endDate)) && result->size<MAX_MOVEMENTS) {
			/* Set the new date */
			newMovement.date=date;
			
			/* Add to the result table */
			movTable_add(result, newMovement);
			
			/* Move one month */
			date=date_add(date, 1);
		}
	}
}

/* EXERCICES */
void movTable_init(tMovementTable *table) {
	table->size=0;
}

tError movTable_load(tMovementTable *table, const char* filename) {
	FILE *fin=0;	
	char line[512];
	tMovement newMovement;
	
	/* Initialize the output table */
	movTable_init(table);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))==0) {
		return ERR_FILE_NOT_FOUND;
	}
	
	/* Read all the movements */
	while(!feof(fin) && table->size<MAX_MOVEMENTS) {
		/* Remove any content from the line */
		line[0] = '\0';
		/* Read one line (maximum 255 chars) and store it in "line" variable */
		fgets(line, 512, fin);
		/* Ensure that the string is ended by 0*/
		line[511]='\0';
		if(strlen(line)>0) {
			/* Obtain the object */
			getMovementObject(line, &newMovement);
			/* Add the new movement to the output table */
			movTable_add(table, newMovement);		
		}
	}	
		
	/* Close the file */
	fclose(fin);
	
	return OK;
}

tError movTable_save(tMovementTable table, const char* filename) {
	FILE *fout=0;
	unsigned int i;
	char str[512];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		return ERR_CANNOT_WRITE;
	}
	
	/* Save all movements to the file */
	for(i=0;i<table.size;i++) {
		getMovementStr(table.table[i], 512, str);
		fprintf(fout, "%s\n", str);
	}
	
	/* Close the file */
	fclose(fout);
	
	return OK;
}

tError movTable_add(tMovementTable *table, tMovement movement) {
	/* Check if there enough space for the new movement */
	if(table->size>=MAX_MOVEMENTS) {
		return ERR_MEMORY;
	}
	
	/* Add the new movement to the end of the table */
	movement_cpy(&(table->table[table->size]), movement);	
	table->size++;
	
	return OK;
}

void movTable_del(tMovementTable *table, tMovement movement) {
	unsigned int i;
	tBoolean displace=FALSE;
	
	/* If the movement is found, all the rest of the elements are displaced one position */
	for(i=0; i<table->size; i++) {		
		if(movement_cmp(table->table[i], movement)==0) {						
			displace=TRUE;
		}
		if(displace) {	
			movement_cpy(&(table->table[i]), table->table[i+1]);			
		}
	}
	if(displace) {
		table->size=table->size-1;			
	}
}

int movement_cmp(tMovement m1, tMovement m2) {
	int retVal=0;
	if(date_cmp(m1.date, m2.date)!=0) {
		/* If the dates are different, sort by date */
		retVal=date_cmp(m1.date, m2.date);
	} else {
		/* If the concepts are different, order by concept */
		if(m1.conceptID!=m2.conceptID) {
			if(m1.conceptID<m2.conceptID) {
				retVal=-1;
			} else {
				retVal=1;
			}
		} else {			
			if(m1.type!=m2.type) {
				/* If the types are different, order by type */
				if(m1.type<m2.type) {
					retVal=-1;
				} else {
					retVal=1;
				}
			} else {				
				if(m1.isPeriodic!=m2.isPeriodic) {
					/* If the description are different, order by description */
					if(m1.isPeriodic<m2.isPeriodic) {
						retVal=-1;
					} else {
						retVal=1;
					}
				} else {					
					if(strcmp(m1.description, m2.description)!=0) {
						/* If the description are different, order by description */
						retVal=strcmp(m1.description, m2.description);
					} else {						
						if(m1.amount!=m2.amount) {
							/* If the amounts are different, order by amount */
							if(m1.amount<m2.amount) {
								retVal=-1;
							} else {
								retVal=1;
							}
						} else {							
							if(date_cmp(m1.endDate, m2.endDate)!=0) {
								/* If the endDates are different, order by endDate */
								retVal=date_cmp(m1.endDate, m2.endDate);
							} else {
								/* The two moviments are identics */
								retVal=0;
							}
						}
					}					
				}
			}			
		}
		 
	}
	
	return retVal;
}

void movement_cpy(tMovement *dst, tMovement src) {
	dst->type=src.type;	
	strcpy(dst->description, src.description); 
	dst->amount=src.amount;
	dst->isPeriodic=src.isPeriodic;	
	dst->date=src.date; 
	dst->endDate=src.endDate;
	dst->conceptID=src.conceptID;
}

void movTable_find(tMovementTable table, tDate startDate, tDate endDate, tMovementTable *result) {
	unsigned int i;
		
	/* Initialize the result table */
	movTable_init(result);
	
	for(i=0; i< table.size; i++) {
		/* Check if the date is between the two given dates */
		if(date_between(table.table[i].date, startDate, endDate)) {
			/* Add to the result table */
			movTable_add(result, table.table[i]);
		}
	}
}

void movTable_findByConcept(tMovementTable table, unsigned int conceptID, tMovementTable *result) {
	unsigned int i;
		
	/* Initialize the result table */
	movTable_init(result);
	
	for(i=0; i< table.size; i++) {
		/* Check if the concept is the same */
		if(table.table[i].conceptID==conceptID) {
			/* Add to the result table */
			movTable_add(result, table.table[i]);
		}
	}
}

float getMovementsAmount(tMovementTable table) {
	float finalAmount=0;
	unsigned int i=0;
	
	for(i=0; i<table.size; i++) {
		if(table.table[i].type==INCOME) {
			finalAmount+=table.table[i].amount;
		} else {
			finalAmount-=table.table[i].amount;
		}
	}
	
	return finalAmount;
}