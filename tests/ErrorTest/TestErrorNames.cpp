#include <KEUL/UnitTests.hpp>

KE_TEST(KEErrorNaming)
{
	ASSERT_EQUAL(ke::to_string(ke::Error::Error), "Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::InvalidArgument), "Invalid Argument");
    ASSERT_EQUAL(ke::to_string(ke::Error::InvalidArgumentCount), "Invalid Argument Count");
    ASSERT_EQUAL(ke::to_string(ke::Error::DomainError), "Domain Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::LengthError), "Length Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::OutOfRange), "Out of Range");
    ASSERT_EQUAL(ke::to_string(ke::Error::InvalidType), "Invalid Type");

    ASSERT_EQUAL(ke::to_string(ke::Error::OverflowInt), "Overflow Int");
    ASSERT_EQUAL(ke::to_string(ke::Error::OverflowFloat), "Overflow Float");
    ASSERT_EQUAL(ke::to_string(ke::Error::UnderflowInt), "Underflow Int");
    ASSERT_EQUAL(ke::to_string(ke::Error::UnderflowFloat), "Underflow Float");
    ASSERT_EQUAL(ke::to_string(ke::Error::DivisionByZero), "Division by Zero");
    ASSERT_EQUAL(ke::to_string(ke::Error::FormatError), "Format Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::SystemError), "System Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::EmptyArgument), "Empty Argument");

    ASSERT_EQUAL(ke::to_string(ke::Error::FileNotFound), "File Not Found");
    ASSERT_EQUAL(ke::to_string(ke::Error::FileNotOpen), "File Not Open");
    ASSERT_EQUAL(ke::to_string(ke::Error::FileNotReadable), "File Not Readable");
    ASSERT_EQUAL(ke::to_string(ke::Error::FileNotWritable), "File Not Writable");
    ASSERT_EQUAL(ke::to_string(ke::Error::FileCorrupted), "File Corrupted");
    ASSERT_EQUAL(ke::to_string(ke::Error::InvalidFileStructure), "Invalid File Structure");

    ASSERT_EQUAL(ke::to_string(ke::Error::OutOfMemory), "Out of Memory");
    ASSERT_EQUAL(ke::to_string(ke::Error::InvalidMemoryAccess), "Invalid Memory Access");

    ASSERT_EQUAL(ke::to_string(ke::Error::None), "None");
    ASSERT_EQUAL(ke::to_string(ke::Error::UnexpectedError), "Unexpected Error");
    ASSERT_EQUAL(ke::to_string(ke::Error::UnknownError), "Unknown Error");
	KE_LOGINFO("{}", ke::Error::_Count);
}