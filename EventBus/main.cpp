//
//  main.cpp
//  Adobe_TakeHomeAssignment
//
//  Created by Benjamin C Flowers on 5/14/19.
//  Copyright © 2019 Benjamin C Flowers. All rights reserved.
//

#include <iostream>
#include "EventBus.hpp"

void funcNoArgs() {
    std::cout << "Executing funcNoArgs" << std::endl;
}

void funcNoArgs2() {
    std::cout << "Executing funcNoArgs2" << std::endl;
}

// Custom return type indicates cancellation 
cancelReturnT funcNoArgsWithCancel() {
    std::cout << "Executing funcNoArgsWithCancel" << std::endl;
    return {};
}

void funcNoArgs3() {
    std::cout << "Executing funcZeroArgs3" << std::endl;
}

void funcStringArg(std::string s) {
    std::cout << "Executing funcStringArg: " << s << std::endl;
}

void funcStringArg2(std::string s) {
    std::cout << "Executing funcStringArg2: " << s << std::endl;
}

void funcTwoArgs(std::string s, int i) {
    std::cout << "Executing funcTwoArgs: " << s << " , "<< i << std::endl;
}

void funcTwoArgs2(std::string s, int i) {
    std::cout << "Executing funcTwoArgs2: " << s << " , "<< i << std::endl;
}

void funcUnregistered() {
    std::cout << "Executing unregistered function: " << std::endl;
}


int main(int argc, const char * argv[]) {

    EventBus eventBus{};

    std::string noArgsEvent         = "noArgsEvent";
    std::string stringArgEvent      = "stringArgEvent";
    std::string twoArgsEvent        = "twoArgsEvent";
    std::string unregisteredEvent   = "str3";
    
    // No args
    eventBus.Add(noArgsEvent,       funcNoArgs);
    eventBus.Add(noArgsEvent,       funcNoArgs2);
    eventBus.Add(noArgsEvent,       funcNoArgsWithCancel);
    eventBus.Add(noArgsEvent,       funcNoArgs3); // won't execute
    
    // String Arg
    eventBus.Add(stringArgEvent,    funcStringArg);
    eventBus.Add(stringArgEvent,    funcStringArg2);
    
    // Two arguments
    eventBus.Add(twoArgsEvent,      funcTwoArgs);
    eventBus.Add(twoArgsEvent,      funcTwoArgs2);
    
    // Invoke
    eventBus.Invoke(noArgsEvent);
    eventBus.Invoke(stringArgEvent, (std::string) "string arg");
    eventBus.Invoke(twoArgsEvent,   (std::string) "string arg", 42);
    
    // Error Detection Cases: (triggers assertion failures)
    eventBus.Invoke(noArgsEvent,    (std::string) "Invalid Arg");
    eventBus.Invoke(unregisteredEvent);
    


    return 0;
}
