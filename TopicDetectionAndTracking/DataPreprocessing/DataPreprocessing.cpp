#include "DataPreprocessing.h"

/* Set 'corpus' and 'glossary', and do some other preprocessing */
void DataPreprocessing (vector<Story> &corpus,
						map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
						const string &tkn_file, const string &bnd_file, const bool &isWithStemmer)
{
	cout << "> Start DataPreprocessing......" << endl;

	readCorpus (corpus, glossaryIntToString, glossaryStringToInt, tkn_file, bnd_file, isWithStemmer);

	/* Calculate the tfidf, and save it. */
	//	Story::setTFIDFOfCorpus (corpus);
	//	Story::saveTFIDF (corpus, "Dataset/tfidf.dat");

	/* Load the tfidf from file, pls make sure the file exist.  */
	Story::loadTFIDF (corpus, "Dataset/tfidf.dat");

	cout << "> DataPreprocessing Done." << endl;
}

void readCorpus (vector<Story> &corpus,
				 map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
				 const string &tkn_file, const string &bnd_file, const bool &isWithStemmer)
{
	cout << ">> Start reading corpus......" << endl;

	if (!isWithStemmer) {
		// the id of the first and the last words of a story
		vector<int> Brecid;
		vector<int> Erecid;

		readBndFile (corpus, bnd_file, Brecid, Erecid);

		readTknFile (corpus, tkn_file, Brecid, Erecid, glossaryIntToString, glossaryStringToInt);
	} else { // TODO: (optional) add a stemmer to the readCorpus(...) ?
	}

	cout << ">> Reading corpus done." << endl;
}

void readBndFile (vector<Story> &corpus, const string &bnd_file, vector<int> &Brecid,
				  vector<int> &Erecid)
{
	int numOfStories = 0;

	ifstream fin (bnd_file, ios::in);
	assert (fin.is_open ());

	// the first line is title, and it is of no use, so try to work hard to be a useful man
	string titleUseless;
	getline (fin, titleUseless);

	// for each line, if simply use fin, we can get 5 strings:
	// 1. "<BOUNDARY",  useless
	// 2. "docno=CNA + timestamp", the timestamp should be retrieved
	// 3. "doctype=NEWS", useless maybe
	// 4. "Brecid=?", very important
	// 5. "Erecid=?>", very important
	string boundaryUseless;
	while (fin >> boundaryUseless) {
		string timestamp, doctypeUseless;

		// because they are not only Brecid and Erecid, so they are called as follows
		char BrecidWithRedundancy[15] = { };
		char ErecidWithRedundancy[15] = { };

		// the follows are real Brecid and Erecid
		int BrecidInt, ErecidInt;

		fin >> timestamp >> doctypeUseless >> BrecidWithRedundancy >> ErecidWithRedundancy;

		// retrieve the timestamp
		timestamp = timestamp.substr (9, timestamp.length () - 9);

		// use "=" to split the string
		const char *split = "=";

		// point to the real Brecid and Erecid
		char *pid;

		pid = strtok (BrecidWithRedundancy, split);
		pid = strtok (NULL, split);

		// convert char* to int
		BrecidInt = atoi (pid);

		pid = strtok (ErecidWithRedundancy, split);
		pid = strtok (NULL, split);

		ErecidInt = atoi (pid);

		vector<int> words;
		Story newStory (numOfStories, words, timestamp);
		corpus.push_back (newStory);
		numOfStories++;

		Brecid.push_back (BrecidInt);
		Erecid.push_back (ErecidInt);
	}

	fin.close ();
}

void readTknFile (vector<Story> &corpus, const string &tkn_file,
				  const vector<int> &Brecid, const vector<int> &Erecid,
				  map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt)
{

	ifstream fin (tkn_file, ios::in);
	assert (fin.is_open ());

	// the first line is title, and it is of no use, so try to work hard again to be a useful man
	string titleUseless;
	getline (fin, titleUseless);

	// for each line, if simply use fin, we can get 4 strings:
	// 1. "<W",  useless
	// 2. "recid=?", since the recid increases by one, so we can just count to know the value of "?"
	// 3. "tr=Y", it is of no use currently
	// 4. word, very important
	int recid = 1;
	int numOfStories = 0;
	string _WUseless;
	while (fin >> _WUseless) {
		string recidWithRedundancy, TrUseless, word;

		if (recid > Erecid[numOfStories]) {
			numOfStories++;
		}

		fin >> recidWithRedundancy >> TrUseless >> word;

		processWord (word);

		addWordToGlossary (word, glossaryIntToString, glossaryStringToInt);

		corpus[numOfStories].addWord (glossaryStringToInt[word]);

		recid++;
	}

	fin.close ();
}

void processWord (string &word)
{
	int len = word.length ();

	for (int i = 0; i < len; i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] -= ('A' - 'a');
		} else if (word[i] < 'a' || word[i] > 'z') {
			// if you can't figure out, just give up
			word = word.substr (0, i) + word.substr (i + 1, word.length () - (i + 1));
			i--;
			len--;
		}
	}
}

void addWordToGlossary (const string &word, map<int, string> &glossaryIntToString,
						map<string, int> &glossaryStringToInt)
{
	if (glossaryStringToInt.find (word) == glossaryStringToInt.end ()) {
		int index = glossaryStringToInt.size ();
		glossaryStringToInt[word] = index;
		glossaryIntToString[index] = word;
	}
}
