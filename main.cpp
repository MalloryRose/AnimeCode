#include <iostream>
#include "ReadData.h"
#include "Anime.h"
#include <vector>
#include <algorithm>
#include "RecommendAnime.h"
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"

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
            int numRecommendations;
            string response;
            cout << "How many recommendations?" << endl;
            getline(cin, response);
            numRecommendations = stoi(response);

             bool prioritizeGenre = false;
             bool prioritizeEpisodeCount = false;
             bool prioritizeRating = false;
             cout << "Do you want to prioritize Genre? (yes/no)" << endl;
             getline(cin, response);
             if(response == "yes" || response == "Yes")
             {
                 prioritizeGenre = true;
             }
            cout << "Do you want to prioritize Episode Count? (yes/no)" << endl;
             getline(cin, response);
            if(response == "yes" || response == "Yes")
            {
                prioritizeEpisodeCount = true;
            }
            cout << "Do you want to prioritize Rating? (yes/no)" << endl;
            getline(cin, response);
            if(response == "yes" || response == "Yes")
            {
                prioritizeRating = true;
            }
            cout << "Which sorting method would you like to use?" << endl;

            cout << "1. Quick sort" << endl;
            cout << "2. Shell sort" << endl;
            getline(cin, response);
            string sortMethod;
            if(response == "1"){
                sortMethod = "quick";
            } else if (response == "2"){
                sortMethod = "shell";
            } else{
                cout << "Invalid." << endl;
            }
            recommendations.recommendationPrioritizations[0] = prioritizeGenre;
            recommendations.recommendationPrioritizations[1] = prioritizeRating;
            recommendations.recommendationPrioritizations[2] = prioritizeEpisodeCount;
            recommendations.sortMethod = sortMethod;
            cout << "Number of Animes inputted: " << inputtedAnimes.size() << endl;
            recommendations.calculateRecommendations(inputtedAnimes, numRecommendations);
         }
         else
         {
             cout << "Invalid option" << endl;
         }
     }

    // init gui state
//    enum {EASY, HARD};
//    static int op = EASY;
//    static float value = 0.6f;
//    static int i =  20;
//    struct nk_context ctx;
//    struct nk_user_font font;
//    font.userdata.ptr = &font;
//    font.height = ;
//    font.width = your_text_width_calculation;
//    nk_init_fixed(&ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, &font);
//    if (nk_begin(&ctx, "Show", nk_rect(50, 50, 220, 220),
//                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
//        // fixed widget pixel width
//        nk_layout_row_static(&ctx, 30, 80, 1);
//        if (nk_button_label(&ctx, "button")) {
//            // event handling
//        }
//        // fixed widget window ratio width
//        nk_layout_row_dynamic(&ctx, 30, 2);
//        if (nk_option_label(&ctx, "easy", op == EASY)) op = EASY;
//        if (nk_option_label(&ctx, "hard", op == HARD)) op = HARD;
//        // custom widget pixel width
//        nk_layout_row_begin(&ctx, NK_STATIC, 30, 2);
//        {
//            nk_layout_row_push(&ctx, 50);
//            nk_label(&ctx, "Volume:", NK_TEXT_LEFT);
//            nk_layout_row_push(&ctx, 110);
//            nk_slider_float(&ctx, 0, &value, 1.0f, 0.1f);
//        }
//        nk_layout_row_end(&ctx);
//    }
//    nk_end(&ctx);

    return 0;
}
