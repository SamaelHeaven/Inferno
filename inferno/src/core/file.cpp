#include "file.h"

namespace inferno::file {
    std::string format_path(std::string path) {
        std::ranges::replace(path, '\\', '/');
        const auto consecutive_separators = std::ranges::unique(path, [](const char a, const char b) {
            return a == '/' && b == '/';
        }).begin();
        path.erase(consecutive_separators, path.end());
        const auto start_pos = path.find_first_not_of(" \n\r\t/");
        const auto end_pos = path.find_last_not_of(" \n\r\t/");
        if (start_pos == std::string::npos) {
            return "";
        }
        return path.substr(start_pos, end_pos - start_pos + 1);
    }

    std::string path_of(const std::vector<std::string> &paths) {
        std::string result;
        for (const auto &path: paths) {
            result += path + "/";
        }
        return format_path(std::move(result));
    }

    std::string file_name(std::string path) {
        path = format_path(std::move(path));
        auto start = 0;
        for (auto i = 0; i < path.length(); i++) {
            if (path[i] == '/') {
                start = i;
            }
        }
        return format_path(path.substr(start));
    }

    std::string file_name_without_extension(std::string path) {
        path = format_path(std::move(path));
        const auto start = path.find_last_of('.');
        if (start == std::string::npos) {
            return path;
        }
        return path.substr(0, start);
    }

    std::string file_extension(std::string path) {
        path = format_path(std::move(path));
        const auto start = path.find_last_of('.');
        if (start == std::string::npos) {
            return "";
        }
        return path.substr(start + 1);
    }

    std::time_t file_modification_time(std::string path) {
        return internal::GetFileModTime(format_path(std::move(path)).c_str());
    }

    std::string get_directory(std::string path) {
        path = format_path(std::move(path));
        const auto start = path.find_last_of('/');
        if (start == std::string::npos) {
            return "";
        }
        return format_path(path.substr(0, start));
    }

    std::string get_previous_directory(std::string path) {
        return get_directory(get_directory(std::move(path)));
    }

    std::string get_working_directory() {
        return format_path(internal::GetWorkingDirectory());
    }

    void set_working_directory(std::string path) {
        internal::ChangeDirectory(format_path(std::move(path)).c_str());
    }

    std::string get_application_directory() {
        return format_path(internal::GetApplicationDirectory());
    }

    bool is_file(std::string path) {
        return internal::FileExists(format_path(std::move(path)).c_str());
    }

    bool is_directory(std::string path) {
        return internal::DirectoryExists(format_path(std::move(path)).c_str());
    }

    size_t file_size(std::string path) {
        path = format_path(std::move(path));
        if (!is_file(path)) {
            throw std::runtime_error("Requested file does not exists: \"" + path + "\"");
        }
        return internal::GetFileLength(path.c_str());
    }

    std::vector<std::string> directory_files(std::string path) {
        path = format_path(std::move(path));
        if (!is_directory(path)) {
            throw std::runtime_error("Requested directory does not exists: \"" + path + "\"");
        }
        std::vector<std::string> result;
        const auto files = internal::LoadDirectoryFiles(path.c_str());
        for (auto i = 0; i < files.count; i++) {
            result.push_back(format_path(files.paths[i]));
        }
        UnloadDirectoryFiles(files);
        return result;
    }

    std::string read_text(std::string path) {
        path = format_path(std::move(path));
        if (!is_file(path)) {
            throw std::runtime_error("Requested file does not exists: \"" + path + "\"");
        }
        const auto text = internal::LoadFileText(path.c_str());
        if (text == nullptr) {
            throw std::runtime_error("Failed to load text from: \"" + path + "\"");
        }
        const auto result = std::string(text);
        internal::UnloadFileText(text);
        return result;
    }

    void save_text(std::string path, const std::string &text) {
        path = format_path(std::move(path));
        const auto length = text.length();
        const auto buffer = std::make_unique<char[]>(length + 1);
        strncpy(buffer.get(), text.c_str(), length);
        buffer[length] = '\0';
        if (!internal::SaveFileText(path.c_str(), buffer.get())) {
            throw std::runtime_error("Failed to save file: \"" + path + "\"");
        }
    }

    std::vector<uint8_t> read_bytes(std::string path) {
        path = format_path(std::move(path));
        auto size = static_cast<int32_t>(file_size(path));
        const auto data = internal::LoadFileData(path.c_str(), &size);
        std::vector<uint8_t> result;
        for (auto i = 0; i < size; i++) {
            result.push_back(data[i]);
        }
        internal::UnloadFileData(data);
        return result;
    }

    void save_bytes(std::string path, const std::vector<uint8_t> &bytes) {
        path = format_path(std::move(path));
        const auto size = static_cast<int32_t>(bytes.size());
        const auto data = std::make_unique<uint8_t[]>(size);
        memcpy(data.get(), bytes.data(), size);
        if (!internal::SaveFileData(path.c_str(), data.get(), size)) {
            throw std::runtime_error("Failed to save file: \"" + path + "\"");
        }
    }
}
