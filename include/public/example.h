// Most modern compilers support this now.
#pragma once

namespace example
{

/**
 * Currently this class has no functionality, but is used as example
 * code.
 */
class Example
{
public:
    /** 
     * Create the default constructor and make it explicit so that
     * it does not get automatically created based on the compilers
     * interpretation of casting code.
     */
    explicit Example() = default;

    /**
     * Create the default constructor, ensure that it is virtual.
     */
    virtual ~Example() = default;

private:
};

} // namespace example
