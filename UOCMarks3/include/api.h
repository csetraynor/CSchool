#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
tError appData_load(tAppData *object);

/* Save the application data to a file */
tError appData_save(tAppData object);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the students */
tError getStudents(tAppData object, tStudentTable *result);

/* Get the subject information */
tError getStudent(tAppData object, int studentID, tStudent *student);

/* Add a new student */
tError addStudent(tAppData *object, tStudent student);

/* Remove a certain student */
tError removeStudent(tAppData *object, tStudent student);

/* Return the table of subjects */
tError getSubjects(tAppData object, tSubjectTable *result);

/* Get the subject information */
tError getSubject(tAppData object, int subjectID, tSubject *subject);

/* Add a new subject */
tError addSubject(tAppData *object, tSubject subject);

/* Return a table with the marks */
tError getMarks(tAppData object, tMarkTable *result);

/* Get the mark information */
tError getMark(tAppData object, int stuId, int subId, tMark *mark);

/* Add a new mark */
tError addMark(tAppData *object, tMark mark);

/* Remove a certain mark */
tError removeMark(tAppData *object, tMark mark);
