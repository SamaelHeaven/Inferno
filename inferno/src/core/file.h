#pragma once

#include "../inferno.h"

namespace inferno::file {
    std::string format_path(std::string path);

    std::string path_from_project(std::string path);

    std::string path_of(const std::vector<std::string> &paths);

    std::string file_name(std::string path);

    std::string file_name_without_extension(std::string path);

    std::string file_extension(std::string path);

    std::time_t file_modification_time(std::string path);

    std::string directory_from(std::string path);

    std::string previous_directory_from(std::string path);

    std::string get_working_directory();

    void set_working_directory(std::string path);

    std::string get_application_directory();

    bool is_file(std::string path);

    bool is_directory(std::string path);

    size_t file_size(std::string path);

    std::vector<std::string> directory_files(std::string path);

    std::string read_text(std::string path);

    void save_text(std::string path, const std::string &text);

    std::vector<uint8_t> read_bytes(std::string path);

    void save_bytes(std::string path, const std::vector<uint8_t> &bytes);
}
