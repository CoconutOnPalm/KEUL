#include <Testing.h>
#include <Utility.h>

KE_TEST(AssembleString)
{
    // making unit tests with random data hell yeah
    ke::Random generator(0);

    for (int i = 0; i < 1024; i++)
    {
        std::vector<std::string> strings;
        
        for (int j = 0; j < 10; j++)
            strings.push_back(generator.String(i, ke::ClosedRange('a', 'z'), ke::ClosedRange('1', '9'), ke::ClosedRange('A', 'Z')));

        std::string separator = generator.String(1, ke::ClosedRange('!', '/'));

        std::string expected;
        for (int j = 0; j < 10; j++)
        {
            expected += strings[j];
            expected += separator;
        }
        expected.pop_back();

        ASSERT_EQUAL(ke::assembleString(strings, separator), expected);
    }

    // with separator at the end
    for (int i = 0; i < 128; i++)
    {
        std::vector<std::string> strings;
        
        for (int j = 0; j < 10; j++)
            strings.push_back(generator.String(i, ke::ClosedRange('a', 'z'), ke::ClosedRange('1', '9'), ke::ClosedRange('A', 'Z')));

        std::string separator = generator.String(1, ke::ClosedRange('!', '/'));

        std::string expected;
        for (int j = 0; j < 10; j++)
        {
            expected += strings[j];
            expected += separator;
        }

        ASSERT_EQUAL(ke::assembleString(strings, separator, false), expected);
    }

    // with empty separator
    for (int i = 0; i < 128; i++)
    {
        std::vector<std::string> strings;
        
        for (int j = 0; j < 10; j++)
            strings.push_back(generator.String(i, ke::ClosedRange('a', 'z'), ke::ClosedRange('1', '9'), ke::ClosedRange('A', 'Z')));

        std::string separator = "";

        std::string expected;
        for (int j = 0; j < 10; j++)
            expected += strings[j];

        ASSERT_EQUAL(ke::assembleString(strings, separator), expected);
    }
}