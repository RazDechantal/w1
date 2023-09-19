#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

enum class OrderBookType
{
    bid,
    ask
};

int corruptedLines = 0;

ostream &operator<<(ostream &strm, OrderBookType ord)
{
    const string nameTT[] = {"ID", "KeyWord", "Operator", "Expression", "String", "Number", "Char"};
    return strm << ord;
}
class OrderBookEntry
{

private:
    string timestamp;
    string transaction;
    double price;
    double amount;
    OrderBookType ord;

public:
    double getPrice()
    {
        return price;
    }
    double getAmount()
    {
        return amount;
    }
    string getTimestamp()
    {
        return timestamp;
    }
    string getTransaction()
    {
        return transaction;
    }
    OrderBookType getOrderType()
    {
        return ord;
    }
    void setPrice(double givenPrice)
    {
        price = givenPrice;
    }
    void setAmount(double givenAmount)
    {
        amount = givenAmount;
    }
    void setTimestamp(string givenTimestamp)
    {
        timestamp = givenTimestamp;
    }
    void setTransaction(string givenTransaction)
    {
        transaction = givenTransaction;
    }
    void setOrderType(string orderType)
    {
        if (orderType == "bid")
            ord = OrderBookType::bid;
        else
            ord = OrderBookType::ask;
    }
};

std::vector<std::string> tockens;
std::vector<OrderBookEntry> orders;

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
    OrderBookEntry order;

    ifstream csvFile{"x.csv"};
    string line;

    if (csvFile.is_open())
    {
        cout << "File is open" << endl;
        while (std::getline(csvFile, line))
        {
            cout << "Read line: " << line << endl;
            std::vector<std::string> tokens = tokenize(line, ',');
            if (tokens.size() != 5)
            {
                cout << "Bad line" << endl;
                continue;
            }
            try
            {
                double price = stod(tokens[3]);
                double amount = stod(tokens[4]);
                order.setPrice(price);
                order.setAmount(amount);
                order.setTimestamp(tokens[0]);
                order.setTransaction(tokens[1]);
                order.setOrderType(tokens[2]);
                orders.push_back(order);

                cout << "Price is: " << order.getPrice() << endl;
                cout << "Amount is: " << order.getAmount() << endl;
                cout << "Time stamp: " << order.getTimestamp() << endl;
                cout << "Transaction is: " << order.getTransaction() << endl;
                string myOrder = (order.getOrderType() == OrderBookType::ask) ? "ask" : "bid";
                cout << "Order Type: " << myOrder << endl;
            }
            catch (const std::invalid_argument &e)
            {
                cout << "Bad float! " << endl;
                std::cerr << e.what() << '\n';
                ++corruptedLines;
                continue;
            }
        }

        cout << "The total number of orders: " << orders.size() << endl;
        cout << "The total number of corrupted lines: " << corruptedLines << endl;
        csvFile.close();
    }

    return 0;
}