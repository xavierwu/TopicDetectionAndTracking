/* This is file is put in the directory 'Utilities' because this file is public among
the system. If there is any change of directory 'Utilities', notify all authors.  */

#ifndef STORY_H
#define STORY_H

#include "Utilities.h"

/* Default value of 'topicID', meaning the story is clustered.
Please AVOID using it outside 'Story.h' and 'Story.cpp'. */
#define DEFAULT_TOPIC_ID -1
/* Default value of 'storyID', meaning the story is just a tmp story.
Please AVOID using it outside 'Story.h' and 'Story.cpp'. */
#define DEFAULT_STORY_ID -1

class Story
{
private:
	int storyID = DEFAULT_STORY_ID;
	vector<int> words; // the index of each plain word, refer to the glossary
	string timeStamp; // yyyymmdd.ttmm.XXX
	int topicID = DEFAULT_TOPIC_ID;
	// <word id, times it appears in this story>. Before using, make sure setWordsCount is invoked. 
	map<int, int> wordsCount;
	// <word id, term frequency>. Before using, make sure setTermFrequency() is invoked. 
	map<int, double> termFrequency;
	// <word id, tfidf>. Before using, make sure setTFIDFBasedOnCorpus() is invoked
	map<int, double> tfidf;
	//	vector<string> words_s; // unused since we have already the glossary and index of plain word. 

public:
	/* UNSUGGESTED: Default constructor. */
	Story ();
	/* The first two parameters are necessary */
	Story (int storyID, vector<int> words, string timeStamp);

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

	/* Get 'tfidf', before using, you'd better call setTFIDFBasedOnCorpus() first. */
	void getTFIDF (map<int, double> &tfidf) const;
	/* Set 'tfidf' */
	void setTFIDF (const map<int, double> &tfidf);
	/* To calculate tfidf for a certain story, we have to refer to a corpus. */
	void setTFIDFBasedOnCorpus (const vector<Story> &corpus, 
								const map<int, vector<int>> &storiesIndexWithCertainWord);

	/* add word to 'words' */
	void addWord (int wordIndex);

	/* return the length of the story, i.e., the length of 'words' */
	int getLength () const;

	/* return timestamp and words */
	string toString (const map<int, string> &glossary) const;

	/* return true if this story contains a certain word. */
	bool isWordExisted (int wordID) const;

	/* return true if the story is already clustered. */
	bool isClustered () const;

	/* Set 'tfidf' for all stories in corpus. */
	static void setTFIDFOfCorpus (vector<Story> &corpus, 
								  const map<int, vector<int>> &storiesIndexWithCertainWord);
	/* Save the tfidf's of corpus to tfidfFile */
	static void saveTFIDF (const vector<Story> &corpus, const string &tfidfFile);
	/* Load the tfidf's of corpus from tfidfFile */
	static void loadTFIDF (vector<Story> &corpus, const string &tfidfFile);
};

#endif