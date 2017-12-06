
#ifndef exception_h
#define exception_h

class exception
{
  public:
    exception() _USE_NOEXCEPT { }
    virtual ~exception() _USE_NOEXCEPT;

    /** Returns a C-style character string describing the general cause
     *  of the current error.  */
    virtual const char* what() const _USE_NOEXCEPT;
};


#endif // exception_h
