#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "record.h"
#include "subjects.h"
#include "students.h"
#include "marks.h"
#include "queue.h"
#define STUDENT1 "11111111H;González González, Fran;frgo@gmail.com;01/01/1990;0;0;"
#define STUDENT2 "12345678Z;García García, Rosa;roga@gmail.com;01/01/1991;1;0;"
#define STUDENT3 "87654321X;Pérez Pérez, Alba;alpe@gmail.com;01/01/1990;1;0;"

void runTests() {	
	int passedTestPR2, passedTestPR3;
	int totalTestPR2, totalTestPR3;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 2 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR2(&totalTestPR2, &passedTestPR2);

	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 3 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR3(&totalTestPR3, &passedTestPR3);
		
	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR2: Passed %d of %d [%0.2f%%]\n", passedTestPR2, totalTestPR2, (float)passedTestPR2/totalTestPR2*100.0);
	printf("\tPR3: Passed %d of %d [%0.2f%%]\n", passedTestPR3, totalTestPR3, (float)passedTestPR3/totalTestPR3*100.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR2+passedTestPR3, totalTestPR2+totalTestPR3, (float)(passedTestPR2+passedTestPR3)/(totalTestPR2+totalTestPR3)*100.0);
	printf("===================================\n");		
}


void runTestsPR2(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	test_cmp_cpy(totalTest, passedTest);
	test_stu_tab(totalTest, passedTest);	
	test_persistence(totalTest, passedTest);
	test_search(totalTest, passedTest);
	test_count(totalTest, passedTest);
	test_sort(totalTest, passedTest);
	
/*	test_api(totalTest, passedTest);
	test_subjects(totalTest, passedTest);*/
}

void runTestsPR3(int *totalTest, int *passedTest) {	
	*totalTest=0;
	*passedTest=0;	
	
	test_stuRecord(totalTest, passedTest);
	test_queue(totalTest, passedTest);
}

void test_subjects(int *totalTest, int *passedTest) {
	tSubjectTable subjects;		
	tSubject subject1, subject2, subject3;
	tError retVal = OK;
	unsigned int i;
	
	printf("=================================================\n");
	printf(" Subjects\n");
	printf("=================================================\n");
	
	/* Test 1:Initialize the table */
	printf("\nTest1: Initialize the table:");
	(*totalTest)++;
	subTable_init(&subjects);	
	if(subjects.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	/* Test 2: Add a subject */
	printf("\nTest2: Add a subject:");
	(*totalTest)++;
	subTable_init(&subjects);
	getSubjectObject("13243;test subject;4;test desc;", &subject1);	
	retVal=subTable_add(&subjects, subject1);
	if(retVal!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addSubject. Expected %d and returned %d)\n", OK, retVal);
	} else {		
		if(subjects.size==1) {
			if(subject_cmp((subjects.table[0]), subject1)==0) {
				printf("\n\t-> OK\n");			
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", subjects.size);
		}
	}	
	
	/* Test3: Pass the maximum capacity of the table */
	printf("\nTest3: Pass the maximum capacity of the table:");
	(*totalTest)++;
	subTable_init(&subjects);
	for(i=0;i<=MAX_SUBJECTS;i++) {
		subject1.id = i;
		sprintf(subject1.name, "Test subject %d", i);
		subject1.credits = 5;
		sprintf(subject1.desc, "Test subject %d", i);
		retVal=subTable_add(&subjects, subject1);
		if(i<MAX_SUBJECTS) {
			if(retVal!=OK) {				
				printf("\n\t-> FAIL (unexpected return value from addSubject adding object %d of %d. Expected %d and returned %d)\n", i+1, MAX_SUBJECTS, OK, retVal);
				break;
			}
		} else {
			if(retVal==ERR_MEMORY) {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (unexpected return value from addSubject adding last object. Expected %d and returned %d)\n", ERR_MEMORY, retVal);
			} 
		}
	}		
	
	/* Test4: Delete a subject from an empty table */
	printf("\nTest4: Delete a subject from an empty table:");
	(*totalTest)++;
	subTable_init(&subjects);	
	getSubjectObject("SUB0;test subject 0;6;desc;", &subject1);
	subTable_del(&subjects, subject1);	
	if(subjects.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, subjects.size);
	}	
	
	/* Test5: Delete the first subject of a table */
	printf("\nTest5: Delete the first subject of a table:");
	(*totalTest)++;
	subTable_init(&subjects);	
	getSubjectObject("SUB0;test subject 0;6;desc 0;", &subject1);	
	subTable_add(&subjects, subject1);
	getSubjectObject("SUB2;test subject 2;6;desc 1;", &subject2);	
	subTable_add(&subjects, subject2);
	getSubjectObject("SUB1;test subject 1;6;desc 2;", &subject3);	
	subTable_add(&subjects, subject3);
		
	subTable_del(&subjects, subject1);
	
	if(subjects.size==2) {
		if(subject_cmp(subjects.table[0], subject2)!=0 || subject_cmp(subjects.table[1], subject3)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, subjects.size);
	}
	
	/* Test6: Delete the last subject of a table */
	printf("\nTest6: Delete the last subject of a table:");
	(*totalTest)++;
	subTable_init(&subjects);	
	getSubjectObject("10000;test subject 0;4;desc 0;", &subject1);	
	subTable_add(&subjects, subject1);
	getSubjectObject("10002;test subject 2;5;desc 2;", &subject2);	
	subTable_add(&subjects, subject2);
	getSubjectObject("10001;test subject 1;6;desc 1;", &subject3);	
	subTable_add(&subjects, subject3);
		
	subTable_del(&subjects, subject3);
	
	if(subjects.size==2) {
		if(subject_cmp(subjects.table[0], subject1)!=0 || subject_cmp(subjects.table[1], subject2)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, subjects.size);
	}
	
	/* Test7: Delete in middle subject of a table */
	printf("\nTest7: Delete subject in middle of a table:");
	(*totalTest)++;
	subTable_init(&subjects);	
	getSubjectObject("10000;test subject 0;4;desc 0;", &subject1);	
	subTable_add(&subjects, subject1);
	getSubjectObject("10002;test subject 2;5;desc 2;", &subject2);	
	subTable_add(&subjects, subject2);
	getSubjectObject("10001;test subject 1;6;desc 1;", &subject3);	
	subTable_add(&subjects, subject3);
		
	subTable_del(&subjects, subject2);
	
	if(subjects.size==2) {
		if(subject_cmp(subjects.table[0], subject1)!=0 || subject_cmp(subjects.table[1], subject3)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, subjects.size);
	}
	
	/* Test8: Delete a non existing subject */
	printf("\nTest8: Delete a non existing subject:");
	(*totalTest)++;
	subTable_init(&subjects);	
	getSubjectObject("10000;test subject 0;4;desc 0;", &subject1);	
	subTable_add(&subjects, subject1);
	getSubjectObject("10002;test subject 2;5;desc 2;", &subject2);	
	subTable_add(&subjects, subject2);
	getSubjectObject("10001;test subject 1;6;desc 1;", &subject3);		
		
	subTable_del(&subjects, subject3);
	
	if(subjects.size==2) {
		if(subject_cmp(subjects.table[0], subject1)!=0 || subject_cmp(subjects.table[1], subject2)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, subjects.size);
	}	
	
	return;
}

void test_cmp_cpy(int *totalTest, int *passedTest) {	
	tStudent student1, student2;	
		
	printf("=================================================\n");
	printf(" STUDENTS COMPARISON & COPY\n");
	printf("=================================================\n");
	
	printf("\nTest 1a: Compare names:");
	(*totalTest)++;
	getStudentObject(STUDENT1, &student1);	
	getStudentObject(STUDENT2, &student2);	
	if( ( student_cmp(student1, student2) > 0 ) && ( student_cmp(student2,student1) < 0) ){
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1b: Compare ages:");
	(*totalTest)++;
	getStudentObject(STUDENT1, &student1);	
	getStudentObject(STUDENT2, &student2);	
	if( ( student_cmpAge(student1, student2) > 0 ) && ( student_cmpAge(student2,student1) < 0) ) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 1c: Copy student:");
	(*totalTest)++;
	getStudentObject(STUDENT1, &student1);	
	student_cpy(&student2,student1);	
	if( student_cmp(student1, student2) == 0 ) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
}	

void test_stu_tab(int *totalTest, int *passedTest) {	
	tStudentTable students;
	tStudent student1, student2, student3;	
	tError retVal = OK;
	unsigned int i;
		
	printf("=================================================\n");
	printf(" STUDENTS TABLE MANAGEMENT\n");
	printf("=================================================\n");
	
	printf("\nTest 2a1: Initialize the table:");
	(*totalTest)++;
	stuTable_init(&students);
	if(students.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 2a2: Add a student:");
	(*totalTest)++;
	stuTable_init(&students);	
	getStudentObject(STUDENT1, &student1);	
	retVal=stuTable_add(&students, student1);
	if(retVal!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addSubject. Expected %d and returned %d)\n", OK, retVal);
	} else {		
		if(students.size==1) {
			if(student_cmp(students.table[0], student1)==0) {
				printf("\n\t-> OK\n");			
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", students.size);
		}
	}	
			
	printf("\nTest 2a3: Pass the maximum capacity of the table:");
	(*totalTest)++;
	stuTable_init(&students);	
	for(i=0;i<=MAX_STUDENTS;i++) {
		getStudentObject(STUDENT1, &student1);
		student1.id = i;
		retVal=stuTable_add(&students, student1);
		if(i<MAX_STUDENTS) {
			if(retVal!=OK) {				
				printf("\n\t-> FAIL (unexpected return value from addStudent adding object %d of %d. Expected %d and returned %d)\n", i+1, MAX_STUDENTS, OK, retVal);
				break;
			}
		} else {
			if(retVal==ERR_MEMORY) {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (unexpected return value from addStudent adding last object. Expected %d and returned %d)\n", ERR_MEMORY, retVal);
			} 
		}
	}		
	
	printf("\nTest 2b: Search a student with a given ID");
	(*totalTest)++;
	i = stuTable_find(students, MAX_STUDENTS - 1);
	if( i == MAX_STUDENTS - 1 ) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected index returned. Expected %d and returned %d)\n", MAX_STUDENTS - 1, i);
	}	

	
	printf("\nTest 2c1: Delete a student from an empty table:");
	(*totalTest)++;
	stuTable_init(&students);
	getStudentObject(STUDENT1, &student1);	
	stuTable_del(&students, student1);
	if(students.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, students.size);
	}	
	
	printf("\nTest 2c2: Delete the first student of a table:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);
	
	stuTable_del(&students,student1);
	if(students.size==2) {
		if(student_cmp(students.table[0], student2)!=0 || student_cmp(students.table[1], student3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
	
	printf("\nTest 2c3: Delete the last student of a table:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);
	
	stuTable_del(&students,student3);
	if(students.size==2) {
		if(student_cmp(students.table[0], student1)!=0 || student_cmp(students.table[1], student2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
	
	printf("\nTest 2c4: Delete student in middle of a table:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);
	
	stuTable_del(&students,student2);
	if(students.size==2) {
		if(student_cmp(students.table[0], student1)!=0 || student_cmp(students.table[1], student3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
	
	printf("\nTest 2c5: Delete a non existing student:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);

	stuTable_del(&students,student3);
	if(students.size==2) {
		if(student_cmp(students.table[0], student1)!=0 || student_cmp(students.table[1], student2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
	
}

void test_persistence(int *totalTest, int *passedTest) {
	tStudentTable students;
	tStudent student1, student2, student3;
	
	printf("=================================================\n");
	printf(" PERSISTENCE\n");
	printf("=================================================\n");
	
	printf("\nTest 3a: Save and load no data:");
	(*totalTest)++;
	stuTable_init(&students);	
	
	stuTable_save(students, "./testStudent.csv");
	stuTable_init(&students);		
	stuTable_load(&students, "./testStudent.csv");
	
	if(students.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
	
	printf("\nTest 3b: Save and load students:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);

	stuTable_save(students, "./testStudent.csv");
	stuTable_init(&students);		
	stuTable_load(&students, "./testStudent.csv");
	
	if(students.size==3) {
		if(student_cmp(students.table[0], student1)!=0 || 
		   student_cmp(students.table[1], student2)!=0 ||
		   student_cmp(students.table[2], student3)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, students.size);
	}
}

void test_search(int *totalTest, int *passedTest) {	
	tStudentTable students, result;
	tStudent student1, student2, student3;	
		
	printf("=================================================\n");
	printf(" STUDENTS SEARCH\n");
	printf("=================================================\n");
	
	printf("\nTest 4a: Search student by birth year in empty table:");
	(*totalTest)++;
	stuTable_init(&students);	
	
	stuTable_findByBirthYear(students, 1990, &result);
	if(result.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.size);
	}

	printf("\nTest 4b: Search student by birth year:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);
	
	stuTable_findByBirthYear(students, 1990, &result);
	if(result.size==2) {
		if(student_cmp(result.table[0], student1)!=0 || student_cmp(result.table[1], student3)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.size);
	}
}
	
void test_count(int *totalTest, int *passedTest) {	
	tStudentTable students;
	tStudent student1, student2, student3;	
	unsigned int i;
		
	printf("=================================================\n");
	printf(" STUDENTS STATISTICS\n");
	printf("=================================================\n");
	
	printf("\nTest 5a: Count females of empty table:");
	(*totalTest)++;
	stuTable_init(&students);	
	
	i = stuTable_getFemaleNumber(students);
	if(i==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of female in the table. Expected %d and returned %d)\n", 0, i);
	}
	
	printf("\nTest 5b: Count the number of females:");
	(*totalTest)++;
	test_initStuTable(&students,&student1,&student2,&student3);
	
	i = stuTable_getFemaleNumber(students);
	if(i==2) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of female in the table. Expected %d and returned %d)\n", 2, i);
	}
}
	
void test_sort(int *totalTest, int *passedTest) {	
	tStudentTable students, result;
	tStudent student1, student2, student3;	
		
	printf("=================================================\n");
	printf(" STUDENTS SORTING\n");
	printf("=================================================\n");

	printf("\nTest 6a: Sort empty table:");
	(*totalTest)++;
	stuTable_init(&students);		
	
	stuTable_sortByAge(students, &result);
	if(result.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.size);
	}
	
	printf("\nTest 6b: Sort students:");
	(*totalTest)++;
	stuTable_init(&students);		
	getStudentObject(STUDENT1, &student1);	
	stuTable_add(&students, student1);	
	getStudentObject(STUDENT2, &student2);	
	stuTable_add(&students, student2);
	getStudentObject(STUDENT3, &student3);	
	stuTable_add(&students, student3);
	
	stuTable_sortByAge(students, &result);
	if(result.size==3) {
		if(student_cmp(result.table[0], student2)!=0 ||
			student_cmp(result.table[1], student1)!=0 ||
			student_cmp(result.table[2], student3)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 3, result.size);
	}
}

void test_api(int *totalTest, int *passedTest) {
	tAppData appData;		
	tSubjectTable subjectTable;	
	tStudentTable studentTable;
	tSubject subject1, subject2;
	tStudent student1, student2, student3;
	tError retVal = OK;	
	
	printf("=================================================\n");
	printf(" API\n");
	printf("=================================================\n");
		
	/* Test 1: Get the list of subjects */
	printf("\nTest 1: Get empty table of subjects:");
	(*totalTest)++;
	appData_init(&appData);
	getSubjects(appData, &subjectTable);
	if(subjectTable.size==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 2: Add a subject:");
	(*totalTest)++;
	appData_init(&appData);
	getSubjectObject("12345;MATHS1;6;Mathematics 1;", &subject1);	
	retVal=addSubject(&appData, subject1);
	if(retVal!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addSubject. Expected %d and returned %d)\n", OK, retVal);
	} else {
		getSubjects(appData, &subjectTable);
		if(subjectTable.size==1) {
			if(subject_cmp(subjectTable.table[0], subject1)==0) {
				printf("\n\t-> OK\n");			
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", subjectTable.size);
		}
	}
	
	printf("\nTest 3: Add a student:");
	(*totalTest)++;
	appData_init(&appData);
	getStudentObject(STUDENT1, &student1);	
	retVal=addStudent(&appData, student1);
	if(retVal!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addStudent. Expected %d and returned %d)\n", OK, retVal);
	} else {
		getStudents(appData, &studentTable);
		if(studentTable.size==1) {
			if(student_cmp(studentTable.table[0], student1)==0) {
				printf("\n\t-> OK\n");			
				(*passedTest)++;
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", studentTable.size);
		}
	}
	
	printf("\nTest 4: Delete student in middle of a table:");
	(*totalTest)++;
	appData_init(&appData);	

	getStudentObject(STUDENT1, &student1);	
	getStudentObject(STUDENT2, &student2);	
	getStudentObject(STUDENT3, &student3);		
	addStudent(&appData, student1);	
	addStudent(&appData, student2);
	addStudent(&appData, student3);
	removeStudent(&appData, student2);	

	getStudents(appData, &studentTable);
	if(studentTable.size==2) {
		if(student_cmp(studentTable.table[0], student1)!=0 || student_cmp(studentTable.table[1], student3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, studentTable.size);
	}
	
	printf("\nTest 5: Save and load application data:");
	(*totalTest)+=2;
	appData_init(&appData);	
	getSubjectObject("12345;MATHS1;6;Mathematics 1;", &subject1);	
	addSubject(&appData, subject1);
	getSubjectObject("11111;PHISICS2;4;Phisics 2;", &subject2);	
	addSubject(&appData, subject2);
	getStudentObject(STUDENT1, &student1);	
	addStudent(&appData, student1);	
	getStudentObject(STUDENT2, &student2);	
	addStudent(&appData, student2);
	
	appData_setPath(&appData, "./");
	appData_save(appData);
	appData_init(&appData);	
	appData_setPath(&appData, "./");
	appData_load(&appData);
	
	if(appData.subjects.size==2) {
		if(subject_cmp(appData.subjects.table[0], subject1)!=0 || subject_cmp(appData.subjects.table[1],subject2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> subjectS OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the subjects table. Expected %d and returned %d)\n", 2, appData.subjects.size);
	}
	if(appData.students.size==2) {
		if(student_cmp(appData.students.table[0], student1)!=0 || student_cmp(appData.students.table[1], student2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> STUDENTS OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the students table. Expected %d and returned %d)\n", 2, appData.students.size);
	}
}

void test_initSubTable(tSubjectTable *table, tSubject *s1, tSubject *s2, tSubject *s3) {
	
	/* Create 3 test subjects */
	getSubjectObject("12345;MATHS1;6;Mathematics 1;", s1);	
	getSubjectObject("11111;PHISICS2;4;Phisics 2;", s2);	
	getSubjectObject("54321;PROGRAMMING;7;Introduction to programming;", s3);	
	
	/* Add the students to the table */
	subTable_init(table);		
	subTable_add(table, *s1);
	subTable_add(table, *s2);
	subTable_add(table, *s3);

}

void test_initStuTable(tStudentTable *table, tStudent *s1, tStudent *s2, tStudent *s3) {
	
	/* Create 3 test students */
	getStudentObject(STUDENT1, s1);	
	getStudentObject(STUDENT2, s2);	
	getStudentObject(STUDENT3, s3);	
	
	/* Add the students to the table */
	stuTable_init(table);		
	stuTable_add(table, *s1);
	stuTable_add(table, *s2);
	stuTable_add(table, *s3);

}

void test_initMarkTable(tStudentTable stuTab, tSubjectTable subTab, tMarkTable *markTab){
	
	int i, j;
	tMark mark;
	
	mrkTable_init(markTab);
	for (i=0; i<stuTab.size;i++){
		for (j=0;j<subTab.size;j++){
			mark.stuId = stuTab.table[i].id;
			mark.subId = subTab.table[j].id;
			mark.value = ((i+13)*(j+11)) % 10;
			mrkTable_add(markTab,mark);
		}
	}
}

void test_stuRecord(int* totalTest, int* passedTest) {

	tStudentTable students;
	tStudent student1, student2, student3;
	tSubjectTable subjects;
	tSubject subject1, subject2, subject3;
	tMarkTable marks;
	tStudentRecord sr1, sr2;
		
	test_initSubTable(&subjects,&subject1,&subject2,&subject3);
	test_initStuTable(&students,&student1,&student2,&student3);
	test_initMarkTable(students,subjects,&marks);
	
	printf("=================================================\n");
	printf(" STUDENT RECORD \n");
	printf("=================================================\n");
	
	printf("\nTest1: Get the student record for a non existint student:");
	(*totalTest)++;
	if(sr_getStudentRecord(marks,subjects, 10000000, &sr1)==ERR_ENTRY_NOT_FOUND) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL.\n");	
	}
	
	printf("\nTest2: Get the student record for an existing student:");
	(*totalTest)++;
	if(sr_getStudentRecord(marks,subjects,12345678, &sr1)==OK) {
		if(fabs(sr1.avgMark-4.12)>0.01 || fabs(sr1.totCredits-17)>0.1 ) {
			printf("\n\t-> FAIL. Invalid quantities.\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL.\n");	
	}

	printf("\nTest 3: Compare two equal results:");
	(*totalTest)++;
	sr_getStudentRecord(marks,subjects,12345678, &sr1);
	if(sr_equals(sr1, sr1)==TRUE) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL.\n");
	}

	printf("\nTest 4: Compare two diferent results:");
	(*totalTest)++;
	sr_getStudentRecord(marks,subjects,12345678, &sr1);
	sr_getStudentRecord(marks,subjects,87654321, &sr2);
	if(sr_equals(sr1, sr2)==FALSE) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL.\n");
	}
}

void test_queue(int* totalTest, int* passedTest) {
	tStudentTable students;
	tStudent student1, student2, student3;
	tSubjectTable subjects;
	tSubject subject1, subject2, subject3;
	tMarkTable marks;
	tStuRecQueue queue;
	tStudentRecord sr1, sr2, srRet;		
	
	/* Prepare the test data */
	test_initSubTable(&subjects,&subject1,&subject2,&subject3);
	test_initStuTable(&students,&student1,&student2,&student3);
	test_initMarkTable(students,subjects,&marks);
	sr_getStudentRecord(marks,subjects,12345678, &sr1);
	sr_getStudentRecord(marks,subjects,87654321, &sr2);
	
	printf("=================================================\n");
	printf(" QUEUE\n");
	printf("=================================================\n");
	
	printf("\nTest1: Initialize the queue:");
	(*totalTest)++;
	sr_init(&queue);
	if(srQueue_empty(&queue)) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest2: Add an element to the queue:");
	(*totalTest)++;
	sr_init(&queue);
	if(srQueue_enqueue(&queue, sr1)==OK) { 
		if(srQueue_empty(&queue)==FALSE) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		} else {
			printf("\n\t-> FAIL, queue empty\n");
		}
	} else {
		printf("\n\t-> FAIL, ERROR in enqueue\n");
	}
	
	printf("\nTest 3: Enqueue and dequeue an element:");
	(*totalTest)++;
	sr_init(&queue);
	if(srQueue_enqueue(&queue, sr1)==OK) { 
		if(srQueue_empty(&queue)==TRUE) {
			printf("\n\t-> FAIL, queue empty\n");
		} else {
			if(srQueue_dequeue(&queue, &srRet)!=OK) {
				printf("\n\t-> FAIL, queue empty\n");
			} else {
				if(sr_equals(sr1, srRet)!=TRUE || srQueue_empty(&queue)!=TRUE) {
					printf("\n\t-> FAIL\n");
				} else {
					printf("\n\t-> OK\n");
					(*passedTest)++;
				}
			}
		}
	} else {
		printf("\n\t-> FAIL, ERROR in enqueue\n");
	}
	
	printf("\nTest 4: Enqueue two elements and dequeue an element:");
	(*totalTest)++;
	sr_init(&queue);
	if(srQueue_enqueue(&queue, sr1)==OK) {
		if(srQueue_enqueue(&queue, sr2)==OK) {
			if(srQueue_empty(&queue)==TRUE) {
				printf("\n\t-> FAIL, queue empty\n");
			} else {
				if(srQueue_dequeue(&queue, &srRet)!=OK) {
					printf("\n\t-> FAIL, queue empty\n");
				} else {
					if(sr_equals(sr1, srRet)!=TRUE || srQueue_empty(&queue)==TRUE) {
						printf("\n\t-> FAIL\n");
					} else {
						printf("\n\t-> OK\n");
						(*passedTest)++;
					}
				}
			}
		} else {
			printf("\n\t-> FAIL, ERROR in enqueue 2nd element\n");
		}	
	} else {
		printf("\n\t-> FAIL, ERROR in enqueue 1st element\n");
	}
	
	printf("\nTest 5: Deque all elements:");
	(*totalTest)++;
	sr_init(&queue);
	srQueue_enqueue(&queue, sr1);
	srQueue_enqueue(&queue, sr2);	
	
	if(srQueue_dequeue(&queue, &srRet)!=OK) {
		printf("\n\t-> FAIL, queue empty\n");
	} else {
		if(sr_equals(sr1, srRet)!=TRUE || srQueue_empty(&queue)==TRUE) {
			printf("\n\t-> FAIL\n");
		} else {		
			if(srQueue_dequeue(&queue, &srRet)!=OK) {
				printf("\n\t-> FAIL, queue empty\n");
			} else {
				if(sr_equals(sr2, srRet)!=TRUE || srQueue_empty(&queue)!=TRUE) {
					printf("\n\t-> FAIL\n");
				} else {
					printf("\n\t-> OK\n");
					(*passedTest)++;
				}
			}
		}
	}
	
	printf("\nTest 6: Deque all elements and add a new element:");
	(*totalTest)++;
	sr_init(&queue);
	srQueue_enqueue(&queue, sr1);
	srQueue_enqueue(&queue, sr2);
	srQueue_dequeue(&queue, &srRet);
	srQueue_dequeue(&queue, &srRet);
	if(srQueue_enqueue(&queue, sr1)==OK) { 
		if(srQueue_empty(&queue)==TRUE) {
			printf("\n\t-> FAIL, queue empty\n");
		} else {
			if(srQueue_dequeue(&queue, &srRet)!=OK) {
				printf("\n\t-> FAIL, queue empty\n");
			} else {
				if(sr_equals(sr1, srRet)!=TRUE || srQueue_empty(&queue)!=TRUE) {
					printf("\n\t-> FAIL\n");
				} else {
					printf("\n\t-> OK\n");
					(*passedTest)++;
				}
			}
		}
	} else {
		printf("\n\t-> FAIL, ERROR in enqueue\n");
	}	
}