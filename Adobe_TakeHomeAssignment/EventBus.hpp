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
#include <vector>
#include <set>
#include "Utilities.h"



class EventBus
{
private:

    // Associates event names with functions
    mutable std::unordered_map<std::string, std::vector<std::unique_ptr<Function>>> mFunctions;

    std::set<std::string> mCanceledEvents;
    
public:
    EventBus();
    ~EventBus();
    
    template <typename Func>
    void Add(const std::string& str, const Func &function)
    {
        
        auto ptr = std::make_unique<SpecificFunction<Func>>(std::function<Func>(function));
 
        // If event already canceled, return
        if (mCanceledEvents.find(str) != mCanceledEvents.end()) return;
        
        // Remember cancellation events
        if (ptr->cancel) mCanceledEvents.insert(str);
        
        if (mFunctions.find(str) == mFunctions.end()) // New Event
        {
            std::vector<std::unique_ptr<Function>> funcPtrs;
            funcPtrs.emplace_back((std::make_unique<SpecificFunction<Func>>(std::function<Func>(function))));
            mFunctions.emplace(str , std::move(funcPtrs));
        }
        else // Already registered event
        {
            mFunctions[str].emplace_back(std::make_unique<SpecificFunction<Func>>(std::function<Func>(function)));
        }
    }
    
    template <typename... Args>
    void Invoke(const std::string& str, Args&&... args) const
    {
        // Verify that event has been registered already
        assert(mFunctions.find(str) != mFunctions.end() && "Error: Event has not been registered");

        typedef void Func(typename std::remove_reference<Args>::type...);

        // Visit each function associated with event 
        for (const auto & Fptr : mFunctions[str])
        {
            const auto & specificFunc = static_cast<const SpecificFunction<Func> &>(*Fptr);
    
            // Verify that arg count is correct
            assert(sizeof...(Args) == specificFunc.argCount && "Error: Arg count");

            // Perfect forward if only one function
            if (mFunctions[str].size() == 1)
                specificFunc.function(std::forward<Args>(args)...);
            else
                specificFunc.function(args...);
        }
    }
};


#endif /* EventBus_hpp */
