#include "queue.h"

/******************** PR 3 - EX 3B ********************/
void sr_init(tStuRecQueue *queue) {
	queue->nelem=0;
}

/******************** PR 3 - EX 3C ********************/
tBoolean srQueue_empty(tStuRecQueue *queue) {	
	return (queue->nelem==0);
}

/******************** PR 3 - EX 3D ********************/
tError srQueue_enqueue(tStuRecQueue *queue, tStudentRecord newElement) {
	tError retVal = OK;
    if(queue->nelem==MAX_SUBJECTS) {
        return ERR_MEMORY;
    }else{
        queue->data[queue->nelem]=newElement;
        queue->nelem++;
    }
	
	return retVal;
}

/******************** PR 3 - EX 3E ********************/
tError srQueue_dequeue (tStuRecQueue *queue, tStudentRecord *element) {
    tError retVal = OK;
    
    unsigned int i=0;
    
    if(queue->nelem==0){
        retVal = ERROR; 
    } else {
        *element=queue->data[i];
        for(i=0;i<queue->nelem-1; i++) {
            queue->data[i]=queue->data[i+1];
        }
        queue->nelem--;
    }
	return retVal;
}
