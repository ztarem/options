The `options` library provides the overridable class `OptionsBase` which is derived from [CLI11::App][1] and adds the following features:

1. Initializes [spdlog][2] for use by the containing project. 
1. The option "-v,--verbose" is automatically added and controls the level of messages that are written into the log.
1. Options and option values can be checked and manipulated before the client starts using them.
1. An informative header can be created and written to the log.

### A motivating example

Here is a an example of a command-line parser, and it'a usage:

```C++ {.line-numbers}
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
    Options options;
    options.parse_args(argc, argv);
    options.logHeader();
    spdlog::debug("This is a debug message");
    spdlog::info("This is an info message. 'first' is actually {}+1", options.first - 1);
    spdlog::warn("This is a warning message");
    return 0;
}
```
#### Notes:

Create a class derived from `OptionsBase`
1. Add public variables for your options (like `first` here). Reference these variables in the option definitions in the constructor.
1. Call the base class constructor with a description and a 'name'. These will appear on the first line of the generated log header (see output below).
1. Add option definitions in the constructor. See the CLI11 documentation for full details.
1. In the overridden `postParse()` method call the base class implementation and add any other required processing. In particular, you can throw a `CLI11::ValidationError` exception if option verification fails, and you can add label/text pairs to the generated log header (see output below).

Use it a program:
1. create an instance, call `parse_args(argc, argv)` and then call `logHeader()`. Public variables defined in the options class can now be used freely.  
1. The `spdlog::debug()` call will produce output only if the `-v/--verbose` option was given.
1. The `spdlog::info()` call will produce output only if the `-q/--quiet` option was _not_ given.

#### Help output

```
...> ./options-example -h

Option tester
Usage: options-example [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -v,--verbose Excludes: --quiet
                              Write debug messages to the log
  -q,--quiet Excludes: --verbose
                              Write only warnings or worse to the log
  -f,--first INT=1            The first argument
```

#### Execution output

```
...> options-example -v -f 42

2020-10-31 18:23:31.597 info     options-example - Option tester
2020-10-31 18:23:31.597 info       Command: -v -f 42
2020-10-31 18:23:31.597 info       First:   42
2020-10-31 18:23:31.597 debug    This is a debug message
2020-10-31 18:23:31.597 info     This is an info message. 'first' is actually 41+1
2020-10-31 18:23:31.597 warning  This is a warning message
```

# Prerequisites

The library depends on the following tools:

1. A C++17 compliant compiler.
1. The [CLI11][1] command-line parser.
1. The [spdlog][2] logging library.

# Building

Get the repository, build it and install it
```bash
...> cd my-projects
...> git clone https://github.com/ztarem/options
...> cd options
...> mkdir build
...> cd build
...> cmake ..
...> make
...> sudo make install
```

[1]: <https://github.com/CLIUtils/CLI11>
[2]: <https://github.com/gabime/spdlog>
