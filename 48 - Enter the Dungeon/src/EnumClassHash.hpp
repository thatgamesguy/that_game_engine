#ifndef EnumClassHash_hpp
#define EnumClassHash_hpp

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif /* EnumClassHash_hpp */
