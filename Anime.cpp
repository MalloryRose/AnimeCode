#include "Anime.h"

Anime::Anime()
{
}

Anime::Anime(int id, string name, int rating, vector<string> genres, int episodes, float normEpisodes)
{
	this->id = id;
	this->name = name;
	this->rating = rating;
	this->genres = genres;
	this->episodes = episodes;
    this->normEpisodes = normEpisodes;
}

Anime::~Anime()
{
}
