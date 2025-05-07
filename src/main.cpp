#include <iostream>
#include <fstream>
#include <string>
#include <sol/sol.hpp>
#include "example.h"

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math, sol::lib::string);
    
    // register Calculator class into Lua
    lua.new_usertype<Calculator>("Calculator",
        sol::constructors<Calculator()>(),
        "add", &Calculator::add,
        "multiply", &Calculator::multiply,
        "greet", &Calculator::greet
    );
    
    lua.script_file("scripts/test.lua");
    
    return 0;
}
