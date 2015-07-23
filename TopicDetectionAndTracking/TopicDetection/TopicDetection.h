/* To cluster stories on the same topic into bins,
and the creation of bins is an unsupervised task. */

#ifndef TOPIC_DETECTION_H
#define TOPIC_DETECTION_H

#include "../StoryLinkDetection/StoryLinkDetection.h"

/* Threshold for clustering. */
static double threshold = 0.8;  // TODO: to be modified

/* Cluster stories into topics.
Input: corpus
Output: corpus, with 'topicId' set. */
void TopicDetection (vector<Story> &corpus);

#endif
