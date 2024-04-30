#ifndef TOPFILM_FILE_MAIN_H
#define TOPFILM_FILE_MAIN_H

#include <iostream>
#include <filesystem>
#include <vector>
#include <random>

std::vector<std::string> getFilesInDirectory(const std::filesystem::path& directory) {
    std::vector<std::string> files;
    for (const auto& item : std::filesystem::directory_iterator(directory)) {
        if (item.is_regular_file()) {
            files.push_back(item.path().filename().string());
        }
    }
    return files;
}

std::string chooseRandomFile(const std::filesystem::path &directory) {
    std::vector<std::string> files = getFilesInDirectory(directory);
    std::cout << "Files in the directory: " << std::endl;
    std::for_each(files.begin(), files.end(), [](std::string &file) -> void {
        std::cout << file << ", ";
    });
    std::cout << std::endl;
    if (files.empty()) {
        return "";
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, files.size() - 1);
    return files[distrib(gen)];
}

int fileMain() {
    std::filesystem::path directory = ".";
    std::string secretFile = chooseRandomFile(directory);
    if (secretFile.empty()) {
        std::cout << "No files in the directory." << std::endl;
        return 1;
    }

    std::cout << "Guess the name of the file in the directory." << std::endl;
    int attempts = 3;
    std::string guess;
    while (attempts-- > 0) {
        std::cin >> guess;
        if (guess == secretFile) {
            std::cout << "You win! Correct file is " << secretFile << std::endl;
            return 0;
        } else {
            std::cout << "Wrong, try again." << std::endl;
        }
    }

    std::cout << "Computer wins! The file was: " << secretFile << std::endl;
    return 0;
}

#endif //TOPFILM_FILE_MAIN_H