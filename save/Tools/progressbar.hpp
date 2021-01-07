#ifndef SRC_TOOLS_PROGRESSBAR_HPP
#define SRC_TOOLS_PROGRESSBAR_HPP

#include <iostream>
#include <string>

#include "../orionglobal.hpp"

class ProgressBar
{
public:
    ProgressBar (std::string name, ul_t total);
    ~ProgressBar ();
    void PutAt (ul_t i);
    void End ();

protected:
    std::string m_name;
    ul_t        m_size;
};
#endif /* SRC_TOOLS_PROGRESSBAR_HPP */
