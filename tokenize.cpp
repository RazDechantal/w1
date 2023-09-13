#include <iostream>
#include <vector>

std::vector<std::string> tockens;
using namespace std;

std::vector<std::string> tokenize(std::string s, char c)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token, newStr;
    start = s.find_first_not_of(',', 0);
    do
    {
        end = s.find_first_of(',', start);
        if (start == end || s.length() == start)
            break;
        if (end >= 0)
        {
            token = s.substr(start, end - start);
        }
        else
        {
            token = s.substr(start, s.length() - start);
        }

        start = end + 1;
        tokens.push_back(token);
    } while (end > 0);

    return tokens;
}

int main()
{
    std::string s = "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187308,7.44564869";
    std::vector<std::string> tokens = tokenize(s, ',');
    for (const std::string &t : tokens)
    {
        std::cout << t << std::endl;
    }
    return 0;
}