#include <iostream>
#include <sstream>
#include <fstream>
#include <string> 
#include <vector>
#include <array>
#include <cmath>

static constexpr int kBingoSize = 5;

class BingoBoard
{
    public:
        BingoBoard();
        void AddRow(std::array<int, 5>&& row, const int pos);
        bool DrawNumber(const int num);
        int GetSum() {return win_sum_;}
        int GetWin() {return is_winner_;}
        void PrintBoard() const;
    private:
        void ComputeSumUnmarked();
        bool HasWon(const int row, const int col);

        // probably should just make this an array of tuples, but oh well
        std::array<std::array<int, kBingoSize>, kBingoSize> num_board_;
        std::array<std::array<bool, kBingoSize>, kBingoSize> bool_board_;
        bool is_winner_ = false;
        int win_sum_ = 0;
};

BingoBoard::BingoBoard()
{
    // empty constructor
}


void BingoBoard::AddRow(std::array<int, kBingoSize>&& row, const int pos){
    num_board_.at(pos) = std::move(row);
    bool_board_.at(pos) = {false, false, false, false, false};
}

void BingoBoard::PrintBoard() const
{
    for(const auto& row : num_board_){
        for(const auto& num : row){
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

bool BingoBoard::DrawNumber(const int num)
{
    bool num_found = false;
    int col, row;
    for(int i = 0; i < kBingoSize; i++){
        for(int j=0; j<kBingoSize; j++){
            if(num_board_[i][j] == num){
                num_found = true;
                row = i;
                col = j;
                bool_board_[i][j] = true;
                break;
            }
        }
    }
    if(num_found){
        return HasWon(row, col);
    }
    else{
        return num_found;
    }
}

void BingoBoard::ComputeSumUnmarked(){
    for(int i=0; i<kBingoSize; i++){
        for(int j=0; j<kBingoSize; j++){
            if(!bool_board_[i][j]){
                win_sum_ += num_board_[i][j];
            }
        }
    }
}

bool BingoBoard::HasWon(const int row, const int col)
{
    bool win = true;

    for(int i=0; i<kBingoSize; i++){
        win = win && bool_board_[i][col];
    }
    if(win){
        is_winner_ = win;
        ComputeSumUnmarked();
        return win;
    }

    win = true;
    for(int j=0; j<kBingoSize; j++){
        win = win && bool_board_[row][j];
    }
    if(win){
        is_winner_ = win;
        ComputeSumUnmarked();
        return win;
    }
    return win;
}

std::vector<int> LineToIntVec(const std::string& line, const char delim){
    std::vector<int> line_nums;
    std::string word = "";
    for(const char& c : line){
        if(c == delim){
            if(word.length() > 0){
                line_nums.emplace_back(std::stoi(word));
                word = "";
            }

        }
        else{
            word += c;
        }
    }
    // Gotta catch the last word that would be a new line at the end
    line_nums.emplace_back(std::stoi(word));
    return line_nums;

}

int RunBingoGame(const std::string& file_name, bool first_win=true){
    std::ifstream file(file_name, std::ios::in);

    std::vector<int> nums_to_play;
    std::vector<BingoBoard> boards_in_game;
    BingoBoard last_win_board;
    int last_win_num;
    // bool any_board_won = false;
    // bool all_boards_won = false;

    if(file.is_open()){
        std::string line;

        // Get the first line
        std::getline(file, line);

        // String Split by delimiter commas
        nums_to_play = LineToIntVec(line, ',');

        // Read the first blank line this is the file format
        // std::getline(file, line);
        // Declare a bingboar to fille
        BingoBoard cur_board;
        int row_num = 0;

        while(std::getline(file, line)){
            if(line.empty()){
                // nothing to do here
                continue;
            }
            else{
                std::vector<int> row_vec = LineToIntVec(line, ' ');
                std::array<int, 5> row_array;
                std::move(row_vec.begin(), row_vec.end(),row_array.begin());
                cur_board.AddRow(std::move(row_array), row_num);
                row_num++;
                if(row_num == 5){                
                    boards_in_game.emplace_back(std::move(cur_board));
                    cur_board = BingoBoard();
                    row_num = 0;
                }
            }
        }

        for(const auto& num: nums_to_play){
            for(auto& board: boards_in_game){
                if(board.GetWin()){
                    // If the board has won skip it
                    // I should really remove it, but lazy..
                    continue;
                }
                if(board.DrawNumber(num)){
                    if(first_win){
                        std::cout << "Winning Num is " << num << std::endl;
                        board.PrintBoard();
                        return board.GetSum() * num;
                    }
                    else{
                        last_win_board = board;
                        last_win_num = num;
                    }
                }
            }
        }
    }
    if(first_win){
        return 0;
    }
    else{
        std::cout << "Winning Num is " << last_win_num << std::endl;
        last_win_board.PrintBoard();
        return last_win_board.GetSum() * last_win_num;
    }
}

int main()
{
    std::cout << "Hello World" << std::endl;
    std::cout << "Result: " << RunBingoGame("input.txt") << std::endl;
    std::cout << RunBingoGame("input.txt", false) << std::endl;
    return 0;
}