#include <KEUL/UnitTests.hpp>

KE_TEST(KEErrorNaming)
{
	ASSERT_EQUAL(ke::toString(ke::Error::Error), "Error");
    ASSERT_EQUAL(ke::toString(ke::Error::InvalidArgument), "Invalid Argument");
    ASSERT_EQUAL(ke::toString(ke::Error::InvalidArgumentCount), "Invalid Argument Count");
    ASSERT_EQUAL(ke::toString(ke::Error::DomainError), "Domain Error");
    ASSERT_EQUAL(ke::toString(ke::Error::LengthError), "Length Error");
    ASSERT_EQUAL(ke::toString(ke::Error::OutOfRange), "Out of Range");
    ASSERT_EQUAL(ke::toString(ke::Error::InvalidType), "Invalid Type");

    ASSERT_EQUAL(ke::toString(ke::Error::OverflowInt), "Overflow Int");
    ASSERT_EQUAL(ke::toString(ke::Error::OverflowFloat), "Overflow Float");
    ASSERT_EQUAL(ke::toString(ke::Error::UnderflowInt), "Underflow Int");
    ASSERT_EQUAL(ke::toString(ke::Error::UnderflowFloat), "Underflow Float");
    ASSERT_EQUAL(ke::toString(ke::Error::DivisionByZero), "Division by Zero");
    ASSERT_EQUAL(ke::toString(ke::Error::FormatError), "Format Error");
    ASSERT_EQUAL(ke::toString(ke::Error::SystemError), "System Error");
    ASSERT_EQUAL(ke::toString(ke::Error::EmptyArgument), "Empty Argument");

    ASSERT_EQUAL(ke::toString(ke::Error::FileNotFound), "File Not Found");
    ASSERT_EQUAL(ke::toString(ke::Error::FileNotOpen), "File Not Open");
    ASSERT_EQUAL(ke::toString(ke::Error::FileNotReadable), "File Not Readable");
    ASSERT_EQUAL(ke::toString(ke::Error::FileNotWritable), "File Not Writable");
    ASSERT_EQUAL(ke::toString(ke::Error::FileCorrupted), "File Corrupted");
    ASSERT_EQUAL(ke::toString(ke::Error::InvalidFileStructure), "Invalid File Structure");

    ASSERT_EQUAL(ke::toString(ke::Error::OutOfMemory), "Out of Memory");
    ASSERT_EQUAL(ke::toString(ke::Error::InvalidMemoryAccess), "Invalid Memory Access");

    ASSERT_EQUAL(ke::toString(ke::Error::None), "None");
    ASSERT_EQUAL(ke::toString(ke::Error::UnexpectedError), "Unexpected Error");
    ASSERT_EQUAL(ke::toString(ke::Error::UnknownError), "Unknown Error");
	KE_LOGINFO("{}", ke::Error::_Count);
}