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
         else if(inputtedAnimeString == "show recommendations")
         {
            /* if(inputtedAnimes.size() <= 3)
             {
                 cout << "not enough data" << endl;
                 continue;
             }*/
             string response;
             bool prioritizeGenre = false;
             bool prioritizeEpisodeCount = false;
             bool prioritizeRating = false;
             cout << "Do you want to prioritize Genre" << endl;
             cin >> response;
             if(response == "yes")
             {
                 prioritizeGenre = true;
             }
            cout << "Do you want to prioritize Episode Count" << endl;
            cin >> response;
            if(response == "yes")
            {
                prioritizeEpisodeCount = true;
            }
            cout << "Do you want to prioritize Rating" << endl;
            cin >> response;
            if(response == "yes")
            {
                prioritizeRating = true;
            }
            recommendations.recommendationPrioritizations[0] = prioritizeGenre;
            recommendations.recommendationPrioritizations[1] = prioritizeRating;
            recommendations.recommendationPrioritizations[2] = prioritizeEpisodeCount;
            recommendations.calculateRecommendations(inputtedAnimes);
         }
         else
         {
             cout << "anime does not exist" << endl;
         }
     }



    return 0;
}
