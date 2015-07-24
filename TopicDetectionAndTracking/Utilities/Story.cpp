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

/* Set 'tfidf', based on corpus */
void Story::setTFIDF (const vector<Story> &corpus)
{
	if (this->termFrequency.empty ())
		this->setTermFrequency ();

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

void Story::copyTFIDF (const map<int, double> &tfidf)
{
	this->tfidf.clear ();
	this->tfidf = tfidf;
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

string Story::toString (const map<int, string> &glossary) const
{
	string result = "";
	result += this->timeStamp;
	for (const int wordID : this->words)
		if (glossary.find (wordID) != glossary.cend ())
			result += " " + glossary.find (wordID)->second;
	return result;
}

void Story::addWord (int wordIndex)
{
	words.push_back (wordIndex);
}

bool Story::isClustered () const
{
	return topicID != UNCLUSTERED;
}

void Story::setTFIDFOfCorpus (vector<Story> &corpus)
{
	cout << ">> Start calculating tfidf of corpus......" << endl;
	for (unsigned count = 0; count < corpus.size (); ++count) {
		if (count % 10 == 0)
			cout << count << " / " << corpus.size () << endl;
		corpus[count].setTFIDF (corpus);
	}
	cout << ">> Calculating tfidf's done." << endl;
}

/* Save the tfidf's of corpus to tfidfFile */
void Story::saveTFIDF (const vector<Story> &corpus, const string &tfidfFile)
{
	cout << "> Start saving tfidf......" << endl;
	ofstream fout (tfidfFile, ios::out);
	for (const Story &story : corpus) {
		map<int, double> tfidf;
		story.getTFIDF (tfidf);
		for (map<int, double>::const_iterator citer = tfidf.cbegin ();
			 citer != tfidf.cend (); ++citer)
			 fout << citer->first << ":" << citer->second << " ";
		fout << endl;
	}
	fout.close ();
	cout << "> Saving tfidf done. " << endl;
}

/* Load the tfidf's of corpus from tfidfFile */
void Story::loadTFIDF (vector<Story> &corpus, const string &tfidfFile)
{
	cout << "> Start loading tfidf......" << endl;
	ifstream fin (tfidfFile, ios::in);
	string line = "";
	map<int, double> tfidf;
	stringstream ss;
	int key;
	double value;
	int i = 0;
	while (std::getline (fin, line)) {
		tfidf.clear ();
		ss.clear ();
		ss << line;
		while (ss >> key) {
			ss.get ();
			ss >> value;
			tfidf[key] = value;
		}
		corpus[i++].copyTFIDF (tfidf);
	}
	fin.close ();
	cout << "> Loading tfidf done. " << endl;
}