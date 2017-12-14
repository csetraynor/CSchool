#include <stdio.h>
#include <math.h>
#include <string.h>
#include "marks.h"
#include "record.h"
#include "students.h"
#include "subjects.h"

/******************** PR 3 - EX 2A ********************/
tError sr_getStudentRecord(tMarkTable tabM, tSubjectTable tabSub, unsigned int stuId, tStudentRecord *sr ){
    unsigned int i, a;
    unsigned int numSubjects=0;
	tError retVal = OK;
    tBoolean found =FALSE;
    sr->id = stuId;
    sr->numSubjects=0;
    sr->totCredits=0;
    
    for(i=0; i<tabM.size; i++){
        if(tabM.table[i].stuId == stuId){
            mark_cpy(&(sr->tabM.table[sr->tabM.size]), tabM.table[i]);
            while(a<tabSub.size && found==FALSE){
                if(tabSub.table[a].id==tabM.table[i].subId){
                    sr->tabS[numSubjects]=&(tabSub.table[i]);
                    found=TRUE;
                }
                sr->totCredits += tabSub.table[a].credits;
                sr->avgMark += (float)tabM.table[i].value/(float)tabSub.table[a].credits;
                numSubjects++; 
                a++;
            }
        }
    }
    sr->avgMark = sr->avgMark/ (float) numSubjects;

    sr->tabS[numSubjects]=NULL;
    
    if(numSubjects==0){
        retVal =ERR_ENTRY_NOT_FOUND;
    }

	return retVal;
}

/******************** PR 3 - EX 2B ********************/
tBoolean sr_equals(tStudentRecord sr1, tStudentRecord sr2){
	
	tBoolean retVal=TRUE;
	if ((sr1.id != sr2.id) || (sr1.numSubjects != sr2.numSubjects) || (sr1.totCredits != sr2.totCredits) || sr1.avgMark != sr2.avgMark){
        retVal=FALSE;
    }
    unsigned int i=0;
    while(sr1.tabS!=NULL) {
        if(sr1.tabS!=sr2.tabS){
            retVal = FALSE;
        }
        i++;
    }

	return retVal;
}