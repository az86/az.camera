#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "item.h"

template <typename Archive>
void item::serialize(Archive& ar, const unsigned version)
{
    ar & BOOST_SERIALIZATION_NVP(reqCode)
        & BOOST_SERIALIZATION_NVP(value)
        & BOOST_SERIALIZATION_NVP(index);
}

void special()
{
    item a;
    boost::archive::xml_iarchive *pxml = nullptr;
    a.serialize(*pxml, 0);
}