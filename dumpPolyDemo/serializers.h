#include "data.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>

#include <cereal/types/polymorphic.hpp>
// Include any archives you plan on using with your type before you register it
// Note that this could be done in any other location so long as it was prior
// to this file being included


#define EXTERNAL_NVP(val) cereal::make_nvp(#val, m.val)

#define VBC(base) cereal::make_nvp(#base, cereal::base_class<base>(&m))
  namespace detail
  {
    struct PlainPolymorphCore {};
  }

template <class T>
  class PlainPolymorph : detail::PlainPolymorphCore
  {
    private:
      // If we get passed an array, keep the type as is, otherwise store
      // a reference if we were passed an l value reference, else copy the value
      using Type = typename std::conditional<std::is_array<typename std::remove_reference<T>::type>::value,
                                             typename std::remove_cv<T>::type,
                                             typename std::conditional<std::is_lvalue_reference<T>::value,
                                                                       T,
                                                                       typename std::decay<T>::type>::type>::type;

      // prevent nested nvps
      // static_assert( !std::is_base_of<detail::NameValuePairCore, T>::value,
      //                "Cannot pair a name to a NameValuePair" );

      PlainPolymorph & operator=( PlainPolymorph const & ) = delete;

    public:
      //! Constructs a new PlainPolymorph
      /*! @param v The value to pair.  Ideally this should be an l-value reference so that
                   the value can be both loaded and saved to.  If you pass an r-value reference,
                   the PlainPolymorph will store a copy of it instead of a reference.  Thus you should
                   only pass r-values in cases where this makes sense, such as the result of some
                   size() call.
          @internal */
      PlainPolymorph( T && v ) : value(std::forward<T>(v)) {}

      Type value;
  };

  // template<class T> inline
  //   PlainPolymorph<T>  make_pp(  T && value)
  // {
  //   return {std::forward<T>(value)};
  // }




template <class Archive>
void serialize(Archive &archive, Data &m)
{
    archive(EXTERNAL_NVP(owner), EXTERNAL_NVP(employees), EXTERNAL_NVP(parking), EXTERNAL_NVP(miscData)
    //,cereal::make_nvp("employeeNames", cereal::make_pp<std::vector<std::string>&>(m.employeeNames))
    );
};
template <class Archive>
void serialize(Archive &archive, MiscData &m)
{
    archive(EXTERNAL_NVP(revenue), EXTERNAL_NVP(taxes));
};
template <class Archive>
void serialize(Archive &archive, ParkingLot &m)
{
    archive(EXTERNAL_NVP(name), EXTERNAL_NVP(numSpots), cereal::make_nvp("parkedVehicles", cereal::make_pp(m.parkedVehicles)));
};



namespace cereal {




template <class Archive, class contents>
void serialize(Archive &archive, SemiTruck<contents> &m)
{
    archive(VBC(Vehicle), EXTERNAL_NVP(payload));
};

template <class Archive, class contents>
void serialize(Archive &archive, Payload<contents> &m)
{
    archive( EXTERNAL_NVP(item),EXTERNAL_NVP(totalWeight),EXTERNAL_NVP(oversize));
};

// template <class Archive>
// void serialize(Archive &archive, SemiTruck<LooseBoxes> &m)
// {
//     archive(VBC(Vehicle), EXTERNAL_NVP(payload));
// };
// template <class Archive>
// void serialize(Archive &archive, SemiTruck<FlatbedLoad> &m)
// {
//     archive(VBC(Vehicle), EXTERNAL_NVP(payload));
// };
}
template <class Archive>
void serialize(Archive &archive, Car &m)
{
    archive(VBC(Vehicle), EXTERNAL_NVP(occupants));
};
template <class Archive>
void serialize(Archive &archive, Motorcycle &m)
{
    archive(VBC(Vehicle), EXTERNAL_NVP(cc));
};
template <class Archive>
void serialize(Archive &archive, FlatbedLoad &m)
{
    archive(EXTERNAL_NVP(itemName));
};
template <class Archive>
void serialize(Archive &archive, LooseBoxes &m)
{
    archive(EXTERNAL_NVP(numBoxes));
};
template <class Archive>
void serialize(Archive &archive, Pallet &m)
{
    archive(EXTERNAL_NVP(weight), EXTERNAL_NVP(contents));
};
template <class Archive>
void serialize(Archive &archive, Vehicle &m)
{
    archive(EXTERNAL_NVP(weight));
};

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

// Register DerivedClassOne
CEREAL_REGISTER_TYPE(Motorcycle);
CEREAL_REGISTER_TYPE(Car);
// namespace cereal
// {
//     namespace detail
//     {
//         template <>
//         struct binding_name<SemiTruck<Pallet>>
//         {
//             static constexpr char const *name() { return "SemiTruck<Pallet>"; }
//         };
//          template <>
//         struct binding_name<SemiTruck<LooseBoxes>>
//         {
//             static constexpr char const *name() { return "SemiTruck<LooseBoxes>"; }
//         };
//          template <>
//         struct binding_name<SemiTruck<FlatbedLoad>>
//         {
//             static constexpr char const *name() { return "SemiTruck<FlatbedLoad>"; }
//         };
//     }
// }
// namespace cereal
// {
//     namespace detail
//     {
//         template <class contents>
//         struct init_binding<SemiTruck<contents>>
//         {
//             static inline bind_to_archives<SemiTruck<contents>> const &b = ::cereal::detail::StaticObject<bind_to_archives<SemiTruck<contents>>>::getInstance().bind();
//         };
//     }
// };

CEREAL_REGISTER_TYPE_WITH_NAME(SemiTruck<Pallet>, "PalletTruck");
CEREAL_REGISTER_TYPE_WITH_NAME(SemiTruck<LooseBoxes>, "BoxTruck");
CEREAL_REGISTER_TYPE_WITH_NAME(SemiTruck<FlatbedLoad>, "FlatbedTruck");
CEREAL_REGISTER_DYNAMIC_INIT(cer)
CEREAL_FORCE_DYNAMIC_INIT(cer)

// CEREAL_REGISTER_TYPE(SemiTruck<LooseBoxes>);
// CEREAL_REGISTER_TYPE(SemiTruck<FlatbedLoad>);

// Register EmbarassingDerivedClass with a less embarrasing name
