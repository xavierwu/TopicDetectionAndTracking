/* To cluster stories on the same topic into bins,
and the creation of bins is an unsupervised task. */

#ifndef TOPIC_DETECTION_H
#define TOPIC_DETECTION_H

#include "../StoryLinkDetection/StoryLinkDetection.h"

/* Cluster stories into topics.
Input: corpus
Output: corpus, with 'topicId' set. */
void TopicDetection(vector<Story> &corpus);

#endif