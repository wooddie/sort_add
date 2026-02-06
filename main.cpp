#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <iostream>

struct Person
{
    std::string id;
    int amount;
};

std::vector<Person> readCSV(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<Person> data;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        Person p;
        std::getline(ss, p.id, '\t');
        std::getline(ss, token, '\t');
        p.amount = std::stoi(token);

        data.push_back(p);
    }
    return data;
}

void writeCSV(const std::string &filename, const std::vector<Person> &data)
{
    std::ofstream file(filename);
    for (const auto &p : data)
    {
        file << p.id << "\t" << p.amount << "\n";
    }
}

void normalizeId(Person &p)
{
    const size_t WIDTH = 12;
    if (p.id.length() < WIDTH)
    {
        p.id.insert(0, WIDTH - p.id.length(), '0');
    }
}

void process(std::vector<Person> &data)
{
    for (auto &p : data)
    {
        normalizeId(p);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "\nFor Linux/MacOS\nUsage: ./program input.csv\n\nFor Windows\nnUsage: program input.csv\n";
        return 1;
    }

    auto data = readCSV(argv[1]);
    process(data);
    writeCSV("output.csv", data);

    return 0;
}

/*
*   excel formula
*   =ЕСЛИ(A1<>""; ТЕКСТ(A1; "000000000000"); "")
*/