#include <iostream>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <string>
#include <set>

template<std::ranges::view View>
bool all_elements_unique(View view)
{
    //could use algorithm
        //sort(rng)
        //auto pos = std::adjacent_find(rng)
        //return pos 
    //but sorting the view sorts the underlying container and we don't want that

    for (auto begin = std::ranges::begin(view), end = std::ranges::end(view); begin != end; ++begin)
    {
        auto current = begin;
        ++current;
        for ( ; current != end; ++current)
        {
            if (*begin == *current)
            {
                return false;
            }
        }
    }
    return true;
}

template<std::ranges::sized_range Rng>
int first_n_unique_elements_pos(Rng rng, std::size_t n)
{
    //c++23 has std::views::slide which would be perfect for this...
    auto begin = std::ranges::begin(rng);
    for (auto pos : std::views::iota(0u, std::ranges::size(rng) - n))
    {
        auto slide_view = std::ranges::subrange(begin, begin + n);
        if (all_elements_unique(slide_view))
        {
            return pos;
        }
        ++begin;
    }
    return -1;
}

int find_first_packet_marker(std::string_view buffer)
{
    static constexpr auto marker_size{ 4 };
    if (const int pos = first_n_unique_elements_pos(buffer, marker_size); pos != -1)
    {
        return pos + marker_size;
    }
    return -1;
}

int find_first_message_marker(std::string_view buffer)
{
    static constexpr auto marker_size{ 14 };
    if (const int pos = first_n_unique_elements_pos(buffer, marker_size); pos != -1)
    {
        return pos + marker_size;
    }
    return -1;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout << "Incorrect number of args\n";
            return 1;
        }

        if (std::ifstream data(argv[1]); data)
        {
            std::string buffer;
            while (std::getline(data, buffer))
            {
                //tried using std::views::istream but it did not want to compile
                //std::views::istream is probably not sized which would make sense
                const int packet_pos = find_first_packet_marker(buffer);
                if (packet_pos == -1)
                {
                    std::cout << "Could not find marker\n";
                }
                else
                {
                    std::cout << "Found packet marker at position " << packet_pos << '\n';
                }

                const int message_pos = find_first_message_marker(buffer);
                if (message_pos == -1)
                {
                    std::cout << "Could not find marker\n";
                }
                else
                {
                    std::cout << "Found message marker at position " << message_pos << '\n';
                }
            }
        }

        std::cout << "Could not open file " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}