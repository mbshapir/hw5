// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void rolling(const std::set<std::string>& dict, std::set<std::string>& optionsList, size_t count, std::string in, std::string floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		size_t count = 0;
		std::set<std::string> optionsList;
		rolling(dict, optionsList, count, in, floating);
		return optionsList;
}

// Define any helper functions here
void rolling(const std::set<std::string>& dict, std::set<std::string>& optionsList, size_t count, std::string in, std::string floating){

	string adjustableFLList = floating; //must make seperate var so we can cut down on list when letters are used

	if(in[count] != '-' && in.size() != count){ //check if current space is a dash - if not and we are not at the end of the word, move up one letter
		rolling(dict, optionsList, count+1, in, adjustableFLList);
		return;
	}

	if(in.size() == count && adjustableFLList.empty() && dict.find(in) != dict.end()){ // check if we are at the end of word and no floating letters left and word in dictionary
			optionsList.insert(in); //if all above true, add current word to output list
	}else if(in.size() == count && adjustableFLList.empty() && dict.find(in) == dict.end()){ //if at end of word and no floating letters left, but word not in dictionary
		return; //continue without adding word to ouput set
	}

	unsigned int dashCount = 0;
	unsigned int counter = 0;
	while(counter < in.size()){ //see how many dashes currently in word
		if(in[counter] == '-'){
			dashCount++;
		}
		counter++;
	}

	if(dashCount <= adjustableFLList.size()){ //if there are less or equal dashes to floating letters, we know only floating letters are left
		for(unsigned int i = 0; i < adjustableFLList.size(); i++){ //iterate through all floating letters
			string temp = adjustableFLList;
			in[count] = adjustableFLList[i];
			temp.erase(i, 1);
			rolling(dict, optionsList, count+1, in, temp);
		}
	}else{ //there are places we will need to guess letters asides from the floating ones
		for(int i = 97; i <= 122; i++){ //iterate through ascii values for lowercase letters
				if((int)adjustableFLList.find(char(i)) != -1){
					string temp = adjustableFLList;
					in[count] = char(i);
					temp.erase(adjustableFLList.find(char(i)), 1);
					rolling(dict, optionsList, count+1, in, temp);
				}else{
					in[count] = char(i);
					rolling(dict, optionsList, count+1, in, adjustableFLList);
				}
		}
	}

}