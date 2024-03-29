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
    multiprecisionBits = stoi(chompLine(datFile, true));
    sampleRate = stoi(chompLine(datFile, true));
    length = stoi(chompLine(datFile, true));
    chompLine(datFile);
    string dataString;
    if (isMultiprecision)
        while (datFile >> dataString)
            data.push_back(SampleValue(true, multiprecisionBits, dataString));
    else
        while (datFile >> dataString)
            data.push_back(SampleValue(stod(dataString)));
    datFile.close();
}
