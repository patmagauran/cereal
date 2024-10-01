#include <string>
#include <vector>
#include <memory>
#ifndef CER_DATA_H
#define CER_DATA_H
class Vehicle
{
public:
    float weight;
    virtual void foo() = 0;
    Vehicle(float weight) : weight(weight) {}
    Vehicle(){};
    Vehicle(const Vehicle&) = delete;
Vehicle(Vehicle&&) = default;
};

class Car : public Vehicle
{
public:
    void foo() {};
    int occupants;
    Car(int occupants, float weight) : Vehicle(weight), occupants(occupants){};
    Car(){};
};

class Motorcycle : public Vehicle
{
public:
    void foo() {};

    int cc;
    Motorcycle(int cc, float weight) : Vehicle(weight), cc(cc){};
    Motorcycle(){};
};

enum PalletContents
{
    Boxes,
    Machinery,
    Barrels
};

struct Pallet
{
    float weight;
    PalletContents contents;
};

struct LooseBoxes
{
    int numBoxes;
};

struct FlatbedLoad
{
    std::string itemName;
};

template <class contents>
class Payload
{
public:
    contents item;
    float totalWeight;
    bool oversize;
};

template <class contents>
class SemiTruck : public Vehicle
{
public:
    void foo() {};

    Payload<contents> payload;
    SemiTruck(Payload<contents> payload, float weight) : Vehicle(weight), payload(payload){};
    SemiTruck(){};
//     template<class Archive>
//   void serialize( Archive & ar )
//   { archive(cereal::make_nvp("vehicle", cereal::base_class<Vehicle>(this)), CEREAL_NVP(payload)); }
    // template <class Archive>
    // void serialize(Archive &archive)
    // {
    //     archive(cereal::make_nvp("vehicle", cereal::base_class<Vehicle>(this)), CEREAL_NVP(payload));
    // };
};

//typedef std::vector<std::unique_ptr<Vehicle>> VehicleList;


class ParkingLot
{

public:
    std::string name;
    int numSpots;
    std::vector<std::unique_ptr<Vehicle>> parkedVehicles;
    ParkingLot() {}
    ParkingLot(std::string name, int numSpots): name(name), numSpots(numSpots) {}

        ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

//     ParkingLot(const ParkingLot& lot) : name(lot.name),
//      numSpots(lot.numSpots), parkedVehicles(std::move(lot.parkedVehicles)) {};
//     // Delete default copy constructor + assignment operator
//   //  ParkingLot(const ParkingLot &) = delete;
//     ParkingLot& operator= (const ParkingLot & lot) {
//         name = lot.name;
//         numSpots = lot.numSpots;
//         parkedVehicles = std::move(lot.parkedVehicles);
//     };
    ParkingLot& operator=(ParkingLot&& other) noexcept {
        if (this != &other) {
            parkedVehicles = std::move(other.parkedVehicles);
             name = other.name;
         numSpots = other.numSpots;
        }
        return *this;
    }
};

class MiscData
{
public:
    float revenue;
    float taxes;
};

class Data
{
public:
    std::string owner;
    int employees;
    ParkingLot parking;
    MiscData miscData;
    std::vector<std::string> employeeNames;
    Data() {};
        Data(const Data&) = delete;
    Data& operator=(const Data&) = delete;
};
#endif