#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include <Windows.h>

#include <mapitron/mapitron.hpp>

int run()
{
    // call add
    std::cout << "8 + 3 = " << mapitron::add(8, 3) << std::endl;

    // call add_layer
    std::cout << "Adding layer" << std::endl;
    mapitron::add_layer(R"({ "type": "fill" })");
    std::cout << "Added layer" << std::endl;

    // load token
    {
        std::ifstream fstream("assets/secrets/token.txt");
        if (!fstream.is_open())
        {
            std::cout << "Failed to open token file (working directory: " << std::filesystem::current_path() << ")" << std::endl;
            return 1;
        }
        else
        {
            std::string line;
            std::getline(fstream, line);
            std::cout << "Token value: " << line << std::endl;
            fstream.close();
        }
    }

    // generate random number
    {
        int seed = 0;
        std::string filename = "assets/cache/seed.txt";

        // load file if it exists
        {
            std::ifstream istream(filename);    // scope closes the file
            if (istream.is_open())
            {
                std::string line;
                std::getline(istream, line);
                seed = std::stoi(line);
            }
        }

        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> distribution(1, 100);
        int value = distribution(gen);

        // write to file
        {
            std::ofstream ostream(filename);    // scope closes the file
            if (!ostream.is_open())
            {
                std::cout << "Failed to open seed file (working directory: " << std::filesystem::current_path() << ")" << std::endl;
                return 1;
            }
            else
            {
                std::cout << "New seed: " << value << std::endl;
                ostream << value;
            }
        }
    }

    // load roboto font
    {
        std::string roboto = mapitron::load_roboto();
        std::cout << "Roboto font: " << roboto << std::endl;
    }

    // load programs
    {
        std::cout << "Loaded programs: " << mapitron::load_programs() << std::endl;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    return run();
}