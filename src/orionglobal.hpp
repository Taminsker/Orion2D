#ifndef ORIONGLOBAL_HPP
#define ORIONGLOBAL_HPP

// typedef
typedef double        real_t;
typedef unsigned long ul_t;
typedef int           error_t;
typedef int           idx_t;

// values
#define MATH_PI    3.14159265358979323846264338328
#define MATH_SQRT3 1.732050807568877293527446341506

// attributes for function
#define ORION_INLINE        inline
#define ORION_FLATTEN       __attribute__ ((flatten))
#define ORION_ALWAYS_INLINE __attribute__ ((always_inline))
#define ORION_HARD_INLINE   ORION_INLINE ORION_FLATTEN ORION_ALWAYS_INLINE

// Colors
#define COLOR_BLACK   "\033[0;30m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[0;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_WHITE   "\033[0;97m"
#define COLOR_DEFAULT "\033[0;0m"
#define UNDERLINE     "\033[0;4m"
#define BLINK         "\033[0;5m"
#define REVERSE       "\033[1;7m"
#define TREE_BRANCH   "\u251C\u2500\u2500"
#define ENDLINE       COLOR_DEFAULT << std::endl
#define FLUSHLINE     COLOR_DEFAULT << std::flush
#define SEPARATOR     "--------------------------"
#define ENDFUN        std::cout << ENDLINE
#define COUT          std::cout

#define SPC  std::setw (15) <<
#define NEXT " " <<

#define USE_ERROR(X)                                                                                                   \
    if (X == EXIT_FAILURE)                                                                                             \
    {                                                                                                                  \
        return X;                                                                                                      \
    }

#define TRY(X)                                                                                                         \
    {                                                                                                                  \
        error_t error = X;                                                                                             \
        if (error == EXIT_FAILURE)                                                                                     \
        {                                                                                                              \
            return EXIT_FAILURE;                                                                                       \
        }                                                                                                              \
    }

// Custom print

#ifdef DEBUG
#define DEBUG_FORMAT        "[" << __FUNCTION__ << ", " << __LINE__ << "] "
#define GEAR_SYMBOL         ""
#define ARROW_NOTAIL_SYMBOL ""
#define HAMMER_SYMBOL       ""
#define WARNING_SYMBOL      ""
#define ARROW_SYMBOL        ""
#else
#define DEBUG_FORMAT        ""
#define GEAR_SYMBOL         "\u2699 "
#define ARROW_NOTAIL_SYMBOL "\u27A4 "
#define HAMMER_SYMBOL       "\u2692 "
#define WARNING_SYMBOL      "\u26A0 "
#define ARROW_SYMBOL        "\u279C "
#endif

#define BEGIN   std::cout << DEBUG_FORMAT << REVERSE << ARROW_SYMBOL
#define STATUS  std::cout << DEBUG_FORMAT << COLOR_RED << GEAR_SYMBOL << COLOR_DEFAULT
#define INFOS   std::cout << DEBUG_FORMAT << COLOR_GREEN << ARROW_NOTAIL_SYMBOL << COLOR_DEFAULT
#define ERROR   std::cerr << DEBUG_FORMAT << COLOR_RED << HAMMER_SYMBOL
#define WARNING std::cout << DEBUG_FORMAT << COLOR_YELLOW << WARNING_SYMBOL

// Additional defs
#define ORION_UNUSED(X)                    (void) X
#define ORION_NAMESPACE                    orion_internal
#define ORION_FORWARD_DECLARE_CLASS(Class) class Class;

#define ORION_DISABLE_CONSTRUCTOR(Class) Class () = delete;

#define ORION_DISABLE_COPY(Class)                                                                                      \
    Class (const Class &) = delete;                                                                                    \
    Class &operator= (const Class &) = delete;

#define ORION_DISABLE_MOVE(Class)                                                                                      \
    Class (Class &&) = delete;                                                                                         \
    Class &operator= (Class &&) = delete;

#define ORION_DISABLE_COPY_MOVE(Class)                                                                                 \
    ORION_DISABLE_COPY (Class)                                                                                         \
    ORION_DISABLE_MOVE (Class)

#endif /* ORIONGLOBAL_HPP */
