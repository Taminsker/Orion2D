#ifndef SRC_CORE_MACROS_HPP
#define SRC_CORE_MACROS_HPP

#define INSERT_THE(X, Y)      \
    ORION_HARD_INLINE         \
    void                      \
    Insert (X * object)       \
    {                         \
        if (!object)          \
            return;           \
                              \
        for (X * in : Y)      \
            if (in == object) \
                return;       \
                              \
        Y.push_back (object); \
                              \
        return;               \
    }

#define REMOVE_THE(X, Y)           \
    ORION_HARD_INLINE              \
    void                           \
    Remove (X * object)            \
    {                              \
        if (!object)               \
            return;                \
                                   \
        std::vector<X *> to;       \
        for (X * in : Y)           \
            if (object != in)      \
                to.push_back (in); \
                                   \
        Y = to;                    \
                                   \
        return;                    \
    }

#define GET_THE(X, Y)    \
    ORION_HARD_INLINE    \
    X * Get##X (ul_t id) \
    {                    \
        return Y [id];   \
    }

#define GET_NUMBER_OF(X, Y)   \
    ORION_HARD_INLINE         \
    ul_t GetNumberOf##X##s () \
    {                         \
        return Y.size ();     \
    }

#endif /* SRC_CORE_MACROS_HPP */
