/* Run all the test set */
#include "data.h"
#include "api.h"

void runTests();

/* Run all the test set for PR2 */
void runTestsPR2(int* totalTest, int* passedTest);

/* Run all the test set for PR3 */
void runTestsPR3(int* totalTest, int* passedTest);

void test_initStuTable(tStudentTable *table, tStudent *s1, tStudent *s2, tStudent *s3);

void test_subjects(int* totalTest, int* passedTest);

/* Test the student comparison and copy */
void test_cmp_cpy(int* totalTest, int* passedTest);

/* Test the student table management*/
void test_stu_tab(int* totalTest, int* passedTest);

/* Test the student data persistence */
void test_persistence(int* totalTest, int* passedTest);

/* Test the student search */
void test_search(int* totalTest, int* passedTest);

/* Test the student statistics */
void test_count(int* totalTest, int* passedTest);

/* Test the student sorting */
void test_sort(int* totalTest, int* passedTest);

/* Test the api calls */
void test_api(int* totalTest, int* passedTest);

void test_stuRecord(int* totalTest, int* passedTest);

void test_queue(int* totalTest, int* passedTest);

