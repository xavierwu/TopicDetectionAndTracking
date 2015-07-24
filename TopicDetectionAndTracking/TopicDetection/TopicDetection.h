/* To cluster stories on the same topic into bins,
and the creation of bins is an unsupervised task. */

#ifndef TOPIC_DETECTION_H
#define TOPIC_DETECTION_H

#include "../StoryLinkDetection/StoryLinkDetection.h"

/* Cluster stories into topics.
Input: corpus
Output: corpus, with 'topicID' set. */
void TopicDetection (vector<Story> &corpus, int &numOfTopics);

/* Naive clustering, simply cluster two stories to be of same topic, if the similarity is above threshold.
Input: corpus, threshold
Output: numOfTopics, corpus[].topicID
*/
void NaiveClustering (vector<Story> &corpus, int &numOfTopics, const double &threshold);

#endif
