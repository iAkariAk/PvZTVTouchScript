// Created by 12595 on 2023/6/17.
//

#include "FUtils.h"
#include <fstream>
#include <sstream>

namespace fairy::utils {
    uint64_t gLibBaseOffset = 0;
    JavaVM *gJavaVM = nullptr;
    const char *gLocale = nullptr;
    AAssetManager *gAAssetManager = nullptr;
    std::string gCacheDir = "";

    void Init() {
        if (gLibBaseOffset == 0) {
            std::string filename = "/proc/self/maps";
            std::ifstream file(filename);
            if (!file.is_open()) {
                LogError("Can not open dll file: %s", filename.c_str());
                return;
            }

            std::string line;
            while (std::getline(file, line)) {
                if (line.find(DLL_NAME) != std::string::npos) {
                    std::stringstream ss(line);
                    ss >> std::hex >> gLibBaseOffset;
                    break;
                }
            }
            file.close();
        }
        LogDebug("Base Address: 0x%llx", gLibBaseOffset);
    }

    void InitJni(JavaVM *vm) {
        LogDebug("Initialize jni");
        gJavaVM = vm;
    }

    void TaskQueue::submit(Task task) {
        tasks.push_back(task);
    }

    void TaskQueue::execute() {
        tasksMutex.lock();
        for (auto &task: tasks) {
            task();
        }
        tasks.clear();
        tasksMutex.unlock();
    }

    void ClearFolder(const std::string &path, bool clearSubFolder) {
        for (auto &entry: std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file()) {
                std::filesystem::remove(entry);
            } else if (entry.is_directory() && clearSubFolder) {
                ClearFolder(entry.path().string(), true);
            }
        }
    }
}
