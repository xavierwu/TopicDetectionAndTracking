#include "Presentation.h"

void Presentation (const vector<Story> &firstStories, const vector<Story> &corpus,
				   const map<int, string> &glossary, const int &numOfTopics)
{
	cout << "> Start presenting......" << endl;
	printClusters (corpus, glossary, numOfTopics, false);
	cout << "> Presenting done. " << endl;
}

void printFirstStories (const vector<Story> &firstStories, const map<int, string> &glossary,
						const bool &isPrintItAll)
{
	for (const Story &curStory : firstStories) {
		cout << curStory.getTopicID () << endl;
		if (isPrintItAll)
			cout << curStory.toString (glossary) << endl;
		else
			cout << curStory.getTimeStamp () << endl;
	}
}

void printClusters (const vector<Story> &corpus, const map<int, string> &glossary,
					const int &numOfTopics, const bool &isPrintItAll)
{
	for (int curTopic = 0; curTopic < numOfTopics; ++curTopic) {
		cout << curTopic << endl;
		for (const Story &curStory : corpus) {
			if (curStory.getTopicID () == curTopic) {
				if (isPrintItAll)
					cout << curStory.toString (glossary) << endl;
				else
					cout << curStory.getTimeStamp () << endl;
			}
		}
	}
}