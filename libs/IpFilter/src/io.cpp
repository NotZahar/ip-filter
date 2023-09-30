#include "io.h"
#include "helper.h"

namespace filter {
    IO::IO(inputType type, const std::optional<std::filesystem::path>& filePath) 
        :  _type(type), _filePath() 
    {
        if (_type == inputType::file)
            _filePath = (filePath ? filePath : paths::EXAMPLE_FILE_PATH);
    }

    std::optional<std::filesystem::path> IO::getFilePath() const {
        return _filePath;
    }

    std::ostream& operator<<(std::ostream& stream, const IO& io) {
        stream << io._filePath.value_or(messages::NO_FILE_PATH) << std::endl;
        return stream;
    }

    void IO::outAddress(const std::vector<int>& addr) const {
        std::cout << addr[0] << '.' << addr[1] << '.' << addr[2] << '.' << addr[3] << '\n';
    }

    bool IO::bytePositionIsValid(bytePosition pos) const {
        return (pos > 0) || (pos < 5);
    }
}
