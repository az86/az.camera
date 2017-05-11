#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

//#include <boost/serialization/version.hpp> 
#include <string>
#include <fstream>
#include <vector>
#include <map>
struct A
{
    
};
int main()
{
    int width = 1280;
    int height = 1924;
    std::vector<int> cmd{ 0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xf6,0xa7,0xa8,0xa8 };
    std::vector<int> cmd1{1234,2,3,4,5,56,6,7,8,8};
    std::map<std::string, std::vector<int>> configs;
    configs["xxx cmd"] = cmd;
    configs["abc cmd"] = cmd1;
    std::ofstream ifile("a.xml");
    boost::archive::xml_oarchive ar(ifile);
    ar & BOOST_SERIALIZATION_NVP(width);
    ar & BOOST_SERIALIZATION_NVP(height);

    ifile << std::hex;
    ar & BOOST_SERIALIZATION_NVP(configs);

    return 0;
}