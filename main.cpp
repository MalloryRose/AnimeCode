#include <iostream>
#include "ReadData.h"

using namespace std;

int main() {
    ReadData data;
    data.loadData();
   data.printGenresMap();
 //  data.printData();

    return 0;
}
