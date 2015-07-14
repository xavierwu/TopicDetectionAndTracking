#ifndef STORY_H
#define STORY_H

#include "Utilities.h"

class Story
{
public:
	vector<string> words_s; // the remaining words after stemming
	vector<int> words_i; // the index of each word of 'words_s', refer to the glossary
	int topicId = -1;

	Story();
	~Story();
};

#endif