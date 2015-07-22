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
	// <word id, times it appears in this story>. Before using, make sure setWordsCount is invoked. 
	map<int, int> wordsCount; 
	// <word id, term frequency>. Before using, make su/* This is file is put in the directory 'Utilities' because this file is public among
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
	// <word id, times it appears in this story>. Before using, make sure setWordsCount is invoked. 
	map<int, int> wordsCount; 
	// <word id, term frequency>. Before using, make sure setTermFrequency() is invoked. 
	map<int, double> termFrequency; 
	// <word id, tfidf>. Before using, make sure setTFIDF() is invoked
	map<int, double> tfidf; 
	//	vector<string> words_s; // unused since we have already the glossary and index of plain word. 

public:
	/* The first two parameters are necessary, so we dont use default constructor. */
	Story (int storyID, const vector<int> words, const string &timeStamp, int topicID = UNCLUSTERED);

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

	/* Get 'wordsCount', before using, you'd better call setWordsCount() first. */
	void getWordsCount (map<int, int> &wordsCount) const;
	/* Set 'wordsCount' */
	void setWordsCount ();

	/* Get 'termFrequency', before using, you'd better call setTermFrequency() first. */
	void getTermFrequency (map<int, double> &termFrequency) const;
	/* Set 'termFrequency' */
	void setTermFrequency ();

	/* Get 'tfidf', before using, you'd better call setTFIDF() first. */
	void getTFIDF (map<int, double> &tfidf) const;
	/* Set 'tfidf' */
	void setTFIDF (const vector<Story> &corpus);

	/* return the length of the story, i.e., the length of 'words' */
	int getLength () const;

	/* return true if this story contains a certain word. */
	bool isWordExisted (int wordID) const;

	/* return timestamp and words */
	string toString (const vector<string> &glossary) const;

	/* add word to words */
	void addWord(int wordIndex);
};

#endif
re setTermFrequency() is invoked. 
	map<int, double> termFrequency; 
	// <word id, tfidf>. Before using, make sure setTFIDF() is invoked
	map<int, double> tfidf; 
	//	vector<string> words_s; // unused since we have already the glossary and index of plain word. 

public:
	/* The first two parameters are necessary, so we dont use default constructor. */
	Story (int storyID, const vector<int> words, const string &timeStamp, int topicID = UNCLUSTERED);

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

	/* Get 'wordsCount', before using, you'd better call setWordsCount() first. */
	void getWordsCount (map<int, int> &wordsCount) const;
	/* Set 'wordsCount' */
	void setWordsCount ();

	/* Get 'termFrequency', before using, you'd better call setTermFrequency() first. */
	void getTermFrequency (map<int, double> &termFrequency) const;
	/* Set 'termFrequency' */
	void setTermFrequency ();

	/* Get 'tfidf', before using, you'd better call setTFIDF() first. */
	void getTFIDF (map<int, double> &tfidf) const;
	/* Set 'tfidf' */
	void setTFIDF (const vector<Story> &corpus);

	/* return the length of the story, i.e., the length of 'words' */
	int getLength () const;

	/* return true if this story contains a certain word. */
	bool isWordExisted (int wordID) const;

	/* return timestamp and words */
	string toString (const vector<string> &glossary) const;
};

#endif
