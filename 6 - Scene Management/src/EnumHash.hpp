#ifndef EnumHash_hpp
#define EnumHash_hpp

struct EnumHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

#endif /* EnumHash_hpp */
