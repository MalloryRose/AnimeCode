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
            void printRecommendations(float normalizedEpisodes, float normalizedRating,
                                      unordered_map<string, int> inputtedGenres);
            void calculateRecommendations(vector<Anime*> inputtedAnimes);
        };
