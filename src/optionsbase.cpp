#include "options/optionsbase.h"
#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem.hpp>
#include <spdlog/spdlog.h>

namespace alg = boost::algorithm;
namespace fs = boost::filesystem;

OptionsBase::OptionsBase(const std::string &description, const std::string &app_name) : super(description, app_name)
{
    spdlog::set_pattern("%Y-%m-%d %T.%e %^%-8l%$ %v");
    spdlog::set_level(spdlog::level::info);
    this->add_flag("-v,--verbose", this->verbose, "Write debug messages to the log");
}

void OptionsBase::parse(int argc, const char **argv, bool emitCmdline)
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

    if (emitCmdline && argc > 1)
    {
        std::string cmdline = alg::join(std::vector<std::string>{argv + 1, argv + argc}, " ");
        this->addOptionDisplay("Command line", cmdline);
    }
    postParse();
}

void OptionsBase::logHeader()
{
    spdlog::info("{} - {}", this->get_name(), this->get_description());
    if (!m_optionDisplayList.empty())
    {
        size_t labelWidth = std::accumulate(
            m_optionDisplayList.begin(), m_optionDisplayList.end(), 0,
            [](size_t maxWidth, const OptionDisplay &od) { return std::max(maxWidth, od.label.size()); });
        for (auto &od : m_optionDisplayList)
        {
            spdlog::info("  {:{}} {}", od.label, labelWidth, od.value);
        }
    }
}

void OptionsBase::postParse()
{
    if (this->verbose)
    {
        spdlog::set_level(spdlog::level::debug);
    }
}
