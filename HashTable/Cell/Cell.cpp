#include "Cell.h"
#include<iostream>
#include<algorithm>
#include<fstream>
#include <cstring>
#include <string>

using namespace std;
Cell::Cell(string word)
{
    this->word=word;
    duplicates = 1;

}
