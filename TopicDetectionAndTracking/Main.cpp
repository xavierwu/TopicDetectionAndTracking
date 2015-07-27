/* Author: Zewei Wu, Zitong Wang, Zhaoqi Wang, Peng Kang */

#include "DataPreprocessing/DataPreprocessing.h"
#include "StoryLinkDetection/StoryLinkDetection.h"
#include "TopicDetection/TopicDetection.h"
#include "FirstStoryDetection/FirstStoryDetection.h"
#include "Evaluation/Evaluation.h"
#include "Presentation/Presentation.h"

int main (int argc, char **argv)
{
	vector<Story> corpus;
	vector<Story> firstStories;
	/* <wordID, plain word> */
	map<int, string> glossaryIntToString;
	/* <plain word, wordID> */
	map<string, int> glossaryStringToInt;
	/* <wordID, vector of stories' indices in corpus> */
	map<int, set<int>> storiesIndexWithCertainWord;

	// 	string tkn_file = "Dataset/mttkn/20030402_0530_0700_CNA_MAN.mttkn";
	// 	string bnd_file = "Dataset/mttkn_bnd/20030402_0530_0700_CNA_MAN.mttkn_bnd";
	string tknDir = "Dataset/mttkn/";
	string bndDir = "Dataset/mttkn_bnd/";

	DataPreprocessing (corpus, glossaryIntToString, glossaryStringToInt, storiesIndexWithCertainWord,
					   tknDir, bndDir);

	cout << "corpus.size() = " << corpus.size () << endl;
	assert (corpus.size () > 0);
	cout << "glossaryIntToString.size () = " << glossaryIntToString.size () << endl;
	assert (glossaryIntToString.size () > 0);
	cout << "glossaryStringToInt.size () = " << glossaryStringToInt.size () << endl;
	assert (glossaryStringToInt.size () > 0);
	assert (glossaryIntToString.size () == glossaryStringToInt.size ());
	cout << "storiesIndexWithCertainWord.size () = " << storiesIndexWithCertainWord.size () << endl;
	assert (storiesIndexWithCertainWord.size () > 0);

	StoryLinkDetection (corpus, storiesIndexWithCertainWord);

	int numOfTopics = 0;
	TopicDetection (corpus, numOfTopics);
	
	cout << "numOfTopics = " << numOfTopics << endl;
	assert (numOfTopics > 0);

	FirstStoryDetection (firstStories, corpus, numOfTopics);

	cout << "firstStories.size() = " << firstStories.size () << endl;
	assert (firstStories.size () == numOfTopics);

	Presentation (firstStories, corpus, glossaryIntToString, numOfTopics);

	return 0;
}
