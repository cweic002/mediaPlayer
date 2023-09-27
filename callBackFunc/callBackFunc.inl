
template<typename Func>
inline CallBackFunc<Func>::CallBackFunc(Func func):_func(func){}

template <typename Func>
inline void CallBackFunc<Func>::operator()(){
    _func();
}