#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <cmath>

int compute_power(const std::string& file_name)
{
    // Open the file 
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int gamma = 0;
    int epsilon = 0;

    // Check if the file is open
    std::vector<int> ones;
    int total_entries = 0;

    if(file.is_open()){

        std::string line;
        while( std::getline(file, line) )
        {
            // This is our first line, resize the vector
            if(ones.size() == 0){
                ones.resize(line.size(), 0);
            }
            for(int i = 0; i < line.size(); i++){
                // If it's a 1 increase the ones vector
                // std::cout << line.at(i) << std::endl;
                if(line.at(i) == '1'){
                    ones[i]++; 
                }
            }
            total_entries++;
        }
    }
    for(int i = 0; i < ones.size(); i++)
    {
        if(static_cast<double>(ones.at(i)) >= static_cast<double>(total_entries / 2.0))
        {
            // Common value is a 1
            epsilon += std::pow(2, (ones.size() - 1) - i) * 1;
            gamma += std::pow(2, (ones.size() - 1) - i) * 0;
        }
        else{
            // Common value is a 1
            epsilon += std::pow(2, (ones.size() - 1) - i) * 0;
            gamma += std::pow(2, (ones.size() - 1) - i) * 1;                
        }
    }
    return gamma * epsilon;
}

char find_most_common(const std::vector<std::string>& lines, int idx){
    
    // Check if the file is open
    int total_ones = 0;
    for(const auto& entry : lines){
        if(entry.at(idx) == '1'){
            total_ones++;
        }
    }
    if(static_cast<double>(total_ones) >= static_cast<double>(lines.size()/2.0))
    {
        return '1';
    }
    else
    {
        return '0';
    }

}

char find_least_common(const std::vector<std::string>& lines, int idx){
    
    // Check if the file is open
    int total_zeros = 0;
    for(const auto& entry : lines){
        if(entry.at(idx) == '0'){
            total_zeros++;
        }
    }
    if(static_cast<double>(total_zeros) <= static_cast<double>(lines.size()/2.0))
    {
        return '0';
    }
    else
    {
        return '1';
    }

}

void remove_lines(std::vector<std::string>& lines, char val, int idx){
    auto itr = lines.begin();
    while(itr != lines.end())
    {
        if((*itr).at(idx) == val)
        {
            itr = lines.erase(itr);
        }
        else{
            ++itr;
        }
    }
}

int compute_life(const std::string& file_name)
{
    // Open the file 
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int oxy = 0;
    int co2 = 0;

    // Lets start with an ugly solution
    // Read in the file to a vector and make a copy.... ugh
    std::vector<std::string> lines_oxy;
    std::size_t line_size = 0;
     
    if(file.is_open()){

        std::string line;
        while( std::getline(file, line) )
        {   
            if(line_size == 0){
                line_size = line.size();
            }
            lines_oxy.emplace_back(line);
        }
    }
    std::vector<std::string> lines_co2 = lines_oxy;
    std::cout << lines_oxy.size() << std::endl;
    // Go through the whole line
    std::cout << line_size << std::endl;
    std::string oxy_line, co2_line;
    for(int i = 0; i < line_size; i++)
    {
        std::cout << "Iteration " << i << std::endl;
        if(lines_co2.size() > 1){
            char most_common = find_most_common(lines_co2, i);
            std::cout << most_common << std::endl;
            remove_lines(lines_co2, most_common, i);
        }
        if(lines_oxy.size() > 1)
        {
            char least_common = find_least_common(lines_oxy, i);
            remove_lines(lines_oxy, least_common, i);
        }
        if(lines_oxy.size() == 1){
            oxy_line = lines_oxy.at(0);
        }
        if(lines_co2.size() == 1){
            co2_line = lines_co2.at(0);
        }
    }

    std::cout << "oxygen line " << oxy_line << std::endl;
    std::cout << "co2 line " << co2_line <<  std::endl;

    // Compute oxy
    for(int i=0; i <oxy_line.size(); i++)
    {
        if(oxy_line.at(i) == '1')
        {
            oxy += std::pow(2, (oxy_line.size() - 1) - i) * 1;
        }
        else{
            oxy += std::pow(2, (oxy_line.size() - 1) - i) * 0;
        }
    }


    for(int i=0; i <co2_line.size(); i++)
    {
        if(co2_line.at(i) == '1')
        {
            co2 += std::pow(2, (co2_line.size() - 1) - i) * 1;
        }
        else{
            co2 += std::pow(2, (co2_line.size() - 1) - i) * 0;
        }
    }


    return oxy * co2;
}

int main()
{
    std::cout << compute_power("small_input.txt") << std::endl;
    std::cout << compute_life("input.txt") << std::endl;
    return 0;
}