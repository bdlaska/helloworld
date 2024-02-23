#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>

namespace fs = std::filesystem;

namespace {
    std::mutex mutex;
    bool fileFound = false;
    int activeThreads = 0;

    void searchInDirectory(const std::string& filename, const fs::path& directory) {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.path().filename() == filename) {
                mutex.lock();
                std::cout << "File found: " << entry.path() << std::endl;
                fileFound = true;
                mutex.unlock();
                return;
            } else if (entry.is_directory()) {
                mutex.lock();
                if (activeThreads < 8) {
                    activeThreads++;
                    mutex.unlock();
                    searchInDirectory(filename, entry.path()); // Recursive call without thread detachment
                } else {
                    mutex.unlock();
                    searchInDirectory(filename, entry.path());
                }
            }

            if (fileFound)
                return;
        }
        mutex.lock();
        activeThreads--;
        mutex.unlock();
    }
}

namespace FileSearch {
    void searchFile(const std::string& filename) {
        searchInDirectory(filename, "/");
    }
}
