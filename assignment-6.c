/********************************************************************
Name: Akhil Mujje
UT EID: dam4335
Section: 16215
EE312-Assignment 6

********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_URL_LENGTH 100

 struct tnode { /* the tree node: */
   char *key; /* points to the url string */
   int count; /* number of occurrences */
   struct tnode *left; /* left child */
   struct tnode *right; /* right child */   
 };


 /* add_to_tree:  add a node with url, at or below p 
  * p: pointer to the root of the (sub)tree where you must add a value
  * url: the URL to be added
  */
 struct tnode* add_to_tree(struct tnode* p, char* url)
 {	
	 if (!p){
		 struct tnode *t_node = malloc(sizeof(struct tnode));
		 t_node->count = 1;
		 t_node->key = malloc(sizeof(char[MAX_URL_LENGTH]));
		 strcpy(t_node->key, url);
		 t_node->left = 0;
		 t_node->right = 0;
		 return t_node;
	 }
	 
	 int cmp = strcmp(p->key, url);
	 
	 int null_flag_left = 0;
	 int null_flag_right = 0;
	 if (cmp > 0) {
		 if (p->left) {			 
			 add_to_tree(p->left, url);
			 return p;

		 }
		 else {
			 null_flag_left = 1;			 
			 //if (!(p->right))
			//	 null_flag_right = 1;
		 }

	 }
	 else if (cmp < 0) {
		 if (p->right) {			 
			add_to_tree(p->right, url);	
			return p;
		 }
		 else {
			 null_flag_right = 1;
			 //if (!(p->left))
			 //	 null_flag_left = 1;
		 }
	 }
	 else { //cmp == 0	

		 p->count++;		 
		 return p; 
	 }
	 //When creating a new node, it says in the lab document that the two children should be made null.
	 //However, isn't the new node connected to the current node within the tree?
	 /*if (null_flag_left && null_flag_right) {
		 struct tnode *t_node = malloc(sizeof(struct tnode));
		 t_node->count = 1;
		 strcpy(t_node->key, url);
		 if (cmp < 0) {
			 t_node->left = 0;
			 t_node->right = p;
			 p->left = t_node;
		 }
		 if (cmp > 0) {
			 t_node->left = p;
			 t_node->right = 0;
			 p->right = t_node;
		 }
		 return t_node;
	 }*/

	// if (null_flag_left || null_flag_right)
	// {
		 struct tnode *t_node =  malloc(sizeof(struct tnode));
		 t_node->count = 1;
		 t_node->key = malloc(sizeof(char[MAX_URL_LENGTH]));
		 strcpy(t_node->key, url);
		 t_node->left = 0;
		 t_node->right = 0;
		 if (null_flag_left) {			
			 p->left = t_node;
		 }
		 if (null_flag_right) {			 
			 p->right = t_node;
		 }
		 return p;			
	// }
	// return p;  
 }


 /* populate_tree: repeatedly call add_to_tree on urls from a file 
  * url_file: name of file to read URLs from
  * R: pointer to the root pointer of the tree
  */
 void populate_tree(char *url_file, struct tnode** R)
 {
	 FILE *fp;
	 fp = fopen(url_file, "r");
	 if (!fp) {
		 return;
	 }
	 int count = 0;	 
	 char string[MAX_URL_LENGTH] = { 0 };
	 while (!feof(fp)) {		 
		 if (fgets(string, MAX_URL_LENGTH + 1, fp) != 0)
		 {
			 for (int i = 0; i < MAX_URL_LENGTH; i++) {
				 if (string[i] == '\n') {
					 string[i] = 0;
					 break;
				 }
			 }
			 if (string[0] == 0) { 1; } //DO NOTHING...DONT ADD TO TREE

				 
			 else if (count == 0) {
				 *R = add_to_tree(*R, string);
				 count = 1;
			 }
			 else {
				 add_to_tree(*R, string);				 
			 }
		 }		 
	 } 	
	  fclose(fp); 
	 

 }





 /* lookup:  look up a url in the tree rooted at p, return the frequency of that url
  * p: pointer to the root of the (sub)tree
  * url: url to look for
  */
 int lookup(struct tnode* p, char* url) // Return the frequency of the url
 {
	if (!p) return 0;	 
	 int cmp = strcmp(p->key, url);
	 int value = 0;
	 int null_flag = 0;	
	 if (cmp > 0) {
		 if (p->left) {
			 value = lookup(p->left, url);
			 return value;
		 }
		 else	 
			 null_flag = 1;		 
	}
    else if (cmp < 0) {
		if (p->right) {
			value = lookup(p->right, url);
			return value;
		}
		 else
			 null_flag = 1;
	 }
	else {
		return p->count;
	}	
	return 0;
	
  

 }


 /* treeprint:  in-order print of tree p
  * Set the urls in the passed in array in alphabetical fashion. Also set their respective frequencies in a second int array.
  * Return the number of elements set
  * size: how many elements you have currently inserted into the array(s)
  * p: pointer to the root of the (sub)tree
  * URL_array: array to store URLs in
  * n: integer array to store frequencies in
  */ 
int treeprint(int size, struct tnode* p, char URL_array[][MAX_URL_LENGTH], int *n)
{
	int index = size;	
	int left, right = 0;
		
	if (!p) return 0;

	if (index >= 10)
		return 10;

	//left branches
	left =  treeprint(index, p->left, URL_array, n);			
	index += left;
	
	if (index >= 10)
		return 10;

	//root
	strcpy(URL_array[index], p->key);
	n[index] = p->count;
	index++;	

	if (index >= 10)
		return 10;

	//right branches
	
	right = treeprint(index, p->right, URL_array, n);
	if (left + right + 1 >= 10)
		return 10;	

	return left + right + 1 ;	

}

