#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <sstream>

namespace ArgumentParser {

class ArgParser {
public:
    explicit ArgParser(const std::string& program_name);

    // создание аргументов
    ArgParser& AddStringArgument(const std::string& name, const std::string& description = "");
    ArgParser& AddStringArgument(char short_name, const std::string& long_name, const std::string& description = "");

    ArgParser& AddIntArgument(const std::string& name, const std::string& description = "");
    ArgParser& AddIntArgument(char short_name, const std::string& long_name, const std::string& description = "");

    ArgParser& AddFlag(const std::string& long_name, const std::string& description = "");
    ArgParser& AddFlag(char short_name, const std::string& long_name, const std::string& description = "");

    ArgParser& AddHelp(char short_name, const std::string& long_name, const std::string& description = "");

    // модификаторы последнего добавленного аргумента
    ArgParser& Default(const std::string& val);
    ArgParser& Default(const char* val);
    ArgParser& Default(int val);
    ArgParser& Default(bool val);

    ArgParser& MultiValue(size_t min_count = 0);
    ArgParser& Positional();

    ArgParser& StoreValue(std::string& ref);
    ArgParser& StoreValue(int& ref);
    ArgParser& StoreValue(bool& ref);

    ArgParser& StoreValues(std::vector<std::string>& ref);
    ArgParser& StoreValues(std::vector<int>& ref);

    // парсинг
    bool Parse(int argc, char** argv);
    bool Parse(const std::vector<std::string>& args);

    // помощь
    bool Help() const;
    std::string HelpDescription() const;

    // геттеры
    std::string GetStringValue(const std::string& name) const;
    int GetIntValue(const std::string& name, size_t idx = 0) const;
    bool GetFlag(const std::string& name) const;
};

} // namespace ArgumentParser
