#include "data.h"
#include "serialize.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello World" << endl;

    Payload<Pallet> palletLoad = {
        .item = {
            .weight = 934.1,
            .contents = PalletContents::Barrels},
        .totalWeight = 954.32,
        .oversize = false};
    Payload<LooseBoxes> looseBoxesLoad = {
        .item = {
            .numBoxes = 324},
        .totalWeight = 845.26,
        .oversize = false};
    Payload<FlatbedLoad> flatbedLoad = {
        .item = {
            .itemName = "Excavator"},
        .totalWeight = 26984.68,
        .oversize = true};

    std::unique_ptr<Motorcycle> cycle = std::make_unique<Motorcycle>(120, 501);

    std::unique_ptr<Car> car = std::make_unique<Car>(4, 2300);

    std::unique_ptr<SemiTruck<Pallet>> palletTruck = std::make_unique<SemiTruck<Pallet>>(palletLoad, 8000);
    std::unique_ptr<SemiTruck<LooseBoxes>> looseTruck = std::make_unique<SemiTruck<LooseBoxes>>(looseBoxesLoad, 7500);
    std::unique_ptr<SemiTruck<FlatbedLoad>> flatBedTruck = std::make_unique<SemiTruck<FlatbedLoad>>(flatbedLoad, 32000);


std::vector<std::unique_ptr<Vehicle>> parkedVehicles;

   // ParkingLot lot("5th Street Parking",34);
    
    {
        Data data;
        
        data.owner = "Bob";
            data.employees = 4;
            data.miscData = {
                .revenue = 10000,
                .taxes = 5000};
            data.employeeNames.push_back("Joe Smith");
            data.employeeNames.push_back("Jane Doe");
            data.employeeNames.push_back("Bill Gates");
                data.parking.name = "5th Street Parking";
                data.parking.numSpots = 34;
data.parking.parkedVehicles.push_back(std::make_unique<Motorcycle>(120, 501));
     data.parking.parkedVehicles.push_back(std::make_unique<Car>(4, 2300));
     data.parking.parkedVehicles.push_back(std::make_unique<SemiTruck<Pallet>>(palletLoad, 8000));
     data.parking.parkedVehicles.push_back(std::make_unique<SemiTruck<LooseBoxes>>(looseBoxesLoad, 7500));
     data.parking.parkedVehicles.push_back(std::make_unique<SemiTruck<FlatbedLoad>>(flatbedLoad, 32000));
        writeToFile(data, "Data.xml");
    }

    // {
    //     Data data;

    //     readFromFile(data, "Data.xml");
    //         cin.ignore();

    // }


    return 0;
}