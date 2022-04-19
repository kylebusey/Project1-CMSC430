// Compiler Theory and Design
// Dr. Duane J. Jarc

// This file contains the bodies of the functions that produces the compilation
// listing

#include <cstdio>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

#include "listing.h"

static int lineNumber;
static string error = "";
static int totalErrors = 0;
static int lexicalErrors = 0;
static int syntaxErrors = 0;
static int semanticErrors = 0;

static queue<string> errorQueue;

static ErrorCategories errorCategory;
static string message = "";

static void displayErrors();
void print_queue(std::queue<string> &queue);

void firstLine()
{
	lineNumber = 1;
	printf("\n%4d  ",lineNumber);
}

void nextLine()
{
	displayErrors();
	lineNumber++;
	printf("%4d  ",lineNumber);
}

int lastLine()
{

	printf("\r");
	displayErrors();
	printf("     \n");

	if(totalErrors > 0) {
		printf("Lexical errors: %4d\n", lexicalErrors);
		printf("Syntax errors: %4d\n", syntaxErrors);
		printf("Semantic errors: %4d\n", semanticErrors);

	} else {
		printf("Compiled Successfully");
	}

	

	return totalErrors;
}
    
void appendError(ErrorCategories errorCategory, string message)
{

	string messages[] = { "Lexical Error, Invalid Character ", "",
		"Semantic Error, ", "Semantic Error, Duplicate Identifier: ",
		"Semantic Error, Undeclared " };

	error = messages[errorCategory] + message;
	errorQueue.push(error);
	totalErrors++;

	if(errorCategory == LEXICAL || errorCategory == DUPLICATE_IDENTIFIER) {
		lexicalErrors++;
	} else if (errorCategory == SYNTAX) {
		syntaxErrors++;
	} else if (errorCategory == GENERAL_SEMANTIC) {
		semanticErrors++;
	}

}

void displayErrors()
{
	print_queue(errorQueue);
	error = "";
}

void print_queue(std::queue<string> &queue) 
{
	while( !queue.empty() )
    {
       std::cout << queue.front();
       queue.pop();
	   printf("\n");
    }
    std::cout << std::endl;
}




