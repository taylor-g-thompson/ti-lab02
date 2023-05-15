/*

Name: Taylor Thompson
Lab 02 - Parsing
Purpose of file: Contains the files needed to create a parser for sentences

*/

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int nextToken = 0;

// Production functions
bool firstOf_sentence();
void adjective_phrase();
bool firstOf_adjective_phrase();
void noun_phrase();
bool firstOf_noun_phrase();
void verb_phrase();
bool firstOf_verb_phrase();
int noun_counter = 1;
int verb_counter = 1;
int adjective_counter = 1;

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;

  noun_phrase();
  verb_phrase();
  noun_phrase(); 

  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence() {
  if (nextToken != ARTICLE && nextToken != POSSESSIVE)
    return false;
  return true;
}

/* Adjective Phrase */

void adjective_phrase() {
  if ( firstOf_adjective_phrase() == false )
    throw( "<adjective_phrase> did not start with an article or possessive." );

  cout << "Enter <adjective_phrase> " << adjective_counter << endl;

  if (nextToken == ARTICLE)
    output("ARTICLE");

  else if (nextToken == POSSESSIVE)
    output("POSSESSIVE");

  lex();

  if (nextToken != ADJECTIVE)
    throw( "<adjective_phrase> did not have adjective.");

  output("ADJECTIVE");

  lex();

  cout << "Exit <adjective_phrase> " << adjective_counter << endl;
  adjective_counter++;
}

bool firstOf_adjective_phrase() {
  if (nextToken != ARTICLE && nextToken != POSSESSIVE)
    return false;
  return true;
}

/* Noun Phrase */

void noun_phrase() {
  if ( firstOf_noun_phrase() == false )
    throw( "<noun_phrase> did not start with an article or possessive." );

  cout << "Enter <noun_phrase> " << noun_counter << endl;

  adjective_phrase();

  if (nextToken != NOUN)
    throw( "<noun_phrase> did not have a noun." );

  output("NOUN");

  lex();
   
  cout << "Exit <noun_phrase> " << noun_counter << endl;
  noun_counter++;
}

bool firstOf_noun_phrase() {
  if (nextToken != ARTICLE && nextToken != POSSESSIVE)
    return false;
  return true;
}

/* Verb Phrase */

void verb_phrase() {
  if ( firstOf_verb_phrase() == false )
    throw( "<verb_phrase> did not start with an verb or an adverb." );
    int temp = verb_counter++;

  cout << "Enter <verb_phrase> " << temp << endl;

  if (nextToken == VERB) {
    output("VERB");
    lex();
  }

  else {
    output("ADVERB");
    lex();
    verb_phrase();
  }
   
  cout << "Exit <verb_phrase> " << temp << endl;
}

bool firstOf_verb_phrase() {
  if (nextToken != VERB && nextToken != ADVERB)
    return false;
  return true;
}
