/* This is file is put in the directory 'Utilities' because this file is public among
the system. If there is any change of directory 'Utilities', notify all authors.  */

#ifndef STORY_H
#define STORY_H

#include "Utilities.h"

const int UNCLUSTERED = -1; // Default value of topicID, it means the story is unclusered. 

class Story
{
private:
	int storyID; // TODO: it might be same for two actually different stories, how to avoid it ?
	vector<int> words; // the index of each plain word, refer to the glossary
	string timeStamp; // TODO: the format of date and time is not yet determined. 
	int topicID = UNCLUSTERED;
	//	vector<string> words_s; // unused since we have already the glossary and index of plain word. 

public:
	/* The first two parameters are necessary, so we dont use default constructor. */
	Story (int storyID, const vector<int> words, const string &timeStamp = "", int topicID = UNCLUSTERED);

	/* Set & get storyID */
	//	void setStoryID (int storyID); // Unused. The storyID should be set only once, when the story is created. 
	int getStoryID () const;
	/* Set & get words, the whole vector. */
	//	void setWords (vector<int> &words); // Unused. The words should be set only once, when the story is created. 
	vector<int> getWords () const;
	/* Set & get words[index], a specific element in the vector. */
	//	void setWord (int index); // Unused. The words should be set only once, when the story is created. 
	int getWord (int index) const;
	/* Set & get timeStamp */
	void setTimeStamp (const string &timeStamp);
	string getTimeStamp () const;
	/* Set & get topicID */
	void setTopicID (int topicID);
	int getTopicID () const;
};

#endif
