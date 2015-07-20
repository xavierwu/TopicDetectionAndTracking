/* Author: Zewei Wu, Zitong Wang, Zhaoqi Wang, Peng Kang */

#include "DataPreprocessing/DataPreprocessing.h"
#include "TopicDetection/TopicDetection.h"
#include "FirstStoryDetection/FirstStoryDetection.h"
#include "Evaluation/Evaluation.h"
#include "Presentation/Presentation.h"

int main (int argc, char **argv)
{
	vector<Story> corpus;
	vector<string> glossary;
	vector<Story> firstStories;

	string tkn_file = "Dataset/mttkn/20030402_0530_0700_CNA_MAN.mttkn";
	string bnd_file = "Dataset/mttkn_bnd/20030402_0530_0700_CNA_MAN.mttkn_bnd";

	DataPreprocessing (corpus, glossary, tkn_file, bnd_file);
	TopicDetection (corpus);
	FirstStoryDetection (firstStories, corpus);

	return 0;
}