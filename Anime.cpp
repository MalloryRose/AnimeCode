#include "Anime.h"

Anime::Anime()
{
}

Anime::Anime(int id, string name, string rating, vector<string> genres, string episodes)
{
	this->id = id;
	this->name = name;
	this->rating = rating;
	this->genres = genres;
	this->episodes = episodes;
}

Anime::~Anime()
{
}
