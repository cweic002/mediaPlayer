#ifndef CALBACkFUNC_H
#define CALBACkFUNC_H
#include "ICallBackFunc.h"

template <typename Func>
class CallBackFunc : public ICallBackFunc {
    Func _func;
public:
    CallBackFunc(Func func);
    void operator ()() override;
};

#include "callBackFunc.inl"

#endif //CALBACkFUNC_H