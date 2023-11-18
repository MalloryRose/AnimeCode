#include "Anime.h"

Anime::Anime()
{
    weight = 0;
    compareWeight = 0;
}

Anime::Anime(int id, string name, float rating, vector<string> genres, int episodes, float normEpisodes, float weight, float compareWeight)
{
	this->id = id;
	this->name = name;
	this->rating = rating;
	this->genres = genres;
	this->episodes = episodes;
    this->normEpisodes = normEpisodes;
    this->weight = weight;
    this->compareWeight = compareWeight;

}

Anime::~Anime()
{
}
