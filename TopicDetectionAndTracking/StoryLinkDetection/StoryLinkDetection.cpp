#include "StoryLinkDetection.h"

/* Preparing for the similarity calculation, e.g., calculating tfidf's. */
void StoryLinkDetection (vector<Story> &corpus, const map<int, vector<int>> &storiesIndexWithCertainWord)
{
	cout << "> Start StoryLinkDetection......" << endl;

	prepareTFIDF (corpus, storiesIndexWithCertainWord);

	cout << "> StoryLinkDetection done. " << endl;
}

void prepareTFIDF (vector<Story> &corpus, const map<int, vector<int>> &storiesIndexWithCertainWord)
{
	cout << ">> Start prepareTFIDF......" << endl;

	/* Calculate the tfidf, and save it. */
	Story::setTFIDFOfCorpus (corpus, storiesIndexWithCertainWord);
	Story::saveTFIDF (corpus, "Dataset/tfidf.dat");

	/* Load the tfidf from file, pls make sure the file exist.  */
	// Story::loadTFIDF(corpus, "Dataset/tfidf.dat");

	cout << ">> prepareTFIDF done. " << endl;
}

bool isTwoStoriesSimilar (const Story &story1, const Story &story2, double threshold)
{
	double similarity = getSimilarity (story1, story2);
	return similarity >= threshold;
}

double getSimilarity (const Story &story1, const Story &story2)
{
	// TODO: what about other similarity measures?
	return getCosineSimilarity (story1, story2);
}

double getCosineSimilarity (const Story &story1, const Story &story2)
{
	double similarity = 0.0;
	double innerProduct = 0.0;
	double squareSum1 = 0.0;
	double squareSum2 = 0.0;

	map<int, double> tfidf1;
	map<int, double> tfidf2;
	story1.getTFIDF (tfidf1);
	story2.getTFIDF (tfidf2);

	for (map<int, double>::const_iterator citer = tfidf1.cbegin ();
		 citer != tfidf1.cend (); ++citer)
		 if (tfidf2.find (citer->first) != tfidf2.cend ()) {
			 innerProduct += citer->second * tfidf2[citer->first];
			 squareSum1 += (citer->second) *(citer->second);
			 squareSum2 += tfidf2[citer->first] * tfidf2[citer->first];
		 }

	similarity = innerProduct / sqrt (squareSum1 * squareSum2);

	return similarity;
}

