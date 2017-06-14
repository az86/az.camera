#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include "CommandConfig.h"

CommandConfig::CommandConfig()
{
    std::ifstream ifile("config/cmds.xml");
    if (ifile.is_open())
    {
        printf("load config config / cmds.xml ok\n");
    }
    boost::archive::xml_iarchive ar(ifile);
    ifile >> std::hex;
    ar & BOOST_SERIALIZATION_NVP(configs);
}
CommandConfig & CommandConfig::Instance()
{
    static CommandConfig instance;
    return instance;
}