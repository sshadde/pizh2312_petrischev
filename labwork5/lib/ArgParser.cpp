#include "ArgParser.h"
#include <algorithm>
#include <iostream>

using namespace ArgumentParser;

// конструктор
ArgParser::ArgParser(const std::string& program_name)
: prog_name_(program_name) {}

// добавление аргументов
ArgParser& ArgParser::AddStringArgument(const std::string& name, const std::string& desc) {
    auto p = std::make_unique<Typed<std::string>>();
    p->long_name = name;
    p->description = desc;
    args_.push_back(std::move(p));
    last_ = args_.back().get();
    long_map_[name] = last_;
    return *this;
}

ArgParser& ArgParser::AddStringArgument(char s, const std::string& name, const std::string& desc) {
    AddStringArgument(name, desc);
    last_->short_name = s;
    short_map_[s] = last_;
    return *this;
}

ArgParser& ArgParser::AddIntArgument(const std::string& name, const std::string& desc) {
    auto p = std::make_unique<Typed<int>>();
    p->long_name = name;
    p->description = desc;
    args_.push_back(std::move(p));
    last_ = args_.back().get();
    long_map_[name] = last_;
    return *this;
}

ArgParser& ArgParser::AddIntArgument(char s, const std::string& name, const std::string& desc) {
    AddIntArgument(name, desc);
    last_->short_name = s;
    short_map_[s] = last_;
    return *this;
}

ArgParser& ArgParser::AddFlag(const std::string& name, const std::string& desc) {
    auto p = std::make_unique<Flag>();
    p->long_name = name;
    p->description = desc;
    args_.push_back(std::move(p));
    last_ = args_.back().get();
    long_map_[name] = last_;
    return *this;
}

ArgParser& ArgParser::AddFlag(char s, const std::string& name, const std::string& desc) {
    AddFlag(name, desc);
    last_->short_name = s;
    short_map_[s] = last_;
    return *this;
}

ArgParser& ArgParser::AddHelp(char s, const std::string& name, const std::string& desc) {
    help_short_ = s;
    help_long_ = name;
    help_description_ = desc;
    return AddFlag(s, name, desc);
}

// модификаторы
ArgParser& ArgParser::Default(const std::string& val) {
    auto t = dynamic_cast<Typed<std::string>*>(last_);
    t->has_default = true;
    t->default_value = val;
    return *this;
}

ArgParser& ArgParser::Default(const char* val) {
    return Default(std::string(val));
}

ArgParser& ArgParser::Default(int val) {
    auto t = dynamic_cast<Typed<int>*>(last_);
    t->has_default = true;
    t->default_value = val;
    return *this;
}

ArgParser& ArgParser::Default(bool val) {
    auto f = dynamic_cast<Flag*>(last_);
    f->has_default = true;
    f->default_value = val;
    return *this;
}

ArgParser& ArgParser::MultiValue(size_t min_count) {
    last_->min_count = min_count;
    return *this;
}

ArgParser& ArgParser::Positional() {
    last_->positional = true;
    return *this;
}

ArgParser& ArgParser::StoreValue(std::string& ref) {
    auto t = dynamic_cast<Typed<std::string>*>(last_);
    t->single_ptr = &ref;
    return *this;
}

ArgParser& ArgParser::StoreValue(int& ref) {
    auto t = dynamic_cast<Typed<int>*>(last_);
    t->single_ptr = &ref;
    return *this;
}

ArgParser& ArgParser::StoreValue(bool& ref) {
    auto f = dynamic_cast<Flag*>(last_);
    f->ptr = &ref;
    return *this;
}

ArgParser& ArgParser::StoreValues(std::vector<std::string>& ref) {
    auto t = dynamic_cast<Typed<std::string>*>(last_);
    t->multi_ptr = &ref;
    return *this;
}

ArgParser& ArgParser::StoreValues(std::vector<int>& ref) {
    auto t = dynamic_cast<Typed<int>*>(last_);
    t->multi_ptr = &ref;
    return *this;
}
