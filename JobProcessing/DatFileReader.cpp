#include "DatFileReader.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "StringUtils.h"

using namespace std;
using namespace StringUtils;

void DatFileReader::getData(int modOutId)
{
    ifstream datFile {"ModOut" + to_string(modOutId) + ".dat"};
    this->modOutId = stoi(chompLine(datFile, true));
    isMultiprecision = (chompLine(datFile, true) == "multiprecision") ?
                       true :
                       false;
    datFile.close();
}
