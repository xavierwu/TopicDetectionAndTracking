#include "StoryLinkDetection.h"

bool isTwoStoriesSimilar (const Story &story1, const Story &story2, double threshold)
{
	double similarity = getSimilarity (story1, story2);
//	if (similarity <= threshold)
//		cout << similarity << endl;
	return similarity >= threshold;
	//return getSimilarity (story1, story2) >= threshold;
}

double getSimilarity (const Story &story1, const Story &story2)
{
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