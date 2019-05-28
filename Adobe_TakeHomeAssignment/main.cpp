//
//  main.cpp
//  Adobe_TakeHomeAssignment
//
//  Created by Benjamin C Flowers on 5/14/19.
//  Copyright © 2019 Benjamin C Flowers. All rights reserved.
//

#include <iostream>
#include "EventBus.hpp"

void freestanding() {
    std::cout << "executing freestanding" << std::endl;
}

void freestandingInt(int iArg) {
    std::cout << "executing freestandingInt " << iArg << std::endl;
}

void freestandingTwoArgs(int iArg, std::string s) {
    std::cout << "executing freestandingTwoArgs " << iArg << s << std::endl;
}

void Random(int iArg, std::string s) {
    std::cout << "Random " << iArg << s << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    //func<int,int> f = Add_;
    
    EventBus eventBus{};
 
    
    
    std::string s0 = "str0";
    std::string s1 = "str1";
    std::string s2 = "str2";
    std::string s3 = "str3";
    
    eventBus.Add(s0, freestanding);
    eventBus.Add(s1, freestandingInt);
    eventBus.Add(s1, freestandingInt);
    eventBus.Add(s2, freestandingTwoArgs);
    
    //eventBus.Add(s3, Random);
    
    //freestandingTwoArgs
//    eventBus.Add(s, func0);
//    eventBus.A
    
    eventBus.Invoke("str0");
    eventBus.Invoke("str1",42);
    eventBus.Invoke("str3", 42);
    //eventBus.Invoke("str2", 42, (std::string)"potato", 69);
    
    
    //std::cout << getArgumentCount(freestandingTwoArgs) << std::endl;

    return 0;
}
