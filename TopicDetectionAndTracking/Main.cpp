#include "DataPreprocessing.h"
#include "TopicDetection.h"
#include "FirstStoryDetection.h"
#include "Evaluation.h"

vector<Story> corpus;
vector<string> glossary;
vector<Story> firstStories;

int main(int argc, char **argv)
{
	string tkn_file = "20030402_0530_0700_CNA_MAN.mttkn";
	string bnd_file = "20030402_0730_0930_XIN_MAN.mttkn_bnd";
	DataPreprocessing(corpus, glossary, tkn_file, bnd_file);
	TopicDetection(corpus);
	FirstStoryDetection(firstStories, corpus);
	Evaluation(firstStories, corpus);

	return 0;
}