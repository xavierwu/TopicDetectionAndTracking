#include "Story.h"

Story::Story (int storyID, const vector<int> words, const string &timeStamp, int topicID)
	: storyID (storyID), words (words), timeStamp (timeStamp), topicID (topicID)
{
}

/* Set & get storyID */
//// Unused. The storyID should be set only once, when the story is created. 
//void Story::setStoryID (int storyID) 
//{
//	this->storyID = storyID;
//}

int Story::getStoryID () const
{
	return this->storyID;
}

/* Set & get words, the whole vector. */
//// Unused. The words should be set only once, when the story is created. 
//void Story::setWords (vector<int> &words) 
//{
//	this->words = words;
//}

vector<int> Story::getWords () const
{
	return this->words;
}

/* Set & get words[index], a specific element in the vector. */
//// Unused. The words should be set only once, when the story is created. 
//void Story::setWord (int index, int value)
//{
//	this->words[index] = value;
//}

int Story::getWord (int index) const
{
	return this->words[index];
}

/* Set & get timeStamp */
void Story::setTimeStamp (const string &timeStamp)
{
	this->timeStamp = timeStamp;
}

string Story::getTimeStamp () const
{
	return this->timeStamp;
}

/* Set & get topicID */
void Story::setTopicID (int topicID)
{
	this->topicID = topicID;
}

int Story::getTopicID () const
{
	return this->topicID;
}