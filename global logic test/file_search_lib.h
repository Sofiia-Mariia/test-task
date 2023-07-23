#ifndef FILE_SEARCH_LIB_H
#define FILE_SEARCH_LIB_H

#include <string>

namespace file_search_lib {
    class FileSearch {
    public:
        static std::string findFile(const std::string& rootDirectory, const std::string& fileName);
        static void stopSearch();
    };
}

#endif 
