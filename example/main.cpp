#include "options/optionsbase.h"
#include <spdlog/spdlog.h>

class Options : public OptionsBase
{
    using super = OptionsBase;

  public:
    int first = 1;

    explicit Options(const std::string &app_name = "") : super("Option tester", app_name)
    {
        this->add_option("-f,--first", this->first, "The first argument", true);
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
    Options options("Tester");
    options.parse(argc, argv);
    options.logHeader();
    spdlog::debug("Log level set to debug");
    return 0;
}
