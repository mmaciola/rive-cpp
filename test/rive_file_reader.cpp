#include "rive_file_reader.hpp"
#include "no_op_factory.hpp"

static rive::NoOpFactory gEmptyFactory;

RiveFileReader::RiveFileReader(const char path[], rive::Factory* factory) {
    if (!factory) {
        factory = &gEmptyFactory;
    }

    FILE* fp = fopen(path, "r");
    REQUIRE(fp != nullptr);

    fseek(fp, 0, SEEK_END);
    const size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    auto bytes = new uint8_t[length];
    REQUIRE(fread(bytes, 1, length, fp) == length);
    m_Reader = std::make_unique<rive::BinaryReader>(bytes, length);
    rive::ImportResult result;
    m_File = rive::File::import(factory, *m_Reader, &result);
    delete[] bytes;

    REQUIRE(result == rive::ImportResult::success);
    REQUIRE(m_File != nullptr);
    REQUIRE(m_File->artboard() != nullptr);
}
