/*
    hangman.cpp
        
    Method implementations for the hangman class.
    
    assignment: CSCI 262 Project - Evil Hangman        

    author: Alexa Nelson

    last modified: 3/7/2019
*/

#include "hangman.h"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// constructor
hangman::hangman() { 
    //Read in and store words from dictionary.txt
    word_count = false;
    _tries = 0;
    _curr_letter = 'a';
    string word;
    _word_length = 0;
    possibles.clear();
    ifstream dictionary("dictionary.txt");
    while ( dictionary >> word){
        _words.push_back(word);
    }
}

//this will recursively find all possible letter combinations you can make with the remaining spaces
void hangman::_recursed(char set[], int size, string filler) {
    if (size == 0){ //base case once temp has been filled
        possibles.push_back(filler);
        return;
    }
    for (int i = 0; i < 2; i++){
        string new_filler = filler + set[i];
        _recursed(set, size-1, new_filler);
    }
}
void hangman::_more_cursed(char set[], int size) {
    _recursed(set, size, "");
}
//will return a vector of 0's and 1's that indicate where the words that match are
vector<int> hangman::_find_locations(string s, char looking) {
    vector<int> locations; //the vector we return
    for(int i = 0; i < s.size(); i++){
        if(s[i] == looking){
            locations.push_back(1);
        }else {
            locations.push_back(0);
        }
    }
    return locations;
}

//maps all possible partial word combinations with words that fit each keys criteria
void hangman::_map_time() {
    vector<int> temp1;//temp for possible letter placing
    vector<int> temp2;//temp for words in dict that match same criteria
    int max = 0;

    for (int i = 0; i < possibles.size(); i++){ //every string in possibles
        vector<string> key_words = {};//the words to add to each key
        temp1 = _find_locations(possibles[i], _curr_letter);
        for (int x = 0; x < _words.size(); x++){ //every word in dict
            temp2 = _find_locations(_words[x], _curr_letter);
            if(temp1 == temp2){
                key_words.push_back(_words[x]);
            }
        }
        if (key_words.size() > max){
            _words_temp.clear();
            max = key_words.size();
            _words_temp = key_words;
            _word = possibles[i];
        }
    }
    _words.clear();
    _words = _words_temp;

}
void hangman::_merge() {
    vector<int> places;
    vector <string> possibles_temp = possibles;
    for (int i = 0; i < possibles_temp.size(); i++){
        possibles_temp[i] = _word;
    }
    for(int i = 0; i < _word.size(); i++) { //find the empty spaces in the word
        if (_word[i] == '-') {
            places.push_back(i);
        }
    }

    for (int i = 0; i < places.size(); i++){
        string temp = _word;
        int place = places[i];
        for (int j = 0; j < possibles.size(); j++){
            possibles_temp[j].at(place) = possibles[j].at(place);
        }
    }

    possibles.clear();
    possibles = possibles_temp;

}


// start_new_game()
//
// Setup a new game of hangman.
void hangman::start_new_game(int num_guesses, int word_length) {
    _tries = num_guesses;
    _word_length = word_length;
    for(int i = 0; i < word_length; i++){ //initialize the blank word
        _word+= "-";
    }
    for (int i = 0; i < _words.size(); i++){
        if (_words[i].size() == _word_length){
            _words_temp.push_back(_words[i]); //only stores words that are the right length
        }
    }
    _words = _words_temp;//make _words the main again
    _words_temp.clear();//make temp ready to reuse
}


// process_guess()
//
// Process a player's guess - should return true/false depending on whether
// or not the guess was in the hidden word.  If the guess is incorrect, the
// remaining guess count is decreased.
bool hangman::process_guess(char c) {
    _curr_letter = c;
    _letters += c;
    char set[] = {c, '-'};
    int recursive = _word_length;
    possibles.clear(); //clear before each guess
    _more_cursed(set, recursive);//calls the recursive function
    _merge(); //merge the word with new possible words
    _map_time(); //maps possible families after recursion called
    for(int i = 0; i < _word.size(); i++){
        if(_word[i] == c){
            return true;
        }
    }
    _tries --;
    return false;
}


// get_display_word()
//
// Return a representation of the hidden word, with unguessed letters
// masked by '-' characters.
string hangman::get_display_word() {
    return _word;
}


// get_guesses_remaining()
//
// Return the number of guesses remaining for the player.
int hangman::get_guesses_remaining() {
    return _tries;
}


// get_guessed_chars()
//
// What letters has the player already guessed?  Return in alphabetic order.
string hangman::get_guessed_chars() {
    sort(_letters.begin(), _letters.end());
    return _letters;
}


// was_char_guessed()
//
// Return true if letter was already guessed.
bool hangman::was_char_guessed(char c) {
    return _letters.find(c) != string::npos;
}


// is_won()
//
// Return true if the game has been won by the player.
bool hangman::is_won() {
    for (int i = 0; i < _word_length; i++){
        if (_word[i] == '-'){
            return false;
        }
    }
    cout << _word;
    return true;
}


// is_lost()
//
// Return true if the game has been lost.
bool hangman::is_lost() {
    return _tries == 0;
}


// get_hidden_word
//
// Return the true hidden word to show the player.
string hangman::get_hidden_word() {
    return _words[0];
}

int hangman::get_word_fam() {
    return _words.size();
}

bool hangman::find_word_of_length(int length) {
    for (int i = 0; i < _words.size(); i++){
        if(_words[i].size() == length){
            return true;
        }
    }
    return false;
}

