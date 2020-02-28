The `options` library provides the overridable class `OptionsBase` which is derived from [CLI11::App][1] and adds the following features:

1. Initializes [spdlog][2] for use by the containing project. 
1. The option "-v,--verbose" is automatically added and controls the level of messages that are written into the log.
1. Options and option values can be checked and manipulated before the clients starts using them.
1. An informative header can be created and written to the log.

[1]: <https://github.com/CLIUtils/CLI11>
[2]: <https://github.com/gabime/spdlog>

### A motivating example
Here is a an example of a command-line parser, and it'a usage:

```C++ {.line-numbers}
#include "options/optionsbase.h"
#include <spdlog/spdlog.h>

class Options : public OptionsBase
{
public:
    int first = 1;

    explicit Options(const std::string& app_name = "")
            : super("Option tester", app_name)
    {
        this->add_option("-f,--first", this->first, "The first argument", true);
    }

    ~Options() override = default;

protected:
    using super = OptionsBase;

    void postParse() override
    {
        super::postParse();
        this->addOptionDisplay("First", this->first);
    }
};

int main(int argc, const char* argv[])
{
    Options options("Tester");
    options.parse(argc, argv);
    options.logHeader();
    spdlog::debug("Log level set to debug");
    return 0;
}
```
Notes:

1. Add public variables for your options (like `first` here). Reference these variables in the option definitions in the constructor.
1. Call the base class constructor with a description and a 'name'. These will appear on the first line of the generated log header (see output below).
1. Add option definitions in the constructor. See the CLI11 documentation for full details.
1. In the overridden `postParse()` method call the base class implementation and add any other required processing. In particular, you can throw a `CLI11::ValidationError` exception if option verification fails, and you can add label/text pairs to the generated log header (see output below).
1. To use the class, create an instance, call `parse(argc, argv)` and then call logHeader()`. Public variable defined in the class can now be used freely.  
1. The `spdlog::debug()` call will produce output only if the -v/--verbose option was given.

#### Help output
```
...> /options-example -h

Option tester
Usage: Tester [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -v,--verbose                Write debug messages to the log
  -f,--first INT=1            The first argument
```

#### Execution output
```
...> options-example -v -f 42

2020-02-28 16:01:12.519 info     Tester - Option tester
2020-02-28 16:01:12.519 info       Command line: -v -f 42
2020-02-28 16:01:12.519 info       First:        42
2020-02-28 16:01:12.519 debug    Log level set to debug
```
