/* Determine whether or not two stories discuss the same topic. */

#ifndef STORY_LINK_DETECTION_H
#define STORY_LINK_DETECTION_H

#include "../Utilities/Story.h"

/* Preparing for the similarity calculation, e.g., calculating tfidf's.
Input: 'corpus', storiesIndexWithCertainWord
*/
void StoryLinkDetection (vector<Story> &corpus, const map<int, set<int>> &storiesIndexWithCertainWord);

/* Calculating tfidf's of stories in corpus */
void prepareTFIDF (vector<Story> &corpus, const map<int, set<int>> &storiesIndexWithCertainWord);

/* Given two stories, return whether or not these two stories discuss the same topic.
ACQUIRED: invoke StoryLinkDetection() before this function. 
Input: 'story1', 'story2', 'threshold'
Output: return true/false */
bool isTwoStoriesSimilar(const Story &story1, const Story &story2, double threshold);

/* Return the similarities between any two stories.
REQUIRE: call setTFIDFBasedOnCorpus() before using the stories as parameters.
NOTE: we simply use getCosineSimilarity() for now. 
Input: 'story1', 'story2'
Output: similarity */
double getSimilarity(const Story &story1, const Story &story2);

/* Before using this function, make sure that each story contains non-empty tfidf. */
double getCosineSimilarity (const Story &story1, const Story &story2);



#endif