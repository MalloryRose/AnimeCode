#include "ReadData.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

void ReadData::loadData()
{
	ifstream file("anime-dataset-2023.csv", ios::in | ios_base::binary);

	if (file.is_open()) {
		cout << "file opened" << endl;

        vector<string> ids;
        vector<string> names;
        vector<string> scores;
        vector<string> genres;
        vector<string> episodes;
        bool unknown;
        // Read and process each line in the CSV file
        std::string line;
        bool firstLine = true;
        while (std::getline(file, line)) {
            unknown = false;
            // Use a stringstream to split the line into columns
            if (!firstLine) {
                std::stringstream ss(line);
                std::stringstream checkUnknown(line);
                string content = checkUnknown.str();
                std::string value;
                std::string word;

                if(content.find("UNKNOWN") != std::string::npos){
                    unknown = true;
                } else{
                    unknown = false;
                }

                if(!unknown){
                    Anime* anime = new Anime;
                    // Read and store each column's value
                    std::getline(ss, value, ',');
                    ids.push_back(value);
                    anime->id = stoi(value);

                    char check;
                    stack<char> stk;

                    // must check if it has quotes. if it doesn't, there's only one genre
                    ss.get(check);
                    if (check != '"'){
                        std::getline(ss, value, ',');
                        value = check + value;
                        value.erase(0, value.find_first_not_of(' '));
                        names.push_back(value);
                        anime->name = value;
                    } else{


                        std::getline(ss, value, '"');
                        value.erase(0, value.find_first_not_of(' '));
                        names.push_back(value);
                        anime->name = value;
                        std::getline(ss, value, ',');
                    }

                  \


                    // value is sometimes "unknown", in this case, it cannot be converted to an integer

                    std::getline(ss, value, ',');
                    scores.push_back(value);


                    anime->rating = stoi(value);

                    char ch;

                    // must check if it has quotes. if it doesn't, there's only one genre
                    ss.get(ch);
                    if (ch != '"') {

                        std::getline(ss, value, ',');
                        value = ch + value;
                    }
                    else {
                        std::getline(ss, value, '"');
                    }
                    genres.push_back(value);
                    string singleGenre;
                    std::stringstream genresStream(value);
                    while (getline(genresStream, singleGenre, ',')) {
                        // remove the period and quotes in a genre
                        if(singleGenre.find("\"")  != std::string::npos){
                            singleGenre.pop_back();
                        }
                        if(singleGenre.find(".")  != std::string::npos){
                            singleGenre.pop_back();
                        }
                        if(singleGenre.find("?")  != std::string::npos){
                            singleGenre.pop_back();
                        }
                        singleGenre.erase(0, singleGenre.find_first_not_of(' '));
                        addGenre(singleGenre); // will add the genre to the map only if its a new genre
                        anime->genres.push_back(singleGenre);
                    }



                    std::getline(ss, value, ',');
                    std::getline(ss, value, ',');
                    value.erase(0, value.find_first_not_of(' '));
                    episodes.push_back(value);
                    anime->episodes = stoi(value);



                    animeObj.push_back(anime);
                    animeList.emplace(anime->name, anime);
                }
                


            }
            firstLine = false;

            
        }

        normalizeEpisodes();

        // Close the file
        file.close();

        // Example: Print the values from each column
       

        // You now have the data from each column stored in the vectors
        // You can process and manipulate the data as needed

     
	}
	else {
		cout << "file did not open" << endl;
	}



}

void ReadData::printData()
{
    for (int i = 0; i < animeObj.size(); i++) {
        std::cout << "ID: " << animeObj[i]->id << " | ";
        std::cout << "Name: " << animeObj[i]->name << " | ";
        std::cout << "Score: " << animeObj[i]->rating << " | ";
        cout << "Genres: ";
        for (int j = 0; j < animeObj[i]->genres.size(); j++) {
            std::cout  << animeObj[i]->genres[j] << " ";
        }
        cout << " | ";
        
        std::cout << "Episodes: " << animeObj[i]->episodes << " | ";
        std::cout << "Normalized Episode Value: " << animeObj[i]->normEpisodes << std::endl;

    }
    
}

void ReadData::addGenre(string genre)
{
    if (genresMap.find(genre) == genresMap.end())
        genresMap[genre] = genresIndex++;

}

void ReadData::printGenresMap()
{
    for (auto genre : genresMap) {
        cout << genre.first << ": " << genre.second << "\n";
    }

}

int ReadData::getNumGenres()
{
    return genresIndex + 1;
}



ReadData::~ReadData()
{
    for (size_t i = 0; i < animeObj.size(); i++) {
        delete animeObj[i];
    }
    animeObj.clear(); // Clear the vector to remove the pointers
}

float ReadData::normalizedValue(float val, float min, float max) {
    return (val - min) / (max - min);

}

int ReadData::findMaxEpisodes() {
    int max = 0;

    for (int i = 0; i < animeObj.size(); i++) {
        if(animeObj[i]->episodes > max){
            max = animeObj[i]->episodes;
        }
    }

    return max;

}

int ReadData::findMinEpisodes() {
    int min = 1000;

    for (int i = 0; i < animeObj.size(); i++) {
        if(animeObj[i]->episodes < min){
            min = animeObj[i]->episodes;

        }
    }
    return min;
}

void ReadData::normalizeEpisodes() {
    int minEpisodes = findMinEpisodes();
    int maxEpisodes = findMaxEpisodes();
    for (int i = 0; i < animeObj.size(); i++) {
       animeObj[i]->normEpisodes = normalizedValue(animeObj[i]->episodes, minEpisodes, maxEpisodes);

    }

}
