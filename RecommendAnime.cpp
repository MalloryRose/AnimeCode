//
// Created by chlaw on 11/14/2023.
//

#include "RecommendAnime.h"
#include <algorithm>



RecommendAnime::RecommendAnime() {
    data1.loadData();
}



void RecommendAnime::calculateRecommendations(vector<Anime *> inputtedAnimes, int numRecommendations)
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

    printRecommendations(normalizedEpisodeCount, normalizedRating, inputtedShowGenres, inputtedAnimes, numRecommendations);
}

void
RecommendAnime::printRecommendations(float normalizedEpisodes, float normalizedRating, vector<string> inputtedGenres, vector<Anime *> inputtedAnimes, int numRecommendations)
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
    if(recommendationPrioritizations[0] &&  !recommendationPrioritizations[1] && !recommendationPrioritizations[2]) { // Only genre was selected as preference in this scenario
        weight1 = getOverallWeight(normalizedEpisodes, normalizedRating, 0.5, 0.5);
        cout << "Overall weight based on input: " << weight1 << endl;
        recommendationList = getAnimeWithSameGenre(inputtedAnimes, inputtedGenres);
        for (int i = 0; i < recommendationList.size(); i++) {
            weight2 = getOverallWeight(recommendationList[i]->normEpisodes, recommendationList[i]->rating, 0.5, 0.5);
            recommendationList[i]->weight = weight2;
            compareWeights = abs(weight2 - weight1);
            recommendationList[i]->compareWeight = compareWeights;
            // smaller value means better recommendation


        }
        // sort the compareWeights in ascending order
        quickSort(recommendationList, 0, recommendationList.size() - 1);


        for (int i = 0; i < numRecommendations; i++) {
            ReadData::printAnimeInfo(recommendationList[i]);
        }
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

void RecommendAnime::swap(vector<Anime*> &vect, int i, int j) {
    Anime* temp = vect[i];
    vect[i] = vect[j];
    vect[j] = temp;
}


int RecommendAnime::partition(vector<Anime*> &vect, int low, int high) {
    // pivot is choosen as the last element
    float pivot = vect[high]->compareWeight;

    // Index of smaller element
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (vect[j]->compareWeight <= pivot) {
            // If current element is smaller than or
            // equal to pivot
            i++;

            // swap arr[i] and arr[j]
            swap(vect, i, j);
        }
    }

    // Swap the pivot element with arr[i + 1]
    swap(vect, i+1, high);

    // Return the position from where partition
    // is done
    return (i + 1);

}

void RecommendAnime::quickSort(vector<Anime*> &vect, int low, int high) {
    if (low < high) {
        /* pi is the partitioning index, arr[pi] is
           now at right place */
        int pi = partition(vect, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(vect, low, pi - 1);
        quickSort(vect, pi + 1, high);
    }
}




