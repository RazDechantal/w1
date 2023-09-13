#include <iostream>
#include <vector>
#include <fstream>

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
    // std::string s = "2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187308,7.44564869";
    // for (const std::string &t : tokens)
    // {
    //     std::cout << t << std::endl;
    // }
    // s = "1,22,333,4444,55555";
    // tokens = tokenize(s, ',');
    // for (const std::string &t : tokens)
    // {
    //     std::cout << t << std::endl;
    // }
    // s = "ölkölk,iuoiuoi,1,2,ölkölkölk,7777";
    // tokens = tokenize(s, ',');
    // for (const std::string &t : tokens)
    // {
    //     std::cout << t << std::endl;
    // }

    ifstream csvFile{"20200317.csv"};
    string line;
    std::vector<std::string> tokens;

    if (csvFile.is_open())
    {
        cout << "File is open" << endl;
        getline(csvFile, line);

        while (getline(csvFile, line))
        {
            cout << "Read line: " << line << endl;
            tockens = tokenize(line, ',');
            cout << "Token size is: " << tokens.size() << endl;
            if (tokens.size() != 5)
            {
                cout << "Bad token" << endl;
                continue;
            }
            double price = stod(tokens[3]);
            double amount = stod(tokens[4]);
            cout << price << ": " << amount << endl;
        }

        csvFile.close();
    }

    return 0;
}