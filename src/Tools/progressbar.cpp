#include "progressbar.hpp"

ProgressBar::ProgressBar (std::string name, ul_t total) : m_name (name),
                                                          m_size (total)
{
}

ProgressBar::~ProgressBar ()
{
}

void
ProgressBar::PutAt (ul_t i)
{
    real_t progress = static_cast<real_t> (i) / m_size;

    int barWidth = 70;

    std::cout << m_name << std::string (10 - m_name.size (), ' ') << " [";
    int pos = barWidth * progress;

    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }

    std::cout << "] " << int (progress * 100.0) << "% \r";
    std::cout.flush ();
}

void
ProgressBar::End ()
{
    std::cout << std::endl;
    return;
}