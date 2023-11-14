//
// Created by chlaw on 11/14/2023.
//

#pragma once
#include "ReadData.h"
#include "Anime.h"

class RecommendAnime
        {
public:
            void printRecommendations();
            void calculateRecommendations(vector<Anime*> inputtedAnimes);
        };
