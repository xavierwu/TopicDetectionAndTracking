#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "../Utilities/Story.h"

/* Simply print the firstStories for now. */
void Presentation (const vector<Story> &firstStories, const vector<Story> &corpus, 
				   const map<int, string> &glossary);

void printClusters ();

#endif