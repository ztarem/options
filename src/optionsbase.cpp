#include "options/optionsbase.h"
#include <filesystem>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

OptionsBase::OptionsBase(const std::string &description, const std::string &app_name) : super(description, app_name)
{
    spdlog::set_pattern("%Y-%m-%d %T.%e %^%-8l%$ %v");
    spdlog::set_level(spdlog::level::info);
    this->add_flag("-v,--verbose", this->verbose, "Write debug messages to the log");
    this->add_flag("-q,--quiet", this->quiet, "Write only warning and error messages to the log")
        ->excludes("--verbose");
}

void OptionsBase::parse_args(int argc, const char **argv)
{
    if (this->get_name().empty())
    {
        this->name(fs::path(argv[0]).stem().string());
    }
    try
    {
        super::parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(super::exit(e));
    }

    if (argc > 1)
    {
        std::string cmdline{argv[1]};
        for (int i = 2; i < argc; i++)
        {
            cmdline += std::string(" ") + argv[i];
        }
        this->addOptionDisplay("Command", cmdline);
    }
    this->postParse();
}

void OptionsBase::parse_args(const std::string &commandline, bool program_name_included)
{
    try
    {
        super::parse(commandline, program_name_included);
    }
    catch (const CLI::ParseError &e)
    {
        ::exit(super::exit(e));
    }

    if (!commandline.empty())
    {
        this->addOptionDisplay("Command", commandline);
    }
    this->postParse();
}

void OptionsBase::logHeader()
{
    spdlog::info("{} - {}", this->get_name(), this->get_description());
    if (!m_optionDisplayList.empty())
    {
        size_t labelWidth = 0;
        for (const auto &[label, _] : m_optionDisplayList)
        {
            labelWidth = std::max(labelWidth, label.size());
        }
        for (const auto &[label, value] : m_optionDisplayList)
        {
            spdlog::info("  {:{}} {}", label, labelWidth, value);
        }
    }
}

void OptionsBase::postParse()
{
    if (this->verbose)
    {
        spdlog::set_level(spdlog::level::debug);
    }
    else if (this->quiet)
    {
        spdlog::set_level(spdlog::level::warn);
    }
}
