#include "TopicDetection.h"

void TopicDetection (vector<Story> &corpus, int &numOfTopics)
{
	cout << "> Start TopicDetection......" << endl;

	numOfTopics = 6;
	KMeans (corpus, numOfTopics);
	//NaiveClustering (corpus, numOfTopics, 0.5);

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

void KMeans(vector<Story> &corpus, int &numOfTopics) {
//  vector< map<int, double> > means;
    vector<Story> means;	// centers
    
    initMeans(means, corpus, numOfTopics);
    
    int loopCnt = 10;	// Kmeans loop execution counter, set to 10 temporarily

    while (loopCnt) {
    	// label clusters
        for (unsigned int i = 0; i < corpus.size(); i++) {
            cluster(corpus[i], means, numOfTopics);
        }

    	// Calculate centers
        for (int i = 0; i < numOfTopics; i++) {
            means[i] = getMean(corpus, i);
        }
        
        loopCnt--;
    }
    
}

void initMeans(vector<Story> &means, const vector<Story> &corpus, const int &numOfTopics) {

    for (int i = 0; i < numOfTopics; i++) {
//      map<int, double> tfidf;
//      corpus[i].(tfidf);
    	assert(i >= 0 && i < numOfTopics);
        means.push_back(corpus[i]);	// set initial centers to several stories, for temporary.
    }
}

Story getMean(const vector<Story> &corpus, const int &topicID) {
//  map<int, double> mean;
    Story mean;
    int storyNumOfTopic = 0;
    
    // Add all TF-IDF value to mean
    for (unsigned int i = 0; i < corpus.size(); i++) {
        if (corpus[i].getTopicID() == topicID) {
            storyNumOfTopic++;
            
            map<int, double> tfidf;
            corpus[i].getTFIDF(tfidf);
            
            for (map<int, double>::const_iterator it = tfidf.cbegin(); it != tfidf.cend(); it++) {
            	map<int, double> tfidfOfMean;
            	mean.getTFIDF(tfidfOfMean);
                if (tfidfOfMean.find(it->first) != tfidfOfMean.cend()) {
                    tfidfOfMean[it->first] += it->second;
                } else {
                    tfidfOfMean.insert(std::pair<int, double> (it->first, it->second));
                }
                mean.copyTFIDF(tfidfOfMean);
            }
        }
    }
    
	map<int, double> tfidfOfMean;
	mean.getTFIDF(tfidfOfMean);
    for (map<int, double>::iterator it = tfidfOfMean.begin(); it != tfidfOfMean.end(); it++) {
        it->second /= storyNumOfTopic;
    }
    mean.copyTFIDF(tfidfOfMean);

    return mean;
}

void cluster(Story &story, const vector<Story> &means, const int &numOfTopics) {
    double maxSimilarity = 0;
    
    for (unsigned int i = 0; i < numOfTopics; i++) {
		double similarity = getSimilarity (story, means[i]);
		//cout << "sim of " << i << " = " << similarity << endl;
        if (similarity > maxSimilarity) {
            maxSimilarity = similarity;
            story.setTopicID(i);
        }
    }
}
