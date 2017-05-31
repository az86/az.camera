#pragma once
#include <vector>
#include <map>
#include "item.h"
#pragma warning(disable:4251)
#ifdef AZ_CAMERA_CONFIG_DLLEXT
#define AZ_CAMERA_CONFIG_DLLEXT_CLS __declspec(dllexport)
#else
#define AZ_CAMERA_CONFIG_DLLEXT_CLS __declspec(dllimport)
#endif
struct AZ_CAMERA_CONFIG_DLLEXT_CLS CommandConfig
{
    std::map<std::string, std::vector<item>> configs;
    static CommandConfig & Instance();
private:
    CommandConfig();
};