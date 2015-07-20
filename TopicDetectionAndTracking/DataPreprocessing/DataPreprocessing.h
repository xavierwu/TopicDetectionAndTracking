/* Retrieve data from existed files (tkn_file & bnd_file), and do some pre-processing.  */

#ifndef DATA_PREPROCESSING_H
#define DATA_PREPROCESSING_H

#include "../Utilities/Story.h"

/* Read from files, set the 'corpus' and 'glossary', and do some other preprocessing.
Input: 'tkn_file', 'bnd_file', 'isWithStemmer'
Output: 'corpus', 'glossary' */
void DataPreprocessing(vector<Story> &corpus, vector<string> &glossary, 
	const string &tkn_file, const string &bnd_file, bool isWithStemmer = false);

/* Read from files, set the 'corpus' and 'glossary'.
Input: 'tkn_file', 'bnd_file', 'isWithStemmer'
Output: 'corpus', 'glossary' */
void readCorpus(vector<Story> &corpus, vector<string> &glossary,
	const string &tkn_file, const string &bnd_file, bool isWithStemmer = false);

#endif