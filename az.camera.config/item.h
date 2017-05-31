#pragma once
struct item
{
    unsigned char reqCode;
    unsigned short value;
    unsigned short index;
    template<typename Archive>
    void serialize(Archive& ar, const unsigned version);
};

