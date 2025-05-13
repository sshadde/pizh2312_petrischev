#pragma once

#include <cstdint>
#include <istream>
#include <memory>
#include <string>
#include <functional>
#include <ostream>
#include <iostream>

uint32_t readSyncSafeInt(std::istream& in);
uint32_t readBigEndianInt(std::istream& in);
std::string readBytesAsString(std::istream& in, size_t size);

class ID3Frame {
public:
    virtual ~ID3Frame() = default;
    virtual void parse(std::istream& in, uint32_t size) = 0;
    virtual void print(std::ostream& out = std::cout) const = 0;
};

class FrameFactory {
public:
    using Creator = std::function<std::unique_ptr<ID3Frame>(uint32_t)>;

    static void registerFrame(const std::string& id, Creator creator);

    static std::unique_ptr<ID3Frame> create(const std::string& id, uint32_t size);
};

void parseID3v2_4(std::istream& in, std::ostream& out = std::cout);

