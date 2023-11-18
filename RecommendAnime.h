//
// Created by chlaw on 11/14/2023.
//

#pragma once
#include "ReadData.h"
#include "Anime.h"
#include <vector>
#include <unordered_map>

class RecommendAnime
        {
public:
            ReadData data1;
            bool recommendationPrioritizations[3];
            RecommendAnime();
            void printAnimeInfo(Anime* anime);
            void printRecommendations(float normalizedEpisodes, float normalizedRating,
                                      vector<string> inputtedGenres, vector<Anime *> inputtedAnimes, int numRecommendations);
            void calculateRecommendations(vector<Anime*> inputtedAnimes, int numRecommendations);
            vector<Anime*> getAnimeWithSameGenre(vector<Anime *> inputtedAnimes, vector<string> inputtedGenres);
            float getOverallWeight(float normalizedEpisodes, float normalizedRating, float epWeight, float ratingWeight);

            // sorting algorithm
           // low  --> Starting index,
           // high  --> Ending index

            void swap(vector<Anime*> &vect, int i, int j);
            void quickSort(vector<Anime*> &vect, int low, int high);
            int partition(vector<Anime*> &vect, int low, int high);


        };
