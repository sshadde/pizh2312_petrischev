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

// поиск
ArgParser::Base* ArgParser::findByLong(const std::string& name) const {
    auto it = long_map_.find(name);
    return it != long_map_.end() ? it->second : nullptr;
}

ArgParser::Base* ArgParser::findByShort(char c) const {
    auto it = short_map_.find(c);
    return it != short_map_.end() ? it->second : nullptr;
}

// парсинг
bool ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> v;
    for (int i = 0; i < argc; ++i) v.emplace_back(argv[i]);
    return Parse(v);
}

bool ArgParser::Parse(const std::vector<std::string>& args) {
    // сброс
    help_requested_ = false;
    for (auto& p : args_) {
        if (auto f = dynamic_cast<Flag*>(p.get())) {
            f->value = f->has_default ? f->default_value : false;
        } else if (auto ts = dynamic_cast<Typed<std::string>*>(p.get())) {
            ts->values.clear();
        } else if (auto ti = dynamic_cast<Typed<int>*>(p.get())) {
            ti->values.clear();
        }
    }

    for (size_t i = 1; i < args.size(); ++i) {
        const std::string& s = args[i];
        if (s.rfind("--", 0) == 0) {
            auto eq = s.find('=');
            std::string name = s.substr(2, eq - 2);
            Base* b = findByLong(name);
            if (!b) return false;
            if (name == help_long_) {
                help_requested_ = true;
                return true;
            }
            if (b->isFlag()) {
                auto f = static_cast<Flag*>(b);
                f->value = true;
                if (f->ptr) *f->ptr = true;
            } else {
                if (eq == std::string::npos) return false;
                std::string val = s.substr(eq + 1);
                if (auto ts = dynamic_cast<Typed<std::string>*>(b)) {
                    ts->values.push_back(val);
                } else if (auto ti = dynamic_cast<Typed<int>*>(b)) {
                    ti->values.push_back(std::stoi(val));
                }
            }
        } else if (s.rfind("-", 0) == 0) {
            for (size_t k = 1; k < s.size(); ++k) {
                char c = s[k];
                if (c == '=') return false;
                Base* b = findByShort(c);
                if (!b) return false;
                if (c == help_short_) {
                    help_requested_ = true;
                    return true;
                }
                if (b->isFlag()) {
                    auto f = static_cast<Flag*>(b);
                    f->value = true;
                    if (f->ptr) *f->ptr = true;
                } else {
                    // аргумент со значением: должно быть -p=123
                    if (k + 1 >= s.size() || s[k+1] != '=') return false;
                    std::string rest = s.substr(k+2);
                    if (auto ts = dynamic_cast<Typed<std::string>*>(b)) {
                        ts->values.push_back(rest);
                    } else if (auto ti = dynamic_cast<Typed<int>*>(b)) {
                        ti->values.push_back(std::stoi(rest));
                    }
                    break;
                }
            }
        } else {
            // позиционный
            for (auto& p : args_) {
                if (p->positional) {
                    if (auto ts = dynamic_cast<Typed<std::string>*>(p.get())) {
                        ts->values.push_back(s);
                    } else if (auto ti = dynamic_cast<Typed<int>*>(p.get())) {
                        ti->values.push_back(std::stoi(s));
                    }
                    goto next_arg;
                }
            }
            return false;
        }
        next_arg:;
    }

    return applyDefaultAndCheck();
}

bool ArgParser::applyDefaultAndCheck() {
    for (auto& p : args_) {
        if (auto f = dynamic_cast<Flag*>(p.get())) {
            if (f->has_default) {
                f->value = f->default_value;
                if (f->ptr) *f->ptr = f->value;
            }
        } else if (auto ts = dynamic_cast<Typed<std::string>*>(p.get())) {
            if (ts->values.empty()) {
                if (ts->has_default) {
                    ts->values.push_back(ts->default_value);
                } else if (!p->positional) {
                    return false;
                }
            }
            if (ts->values.size() < p->min_count) return false;
            if (ts->single_ptr && !ts->values.empty()) {
                *ts->single_ptr = ts->values[0];
            }
            if (ts->multi_ptr) {
                *ts->multi_ptr = ts->values;
            }
        } else if (auto ti = dynamic_cast<Typed<int>*>(p.get())) {
            if (ti->values.empty()) {
                if (ti->has_default) {
                    ti->values.push_back(ti->default_value);
                } else if (!p->positional) {
                    return false;
                }
            }
            if (ti->values.size() < p->min_count) return false;
            if (ti->single_ptr && !ti->values.empty()) {
                *ti->single_ptr = ti->values[0];
            }
            if (ti->multi_ptr) {
                *ti->multi_ptr = ti->values;
            }
        }
    }
    return true;
}

// геттеры
bool ArgParser::Help() const {
    return help_requested_;
}

std::string ArgParser::GetStringValue(const std::string& name) const {
    auto b = findByLong(name);
    auto ts = dynamic_cast<Typed<std::string>*>(b);
    return ts && !ts->values.empty() ? ts->values[0] : "";
}
int ArgParser::GetIntValue(const std::string& name, size_t idx) const {
    auto b = findByLong(name);
    auto ti = dynamic_cast<Typed<int>*>(b);
    return (ti && idx < ti->values.size()) ? ti->values[idx] : 0;
}
bool ArgParser::GetFlag(const std::string& name) const {
    auto b = findByLong(name);
    auto f = dynamic_cast<Flag*>(b);
    return f ? f->value : false;
}

// справка
std::string ArgParser::HelpDescription() const {
    std::ostringstream oss;
    oss << prog_name_ << "\n";
    if (!help_description_.empty())
        oss << help_description_ << "\n\n";
    for (auto& p : args_) {
        oss << "  ";
        if (p->short_name) {
            oss << "-" << p->short_name << ", ";
        } else {
            oss << "    ";
        }
        oss << "--" << p->long_name;
        if (!p->isFlag()) {
            oss << "=<";
            if (dynamic_cast<Typed<int>*>(p.get())) oss << "int";
            else oss << "string";
            oss << ">";
        }
        if (!p->description.empty()) {
            oss << "\t" << p->description;
        }
        oss << "\n";
    }
    return oss.str();
}
