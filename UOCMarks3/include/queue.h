#include "data.h"

/******************** PR 3 - EX 3A ********************/
typedef struct {
	tStudentRecord data[MAX_SUBJECTS];
    unsigned int nelem;
} tStuRecQueue;

/******************** PR 3 - EX 3B ********************/
void sr_init(tStuRecQueue *queue);

/******************** PR 3 - EX 3C ********************/
tBoolean srQueue_empty(tStuRecQueue *queue);

/******************** PR 3 - EX 3D ********************/
tError srQueue_enqueue(tStuRecQueue *queue, tStudentRecord newElement);

/******************** PR 3 - EX 3E ********************/
tError srQueue_dequeue (tStuRecQueue *queue, tStudentRecord *element);