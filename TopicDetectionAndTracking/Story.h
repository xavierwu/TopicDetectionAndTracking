#ifndef STORY_H
#define STORY_H

#include "Utilities.h"

class Story
{
private:
//	vector<string> words_s; // the remaining words after stemming
	vector<int> words; // the index of each word of 'words_s', refer to the glossary
	int topicID = -1;
	string timeStamp;
	
public:
	Story();
	~Story();
	
	void setWords(vector<int> &words);
	vector<int> getWords() const;
	void setWord(int index); // operation on 'words'
	int getWord(int index) const; // operation on 'words' 
	void setTopicID(int topicID);
	int getTopicID() const;
	void setTimeStamp(const string &timeStamp);
	string getTimeStamp() const;
};

#endif
