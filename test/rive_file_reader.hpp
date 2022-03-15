#ifndef _RIVE_FILE_READER_HPP_
#define _RIVE_FILE_READER_HPP_

#include <rive/core/binary_reader.hpp>
#include <rive/factory.hpp>
#include <rive/file.hpp>
#include "rive_testing.hpp"

class RiveFileReader {
    std::unique_ptr<rive::File> m_File;
    std::unique_ptr<rive::BinaryReader> m_Reader;

public:
    RiveFileReader(const char path[], rive::Factory* = nullptr);

    rive::File* file() const { return m_File.get(); }
};

#endif
