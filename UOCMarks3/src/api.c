#include <stdio.h>
#include <math.h>
#include <string.h>
#include "api.h"
#include "students.h"
#include "subjects.h"
#include "marks.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the students table */
	stuTable_init(&(object->students));
	
	/* Initialize the subjects table */
	subTable_init(&(object->subjects));

	/* Initialize the marks table */
	mrkTable_init(&(object->marks));
}

tError appData_load(tAppData *object) {
	char path[MAX_LINE];
	tError retVal = OK;
		
	/* Load the table of subjects */
	sprintf(path,"%ssubjects.txt", object->path);
	retVal=subTable_load(&(object->subjects), path);
	if(retVal!=OK) {
		printf("ERROR: Error reading the file of subjects\n");
	}

	/* Load the table of students */
	sprintf(path,"%sstudents.txt", object->path);
	retVal=stuTable_load(&(object->students), path);
	if(retVal!=OK) {
		printf("ERROR: Error reading the file of students\n");
	}
	
	return retVal;
}

tError appData_save(tAppData object)  {
	char path[MAX_LINE];
	tError retVal = OK;
	
	/* Save the table of subjects */
	sprintf(path,"%ssubjects.txt", object.path);
	retVal=subTable_save(object.subjects, path);
	if(retVal!=OK) {
		printf("ERROR: Error saving the file of subjects\n");
	}
	
	/* Save the table of students */
	sprintf(path,"%sstudents.txt", object.path);
	retVal=stuTable_save(object.students, path);
	if(retVal!=OK) {
		printf("ERROR: Error saving the file of students\n");
	}
	
	return retVal;
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/
tError getSubjects(tAppData object, tSubjectTable *result) {
	tError retVal = OK;
	*result = object.subjects;	
	return retVal;
}

tError getSubject(tAppData object, int subjectID, tSubject *subject) {
	
	tError retVal = OK;
	tBoolean found;
	unsigned int i;
	
	found = FALSE;
	/* Check if there is another subject with this ID */
	for(i=0; i<object.subjects.size; i++) {
		if(object.subjects.table[i].id==subjectID) {
			subject_cpy(subject,object.subjects.table[i]);
		}
	}
	if (!found) retVal = ERR_ENTRY_NOT_FOUND;
	
	return retVal;
}

tError addSubject(tAppData *object, tSubject subject) {
	tError retVal = OK;
	tSubject tmp;
	
	/* Check if there is another subject with this ID */
	if(getSubject(*object, subject.id, &tmp)==OK) {
		retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new subject using the subject table method */
		retVal =subTable_add(&(object->subjects), subject);
	}
	return retVal;
}

tError getStudents(tAppData object, tStudentTable *result) {
	tError retVal = OK;
	*result = object.students;	
	return retVal;
}

tError getStudent(tAppData object, int studentId, tStudent *student) {
	
	int i;
	tError retVal = OK;
	
	/* Check if there is a student with this ID */
	i = stuTable_find(object.students, studentId);
	if (i!=-1) {
		student_cpy(student,object.students.table[i]);
	} else {
		retVal = ERR_ENTRY_NOT_FOUND;
	}
	
	return retVal;
}


tError addStudent(tAppData *object, tStudent student) {
	tError retVal = OK;
	tStudent tmp;
	
	/* Check if there is another student with this ID */
	if(getStudent(*object, student.id, &tmp) == OK) {
		retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new student using the student table method */
		retVal=stuTable_add(&(object->students), student);	
	}
	
	return retVal;
}

tError removeStudent(tAppData *object, tStudent student) {
	/* Call the method from the student table*/
	stuTable_del(&(object->students), student);
	return OK;
}

tError getMarks(tAppData object, tMarkTable *result) {
	/* Call the method from the marks table*/
	*result = object.marks;	
	return OK;
}

tError getMark(tAppData object, int studentId, int subjectId, tMark *mark) {
	
	unsigned int i;
	tBoolean found;
	tError retVal = OK;
	
	found = FALSE;
	/* Check if there is another subject with this ID */
	for(i=0; i<object.marks.size; i++) {
		if(object.marks.table[i].stuId==studentId && object.marks.table[i].subId==subjectId) {
			mark_cpy(mark, object.marks.table[i]);
		}
	}
	if (!found) retVal = ERR_ENTRY_NOT_FOUND;
	
	return retVal;
}


tError addMark(tAppData *object, tMark mark) {
	tError retVal = OK;
	tMark tmp;
	
	/* Check if there is another student with this ID */
	if(getMark(*object, mark.stuId, mark.subId, &tmp) == OK) {
		retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new student using the student table method */
		retVal=mrkTable_add(&(object->marks), mark);	
	}
	
	return retVal;
}

tError removeMark(tAppData *object, tMark mark) {
	/* Call the method from the student table*/
	mrkTable_del(&(object->marks), mark);
	return OK;
}


/******************** PR 3 - EX 4F ********************/
/* Release the allocated memory */
void appData_release (tAppData *object) {
#ifdef COMPLETE_VERSION
	subTable_release(&(object->subjects));
	stuTable_release(&(object->students));
#endif	
}