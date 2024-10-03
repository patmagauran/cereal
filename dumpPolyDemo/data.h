#include <string>
#include <vector>
#include <memory>
#include <iostream>
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
    void foo() {std::cout << "CAR" << occupants << std::endl;};
    int occupants;
    Car(int occupants, float weight) : Vehicle(weight), occupants(occupants){};
    Car(){};
};

class Motorcycle : public Vehicle
{
public:
    void foo() {std::cout << "Motor" << cc << std::endl;};

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
        friend std::ostream & operator << (std::ostream &out, const Pallet &c);

};

struct LooseBoxes
{
    int numBoxes;
        friend std::ostream & operator << (std::ostream &out, const LooseBoxes &c);

};

struct FlatbedLoad
{
    std::string itemName;
            friend std::ostream & operator << (std::ostream &out, const FlatbedLoad &c);

};

template <class contents>
class Payload
{
public:
    contents item;
    float totalWeight;
    bool oversize;
    template <class contents1>
    friend std::ostream & operator << (std::ostream &out, const Payload<contents1> &c);


 
};

inline std::ostream & operator << (std::ostream &out, const FlatbedLoad &c)
{
    out << c.itemName;
    return out;
}

inline std::ostream & operator << (std::ostream &out, const LooseBoxes &c)
{
    out << c.numBoxes;
    return out;
}

inline std::ostream & operator << (std::ostream &out, const Pallet &c)
{
    out << c.weight << " " << c.contents;
    return out;
}



template <class contents>
std::ostream & operator << (std::ostream &out, const Payload<contents> &c)
{
    out << c.totalWeight << " " << c.oversize << " " << c.item;
    return out;
}

template <class contents>
class SemiTruck : public Vehicle
{
public:
    void foo() {std::cout << "semi" << payload << std::endl;};

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