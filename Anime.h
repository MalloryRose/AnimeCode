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
	float rating;
	vector<string> genres;
	int episodes;
    float normEpisodes; // normalized value for episodes
    float weight;
    float compareWeight;

	Anime();
	~Anime();
	Anime(int id, string name, float rating, vector<string> genres, int episodes, float normEpisodes, float weight, float compareWeight);


};

