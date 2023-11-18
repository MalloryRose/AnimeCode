//
// Created by chlaw on 11/14/2023.
//

#include "RecommendAnime.h"
#include <algorithm>



RecommendAnime::RecommendAnime() {
    data1.loadData();
}



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

    printRecommendations(normalizedEpisodeCount, normalizedRating, inputtedShowGenres, inputtedAnimes);
}

void
RecommendAnime::printRecommendations(float normalizedEpisodes, float normalizedRating, vector<string> inputtedGenres, vector<Anime *> inputtedAnimes)
{
    //recommendationPrioritizations[0] = genre
    //recommendationPrioritizations[1] = rating
    //recommendationPrioritizations[2] = episodeCount

    vector<Anime*> recommendationList;
    float weight1;
    float weight2;
    float compareWeights;
    float compareWeightsOld;
    bool first = true;
    if(recommendationPrioritizations[0] &&  !recommendationPrioritizations[1] && !recommendationPrioritizations[2])
    { // Only genre was selected as preference in this scenario
        weight1 = getOverallWeight(normalizedEpisodes, normalizedRating, 0.5, 0.5);
        recommendationList = getAnimeWithSameGenre(inputtedAnimes, inputtedGenres);
         for(int i = 0; i < recommendationList.size(); i++){
             weight2 = getOverallWeight(recommendationList[i]->normEpisodes, recommendationList[i]->rating, 0.5, 0.5);
             compareWeights = abs(weight2 - weight1);
             // smaller value means better recommendation
             if(!first){
                 if(compareWeights < compareWeightsOld){
                     // swap
                     Anime* temp = recommendationList[i -1];
                     recommendationList[i-1] = recommendationList[i];
                     recommendationList[i] = temp;

                 }
             }
             first = false;
             compareWeightsOld = compareWeights;
         }
    }

    for(int i = 0; i < 10; i++){
        ReadData::printAnimeInfo(recommendationList[i]);
    }

}


vector<Anime *> RecommendAnime::getAnimeWithSameGenre(vector<Anime *> inputtedAnimes,vector<string> inputtedGenres) {

    // this will return a list of all animes that contain the genres found in the input genres parameter.

    vector<Anime*> recommendationList;
    for(int i = 0; i < data1.animeObj.size(); i++)
    {
        std::sort(data1.animeObj[i]->genres.begin(), data1.animeObj[i]->genres.end());
        std::sort(inputtedGenres.begin(), inputtedGenres.end());
        // this will check if the genre list of an Anime in the dataset is a subset of the inputtedGenres.
        bool isSubset = std::includes(inputtedGenres.begin(), inputtedGenres.end(), data1.animeObj[i]->genres.begin(), data1.animeObj[i]->genres.end());

        if(isSubset){
            bool isRepeat = false;
            for(int j = 0; j < inputtedAnimes.size(); j++){
                if(inputtedAnimes[j]->id == data1.animeObj[i]->id){
                    isRepeat = true;
                    break;
                }
            }
            if(!isRepeat){
                recommendationList.push_back(data1.animeObj[i]);
            }
        }
    }
    return recommendationList;
}

float
RecommendAnime::getOverallWeight(float normalizedEpisodes, float normalizedRating, float epWeight, float ratingWeight) {
    return (epWeight * normalizedEpisodes) + (ratingWeight * normalizedRating);

}




