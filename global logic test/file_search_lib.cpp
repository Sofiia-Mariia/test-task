#include "file_search_lib.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>

namespace file_search_lib {
    namespace fs = std::filesystem;

    namespace {
        std::mutex searchMutex;
        bool stopSearching = false;
    }

    std::string FileSearch::findFile(const std::string& rootDirectory, const std::string& fileName) {
        fs::path rootPath(rootDirectory);
        std::vector<std::thread> threads;
        std::string foundPath;

        for (const auto& entry : fs::recursive_directory_iterator(rootPath)) {
            if (stopSearching) break;

            if (entry.is_regular_file() && entry.path().filename() == fileName) {
                foundPath = entry.path().string();
                stopSearch();
                break;
            }
        }

        for (auto& thread : threads) {
            if (thread.joinable())
                thread.join();
        }

        return foundPath;
    }

    void FileSearch::stopSearch() {
        std::lock_guard<std::mutex> lock(searchMutex);
        stopSearching = true;
    }
}
