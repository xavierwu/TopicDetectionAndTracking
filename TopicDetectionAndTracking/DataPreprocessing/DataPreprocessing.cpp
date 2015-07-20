#include "DataPreprocessing.h"

/* Set 'corpus' and 'glossary', and do some other preprocessing */
void DataPreprocessing(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool isWithStemmer)
{
	readCorpus(corpus, glossary, tkn_file, bnd_file, isWithStemmer);
	// TODO: maybe you still need to do something other than reading corpus & glossary?
}

void readCorpus(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool isWithStemmer)
{
	if (!isWithStemmer) {
		// TODO: read corpus
	} else { // OPTIONAL
	}
}
