#include "Presentation.h"

void Presentation (const vector<Story> &firstStories, const vector<Story> &corpus,
				   const map<int, string> &glossary)
{
	cout << "> Start presenting......" << endl;
	for (const Story curStory : firstStories)
		cout << curStory.getTopicID () << "\n" << curStory.toString (glossary) << endl;
	cout << "> Presenting done. " << endl;
}