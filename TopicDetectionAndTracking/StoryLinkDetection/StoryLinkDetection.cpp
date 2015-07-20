#include "StoryLinkDetection.h"

bool isTwoStoriesSimilar (const Story &story1, const Story &story2, double threshold)
{
	return getSimilarity (story1, story2) >= threshold;
}

double getSimilarity (const Story &story1, const Story &story2)
{
	// TODO: similarity
	return getCosineSimilarity (story1, story2);
}

double getCosineSimilarity (const Story &story1, const Story &story2)
{
	double similarity = 0.0;
	double innerProduct = 0.0;
	double squareSum1 = 0.0;
	double squareSum2 = 0.0;

	int length = (story1.getLength () < story2.getLength () ?
				  story1.getLength () : story2.getLength ());

	map<int, double> termFrequencyMap1;
	map<int, double> termFrequencyMap2;
	story1.getTermFrequencyMap (termFrequencyMap1);
	story2.getTermFrequencyMap (termFrequencyMap2);

	for (map<int, double>::const_iterator iter = termFrequencyMap1.cbegin ();
		 iter != termFrequencyMap1.cend (); ++iter) 
		if (termFrequencyMap2.find (iter->first) != termFrequencyMap2.end ()) {
			innerProduct += iter->second * termFrequencyMap2[iter->first];
			squareSum1 += (iter->second) *(iter->second);
			squareSum2 += termFrequencyMap2[iter->first] * termFrequencyMap2[iter->first];
		}

	similarity = innerProduct / sqrt (squareSum1 * squareSum2);

	return similarity;
}