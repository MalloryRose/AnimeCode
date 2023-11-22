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
    if(recommendationList[0]){
        // genre selected
        if(!recommendationPrioritizations[1] && !recommendationPrioritizations[2] || recommendationPrioritizations[1] && !recommendationPrioritizations[2]){
            // only genre or all three selected
            // weight them  the same
            weight1 = getOverallWeight(normalizedEpisodes, normalizedRating, 0.5, 0.5);
            cout << "Overall weight based on input: " << weight1 << endl;
            recommendationList = getAnimeWithSameGenre(inputtedAnimes, inputtedGenres);
            compare(recommendationList, 0.5, 0.5, weight1);
            // sort the compareWeights in ascending order
            quickSort(recommendationList, 0, recommendationList.size() - 1);

            for (int i = 0; i < numRecommendations; i++) {
                ReadData::printAnimeInfo(recommendationList[i]);
            }

        } else if(!recommendationPrioritizations[1] && recommendationPrioritizations[2]){
            //episode and genre
            cout << "Input normalized episode: " << normalizedEpisodes << endl;
            weight1 = getOverallWeight(normalizedEpisodes, normalizedRating, 0.9, 0.1);
            cout << "Overall weight based on input: " << weight1 << endl;
            cout << "Input normalized rating: " << normalizedRating << endl;
            recommendationList = getAnimeWithSameGenre(inputtedAnimes, inputtedGenres);
            compare(recommendationList, 0.9, 0.1, weight1);
            quickSort(recommendationList, 0, recommendationList.size() - 1);

            for (int i = 0; i < numRecommendations; i++) {
                ReadData::printAnimeInfo(recommendationList[i]);
            }

        } else if( recommendationPrioritizations[1] && !recommendationPrioritizations[2]){
            // genre and rating
            weight1 = getOverallWeight(normalizedEpisodes, normalizedRating, 0.4, 0.6);
            cout << "Overall weight based on input: " << weight1 << endl;
            recommendationList = getAnimeWithSameGenre(inputtedAnimes, inputtedGenres);
            compare(recommendationList, 0.4, 0.6, weight1);
            quickSort(recommendationList, 0, recommendationList.size() - 1);

            for (int i = 0; i < numRecommendations; i++) {
                ReadData::printAnimeInfo(recommendationList[i]);
            }
        }

        // genre not selected


    } else if(!recommendationPrioritizations[1] && !recommendationPrioritizations[2]){
        // none selected as preference



    } else if(!recommendationPrioritizations[1] && recommendationPrioritizations[2]){
        // only episode selected

    } else if( recommendationPrioritizations[1] && !recommendationPrioritizations[2]){
        // only rating

    } else{
       // ep and rating selected



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

void RecommendAnime::compare(vector<Anime *> &vect, float epWeight, float ratingWeight, float weight1) {
    for (int i = 0; i < vect.size(); i++) {
        float weight2 = getOverallWeight(vect[i]->normEpisodes, vect[i]->rating, epWeight, ratingWeight);
        vect[i]->weight = weight2;
        float compareWeights = abs(weight2 - weight1);
        vect[i]->compareWeight = compareWeights;
        // smaller value means better recommendation
    }

}




