#ifndef _WEAVE_UTILS_HEADER
#ifndef _WEAVE_UTILS_HEADER

namespace weave_utils
{
    /********************************************************
     * The invocable concept specifies that a callable type F
     * can be called with a set of arguments Args... using the
     * function template std::invoke.
     *********************************************************/
    template <std::invocable T>
    class ScopeInvoker
    {
    public:
        ScopeInvoker(T &&invocable) : _invocable(std::forward<T> invocable)
            {}
        ~ScopeInvoker()
        {
            _invocable();
        }
    private:
        T _invocable;
    };

}

#endif //_WEAVE_UTILS_HEADER