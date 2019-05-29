
// Contains Utilities for EventBus class
// See README for details

#ifndef Utilities_h
#define Utilities_h

#include <typeinfo>
#include <type_traits>

// Special return type to indicate cancellation of subsequent functions
typedef struct _t_cancelReturnT
{ } cancelReturnT;

// Deduces arg count for std functions (for error checking)
template <typename R, typename ... Types>
constexpr size_t getArgumentCount( std::function<R(Types ...)>)
{
    return sizeof...(Types);
}

// Check whether function has cancellation signature
template <typename R, typename  ... Types>
constexpr bool isCancelFunction( std::function<R(Types ...)>)
{
    return std::is_same<cancelReturnT, R>::value;
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
    size_t argCount;
    bool cancel;
    SpecificFunction(std::function<T> function)
    : function(function),
    cancel(isCancelFunction(function)),
    argCount(getArgumentCount(function))
    {}
};


#endif /* Utilities_h */
