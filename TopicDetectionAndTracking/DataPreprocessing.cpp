#include "DataPreprocessing.h"

/* Set 'corpus' and 'glossary', and do some other preprocessing */
void DataPreprocessing(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool withStemmer)
{
	readCorpus(corpus, glossary, tkn_file, bnd_file, withStemmer);
	// maybe you still need to do something other than reading corpus & glossary?
}

void readCorpus(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool withStemmer)
{
	if (!withStemmer) {
		// TODO: read corpus
	} else { // OPTIONAL
	}
}
