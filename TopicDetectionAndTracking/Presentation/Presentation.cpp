#include "Presentation.h"

void Presentation (const vector<Story> &firstStories, const vector<string> &glossary)
{
	for (const Story curStory : firstStories)
		cout << curStory.getTopicID () << " " << curStory.toString (glossary) << endl;
}