#include "StoryLinkDetection.h"

bool isTwoStoriesSimilar (const Story &story1, const Story &story2, double threshold)
{
	return getSimilarity (story1, story2) >= threshold;
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

	map<int, double> termFrequencyMap1;
	map<int, double> termFrequencyMap2;
	story1.getTermFrequency (termFrequencyMap1);
	story2.getTermFrequency (termFrequencyMap2);

	for (map<int, double>::const_iterator citer = termFrequencyMap1.cbegin ();
		 citer != termFrequencyMap1.cend (); ++citer)
		 if (termFrequencyMap2.find (citer->first) != termFrequencyMap2.cend ()) {
			 innerProduct += citer->second * termFrequencyMap2[citer->first];
			 squareSum1 += (citer->second) *(citer->second);
			 squareSum2 += termFrequencyMap2[citer->first] * termFrequencyMap2[citer->first];
		 }

	similarity = innerProduct / sqrt (squareSum1 * squareSum2);

	return similarity;
}