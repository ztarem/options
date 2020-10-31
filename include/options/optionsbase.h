#pragma once

#include <CLI/CLI.hpp>
#include <spdlog/fmt/fmt.h>

class OptionsBase : public CLI::App
{
    using super = CLI::App;

public:
    struct OptionDisplay
    {
        std::string label;
        std::string value;
    };

    using options_display_t = std::vector<OptionDisplay>;

    bool verbose = false;

    bool quiet = false;

    explicit OptionsBase(const std::string &description = "", const std::string &app_name = "");

    ~OptionsBase() override = default;

    void parse_args(int argc, const char **argv);

    void parse_args(const std::string& commandline, bool program_name_included = false);

    template <typename T> void addOptionDisplay(const std::string &label, T value)
    {
        m_optionDisplayList.push_back({label + ":", fmt::format("{}", value)});
    }

    void logHeader();

protected:
    virtual void postParse();

    options_display_t m_optionDisplayList;
};
