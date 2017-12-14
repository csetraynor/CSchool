#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "uocmoney.h"
#include "concepts.h"
#include "movements.h"


void runTests() {
	test_concepts();
	test_movements();	
	test_persistence();
	test_api();
	test_amount();
}

void test_concepts() {
	tConceptTable concepts;		
	tConcept concept1, concept2, concept3;
	tError err;
	unsigned int i;
	
	printf("=================================================\n");
	printf(" CONCEPTS\n");
	printf("=================================================\n");
	
	/* Test 1:Initialize the table */
	printf("\nTest1: Initialize the table:");
	conTable_init(&concepts);	
	if(concepts.size==0) {
		printf("\n\t-> OK\n");
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	/* Test 2: Add a concept */
	printf("\nTest2: Add a concept:");
	conTable_init(&concepts);
	getConceptObject("0;test concept;", &concept1);	
	err=conTable_add(&concepts, concept1);
	if(err!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addConcept. Expected %d and returned %d)\n", OK, err);
	} else {		
		if(concepts.size==1) {
			if(concept_cmp(concepts.table[0], concept1)==0) {
				printf("\n\t-> OK\n");			
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", concepts.size);
		}
	}	
	
	/* Test3: Pass the maximum capacity of the table */
	printf("\nTest3: Pass the maximum capacity of the table:");
	conTable_init(&concepts);
	for(i=0;i<=MAX_CONCEPTS;i++) {
		concept1.id=i;
		sprintf(concept1.description, "test concept %d", i);
		err=conTable_add(&concepts, concept1);
		if(i<MAX_CONCEPTS) {
			if(err!=OK) {				
				printf("\n\t-> FAIL (unexpected return value from addConcept adding object %d of %d. Expected %d and returned %d)\n", i+1, MAX_CONCEPTS, OK, err);
				break;
			}
		} else {
			if(err==ERR_MEMORY) {
				printf("\n\t-> OK\n");
			} else {
				printf("\n\t-> FAIL (unexpected return value from addConcept adding last object. Expected %d and returned %d)\n", ERR_MEMORY, err);
			} 
		}
	}		
	
	/* Test4: Delete a concept from an empty table */
	printf("\nTest4: Delete a concept from an empty table:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);
	conTable_del(&concepts, concept1);	
	if(concepts.size==0) {
		printf("\n\t-> OK\n");
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, concepts.size);
	}	
	
	/* Test5: Delete the first concept of a table */
	printf("\nTest5: Delete the first concept of a table:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);	
	conTable_add(&concepts, concept1);
	getConceptObject("2;test concept 2;", &concept2);	
	conTable_add(&concepts, concept2);
	getConceptObject("1;test concept 1;", &concept3);	
	conTable_add(&concepts, concept3);
		
	conTable_del(&concepts, concept1);
	
	if(concepts.size==2) {
		if(concept_cmp(concepts.table[0], concept2)!=0 || concept_cmp(concepts.table[1], concept3)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, concepts.size);
	}
	
	/* Test6: Delete the last concept of a table */
	printf("\nTest6: Delete the last concept of a table:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);	
	conTable_add(&concepts, concept1);
	getConceptObject("2;test concept 2;", &concept2);	
	conTable_add(&concepts, concept2);
	getConceptObject("1;test concept 1;", &concept3);	
	conTable_add(&concepts, concept3);
		
	conTable_del(&concepts, concept3);
	
	if(concepts.size==2) {
		if(concept_cmp(concepts.table[0], concept1)!=0 || concept_cmp(concepts.table[1], concept2)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, concepts.size);
	}
	
	/* Test7: Delete in middle concept of a table */
	printf("\nTest7: Delete in middle concept of a table:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);	
	conTable_add(&concepts, concept1);
	getConceptObject("2;test concept 2;", &concept2);	
	conTable_add(&concepts, concept2);
	getConceptObject("1;test concept 1;", &concept3);	
	conTable_add(&concepts, concept3);
		
	conTable_del(&concepts, concept2);
	
	if(concepts.size==2) {
		if(concept_cmp(concepts.table[0], concept1)!=0 || concept_cmp(concepts.table[1], concept3)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, concepts.size);
	}
	
	/* Test8: Delete a non existing concept */
	printf("\nTest8: Delete a non existing concept:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);	
	conTable_add(&concepts, concept1);
	getConceptObject("2;test concept 2;", &concept2);	
	conTable_add(&concepts, concept2);
	getConceptObject("1;test concept 1;", &concept3);		
		
	conTable_del(&concepts, concept3);
	
	if(concepts.size==2) {
		if(concept_cmp(concepts.table[0], concept1)!=0 || concept_cmp(concepts.table[1], concept2)!=0 ) {
			printf("\n\t-> FAIL (invalid data)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, concepts.size);
	}	
}

void test_movements() {	
	tMovementTable movements, result;
	tMovement movement1, movement2, movement3;	
	tDate date1,date2;
	tError err;
	unsigned int i;
		
	printf("=================================================\n");
	printf(" MOVEMENTS\n");
	printf("=================================================\n");
	
	/* Test 1: Initialize the table */
	printf("\nTest 1: Initialize the table:");
	movTable_init(&movements);
	if(movements.size==0) {
		printf("\n\t-> OK\n");
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	/* Test 2: Add a movement */
	printf("\nTest 2: Add a movement:");
	movTable_init(&movements);	
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	err=movTable_add(&movements, movement1);
	if(err!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addConcept. Expected %d and returned %d)\n", OK, err);
	} else {		
		if(movements.size==1) {
			if(movement_cmp(movements.table[0], movement1)==0) {
				printf("\n\t-> OK\n");			
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", movements.size);
		}
	}	
			
	/* Test 3: Pass the maximum capacity of the table */
	printf("\nTest 3: Pass the maximum capacity of the table:");
	movTable_init(&movements);	
	
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	for(i=0;i<=MAX_MOVEMENTS;i++) {		
		err=movTable_add(&movements, movement1);
		if(i<MAX_MOVEMENTS) {
			if(err!=OK) {				
				printf("\n\t-> FAIL (unexpected return value from addMovement adding object %d of %d. Expected %d and returned %d)\n", i+1, MAX_MOVEMENTS, OK, err);
				break;
			}
		} else {
			if(err==ERR_MEMORY) {
				printf("\n\t-> OK\n");
			} else {
				printf("\n\t-> FAIL (unexpected return value from addMovement adding last object. Expected %d and returned %d)\n", ERR_MEMORY, err);
			} 
		}
	}		
	
	/* Test4: Delete a movement from an empty table */
	printf("\nTest4: Delete a movement from an empty table:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);
	movTable_del(&movements, movement1);
	if(movements.size==0) {
		printf("\n\t-> OK\n");
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, movements.size);
	}	
	
	/* Test 5: Delete the first movement of a table */
	printf("\nTest 5: Delete the first movement of a table:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);

	movTable_del(&movements,movement1);
	if(movements.size==2) {
		if(movement_cmp(movements.table[0], movement2)!=0 || movement_cmp(movements.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movements.size);
	}
	
	/* Test 6: Delete the last movement of a table */	
	printf("\nTest 6: Delete the last movement of a table:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);

	movTable_del(&movements,movement3);
	if(movements.size==2) {
		if(movement_cmp(movements.table[0], movement1)!=0 || movement_cmp(movements.table[1], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movements.size);
	}
	
	/* Test 7: Delete in middle movement of a table */
	printf("\nTest 7: Delete in middle movement of a table:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);

	movTable_del(&movements,movement2);
	if(movements.size==2) {
		if(movement_cmp(movements.table[0], movement1)!=0 || movement_cmp(movements.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movements.size);
	}
	
	/* Tes t8: Delete a non existing movement */
	printf("\nTest 8: Delete a non existing movement:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	
	movTable_del(&movements,movement3);
	if(movements.size==2) {
		if(movement_cmp(movements.table[0], movement1)!=0 || movement_cmp(movements.table[1], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movements.size);
	}
	
	/* Test 9: Find movements of a given conceptID with empty result */
	printf("\nTest 9: Find movements of a given conceptID with empty result:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;1;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);
	
	movTable_findByConcept(movements, 3, &result);	
	if(result.size==0) {		
		printf("\n\t-> OK\n");		
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.size);
	}
	
	/* Test10: Find movements of a given conceptID */
	printf("\nTest10: Find movements of a given conceptID:");
	movTable_init(&movements);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;1;", &movement2);	
	movTable_add(&movements, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2015;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);
	
	movTable_findByConcept(movements, 0, &result);	
	if(result.size==2) {
		if(movement_cmp(result.table[0], movement1)!=0 || movement_cmp(result.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.size);
	}
		
	/* Test11: Select movements up to a date. */
	printf("\nTest11: Select movements up to a date:");
	movTable_init(&movements);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);	
		
	date1.day=03;
	date1.month=11;
	date1.year=2015;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	movTable_find(movements, date2, date1, &result);	
	if(result.size==2) {
		if(movement_cmp(result.table[0], movement1)!=0 || movement_cmp(result.table[1], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.size);
	}
	
	/* Test12: Select movements from a date. */
	printf("\nTest12: Select movements from a date:");
	movTable_init(&movements);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);
		
	date1.day=03;
	date1.month=9;
	date1.year=2015;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	movTable_find(movements, date1, date2, &result);
	if(result.size==2) {
		if(movement_cmp(result.table[0], movement2)!=0 || movement_cmp(result.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.size);
	}
	
	/* Test13: Select movements between dates. */
	printf("\nTest13: Select movements between dates:");
	movTable_init(&movements);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	movTable_add(&movements, movement3);	
		
	date1.day=03;
	date1.month=9;
	date1.year=2015;
	date2.day=03;
	date2.month=1;
	date2.year=2016;
	movTable_find(movements, date1, date2, &result);	
	if(result.size==1) {
		if(movement_cmp(result.table[0], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, result.size);
	}
}

void test_persistence() {
	tMovementTable movements;
	tConceptTable concepts;
	tMovement movement1, movement2;
	tConcept concept1, concept2;
	
	printf("=================================================\n");
	printf(" PERSISTENCE\n");
	printf("=================================================\n");
	
	/* Test 1: Save and load concepts */
	printf("\nTest 1: Save and load concepts:");
	conTable_init(&concepts);	
	getConceptObject("0;test concept 0;", &concept1);	
	conTable_add(&concepts, concept1);	
	getConceptObject("1;test concept 1;", &concept2);	
	conTable_add(&concepts, concept2);	
	
	conTable_save(concepts, "./test/testConcept.csv");
	conTable_init(&concepts);	
	conTable_load(&concepts, "./test/testConcept.csv");
	
	if(concepts.size==2) {
		if(concept_cmp(concepts.table[0], concept1)!=0 || concept_cmp(concepts.table[1],concept2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, concepts.size);
	}
	
	/* Test 2: Save and load moviments */
	printf("\nTest 2: Save and load movements:");
	movTable_init(&movements);		
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	movTable_add(&movements, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	movTable_add(&movements, movement2);
	
	movTable_save(movements, "./test/testMovement.csv");
	movTable_init(&movements);		
	movTable_load(&movements, "./test/testMovement.csv");
	
	if(movements.size==2) {
		if(movement_cmp(movements.table[0], movement1)!=0 || movement_cmp(movements.table[1], movement2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movements.size);
	}
}

void test_api() {
	tAppData appData;		
	tConceptTable conceptTable;	
	tMovementTable movementTable;
	tConcept concept1, concept2;
	tMovement movement1, movement2, movement3;
	tError err;	
	tDate date1, date2;
	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	
	printf("=================================================\n");
	printf(" API\n");
	printf("=================================================\n");
		
	/* Test 1: Get the list of concepts */
	printf("\nTest 1: Get empty table of concepts:");
	appData_init(&appData);
	getConcepts(appData, &conceptTable);
	if(conceptTable.size==0) {
		printf("\n\t-> OK\n");
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	/* Test 2: Add a concept */
	printf("\nTest 2: Add a concept:");
	appData_init(&appData);
	getConceptObject("0;test concept;", &concept1);	
	err=addConcept(&appData, concept1);
	if(err!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addConcept. Expected %d and returned %d)\n", OK, err);
	} else {
		getConcepts(appData, &conceptTable);
		if(conceptTable.size==1) {
			if(concept_cmp(conceptTable.table[0], concept1)==0) {
				printf("\n\t-> OK\n");			
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", conceptTable.size);
		}
	}
	
	/* Test 3: Add a movement for a non existing concept */
	printf("\nTest 3: Add a movement for a non existing concept:");
	appData_init(&appData);	
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	err=addMovement(&appData, movement1);
	if(err!=ERR_INVALID_CONCEPT_ID) {		
		printf("\n\t-> FAIL (unexpected return value from addMovement. Expected %d and returned %d)\n", ERR_INVALID_CONCEPT_ID, err);
	} else {
		printf("\n\t-> OK\n");					
	}
	
	/* Test 4: Add a movement with an existing conceptID*/
	printf("\nTest 4: Add a movement with an existing conceptID:");
	appData_init(&appData);
	addConcept(&appData, concept1);
	getMovementObject("1;test movement 1;1.34;0;01/10/2015;0/0/0;0;", &movement1);	
	err=addMovement(&appData, movement1);
	if(err!=OK) {		
		printf("\n\t-> FAIL (unexpected return value from addMovement. Expected %d and returned %d)\n", OK, err);
	} else {
		getMovements(appData, date1, date2, &movementTable);
		if(movementTable.size==1) {
			if(movement_cmp(movementTable.table[0], movement1)==0) {
				printf("\n\t-> OK\n");			
			} else {
				printf("\n\t-> FAIL (Stored data is not correct)\n");
			}
		} else {
			printf("\n\t-> FAIL (Number of registers in table is incorrect. Expected 1, and have %d)\n", movementTable.size);
		}
	}
	
	/* Test 5: Select movements up to a date. */
	printf("\nTest 5: Select movements up to a date:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	addMovement(&appData, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
		
	date1.day=03;
	date1.month=11;
	date1.year=2015;
	getMovements(appData, date2, date1, &movementTable);
	if(movementTable.size==2) {
		if(movement_cmp(movementTable.table[0], movement1)!=0 || movement_cmp(movementTable.table[1], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movementTable.size);
	}
	
	/* Test6: Select movements from a date. */
	printf("\nTest 6: Select movements from a date:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	addMovement(&appData, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
		
	date1.day=03;
	date1.month=9;
	date1.year=2015;
	getMovements(appData, date1, date2, &movementTable);
	if(movementTable.size==2) {
		if(movement_cmp(movementTable.table[0], movement2)!=0 || movement_cmp(movementTable.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movementTable.size);
	}
	
	/* Test 7: Select movements between dates. */
	printf("\nTest 7: Select movements between dates:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	addMovement(&appData, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
		
	date1.day=03;
	date1.month=9;
	date1.year=2015;
	date2.day=03;
	date2.month=1;
	date2.year=2016;
	getMovements(appData, date1, date2, &movementTable);
	if(movementTable.size==1) {
		if(movement_cmp(movementTable.table[0], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 1, movementTable.size);
	}
	
	/* Test 8: Delete in middle movement of a table */
	printf("\nTest 8: Delete in middle movement of a table:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	addMovement(&appData, movement2);	
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
	removeMovement(&appData, movement2);	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	getMovements(appData, date1, date2, &movementTable);
	if(movementTable.size==2) {
		if(movement_cmp(movementTable.table[0], movement1)!=0 || movement_cmp(movementTable.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movementTable.size);
	}
	
	/* Test 9: Delete a concept without movements */
	printf("\nTest 9: Delete a concept without movements:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getConceptObject("1;test concept 1;", &concept2);	
	addConcept(&appData, concept2);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;0;", &movement2);	
	addMovement(&appData, movement2);	
	removeConcept(&appData, concept2);
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	getMovements(appData, date1, date2, &movementTable);
	if(movementTable.size==2) {
		if(movement_cmp(movementTable.table[0], movement1)!=0 || movement_cmp(movementTable.table[1], movement2)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movementTable.size);
	}
	
	/* Test 10: Delete a concept with movements */
	printf("\nTest 10: Delete a concept with movements:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getConceptObject("1;test concept 1;", &concept2);	
	addConcept(&appData, concept2);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;1;", &movement2);	
	addMovement(&appData, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
	removeConcept(&appData, concept2);
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	getMovements(appData, date1, date2, &movementTable);
	if(movementTable.size==2) {
		if(movement_cmp(movementTable.table[0], movement1)!=0 || movement_cmp(movementTable.table[1], movement3)!=0){
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, movementTable.size);
	}	
	
	/* Test 11: Save and load application data */
	printf("\nTest 11: Save and load application data:");
	appData_init(&appData);	
	getConceptObject("3;test concept 3;", &concept1);	
	addConcept(&appData, concept1);
	getConceptObject("4;test concept 4;", &concept2);	
	addConcept(&appData, concept2);
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;3;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;4;", &movement2);	
	addMovement(&appData, movement2);
	
	appData_setPath(&appData, "./test/");
	appData_save(appData);
	appData_init(&appData);	
	appData_setPath(&appData, "./test/");
	appData_load(&appData);
	
	if(appData.concepts.size==2) {
		if(concept_cmp(appData.concepts.table[0], concept1)!=0 || concept_cmp(appData.concepts.table[1],concept2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> CONCEPTS OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the concepts table. Expected %d and returned %d)\n", 2, appData.concepts.size);
	}
	if(appData.movements.size==2) {
		if(movement_cmp(appData.movements.table[0], movement1)!=0 || movement_cmp(appData.movements.table[1], movement2)!=0) {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> MOVEMENTS OK\n");
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the movements table. Expected %d and returned %d)\n", 2, appData.movements.size);
	}
}
	

void test_amount() {
	tAppData appData;		
	tConcept concept1, concept2;
	tMovement movement1, movement2, movement3;
	tDate date1, date2;
	float amount, expected;
	
	printf("=================================================\n");
	printf(" Amount\n");
	printf("=================================================\n");
		
	/* Test 1: Get the moviments amount of an empty table */
	printf("\nTest 1: Get the moviments amount of an empty table:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getConceptObject("1;test concept 1;", &concept2);	
	addConcept(&appData, concept2);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("1;test movement 2;4.34;1;02/10/2015;0/0/0;1;", &movement2);	
	addMovement(&appData, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=1;
	date2.month=1;
	date2.year=2000;
	
	amount=getAmount(appData, date1, date2);
	expected=0;
	if(fabs(amount-expected)>0.00001) {
		printf("\n\t-> FAIL (unexpected amount value. Expected %0.4f and returned %0.4f)\n", expected, amount);
	} else {
		printf("\n\t-> OK\n");
	}
	
	/* Test 2: Get the moviments amount of non periodic movements */
	printf("\nTest 2: Get the moviments amount of non periodic movements:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);	
	getConceptObject("1;test concept 1;", &concept2);	
	addConcept(&appData, concept2);	
	getMovementObject("1;test movement 1;1.34;0;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);
	getMovementObject("0;test movement 2;4.34;0;02/10/2015;0/0/0;1;", &movement2);	
	addMovement(&appData, movement2);
	getMovementObject("1;test movement 3;7.4;0;03/10/2016;0/0/0;0;", &movement3);	
	addMovement(&appData, movement3);	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	
	amount=getAmount(appData, date1, date2);
	expected=-1.34 + 4.34 - 7.4;
	if(fabs(amount-expected)>0.00001) {
		printf("\n\t-> FAIL (unexpected amount value. Expected %0.4f and returned %0.4f)\n", expected, amount);
	} else {
		printf("\n\t-> OK\n");
	}
	
	/* Test 3: Get the moviments amount of a periodic movement with end date*/
	printf("\nTest 3: Get the moviments amount of a periodic movement with end date:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);		
	getMovementObject("0;test movement 1;1.34;1;01/01/2015;01/10/2015;0;", &movement1);	
	addMovement(&appData, movement1);	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	
	amount=getAmount(appData, date1, date2);
	expected=10*1.34;
	if(fabs(amount-expected)>0.00001) {
		printf("\n\t-> FAIL (unexpected amount value. Expected %0.4f and returned %0.4f)\n", expected, amount);
	} else {
		printf("\n\t-> OK\n");
	}
	
	/* Test 4: Get the moviments amount of a periodic movement without end date*/
	printf("\nTest 4: Get the moviments amount of a periodic movement without end date:");
	appData_init(&appData);	
	getConceptObject("0;test concept 0;", &concept1);	
	addConcept(&appData, concept1);		
	getMovementObject("0;test movement 1;1.34;1;01/01/2015;0/0/0;0;", &movement1);	
	addMovement(&appData, movement1);	
	date1.day=0;
	date1.month=0;
	date1.year=0;
	date2.day=0;
	date2.month=0;
	date2.year=0;
	
	amount=getAmount(appData, date1, date2);
	expected=MAX_MOVEMENTS*1.34;
	if(fabs(amount-expected)>0.00001) {
		printf("\n\t-> FAIL (unexpected amount value. Expected %0.4f and returned %0.4f)\n", expected, amount);
	} else {
		printf("\n\t-> OK\n");
	}
}
