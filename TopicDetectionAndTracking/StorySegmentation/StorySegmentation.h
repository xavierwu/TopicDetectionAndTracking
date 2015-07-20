/* Take a show of news and to detect the boundaries between stories automatically. */

#ifndef STORY_SEGMENTATION_H
#define STORY_SEGMENTATION_H

#include "../Utilities/Story.h"

/* Detect the boundaries between stories. OPTIONAL: we have both of these two files already. 
input: 'tkn_file' (e.g., "*.mttkn")
output: 'bnd_file' */
void StorySegmentation(const string &tkn_file, string &bnd_file);

#endif