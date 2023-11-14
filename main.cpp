#include <iostream>
#include "ReadData.h"
#include "Anime.h"
#include <vector>
#include <algorithm>
#include "RecommendAnime.h"

using namespace std;

int main() {
    ReadData data;
    data.loadData();
  // data.printGenresMap();
 //    data.printData();

     RecommendAnime recommendations;

     vector<Anime*> inputtedAnimes;
     string inputtedAnimeString;
     Anime* inputtedAnime;
     while(inputtedAnimeString != "exit")
     {
         getline(cin, inputtedAnimeString);
         auto it = data.animeList.find(inputtedAnimeString);
         if(it != data.animeList.end())
         {
            inputtedAnime = data.animeList[inputtedAnimeString];
            inputtedAnimes.push_back(inputtedAnime);
            data.printAnimeInfo(inputtedAnime);

         }
         else if(inputtedAnimeString == "exit")
         {
             break;
         }
         else
         {
             cout << "anime does not exist" << endl;
         }
         if(inputtedAnimes.size() >= 3)
         {
            for(int i = 0; i < inputtedAnimes.size(); i++)
            {
                //recommendations.calculateRecommendations(inputtedAnimes);
            }
         }
     }



    return 0;
}
