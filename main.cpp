#include <iostream>
#include "ReadData.h"
#include "Anime.h"
#include <vector>
#include <algorithm>
#include "RecommendAnime.h"

using namespace std;

void menu(){

    cout << "Enter an option" << endl;
    cout << "1. Add an Anime" << endl;
    cout << "2. Show recommendations" << endl;
    cout << "3. Exit" << endl;
}

int main() {
    ReadData data;
    data.loadData();

  // data.printGenresMap();
 //    data.printData();


     RecommendAnime recommendations;
     vector<Anime*> inputtedAnimes;
     string inputtedAnimeString;
     Anime* inputtedAnime;
    string input;
    cout << "Anime Recommendation Engine" << endl;
    cout << "---------------------------" << endl;
     while(inputtedAnimeString != "exit")
     {
         menu();
         getline(cin, input);
         if(input == "1"){
             cout << "Enter the name of an anime" << endl;
             getline(cin, inputtedAnimeString);
             auto it = data.animeList.find(inputtedAnimeString);

             if(it != data.animeList.end())
             {
                 inputtedAnime = data.animeList[inputtedAnimeString];
                 inputtedAnimes.push_back(inputtedAnime);
                 data.printAnimeInfo(inputtedAnime);
             } else{
                 cout << "Unknown Anime" << endl;
             }


         }


         else if(input == "3")
         {
             break;
         }
         else if(input == "2")
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
             getline(cin, response);
             if(response == "yes")
             {
                 prioritizeGenre = true;
             }
            cout << "Do you want to prioritize Episode Count" << endl;
             getline(cin, response);
            if(response == "yes")
            {
                prioritizeEpisodeCount = true;
            }
            cout << "Do you want to prioritize Rating" << endl;
            getline(cin, response);
            if(response == "yes")
            {
                prioritizeRating = true;
            }
            recommendations.recommendationPrioritizations[0] = prioritizeGenre;
            recommendations.recommendationPrioritizations[1] = prioritizeRating;
            recommendations.recommendationPrioritizations[2] = prioritizeEpisodeCount;
            cout << "Number of Animes inputted: " << inputtedAnimes.size() << endl;
            recommendations.calculateRecommendations(inputtedAnimes);
         }
         else
         {
             cout << "Invalid option" << endl;
         }
     }



    return 0;
}
