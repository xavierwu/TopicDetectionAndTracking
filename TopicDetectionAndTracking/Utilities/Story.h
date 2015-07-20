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

	/* Get 'storyID' */
	int getStoryID () const;
	//// UNUSED: The storyID should be set only once, when the story is created.
	///* Set 'storyID'. */
	//void setStoryID (int storyID);

	/* Get words, the whole vector. */
	vector<int> getWords () const;
	//// UNUSED: The words should be set only once, when the story is created. 
	///* Set words, the whold vector. */
	//void setWords (vector<int> &words); 

	/* Get words[index], a specific element in the vector. */
	int getWord (int index) const;
	//// Unused. The words should be set only once, when the story is created. 
	///* Set words[index], a specific element in the vector. */
	//void setWord (int index);

	/* Get 'timeStamp' */
	string getTimeStamp () const;
	/* Set 'timeStamp' */
	void setTimeStamp (const string &timeStamp);

	/* Get topicID */
	int getTopicID () const;
	/* Set topicID */
	void setTopicID (int topicID);

	/* return the length of the story, i.e., the length of 'words' */
	int getLength () const;

	/* return a map, whose key is the wordID in the glossary and the value is
	 the times a term appears in this story. */
	void getTermCountMap (map<int, int> &termCountMap) const;

	/* termFrequenctMap would be set to include the frequency (in this story) of every word. 
	The key is wordID, and the value is frequency. */
	void getTermFrequencyMap (map<int, double> &termFrequencyMap) const;
};

#endif
