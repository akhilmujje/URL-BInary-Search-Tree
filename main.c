/********************************************************************
Name: Akhil Mujje
UT EID: dam4335
Section: 16215
EE312-Assignment 6

********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "main.h"


int compareArrays(char ar1[][MAX_URL_LENGTH],char ar2[][MAX_URL_LENGTH],int compare_till){
    
    int i;
    for(i=0;i<compare_till;i++){
        if(strcmp(ar1[i],ar2[i]) !=0)
            return 0;
    }
    return 1;
}

int compare_numArrays(int* num_ar1, int* num_ar2,int compare_till){
    
    int i;
    for(i=0;i<compare_till;i++){
        if(num_ar1[i]!= num_ar2[i])
            return 0;
    }
    return 1;
}

void test_print(struct tnode* p, int expectedResult, char expectedArray[][MAX_URL_LENGTH], int expected_freq[10]){
    
	char node_urls[10][MAX_URL_LENGTH];
	int url_frequency[10];
	int j = treeprint(0, p, node_urls, url_frequency);
    if ( expectedResult != j) {
        printf("Test TREE PRINT Failed result.\n");
    }
    else{
        if(compareArrays(expectedArray, node_urls,expectedResult))
            if(compare_numArrays(expected_freq, url_frequency, expectedResult)){
                printf("Test TREE PRINT Passed.\n");
                return;
            }
        printf("Test TREE PRINT Failed.\n");
    }
}




int main()
{

	struct tnode *root;
	char node_urls[10][MAX_URL_LENGTH];
	int url_frequency[10];
	root = NULL;
	root = add_to_tree(root, "google.com");
	root = add_to_tree(root, "google.com");
	assert(root->count == 2);
	root = add_to_tree(root, "amazon.com");
	assert(treeprint(0, root, node_urls, url_frequency) == 2);

	populate_tree("small_url.txt", &root);
	test_print(root, 7, Expected_URLs_small, Expected_Url_Freq_small);

	populate_tree("long_url.txt", &root);
	assert(lookup(root, "vonage.com") == 2323);
	test_print(root, 10, Expected_URLs, Expected_Url_Freq);
	//populate_tree("test_url.txt", &root);
	//test_print(root, 3, test_Expected_URLs_small, test_Expected_Url_Freq_small);
	


	return 0;


	
	
	
 	/*assert(treeprint(0,root,node_urls, url_frequency) == 2);
	
    populate_tree("small_url.txt", &root);
	test_print(root, 7, Expected_URLs_small, Expected_Url_Freq_small);
    
    populate_tree("long_url.txt", &root);
	assert( lookup(root, "vonage.com") == 2323);
	test_print(root, 10, Expected_URLs, Expected_Url_Freq);*/
	
	//return 0;
}

