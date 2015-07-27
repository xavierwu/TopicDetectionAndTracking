#include "DataPreprocessing.h"

const int MAX_FILES = 999999;

/* Set 'corpus' and 'glossary', and do some other preprocessing */
void DataPreprocessing (vector<Story> &corpus,
						map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
						map<int, set<int>> &storiesIndexWithCertainWord,
						const string tknDir, const string bndDir,
						const bool &isWithStemmer)
{
	cout << "> Start DataPreprocessing......" << endl;

	readCorpus (corpus, glossaryIntToString, glossaryStringToInt, storiesIndexWithCertainWord, tknDir,
				bndDir, isWithStemmer);

	cout << "> DataPreprocessing Done." << endl;
}

void readCorpus (vector<Story> &corpus,
				 map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
				 map<int, set<int>> &storiesIndexWithCertainWord,
				 const string tknDir, const string bndDir, const bool &isWithStemmer)
{
	cout << ">> Start reading corpus......" << endl;

	if (!isWithStemmer) {
		cout << "Please choose" << endl;
		cout << "1. Read from the specific file" << endl;
		cout << "2. Read from files in the directory" << endl;

		char choice;
		cin >> choice;

		while (true) {
			fflush (stdin);
			if (choice == '1') {
				readCorpusFromFile (corpus, glossaryIntToString, glossaryStringToInt,
									storiesIndexWithCertainWord, tknDir, bndDir, isWithStemmer);
				break;
			} else if (choice == '2') {
				readCorpusFromDirectory (corpus, glossaryIntToString, glossaryStringToInt,
										 storiesIndexWithCertainWord, tknDir, bndDir, isWithStemmer);
				break;
			} else {
				cout << "Invalid input, please input again!" << endl;
				cin >> choice;
			}
		}

	} else { // TODO: (optional) add a stemmer to the readCorpus(...) ?
	}

	cout << ">> Reading corpus done." << endl;
}

void readCorpusFromFile (vector<Story> &corpus,
						 map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
						 map<int, set<int>> &storiesIndexWithCertainWord,
						 const string tknDir, const string bndDir, const bool &isWithStemmer)
{

	while (true) {
		// the id of the first and the last words of a story
		vector<int> Brecid;
		vector<int> Erecid;

		string bndFile, tknFile;

		cout << "Please input the file name of bnd file" << endl;
		cin >> bndFile;
		bndFile = bndDir + bndFile;

		cout << "Please input the file name of tkn file" << endl;
		cin >> tknFile;
		tknFile = tknDir + tknFile;

		readBndFile (corpus, bndFile, Brecid, Erecid);

		readTknFile (corpus, tknFile, Brecid, Erecid, glossaryIntToString, glossaryStringToInt, storiesIndexWithCertainWord);

		cout << "Continue?(Y/N)" << endl;

		char choice;
		cin >> choice;


REJUDGE:	fflush (stdin);
		if (choice == 'Y' || choice == 'y') {
			continue;
		} else if (choice == 'N' || choice == 'n') {
			break;
		} else {
			cout << "Invalid input, please input again!" << endl;
			cin >> choice;
			goto REJUDGE;
		}

	}
}

void readCorpusFromDirectory (vector<Story> &corpus, map<int, string> &glossaryIntToString,
							  map<string, int> &glossaryStringToInt,
							  map<int, set<int>> &storiesIndexWithCertainWord,
							  const string tknDir, const string bndDir, const bool &isWithStemmer)
{
	_finddata_t file;
	long lf;

	// the id of the first and the last words of a story
	vector<int> Brecid;
	vector<int> Erecid;

	string bnd = bndDir.c_str ();
	bnd += "*.*";
	string tkn = tknDir.c_str ();
	tkn += "*.*";

	int numOfFileTobeRead = 0;
	int numOfFilesRead = 0;

	cout << "Input the number of files want to be read (0 represents all)" << endl;
	cin >> numOfFileTobeRead;

	if (numOfFileTobeRead == 0) {
		numOfFileTobeRead = MAX_FILES;
	}

	if ((lf = _findfirst (bnd.c_str (), &file)) == -1l)
		cout << "No bnd file found!" << endl;
	else {
		// the first file name found is "..", so drop it
		bool firsFileIsGhost = true;
		while (_findnext (lf, &file) == 0 && numOfFilesRead < numOfFileTobeRead) {
			if (!firsFileIsGhost) {
				cout << file.name << "	found" << endl;

				string bndFile (file.name);
				bndFile = bndDir + bndFile;

				readBndFile (corpus, bndFile, Brecid, Erecid);
				numOfFilesRead++;
			}
			firsFileIsGhost = false;
		}
	}

	numOfFilesRead = 0;
	if ((lf = _findfirst (tkn.c_str (), &file)) == -1l)
		cout << "No tkn file found!" << endl;
	else {
		bool firsFileIsGhost = true;
		while (_findnext (lf, &file) == 0 && numOfFilesRead < numOfFileTobeRead) {
			if (!firsFileIsGhost) {
				cout << file.name << "	found" << endl;

				string tknFile (file.name);
				tknFile = tknDir + tknFile;

				readTknFile (corpus, tknFile, Brecid, Erecid, glossaryIntToString, glossaryStringToInt, storiesIndexWithCertainWord);
				numOfFilesRead++;
			}
			firsFileIsGhost = false;
		}
	}

	_findclose (lf);

}

void readBndFile (vector<Story> &corpus, const string bndFile, vector<int> &Brecid,
				  vector<int> &Erecid)
{
	int numOfStories = 0;

	ifstream fin (bndFile, ios::in);
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

	cout << "read bnd file done!" << endl;
}

void readTknFile (vector<Story> &corpus, const string tknFile,
				  const vector<int> &Brecid, const vector<int> &Erecid,
				  map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
				  map<int, set<int>> &storiesIndexWithCertainWord)
{

	ifstream fin (tknFile, ios::in);
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

		// this means a new tkn file is read
		if (Brecid[numOfStories] == 1)
			recid = 1;

		if (recid > Erecid[numOfStories]) {
			numOfStories++;
		}

		fin >> recidWithRedundancy >> TrUseless >> word;

		processWord (word);

		addWordToGlossary (word, glossaryIntToString, glossaryStringToInt);

		int wordID = glossaryStringToInt[word];
		corpus[numOfStories].addWord (wordID);
		storiesIndexWithCertainWord[wordID].insert (numOfStories);

		recid++;
	}

	fin.close ();

	cout << "read tkn file done!" << endl;
}

void processWord (string &word)
{
	int len = word.length ();

	for (int i = 0; i < len; i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] -= ('A' - 'a');
		} else if (word[i] >= '0' && word[i] <= '9') {
			continue;
		} else if (word[i] == '.' || word[i] == '-') {
			continue;
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
