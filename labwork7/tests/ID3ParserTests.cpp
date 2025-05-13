#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "ID3Parser.h"

TEST(UtilsTest, ReadSyncSafeInt) {
    std::vector<uint8_t> bytes = {0x00, 0x00, 0x02, 0x10};
    std::stringstream ss;
    ss.write(reinterpret_cast<char*>(bytes.data()), bytes.size());
    uint32_t value = readSyncSafeInt(ss);
    EXPECT_EQ(value, (0x00u << 21) | (0x00u << 14) | (0x02u << 7) | 0x10u);
}

TEST(UtilsTest, ReadBigEndianInt) {
    std::vector<uint8_t> bytes = {0x01, 0x02, 0x03, 0x04};
    std::stringstream ss;
    ss.write(reinterpret_cast<char*>(bytes.data()), bytes.size());
    uint32_t value = readBigEndianInt(ss);
    EXPECT_EQ(value, 0x01020304u);
}

TEST(UtilsTest, ReadBytesAsString) {
    std::string input = "HelloWorld";
    std::stringstream ss(input);
    std::string out = readBytesAsString(ss, 5);
    EXPECT_EQ(out, "Hello");
}

TEST(FrameFactoryTest, CreateUnknownFrame) {
    auto frame = FrameFactory::create("XXXX", 10);
    std::stringstream ss(std::string(10, 'A'));
    EXPECT_NO_THROW(frame->parse(ss, 10));
}

TEST(TextFrameTest, ParseAndPrintViaFactory) {
    std::stringstream dummyIn("ABC");
    std::stringstream dummyOut;
    parseID3v2_4(dummyIn, dummyOut);

    std::string text = "Test";
    uint32_t size = static_cast<uint32_t>(text.size() + 1);
    std::string payload;
    payload.push_back(0x00);
    payload += text;
    std::stringstream ss(payload);

    auto frame = FrameFactory::create("TIT2", size);
    frame->parse(ss, size);
    std::stringstream out;
    frame->print(out);
    std::string expected = "Title     : Test\n";
    EXPECT_EQ(out.str(), expected);
}

TEST(ParseID3Test, NonID3Header) {
    std::stringstream ss("ABC");
    std::stringstream out;
    parseID3v2_4(ss, out);
    EXPECT_EQ(out.str(), "This is not an ID3 tag\n");
}

TEST(ParseID3Test, SimpleTag) {
    std::stringstream ss(std::ios::binary | std::ios::in | std::ios::out);
    ss.write("ID3", 3);
    ss.put(4).put(0).put(0);
    std::streampos sizePos = ss.tellp();
    ss.write("\0\0\0\0", 4);

    ss.write("TIT2", 4);

    ss.write("\0\0\0\3", 4);
    ss.write("\0\0", 2);
    ss.put(0x00);
    ss.write("Hi", 2);

    uint32_t tagSize = 10 + 3;
    ss.seekp(sizePos);
    uint8_t b0 = (tagSize >> 21) & 0x7F;
    uint8_t b1 = (tagSize >> 14) & 0x7F;
    uint8_t b2 = (tagSize >> 7) & 0x7F;
    uint8_t b3 = tagSize & 0x7F;
    ss.put(b0).put(b1).put(b2).put(b3);

    ss.seekg(0);
    std::stringstream out;
    parseID3v2_4(ss, out);

    std::string expectedHeader = "ID3v2.4.0  flags=0  size=" + std::to_string(tagSize) + "\n\n";
    std::string expectedFrame = "Title     : Hi\n";
    EXPECT_EQ(out.str(), expectedHeader + expectedFrame);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

