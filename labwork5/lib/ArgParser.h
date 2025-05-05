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

private:
    struct Base {
        virtual ~Base() = default;
        std::string long_name;
        char short_name = 0;
        std::string description;
        bool positional = false;
        size_t min_count = 0;
        virtual bool isFlag() const = 0;
    };

    template<typename T>
    struct Typed : Base {
        std::vector<T> values;
        bool has_default = false;
        T default_value{};
        T* single_ptr = nullptr;
        std::vector<T>* multi_ptr = nullptr;
        bool isFlag() const override { return false; }
    };

    struct Flag : Base {
        bool value = false;
        bool has_default = false;
        bool default_value = false;
        bool* ptr = nullptr;
        bool isFlag() const override { return true; }
    };

    // help специальный флаг
    std::string help_description_;
    char help_short_ = 0;
    std::string help_long_;

    std::string prog_name_;
    bool help_requested_ = false;

    std::vector<std::unique_ptr<Base>> args_;
    Base* last_ = nullptr;
    std::unordered_map<std::string, Base*> long_map_;
    std::unordered_map<char, Base*> short_map_;

    // вспомогательные
    Base* findByLong(const std::string& name) const;
    Base* findByShort(char c) const;
    bool applyDefaultAndCheck();
};

} // namespace ArgumentParser
