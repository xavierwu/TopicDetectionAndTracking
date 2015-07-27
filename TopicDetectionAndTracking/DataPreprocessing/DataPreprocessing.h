/* Retrieve data from existed files (tkn_file & bnd_file), and do some pre-processing.  */

#ifndef DATA_PREPROCESSING_H
#define DATA_PREPROCESSING_H

#include "../Utilities/Story.h"

/* Read from files, set the 'corpus' and 'glossary', and do some other preprocessing.
Input: 'tkn_file', 'bnd_file', 'isWithStemmer'
Output: 'corpus', 'glossaryIntToString', 'glossaryStringToInt'
*/
void DataPreprocessing (vector<Story> &corpus,
						map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
						const string &tkn_file, const string &bnd_file,
						const bool &isWithStemmer = false);

/* Read from files, set the 'corpus' and 'glossary'.
Input: 'tkn_file', 'bnd_file', 'isWithStemmer'
Output: 'corpus', 'glossaryIntToString', 'glossaryStringToInt'
*/
void readCorpus (vector<Story> &corpus,
				 map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt,
				 const string &tkn_file, const string &bnd_file, const bool &isWithStemmer = false);

/* Read from bnd files to get the begin and the end of a story.
Input: 'bnd_file'
Output: 'corpus', 'Brecid', 'Erecid' */
void readBndFile (vector<Story> &corpus, const string &bnd_file,
				  vector<int> &Brecid, vector<int> &Erecid);

/* Read from bnd files, get the words for each story and set the glossary.
Input: 'tkn_file', 'Brecid', 'Erecid'
Output: 'corpus', 'glossaryIntToString', 'glossaryStringToInt' */
void readTknFile (vector<Story> &corpus, const string &tkn_file,
				  const vector<int> &Brecid, const vector<int> &Erecid,
				  map<int, string> &glossaryIntToString, map<string, int> &glossaryStringToInt);

/* Process the word, remove punctuations and convert all the letters to lowercase
Input: 'word'
Output: 'word' */
void processWord (string &word);

/* add the word to glossary if the word does not exist
Input: 'word'
Output: 'glossaryIntToString', 'glossaryStringToInt' */
void addWordToGlossary (const string &word, map<int, string> &glossaryIntToString,
						map<string, int> &glossaryStringToInt);

#endif/* Retrieve data from existed files (tkn_file & bnd_file), and do some pre-processing.  */