#include "FirstStoryDetection.h"

void FirstStoryDetection (vector<Story> &firstStories, const vector<Story> &corpus, 
						  const int &numOfTopics)
{
	for (int curTopic = 0; curTopic != numOfTopics; ++curTopic) {
		const Story *firstStoryOfCurTopic = nullptr;
		for (Story curStory : corpus) {
			if (curStory.getTopicID () == curTopic) {
				if (firstStoryOfCurTopic == nullptr)
					firstStoryOfCurTopic = &curStory;
				else if (curStory.getTimeStamp () < firstStoryOfCurTopic->getTimeStamp ())
					// TODO: the comparison between timeStamps
					firstStoryOfCurTopic = &curStory;
			}
		}
		firstStories.push_back (Story (*firstStoryOfCurTopic));
	}
}