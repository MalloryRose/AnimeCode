#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Anime object holds data for each anime in the data sheet

class Anime
{
public:
	int id;
	string name;
	int rating;
	vector<string> genres;
	int episodes;
    float normEpisodes; // normalized value for episodes

	Anime();
	~Anime();
	Anime(int id, string name, int rating, vector<string> genres, int episodes, float normEpisodes);


};

