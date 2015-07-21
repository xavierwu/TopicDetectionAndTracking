/* Determine whether or not two stories discuss the same topic. */

#ifndef STORY_LINK_DETECTION_H
#define STORY_LINK_DETECTION_H

#include "../Utilities/Story.h"

/* Given two stories, return whether or not these two stories discuss the same topic.
Input: 'story1', 'story2', 'threshold'
Output: return true/false */
bool isTwoStoriesSimilar(const Story &story1, const Story &story2, double threshold);

/* Return the similarities between any two stories.
REQUIRE: call setTFIDF() before using the stories as parameters.
NOTE: we simply use getCosineSimilarity() for now. 
Input: 'story1', 'story2'
Output: similarity */
double getSimilarity(const Story &story1, const Story &story2);

/* Before using this function, make sure that each story contains non-empty tfidf. */
double getCosineSimilarity (const Story &story1, const Story &story2);

#endif