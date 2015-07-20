/* Detect the first story of a certain event/activity/topic. */

#ifndef FIRST_STORY_DETECTION_H
#define FIRST_STORY_DETECTION_H

#include "../Utilities/Story.h"

/* Detect the first story of every topic.
Input: 'corpus'
Output: 'firstStories', it's ordered by topicId. */
void FirstStoryDetection(vector<Story> &firstStories, const vector<Story> &corpus);

#endif