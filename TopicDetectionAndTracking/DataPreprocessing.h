/* Do some pre-processing on existed files. */

#ifndef DATA_PREPROCESSING_H
#define DATA_PREPROCESSING_H

#include "Story.h"

/* Read from files, set the 'corpus' and 'glossary', and do some other preprocessing.
Input: 'tkn_file', 'bnd_file', 'withStemmer'
Output: 'corpus', 'glossary' */
void DataPreprocessing(vector<Story> &corpus, vector<string> &glossary, 
	const string &tkn_file, const string &bnd_file, bool withStemmer = false);
/* Read from files, set the 'corpus' and 'glossary'.
Input: 'tkn_file', 'bnd_file', 'withStemmer'
Output: 'corpus', 'glossary' */
void readCorpus(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool withStemmer = false);

#endif