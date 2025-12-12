#include "TestLogCategory.h"

#include <type_traits>
#include <utility>

//======================================================================================================================
std::string str(const TestLogCategory cat)
{
    using Enum = TestLogCategory;

    switch (cat) {
    case Enum::One: return "TestLogCategory::One";
    case Enum::Two: return "TestLogCategory::Two";
    case Enum::Three: return "TestLogCategory::Three";
    default: std::unreachable();
    }
}

//======================================================================================================================
TestLogCategory begin(TestLogCategory)
{
    return TestLogCategory::One;
}

//======================================================================================================================
TestLogCategory end(TestLogCategory)
{
    auto theEnd = TestLogCategory::Three;
    return ++theEnd;
}

//======================================================================================================================
TestLogCategory operator++(TestLogCategory& arg)
{
    return arg = static_cast<TestLogCategory>(static_cast<std::underlying_type_t<TestLogCategory>>(arg) + 1);
}

//======================================================================================================================
TestLogCategory operator*(const TestLogCategory arg)
{
    return arg;
}
