#include "TopicDetection.h"

void TopicDetection (vector<Story> &corpus, int &numOfTopics)
{
	cout << "> Start TopicDetection......" << endl;

	NaiveClustering (corpus, numOfTopics, 0.5);

	cout << "> TopicDetection Done." << endl;
}

void NaiveClustering (vector<Story> &corpus, int &numOfTopics, const double &threshold)
{
	cout << ">> Start NaiveClustering......" << endl;

	numOfTopics = 0;

	for (unsigned i = 0; i < corpus.size (); ++i) {
		if (i % 10 == 0)
			cout << i << " / " << corpus.size () << endl;
		for (unsigned j = i + 1; j < corpus.size (); ++j) {
			if (isTwoStoriesSimilar (corpus[i], corpus[j], threshold)) {
				if (!corpus[i].isClustered () && !corpus[j].isClustered ()) {
					corpus[i].setTopicID (numOfTopics);
					corpus[j].setTopicID (numOfTopics);
					++numOfTopics;
				} else if (!corpus[i].isClustered () && corpus[j].isClustered ()) {
					corpus[i].setTopicID (corpus[j].getTopicID ());
				} else if (corpus[i].isClustered () && !corpus[j].isClustered ()) {
					corpus[j].setTopicID (corpus[i].getTopicID ());
				}
			}
		}
	}

	for (Story &story : corpus)
		if (!story.isClustered ())
			story.setTopicID (numOfTopics++);

	cout << ">> NaiveClustering done." << endl;
}