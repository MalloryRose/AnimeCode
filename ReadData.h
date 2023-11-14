#pragma once
#include "Anime.h"
#include <map>

using namespace std;

class ReadData
{
   
public:
    int genresIndex = 0;
    vector<Anime*> animeObj;
    map<string, Anime*> animeList;
    map<string, int> genresMap; // storing all the genres as integers

    // loading and printing
    void loadData();
    void normalizeEpisodes(); // automatically create normalized values for episodes once data is loaded
    void printData();
    void printGenresMap(); // for testing

    void addGenre(string genre); // function to add a genre to the map of genres as integers
    int getNumGenres();

    // analyzing the data
    float normalizedValue(float val, float min, float max); // normalizing the values for a user's preferred rating
    int findMaxEpisodes(); // returning the anime object with the max episodes
    int findMinEpisodes();
    ~ReadData();
   
};

