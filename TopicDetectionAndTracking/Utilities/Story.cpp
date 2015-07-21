#include "Story.h"

Story::Story (int storyID, const vector<int> words, const string &timeStamp, int topicID)
	: storyID (storyID), words (words), timeStamp (timeStamp), topicID (topicID)
{
}

int Story::getStoryID () const
{
	return this->storyID;
}

/* Set storyID */
//// Unused. The storyID should be set only once, when the story is created. 
//void Story::setStoryID (int storyID) 
//{
//	this->storyID = storyID;
//}

vector<int> Story::getWords () const
{
	return this->words;
}


/* Set words, the whole vector. */
//// Unused. The words should be set only once, when the story is created. 
//void Story::setWords (vector<int> &words) 
//{
//	this->words = words;
//}

int Story::getWord (int index) const
{
	return this->words[index];
}

/* Set words[index], a specific element in the vector. */
//// Unused. The words should be set only once, when the story is created. 
//void Story::setWord (int index, int value)
//{
//	this->words[index] = value;
//}

/* Set & get timeStamp */
string Story::getTimeStamp () const
{
	return this->timeStamp;
}

void Story::setTimeStamp (const string &timeStamp)
{
	this->timeStamp = timeStamp;
}

/* Set & get topicID */
int Story::getTopicID () const
{
	return this->topicID;
}

void Story::setTopicID (int topicID)
{
	this->topicID = topicID;
}

/* Get 'wordsCount', simply invoke the assign operator */
void Story::getWordsCount (map<int, int> &wordsCount) const
{
	wordsCount = this->wordsCount;
}

/* Set 'wordsCount' */
void Story::setWordsCount ()
{
	for (int curWordID : this->words) {
		if (wordsCount.find (curWordID) == wordsCount.end ()) // curWordID not found
			wordsCount[curWordID] = 1;
		else // curWordID is found
			wordsCount[curWordID]++;
	}
}

/* Get 'termFrequency', simply invoke the assign operator */
void Story::getTermFrequency (map<int, double> &termFrequency) const
{
	termFrequency = this->termFrequency;
}

/* Set 'termFrequency' */
void Story::setTermFrequency ()
{
	if (this->wordsCount.empty ())
		this->setWordsCount ();

	double length = this->getLength ();
	for (map<int, int>::const_iterator iter = this->wordsCount.cbegin ();
		 iter != this->wordsCount.cend (); ++iter) {
		termFrequency[iter->first] = iter->second / length;
	}
}

/* Get 'tfidf', simply invoke the assign operator */
void Story::getTFIDF (map<int, double> &tfidf) const
{
	tfidf = this->tfidf;
}

/* Set 'tfidf' */
void Story::setTFIDF (const vector<Story> &corpus)
{
	this->tfidf = this->termFrequency;
	for (map<int, double>::iterator iter = this->tfidf.begin ();
		 iter != this->tfidf.end (); ++iter) {
		double idf = 0.0;
		double storiesWithWord = 0;
		for (const Story curStory : corpus)
			if (curStory.isWordExisted (iter->first))
				storiesWithWord++;
		idf = log (corpus.size () / storiesWithWord);
		iter->second *= idf;
	}
}

int Story::getLength () const
{
	return this->words.size ();
}

bool Story::isWordExisted (int wordID) const
{
	if (!this->wordsCount.empty ()) {
		return this->wordsCount.find (wordID) != this->wordsCount.cend ();
	} else {
		// Option 1: first build up the wordsCount, then use wordsCount.find()
		// Option 2: sort the words, then find (using the binary search)
		return std::find (this->words.cbegin (), this->words.cend (), wordID) != this->words.cend ();
	}
}

string Story::toString (const vector<string> &glossary) const
{
	string result = "";
	result += this->timeStamp;
	for (const int wordID : this->words)
		result += " " + glossary[wordID];
	return result;
}