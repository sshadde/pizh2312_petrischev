#include "ID3Parser.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>

// ——————————————————————————————————————————————————————————
// УТИЛИТЫ
// ——————————————————————————————————————————————————————————

uint32_t readSyncSafeInt(std::istream& in) {
    uint8_t b[4];
    in.read(reinterpret_cast<char*>(b), 4);
    return (b[0] << 21) |
           (b[1] << 14) |
           (b[2] <<  7) |
           (b[3]      );
}

uint32_t readBigEndianInt(std::istream& in) {
    uint8_t b[4];
    in.read(reinterpret_cast<char*>(b), 4);
    return (b[0] << 24) |
           (b[1] << 16) |
           (b[2] <<  8) |
           (b[3]      );
}

std::string readBytesAsString(std::istream& in, size_t size) {
    std::string s(size, '\0');
    in.read(&s[0], size);
    return s;
}

// ——————————————————————————————————————————————————————————
// БАЗОВЫЕ КЛАССЫ ФРЕЙМОВ
// ——————————————————————————————————————————————————————————

class UnknownFrame : public ID3Frame {
    std::string id_;
    uint32_t    size_;
public:
    UnknownFrame(const std::string& id, uint32_t size)
      : id_(id), size_(size) {}

    void parse(std::istream& in, uint32_t) override {
        in.seekg(size_, std::ios::cur);
    }
    void print(std::ostream& /*out*/) const override {
        // ничего не выводим
    }
};

class TextFrame : public ID3Frame {
    std::string id_;
    uint32_t    size_;
    std::string text_;
public:
    TextFrame(const std::string& id, uint32_t size)
     : id_(id), size_(size) {}

    void parse(std::istream& in, uint32_t size) override {
        if (size == 0) return;
        in.get();
        text_ = readBytesAsString(in, size - 1);
    }

    void print(std::ostream& out) const override {
        std::string label;
        if      (id_ == "TIT2") label = "Title";
        else if (id_ == "TPE1") label = "Artist";
        else if (id_ == "TALB") label = "Album";
        else if (id_ == "TDRC") label = "Year";
        else if (id_ == "TCON") label = "Genre";
        else                    label = id_;
        out << std::left << std::setw(10)
            << label << ": " << text_ << "\n";
    }
};

// ——————————————————————————————————————————————————————————
// FrameFactory
// ——————————————————————————————————————————————————————————

using Creator = FrameFactory::Creator;

static std::map<std::string, Creator>& registry() {
    static std::map<std::string, Creator> inst;
    return inst;
}

void FrameFactory::registerFrame(const std::string& id, Creator creator) {
    registry()[id] = std::move(creator);
}

std::unique_ptr<ID3Frame> FrameFactory::create(const std::string& id, uint32_t size) {
    auto it = registry().find(id);
    if (it != registry().end())
        return it->second(size);
    return std::make_unique<UnknownFrame>(id, size);
}

// явная регистрация всех текстовых фреймов
static void registerDefaultTextFrames() {
    static bool done = false;
    if (done) return;
    done = true;
    auto reg = [](const std::string& id){
        FrameFactory::registerFrame(
            id,
            [id](uint32_t sz){ return std::make_unique<TextFrame>(id, sz); }
        );
    };
    reg("TIT2");
    reg("TPE1");
    reg("TALB");
    reg("TDRC");
    reg("TCON");
}

// ——————————————————————————————————————————————————————————
// ПАРСЕР ID3v2.4
// ——————————————————————————————————————————————————————————

void parseID3v2_4(std::istream& in, std::ostream& out) {
    registerDefaultTextFrames();

    char sig[3];
    in.read(sig, 3);
    if (std::string(sig,3) != "ID3") {
        out << "This is not an ID3 tag\n";
        return;
    }
    uint8_t ver1 = in.get();
    uint8_t ver2 = in.get();
    uint8_t flags = in.get();
    uint32_t tagSize = readSyncSafeInt(in);

    out << "ID3v2." << int(ver1) << "." << int(ver2)
        << "  flags=" << int(flags)
        << "  size="  << tagSize << "\n\n";

    uint32_t readTotal = 0;
    while (readTotal + 10 <= tagSize && in.good()) {
        char idbuf[4];
        in.read(idbuf, 4);
        if (!in) break;
        std::string fid(idbuf, 4);
        if (fid == "\0\0\0\0") break;

        uint32_t fsz = readSyncSafeInt(in);
        in.ignore(2);

        if (readTotal + 10 + fsz > tagSize) break;

        auto frame = FrameFactory::create(fid, fsz);
        frame->parse(in, fsz);
        frame->print(out);

        readTotal += 10 + fsz;
    }
}

