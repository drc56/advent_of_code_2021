#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>


struct Point{
    int x;
    int y;
};

using PointList = std::vector<std::pair<Point, Point>>;

struct PointListInput{
    PointList point_list;
    int max_x = 0;
    int max_y = 0;
};

Point parse_point_string(const std::string& point_string){
    const std::string delim = ",";
    auto result = point_string.find(delim);
    if(result == std::string::npos){
        throw std::runtime_error("Invalid formatted point string");
    }
    Point point;
    point.x = std::stoi(point_string.substr(0,result));
    point.y = std::stoi(point_string.substr(result+1, point_string.size()));
    return point;
}

std::pair<Point, Point> parse_line(const std::string& line){

    // Split the string into two points
    const std::string seperator = " -> ";
    auto result = line.find(seperator);
    if(result == std::string::npos){
        throw std::runtime_error("Invalid formatted line");
    }
    const std::string first_point_string = line.substr(0, result);
    const std::string end_point_string = line.substr(result + seperator.size(), line.size());
    
    // Break string into points
    Point start = parse_point_string(first_point_string);
    Point end = parse_point_string(end_point_string);

    return std::make_pair(start, end);
}

PointListInput parse_file(const std::string& file_name){
    std::fstream file(file_name, std::ios::in);

    PointList input_point_list;
    PointListInput input_pl;

    // Parse the file
    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            auto point_pair = parse_line(line);
            input_point_list.emplace_back(point_pair);
            if(point_pair.first.x > input_pl.max_x){
                input_pl.max_x = point_pair.first.x;
            }
            if(point_pair.first.y > input_pl.max_y){
                input_pl.max_y = point_pair.first.y;
            }
            if(point_pair.second.x > input_pl.max_x){
                input_pl.max_x = point_pair.second.x;
            }
            if(point_pair.second.y > input_pl.max_y){
                input_pl.max_y = point_pair.second.y;
            }
        }
    }
    input_pl.point_list = input_point_list;
    return input_pl;
}


int points_with_two_vents(const std::string& file_name){
    
    // Parse file for point list
    PointListInput input_point_data = parse_file(file_name);

    // std::cout << "Max X: " << input_point_data.max_x << 
    // " Max Y: "<< input_point_data.max_y << std::endl;
    std::vector<std::vector<int>> grid(input_point_data.max_x+1, std::vector<int>(input_point_data.max_y+1,0));
    
    // Update grid based on points
    for(const auto& point : input_point_data.point_list){
        bool x_line = false;
        bool y_line = false;
        if(point.first.x != point.second.x){
            x_line = true;
        }
        if(point.first.y != point.second.y){
            y_line = true;
        }
        if(x_line && y_line)
        {
            // I can probably do this cleaner...
            int x_start = point.first.x;
            int x_end = point.second.x;
            int y_start = point.first.y;
            int y_end = point.second.y;
            std::cout << x_start << y_start << " " << x_end << y_end << std::endl;
            if(x_start > x_end && y_start > y_end){
                for(int i=x_start, j=y_start; i>=x_end && j>=y_end; i--, j--){
                    grid[i][j]++;
                }
            }
            if(x_start < x_end && y_start > y_end){
                for(int i=x_start, j=y_start; i<=x_end && j>=y_end; i++, j--){
                    grid[i][j]++;
                }
            }
            if(x_start > x_end && y_start < y_end){
                for(int i=x_start, j=y_start; i>=x_end && j<=y_end; i--, j++){
                    grid[i][j]++;
                }
            }
            if(x_start < x_end && y_start < y_end){
                for(int i=x_start, j=y_start; i<=x_end && j<=y_end; i++, j++){
                    grid[i][j]++;
                }
            }


        }
        else if(x_line && !y_line){
            int start = std::min(point.first.x, point.second.x);
            int end = std::max(point.first.x, point.second.x);
            for(int i=start; i <= end; i++){
                grid[i][point.first.y]++;
            }
        }
        else if(!x_line && y_line){
            int start = std::min(point.first.y, point.second.y);
            int end = std::max(point.first.y, point.second.y);
            for(int i=start; i <= end; i++){
                grid[point.first.x][i]++;
            }
        }
    }
    
    int total_overlaps = 0;
    for(int i=0; i<input_point_data.max_x+1; i++){
        for(int j=0; j<input_point_data.max_y+1; j++){
            std::cout << grid[j][i];
            if(grid[i][j] >= 2 ){
                total_overlaps++;
            }
        }
        std::cout << std::endl;
    }

    return total_overlaps;
}

int main(){
    std::cout << points_with_two_vents("input.txt") << std::endl;
    return 0;
}