#pragma once

#include <glbinding/glbinding_api.h>

#include <set>
#include <vector>
#include <functional>
#include <type_traits>

namespace glbinding 
{

class AbstractFunction;
class AbstractValue;

struct GLBINDING_API FunctionCall
{
    FunctionCall(const AbstractFunction * _function);
    ~FunctionCall();

    FunctionCall & operator=(const FunctionCall &) = delete;

    const AbstractFunction & function;

    std::vector<AbstractValue *> parameters;
    AbstractValue * returnValue;
};

enum class CallbackMask : unsigned char
{
    None        = 0x00,
    Unresolved  = 0x01,
    Before      = 0x02,
    After       = 0x04,
    Parameters  = 0x08,
    ReturnValue = 0x10,
    ParametersAndReturnValue = Parameters | ReturnValue,
    BeforeAndAfter = Before | After
};

using callback_mask_t = std::underlying_type<CallbackMask>::type;

GLBINDING_API CallbackMask operator|(CallbackMask a, CallbackMask b);

GLBINDING_API void setCallbackMask(CallbackMask mask);
GLBINDING_API void setCallbackMaskExcept(CallbackMask mask, const std::set<std::string> & blackList);


using SimpleFunctionCallback = std::function<void(const AbstractFunction &)>;
using FunctionCallback = std::function<void(const FunctionCall &)>;

GLBINDING_API void setUnresolvedCallback(const SimpleFunctionCallback & callback);

GLBINDING_API void setBeforeCallback(const FunctionCallback & callback);
GLBINDING_API void setAfterCallback(const FunctionCallback & callback);

} // namespace glbinding
