#pragma once

#include <CLI/CLI.hpp>
#include <spdlog/fmt/fmt.h>

class OptionsBase : public CLI::App
{
public:
    struct OptionDisplay
    {
        std::string label;
        std::string value;
    };

    using options_display_t = std::vector<OptionDisplay>;

    bool verbose = false;

    explicit OptionsBase(const std::string& description = "", const std::string& app_name = "");

    ~OptionsBase() override = default;

    void parse(int argc, const char** argv, bool emitCmdline = true);

    template<typename T>
    void addOptionDisplay(const std::string& label, T value)
    {
        m_optionDisplayList.push_back({label + ":", fmt::format("{}", value)});
    }

    void logHeader();

protected:
    using super = CLI::App;

    virtual void postParse();

    options_display_t m_optionDisplayList;
};
