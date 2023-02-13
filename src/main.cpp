#include<iostream>
#include <vector>
#include <list>
#include <map>

#include "version.h"

using namespace std;

int main (int arg, char *argv[])
{
    VersionInfo version;

    std::cout << "Cpp development framework!\n";


    if (arg != 2)
    {
        
        std::cout << "Missing parameter: input file name" << std::endl;
        exit(1);
      return 0;
    }

    else
    {
        version.getVersionInfo(argv[1]);
    }

    std::string s {"Test String"};
    std::vector<double> v (3, 3.14);
    std::list<int> l;

    l.push_back(3);
    l.push_back(1);
    l.push_back(3);


    std::map<int, int> testMap;
    testMap[7] = 2;
    testMap[2] = -987;
    
}