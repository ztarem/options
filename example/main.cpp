#include "options/optionsbase.h"
#include <spdlog/spdlog.h>

class Options : public OptionsBase
{
    using super = OptionsBase;

  public:
    int first = 1;

    explicit Options(const std::string &app_name = "") : super("Option tester", app_name)
    {
      this->add_option("-f,--first", this->first, "The first argument");
    }

    ~Options() override = default;

  protected:
    void postParse() override
    {
        super::postParse();
        this->addOptionDisplay("First", this->first);
    }
};

int main(int argc, const char *argv[])
{
    Options options;
    options.parse_args(argc, argv);
    options.logHeader();
    spdlog::debug("This is a debug message");
    spdlog::info("This is an info message. 'first' is actually {}+1", options.first - 1);
    spdlog::warn("This is a warning message");
    return 0;
}
