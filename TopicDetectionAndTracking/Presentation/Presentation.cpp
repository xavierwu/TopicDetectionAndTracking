#include "Presentation.h"

void Presentation (const vector<Story> &firstStories, const map<int, string> &glossary)
{
	for (const Story curStory : firstStories)
		cout << curStory.getTopicID () << " " << curStory.toString (glossary) << endl;
}