#include "TopicDetection.h"

void TopicDetection (vector<Story> &corpus, int &numOfTopics)
{
	// you may need isTwoStoriesSimilar() in 'StoryLinkDetection.h'
	// TODO: topic detection

	numOfTopics = 0;
	for (std::vector<Story>::iterator iterUncategorized = corpus.begin ();
		 iterUncategorized != corpus.end (); iterUncategorized++) {
		for (std::vector<Story>::iterator iterCategorized = corpus.begin();
			 iterCategorized != iterUncategorized; iterCategorized++) {
			/* IF determined as similar, set the uncategorized story id to the id that the categorized has. */
			/* Create a new topic otherwise. */
			if (isTwoStoriesSimilar (*iterUncategorized, *iterCategorized, threshold)) {
				iterUncategorized->setTopicID (iterCategorized->getTopicID());
			} else {
				iterUncategorized->setTopicID (numOfTopics);
				numOfTopics++;
			}
		}
	}
}
