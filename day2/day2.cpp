#include <iostream>
#include <fstream>
#include <string> 

int compute_position(const std::string& file_name)
{
    // Open the file 
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int depth = 0;
    int position = 0;
    // Check if the file is open
    
    if(file.is_open()){
        // String for getting the line
        std::string line;
        while( std::getline(file, line) )
        {
            // Commands are format 'forward 5'
            
            // Find the empty character
            std::string::size_type n = line.find(" ");
            if(n == std::string::npos){
                // This should never happen, but just in case
                std::cout << "Incorrect formatted command" << std::endl;
                continue;
            }
            else{
                std::string command = line.substr(0, n);
                int val = std::stoi(line.substr(n+1,line.size()));
                if(command == "forward"){
                    position += val;
                }
                else if(command == "up")
                {
                    depth -= val;
                }
                else if(command == "down")
                {
                    depth += val;
                }
            }

        }
    }
    return depth * position;
}

int compute_position_2(const std::string& file_name)
{
    // Open the file 
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int depth = 0;
    int position = 0;
    int aim = 0;
    // Check if the file is open
    
    if(file.is_open()){
        // String for getting the line
        std::string line;
        while( std::getline(file, line) )
        {
            // Commands are format 'forward 5'
            
            // Find the empty character
            std::string::size_type n = line.find(" ");
            if(n == std::string::npos){
                // This should never happen, but just in case
                std::cout << "Incorrect formatted command" << std::endl;
                continue;
            }
            else{
                std::string command = line.substr(0, n);
                int val = std::stoi(line.substr(n+1,line.size()));
                if(command == "forward"){
                    position += val;
                    depth += aim*val;
                }
                else if(command == "up")
                {
                    aim -= val;
                }
                else if(command == "down")
                {
                    aim += val;
                }
            }

        }
    }
    return depth * position;
}

int main()
{
    std::cout << compute_position("input.txt") << std::endl;
    std::cout << compute_position_2("input.txt") << std::endl;
    return 0;
}