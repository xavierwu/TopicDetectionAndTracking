#include "StoryLinkDetection.h"

bool isTwoStoriesSimilar (const Story &story1, const Story &story2, double threshold)
{
	return getSimilarity(story1, story2) >= threshold;
}

double getSimilarity(const Story &story1, const Story &story2)
{
	// TODO: get similarity
	return 0.0;
}