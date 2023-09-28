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
}
