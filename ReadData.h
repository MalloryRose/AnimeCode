#pragma once
#include "Anime.h"
#include <map>

using namespace std;

class ReadData
{
   
public:
    int genresIndex = 0;
    vector<Anime*> animeObj;
    map<string, int> genresMap; // storing all the genres as integers

    void loadData();
    void printData();
    void addGenre(string genre); // function to add a genre to the map of genres as integers
    void printGenresMap(); // for testing
    int getNumGenres();
    ~ReadData();
   
};

