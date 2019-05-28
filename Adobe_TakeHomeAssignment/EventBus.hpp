//
//  EventBus.hpp
//  Adobe_TakeHomeAssignment
//
//  Created by Benjamin C Flowers on 5/14/19.
//  Copyright © 2019 Benjamin C Flowers. All rights reserved.
//

#ifndef EventBus_hpp
#define EventBus_hpp

#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <utility>
#include <memory>

// Deduces arg count for std functions (for error checking)
template <typename R, typename ... Types>
constexpr size_t getArgumentCount( std::function<R(Types ...)>)
{
    return sizeof...(Types);
}

// Function base class
struct Function {
    Function() = default;
    virtual ~Function() = default;
};

// Derived function class for specific functions
template <typename T>
struct SpecificFunction : Function {
    std::function<T> function;
    size_t addCount, argCount;
    SpecificFunction(std::function<T> function)
    : function(function),
    addCount(1),
    argCount(getArgumentCount(function))
    {}
};

class EventBus
{
private:
    // Maps event names to functions
    mutable std::unordered_map<std::string, std::unique_ptr<Function>> mFunctions;
    
public:
    EventBus()  = default;
    ~EventBus() = default;
    
    template <typename Func>
    void Add(std::string str, const Func &function)
    {
        std::cout<<"Adding " << str << std::endl;
        
        if (mFunctions.find(str) == mFunctions.end())
        {
            mFunctions.emplace(str , std::make_unique<SpecificFunction<Func>>(std::function<Func>(function)));
        }
        else
        {
            // Increment add count
            static_cast<SpecificFunction<Func> &>(*mFunctions[str]).addCount++;
        }
    }
    
    template <typename... Args>
    void Invoke(const std::string& str, Args&&... args) const
    {
        std::cout<<"Invoking " << str << std::endl;
        // Verify that event has been registered already
        assert(mFunctions.find(str) != mFunctions.end() && "Error: Event has not been added");
        
        typedef void Func(typename std::remove_reference<Args>::type...);
        
        const Function &f = *mFunctions[str];
        const auto specificFunc = static_cast<const SpecificFunction<Func> &>(f);
        
        // Verify that arg count is correct
        assert(sizeof...(Args) == specificFunc.argCount && "Error: Arg count");
        
        // Call functions
        for (auto idx = 0; idx < specificFunc.addCount; idx++)
            specificFunc.function(std::forward<Args>(args)...);
    }
    
    
};


#endif /* EventBus_hpp */
