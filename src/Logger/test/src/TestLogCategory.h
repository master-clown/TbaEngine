#pragma once

#include <string>

//======================================================================================================================
enum class TestLogCategory {
    One,
    Two,
    Three,
};

//----------------------------------------------------------------------------------------------------------------------
std::string str(TestLogCategory);

//----------------------------------------------------------------------------------------------------------------------
TestLogCategory begin(TestLogCategory);
TestLogCategory end(TestLogCategory);
TestLogCategory operator++(TestLogCategory&);
TestLogCategory operator*(TestLogCategory);
