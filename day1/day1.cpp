#include <iostream>
#include <fstream>
#include <string> 
#include <deque>

class CircularBuffer{
    public:
        CircularBuffer(int size);
        void add_element(int element);
        int get_sum();
        int get_size();
    private:
        int max_size_ = 0;
        std::deque<int> buffer_;
};

CircularBuffer::CircularBuffer(int size) : max_size_{size}
{

}

void CircularBuffer::add_element(int element)
{
    if(buffer_.size() < max_size_){
        buffer_.push_front(element);
    }
    else{
        buffer_.pop_back();
        buffer_.push_front(element);
    }
}

int CircularBuffer::get_sum()
{
    int sum = 0;
    for(const auto& val : buffer_){
        sum += val;
    }
    return sum;
}

int CircularBuffer::get_size()
{
    return buffer_.size();
}

int count_increases(const std::string& file_name)
{
    // Open the file 
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int increases = 0;
    // Check if the file is open

    if(file.is_open()){
        // String for getting the line
        std::string line;
        // Get the first line and set it to previous
        std::getline(file, line);
        int prev = std::stoi(line);

        while( std::getline(file, line) )
        {
            int cur = std::stoi(line);
            if(cur > prev){
                increases++;
            }
            prev = cur;
        }
    }
    return increases;
}

int count_increases_window(const std::string& file_name, int window_size)
{
    CircularBuffer meas_buf(window_size);
    
    std::ifstream file(file_name, std::ios::in); // file name, mode
    int increases = 0;

    if(file.is_open()){
        // String for getting the line
        std::string line;

        // Get the first lines up to window size and add to buffer
        for(int i=0; i<window_size; i++){
            std::getline(file, line);
            meas_buf.add_element(std::stoi(line));
        }
        int prev = meas_buf.get_sum();

        while( std::getline(file, line) )
        {
            meas_buf.add_element(std::stoi(line));
            int cur = meas_buf.get_sum();
            if(cur > prev){
                increases++;
            }
            prev = cur;
        }
    }
    return increases;

}


int main()
{
    std::cout << count_increases("input.txt") << std::endl;
    std::cout << count_increases_window("input.txt", 3) << std::endl;
    return 0;
}