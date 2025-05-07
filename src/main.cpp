#include <iostream>
#include <fstream>
#include <string>
#include <sol/sol.hpp>
#include "example.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    return std::string(std::istreambuf_iterator<char>(file), 
                      std::istreambuf_iterator<char>());
}

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
    
    try {
        std::string luaCode = readFile("scripts/test.lua");
        lua.script(luaCode);
    } catch (const sol::error& e) {
        std::cerr << "Error executing Lua script: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
