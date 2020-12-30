#include "progressbar.hpp"

ProgressBar::ProgressBar (std::string name, ul_t total) : m_name (name), m_size (total) {}

ProgressBar::~ProgressBar () {}

void
ProgressBar::PutAt (ul_t i)
{
    real_t progress = static_cast<real_t> (i) / m_size;

    int barWidth = 30;

    std::cout << COLOR_GREEN << "\u27A4 " << COLOR_DEFAULT << m_name << std::string (10 - m_name.size (), ' ') << " ";
    int pos = static_cast<int> (barWidth * progress);

    for (int i = 0; i < barWidth; ++i)
    {
        if (i <= pos)
            std::cout << "\u25AE";
        else
            std::cout << " ";
    }

    std::cout << " " << COLOR_YELLOW << int (progress * 100.0) << "% " << COLOR_DEFAULT << "       \r";
    std::cout.flush ();
}

void
ProgressBar::End ()
{
    std::cout << std::endl;
    return;
}
