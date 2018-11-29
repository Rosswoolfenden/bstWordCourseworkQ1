// wordCountBTS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>  // allows us to read txt document.
#include <string>
#include <vector>
using namespace std;

class btsn
{
public:  //public as all functions in the program will want to be able to see 
	string key; // hold the string value.
	btsn* left, *right; // two pointers to right and left children
	
	int duplicateWord; // to count if words are repeated 
	btsn(string key);
	//atribute to see how many children it has
};

btsn::btsn(string key) { // initiation contructor.
	this->key = key; // on initiation make the key what the key is 
	this->left = NULL; // children not set yet
	this->right = NULL;
	this->duplicateWord = NULL;
}
// function to change duplicate word attribute to count how many times the words apear.
void changeFreq(btsn* tree) {
	tree->duplicateWord = tree->duplicateWord + 1;

}
btsn* insert_node(string x, btsn* tree) {
	/*if (tree->key == x) {
		tree->duplicateWord + 1;
	}*/
	if (tree == NULL) { // if there is nothing in the tree
		tree = new btsn(x); // adds a new instance of the btsn class creating a object
		tree->left = NULL;
		tree->right = NULL; 
	}
	else { //if the tree is not empty 
		if (tree->key > x) {
			if (tree->left == NULL) {
				tree->left = new btsn(x);  //if there is nothing to the left of the node, add it there
			}
			else {
				insert_node(x, tree->left); // else, keep moving down the left of the tree untill there is a space
			}
		}
		else if (tree->key < x) {  // if the value is greater than the current node
			if (tree->right == NULL) { //look if the right child slot is free
				tree->right = new btsn(x); // if the right node is free place itthere
			}
			else {
				insert_node(x, tree->right);//recursivly call fucntion with the right child node 
			}
		}
		else if (tree->key == x) { // if that word already exsits in the tree
			changeFreq( tree);  // call function to change the duplicateWord attribute
		}
	}

	return tree; //returns the tree.
}
// traverse the bts in pre order
void pre_order(btsn* tree) {
	cout << tree->key << endl;
	if (tree->left != 0) {
		pre_order(tree->left);
	}
	if (tree->right != 0) {
		pre_order(tree->right);
	}
}


void find_word(btsn* tree, string word){
	bool found = false;

	if (tree->key == word) {
		cout << "YES";
	}
	else if (tree->key > word) {
		cout << word << " is less than current node - " << tree->key << " so we will move to the left child node of this current node" << endl;
		if (tree->left != NULL) {  // if there is a left child node
			find_word(tree->left, word); // search left child node recursivly
		}
		else {
			cout << "NO";
		}
	}
	else if (tree->key < word) // if word is greater than the key-  further on in the alphabet
	{
		cout << word << " is greater than current node - " << tree->key << " so we will move to the right child node of this current node" << endl;
		if (tree->right != NULL) {
			find_word(tree->right, word);
		}
		else {
			cout << "NO";
		}
	}

}

int main()
{
	int i=0;
	
	ifstream inputtext; // variable to hold the text file text
	inputtext.open("text.txt");   // opens the text file
	string word; // holds each word off the input. 
	vector <string> textPara; // a vector to hold each word of the paragragh in.
	if (!inputtext.fail()) { // if the search for the file is sucseful, if it cant find the file the program will do nothing. 
		
		while (inputtext >> word) { //While there is still data to be read
			textPara.emplace_back(word);// append the data to the back off the vector.
		}
	}
	inputtext.close();  //closes the file
	btsn* tree=insert_node(textPara[0], 0); //adds first word from text to start the tree
	for (int i = 1; i < textPara.size(); i++) {  //^^starts at 1 as the item[0] is already in the the tree ^^^
		insert_node(textPara[i], tree);  // inserts each item from the vector into the bts
	}


	pre_order(tree);

	string wordfind;
	cout << "What word would you like to find:  "; 
	cin >> wordfind;

	find_word(tree, wordfind);



	
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
