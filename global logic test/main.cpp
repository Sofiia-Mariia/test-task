#include <iostream>
#include "file_search_lib.h"
#include <thread>
#include <vector>
#include <filesystem>
using namespace std;
using namespace file_search_lib;

const int MAX_THREADS = 8;

void searchSubDirectory(const std::string& subDir, const std::string& fileName) {
    std::string result = FileSearch::findFile(subDir, fileName);
    if (!result.empty()) {
        cout << "File found: " << result << "\n";
    }
}

int main() {
    const std::string rootDirectory = "C:\\";
    const std::string fileName = "file to be found";

    std::vector<std::thread> searchThreads;
    for (const auto& entry : std::filesystem::directory_iterator(rootDirectory)) {
        if (std::filesystem::is_directory(entry)) {
            if (searchThreads.size() >= MAX_THREADS) {
                for (auto& thread : searchThreads) {
                    if (thread.joinable()) {
                        thread.join();
                    }
                }
                searchThreads.clear();
            }
            searchThreads.emplace_back(searchSubDirectory, entry.path().string(), fileName);
        }
    }

    for (auto& thread : searchThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
