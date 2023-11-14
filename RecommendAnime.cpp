//
// Created by chlaw on 11/14/2023.
//

#include "RecommendAnime.h"

void RecommendAnime::calculateRecommendations(vector<Anime *> inputtedAnimes)
{
    unordered_map<string, int> inputtedShowGenres;
    float normalizedGenre;
    float normalizedRating;
    float normalizedEpisodeCount;
    for(int i = 0; i < inputtedAnimes.size(); i++)
    {
        normalizedRating += inputtedAnimes.at(i)->rating;
        for(int j = 0; j < inputtedAnimes.at(i)->genres.size(); j++)
        {
            inputtedShowGenres.emplace(inputtedAnimes.at(i)->genres.at(j), 0);
        }
        normalizedEpisodeCount += inputtedAnimes.at(i)->normEpisodes;
    }
    printRecommendations(normalizedEpisodeCount, normalizedRating, inputtedShowGenres);
}

void
RecommendAnime::printRecommendations(float normalizedEpisodes, float normalizedRating, unordered_map<string, int> inputtedGenres)
{
    int genreCount = 0;
    for(const auto& genre : inputtedGenres)
    {

    }
}
