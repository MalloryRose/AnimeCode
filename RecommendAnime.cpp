//
// Created by chlaw on 11/14/2023.
//

#include "RecommendAnime.h"
ReadData data1;

void RecommendAnime::calculateRecommendations(vector<Anime *> inputtedAnimes)
{
    vector<string> inputtedShowGenres;
    float normalizedGenre;
    float normalizedRating;
    float normalizedEpisodeCount;
    for(int i = 0; i < inputtedAnimes.size(); i++)
    {
        normalizedRating += inputtedAnimes.at(i)->rating;
        for(int j = 0; j < inputtedAnimes.at(i)->genres.size(); j++)
        {
            inputtedShowGenres.push_back(inputtedAnimes.at(i)->genres.at(j));
        }
        normalizedEpisodeCount += inputtedAnimes.at(i)->normEpisodes;
    }
    normalizedRating = normalizedRating / inputtedAnimes.size();
    normalizedEpisodeCount = normalizedEpisodeCount / inputtedAnimes.size();
    cout << normalizedEpisodeCount << endl;
    cout << normalizedRating << endl;
    //printRecommendations(normalizedEpisodeCount, normalizedRating, inputtedShowGenres);
}

void
RecommendAnime::printRecommendations(float normalizedEpisodes, float normalizedRating, vector<string> inputtedGenres)
{
    //recommendationPrioritizations[0] = genre
    //recommendationPrioritizations[1] = rating
    //recommendationPrioritizations[2] = episodeCount
    vector<Anime*> recommendationList;
    if(recommendationPrioritizations[0])
    {
        for(int i = 0; i < data1.animeObj.size(); i++)
        {

        }
    }
}

