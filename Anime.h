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
	string rating;
	vector<string> genres;
	string episodes;

	Anime();
	~Anime();
	Anime(int id, string name, string rating, vector<string> genres, string episodes);


};

