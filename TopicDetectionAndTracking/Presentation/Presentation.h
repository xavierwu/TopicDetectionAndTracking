#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "../Utilities/Story.h"

/* Simply print the firstStories for now. */
void Presentation (const vector<Story> &firstStories, const vector<Story> &corpus,
				   const map<int, string> &glossary, const int &numOfTopics);

/* Print the first stories of all clusters. 
If isPrintItAll==true, print the timestamp and words. 
Otherwise print the timestamp only. */
void printFirstStories (const vector<Story> &firstStories, const map<int, string> &glossary,
						const bool &isPrintItAll = false);

/* Print the clusters.
If isPrintItAll==true, print the timestamp and words.
Otherwise print the timestamp only. */
void printClusters (const vector<Story> &corpus, const map<int, string> &glossary,
					const int &numOfTopics, const bool &isPrintItAll = false);

#endif