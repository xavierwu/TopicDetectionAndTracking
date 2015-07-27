#include "FirstStoryDetection.h"

void FirstStoryDetection (vector<Story> &firstStories, const vector<Story> &corpus,
						  const int &numOfTopics)
{
	cout << "> Start FirstStoryDetection......" << endl;
	for (int curTopic = 0; curTopic != numOfTopics; ++curTopic) {
		const Story *firstStoryOfCurTopic = nullptr;
		for (const Story &curStory : corpus) {
			if (curStory.getTopicID () == curTopic) {
				if (firstStoryOfCurTopic == nullptr)
					firstStoryOfCurTopic = new Story(curStory);
				else if (curStory.getTimeStamp () < firstStoryOfCurTopic->getTimeStamp ())
					firstStoryOfCurTopic = new Story (curStory);
			}
		}
		assert (firstStoryOfCurTopic != nullptr);
		firstStories.push_back (*firstStoryOfCurTopic);
	}
	cout << "> FirstStoryDetection Done." << endl;
}