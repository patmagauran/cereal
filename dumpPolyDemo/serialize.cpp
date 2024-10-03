#include "serializers.h"

#include "serialize.h"
#include <iostream>
#include <fstream>

using namespace std;
void writeToFile(Data & inputData, std::string filename) {
    cout << "Writing to file" << filename << endl;
     {
    std::ofstream os(filename );
    cereal::XMLOutputArchive oarchive( os );

    
    oarchive( ::cereal::make_nvp("data", inputData) );
  }

}
void readFromFile(Data & outputData, std::string filename) {
    cout << "Reading from file" << filename << endl;
{
    std::ifstream is( filename );
    cereal::XMLInputArchive iarchive( is );


    iarchive( ::cereal::make_nvp("data", outputData) );
  }
}
