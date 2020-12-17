#ifndef _HANGMAN_H
#define _HANGMAN_H

/*
    hangman.h
        
    Class definition for the hangman class.

    assignment: CSCI 262 Project - Evil Hangman        

    author: Alexa Nelson

    last modified: 9/24/2017
*/

#include <string>
#include <vector>
#include <map>

using namespace std;

/******************************************************************************
   class hangman

   Maintains game state for a game of hangman.

******************************************************************************/

class hangman {
public:
    hangman();
    bool word_count;
    // start a new game where player gets num_guesses unsuccessful tries
	void start_new_game(int num_guesses, int word_length);

    // player guesses letter c; return whether or not char is in word
    bool process_guess(char c);

    // display current state of word - guessed characters or '-'
    string get_display_word();

    // How many guesses remain?
	int get_guesses_remaining();

    // What characters have already been guessed (for display)?
    string get_guessed_chars();

    //get the number of words in the fam
    int get_word_fam();

    // Has this character already been guessed?
    bool was_char_guessed(char c);

    // Has the game been won/lost?  (Else, it continues.)
    bool is_won();
    bool is_lost();

    // Return the true hidden word.
    string get_hidden_word();

    bool find_word_of_length(int length);

private:
    int _tries;
    int _word_length;
    string _letters = "";
    string _word;
    vector <string> _words; //the dictionary
    vector <string> _words_temp; //a temp to narrow down dictionary
    vector<string> possibles; //the possible letter placings
    char _curr_letter;
    void _map_time();
    void _merge();
    void _recursed(char set[], int size, string filler);
    void _more_cursed(char set[], int size);
    vector<int> _find_locations(string s, char looking);

};

#endif
