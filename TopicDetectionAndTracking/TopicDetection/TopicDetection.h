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

/*
 * K-means, cluster stories into several topics.
 * Input: corpus, numOfTopics
 * Output: clustered corpus
 */
void KMeans(vector<Story> &corpus, int &numOfTopics);

/*
 * initialize means.
 * Input: means, (with corpus and numOfTopics as parameters)
 * Output: initialized means
 */
void initMeans(vector<Story> &means, const vector<Story> &corpus, const int &numOfTopics);

/*
 * Calculate mean of a cluster.
 * Input: corpus, topicID
 * Output: mean of this topic
 */
Story getMean(const vector<Story> &corpus, const int &topicID);

/*
 * Set Story a certain topicID.
 * Input: story, means
 * Output: story with a certain topicID
 */
void cluster(Story &story, const vector<Story> &means);

#endif
