# KEUL
KEngine Utility Library - easy to use small utility library
The library is header-only

### Getting the repository:
```git clone https://github.com/CoconutOnPalm/KEUL.git```


# Library content

## String module
### ANSI-formatting
Use ```ke::format()``` and ```ke::print()``` ```ke::println()``` to add mapped ANSI codes to std::string using ```[...]``` bracket formatting

formatting: 
`[f1;f2;f3]This is the colorful part [0]This is the default part`, \
where: \
f1, f2, f3 -> are formatting options, \
0 -> is the resetting option (see table below)

***example:***
```
std::string ansi = ke::format("[red]RED [bold;blue]BOLD BLUE");
// str = "\033[31mRED \033[1;34mBOLD BLUE\033[0m"
```
or print it directly
```
ke::println("[red]RED [bold;blue]BOLD BLUE");
/* output: RED BOLD BLUE
            ^     ^
          red   bold blue (in ANSI-compatible consoles)
*/
```
you can also plug in rgb values
```
ke::println("[rgb(160,82,45)] Brown Text")
```
or even inject custom ANSI codes
```
ke::println("[esc(31)] RED [esc(32)] GREEN"); // ANSI code 31 = RED, 32 = GREEN
```
it inherits the behavior of `std::format`
```
ke::println("[red][[ERROR]]: [0]{}", message);
// output: "[ERROR]: <message>"
// note: [[ ]] escapes the brackets, just like std::format's {{ }}
```

**table of the basic codes**

| full           | shortened      | code | result                |
|:--------------:|:-------------:|:----:|:----------------------|
| reset          | 0             | 0    | reset all attributes  |
| bold           | b             | 1    | **bold**              |
| dim, faint     | d, f          | 2    | dim/faint             |
| italic         | i             | 3    | *italic*              |
| underline      | u             | 4    | underline             |
| blink          |               | 5    | blink                 |
| reverse        | rev           | 7    | reverse video         |
| hidden         | hide          | 8    | hidden                |
| strikethrough  | strike        | 9    | ~~strikethrough~~     |
|||||
| black          | k             | 30   | ![BLACK](https://placehold.co/15x15/black/black.png) black |
| red            | r             | 31   | ![RED](https://placehold.co/15x15/red/red.png) red |
| green          | g             | 32   | ![GREEN](https://placehold.co/15x15/green/green.png) green |
| yellow         | y             | 33   | ![YELLOW](https://placehold.co/15x15/yellow/yellow.png) yellow |
| blue           | l             | 34   | ![BLUE](https://placehold.co/15x15/blue/blue.png) blue |
| magenta        | m             | 35   | ![MAGENTA](https://placehold.co/15x15/magenta/magenta.png) magenta |
| cyan           | c             | 36   | ![CYAN](https://placehold.co/15x15/cyan/cyan.png) cyan |
| white          | w             | 37   | ![WHITE](https://placehold.co/15x15/white/white.png) white |
| default        | def           | 39   | console's default |
|||||
| bred           |               | 91   | ![BLACK](https://placehold.co/15x15/EE4B2B/EE4B2B.png) bright red |
| bgreen         |               | 92   | ![RED](https://placehold.co/15x15/33ff57/33ff57.png) bright green |
| ... | ... | ... | ...|
|||||
| bg_black, backblack |               | 40   | ![BLACK](https://placehold.co/15x15/black/black.png) black background |
| bg_red, backred     |               | 41   | ![RED](https://placehold.co/15x15/red/red.png) red bakcground |
| ... | ... | ... | ...|
|||||
| bbackred   | bbackr | 101   | ![RED](https://placehold.co/15x15/EE4B2B/EE4B2B.png) bright red bakcground |
| bbackgreen | bbackg | 102   | ![BLACK](https://placehold.co/15x15/33ff57/33ff57.png) bright green background |
| ... | ... | ... | ...|
| rgb(r,g,b)          |              |    | rgb(r,g,b) text color |
| esc(code)           |              |    | inject any ANSI code  |


### String utilities
#### string convertions
```
ke::toString(10) -> "10"

ke::tryToString(10, "???")              -> "10"
ke::tryToString(NonFormattable, "???")  -> "???"
```

```
ke::fromString<int>("10")   -> 10 // inside std::expected<int, ke::Error>
ke::fromString<int>("abcd") -> std::unexpected<ke::Error>
```

#### lowercase / uppercase
```
ke::toLower("UPPERCASE") -> "uppercase"
ke::toUpper("lowercase") -> "LOWERCASE"
```

#### string splitting
```
ke::splitString<std::vector>("apple;banana|onion;cabbage", {";", "|"}) -> std::vector<std::string> [ "apple", "banana", "onion", "cabbage" ]
ke::splitString<std::vector>("apple;banana|onion;cabbage", {"|"}) -> std::vector<std::string> [ "apple;banana", "onion;cabbage" ]

ke::splitString<std::set>("apple;banana;apple|onion;cabbage", {";", "|"}) -> std::set<std::string> [ "apple", "banana", "onion", "cabbage" ]

ke::splitStringToPair("key: value", { ": " }) -> ("key", "value")


// you can also apply direct transformation on the output
auto toInt = [](const std::string& str) -> int { return ke::fromString<int>(str).value(); };
ke::splitString<int>("1;2;3;4", { ";" }, toInt) -> std::vector<int> [ 1, 2, 3, 4 ]
```

#### string assembling
```
std::vector<std::string> vec = {"a", "b", "c", "d"};
ke::assembleString(vec, ";") -> "a;b;c;d"
```

#### string cleanup
```
ke::shortenString("very long text", 10) -> "very lo..."     // exactly 10 characters long
```

```
ke::trimString("    weirdly shifted text with newline\n") -> "weirdly shifted text with newline"
```

```
ke::removeComments("Lorem ipsum. // comment", "//") -> "Lorem ipsum"
ke::removeComments("Lorem ipsum. # comment", "#")   -> "Lorem ipsum"
```

## Logging

KEUL provides a simple logging module, which consists of two loggers:

### Logger
```
std::string message = "message";

ke::Logger logger;
logger.addLogFile("log");
logger.setLoggingPolicy<ke::policies::DefaultLoggingPolicy>();
logger.setLayer(ke::LogLayer::Warning); // only warning+ levels will be logged
logger.logInfo("info: {}", message);
logger.logDebug("debug: {}", message);
logger.logWarning("warning: {}", message);
logger.logError("error: {}", message);
logger.logCritical("critical: {}", message);

```
output (both in console and "log" file):
```
2025-07-03 18:09:21
[WARNING]: warning: message
2025-07-03 18:09:21
[ERROR]: error: message
2025-07-03 18:09:21
[CRITICAL]: critical: message
```

### SimpleLogger
```
ke::SimpleLogger::setLoggingPolicy<ke::policies::DefaultLoggingPolicy>();
ke::SimpleLogger::setLayer(ke::LogLayer::Warning);
ke::SimpleLogger::logError("error");
```
or use a dedicated macro
```
int var = -1;
KE_LOGERROR("variable {} is invalid", var);
KE_LOGWARNING("this it a warning");
```

### log levels:
|name|hierarchy|
|:--:|:------:|
|INFO|1|
|DEBUG|2|
|WARNING|3|
|ERROR|4|
|CRITICAL ERROR|5|

## Clock, benchmarking

### Clock
```
ke::Clock clock(ke::Clock::TimeUnit::miliseconds);
clock.start();
for (size_t i = 0; i < 1'000'000'000; i++)
{
	// some time consuming operation
}
double time = clock.stop();
std::println("time={:.3f}ms", time);

// output: 
// time=2011.904ms
```

### Benchmark
```
ke::Benchmark benchmark("benchmark name");
for (size_t i = 0; i < 1'000'000'000; i++)
    { }
benchmark.stop(true); // true - automatically print the result

// output: 
// benchmark name: 2038136.600 µs
// may result in funny characters when encoding gets messy
```

### LoopBenchmark
```
ke::LoopBenchmark loopBenchmark("loop benchmark", ke::Clock::TimeUnit::miliseconds);
	
for (size_t i = 0; i < 1000; i++)
{
	loopBenchmark.startIteration();
	for (size_t j = 0; j < 1'000'000; j++)
		{}
	loopBenchmark.endIteration();
}

double avg_time = loopBenchmark.stop();
std::println("avg time: {:.3f}", avg_time);

// output:
// avg time: 1.911
```

both Benchmark and LoopBenchmark were created to be simple and fast to implement. For proper benchmarking, use more robust methods.

### (very) simple file loading

*data.txt*
```
apples: 2
bananas: 5
strawberries: 10
radioisotope thermoelectric generator: 3
```
```
ke::FileReader freader("data.txt");
const std::vector<std::string> data = freader.readAll();
std::println("{}", data);
// output:
[apples: 2, bananas: 5, strawberries: 10, radioisotope thermoelectric generator: 3]
```
the readAll() method reads a file line-by-line, saving many lines of code if you don't have a dedicated reader. It's an easy method, for a more uncivilized age. 

