#include <bits/stdc++.h>
#include "utf8.h"

#include "files.h"

namespace files {
    
    /**
     * @brief Returns the name of the file containing the given maze.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze.
     */
    string get_maze_file_name(unsigned int number) {
        if (!mazes::is_maze_number_valid(number))
            throw "The provided maze number is invalid";

        string file_name = utf8::zfill(to_string(number), '0', 2, true);
        return "MAZE_" + file_name + ".TXT";
    }

    /**
     * @brief Returns the name of the file containing the given maze's winners.
     * 
     * @param number The number of the maze.
     * @return The name of the file containing the given maze's winners.
     */
    string get_maze_winners_file_name(unsigned int number) {
        if (!mazes::is_maze_number_valid(number))
            throw "The provided maze number is invalid.";

        string file_name = utf8::zfill(to_string(number), '0', 2, true);
        return "MAZE_" + file_name + "_WINNERS.TXT";
    }

    /**
     * @brief Opens the given file for reading.
     * If the file doesn't exist, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ifstream open_file_reader(string file_name) {
        ifstream file;
        file.open(file_name, ios::in);
        if (!file.is_open())
            throw "The given file doesn't exist";

        return file;
    }

    /**
     * @brief Opens the given file for writing.
     * If the file doesn't exist and it couldn't be created, an error is thrown.
     * 
     * @param file_name The name of the file. 
     * @return An open stream to the given file.
     */
    ofstream open_file_writer(string file_name) {
        ofstream file;
        file.open(file_name, ios::trunc);
        if (!file.is_open())
            throw "Couldn't create the given file";

        return file;
    }

    /**
     * @brief Returns the requested maze's data.
     * If the given maze file doesn't exist, can't be read or doesn't fulfill the expected format
     * exceptions are thrown.
     * 
     * @param maze The number of the maze.
     * @return The requested maze's data, if it exists.
     */
    mazes::Maze read_maze(unsigned int maze) {
        ifstream file = files::open_file_reader(files::get_maze_file_name(maze));
        
        try {
            char sep;
            size_t width, height;
            file >> width >> sep >> height;
            if (sep != 'x' || width == 0 || height == 0 || file.bad())
                throw "The given file does not fulfill the expected format";

            unsigned int* cells = (unsigned int*) malloc(width * height * sizeof(unsigned int));//TODO: free(cells); !!!!!!!!!!!!!!!!!
            
            try {
                mazes::Player player;
                bool has_found_player = false;

                vector<mazes::Robot> robots;
                
                char ch;
                size_t index = 0;
                while (file.get(ch)) {
                    if (ch == '\r') {
                        if (file.peek() != '\n')
                            throw "The given file does not fulfill the expected format";

                        continue;
                    }

                    if (ch == '\n') {
                        if (index % width != 0)
                            throw "The given file does not fulfill the expected format";

                        continue;
                    }

                    if (index >= width * height)
                        throw "The given file does not fulfill the expected format";

                    unsigned int value;
                    try {
                        value = mazes::translate_to_cell_value(ch);
                    } catch (...) {
                        throw "The given file does not fulfill the expected format";
                    }

                    size_t x = index % width;
                    size_t y = index / width;

                    if (mazes::is_cell_human(value)) {
                        if (!has_found_player) {
                            player.x = x;
                            player.y = y;

                            has_found_player = true;
                        } else
                            throw "The given file does not fulfill the expected format";

                    } else if (mazes::is_cell_robot(value)) {
                        robots.push_back({
                            robots.size() + 1, // Robot IDs start at 1
                            x, y
                        });
                    }

                    cells[index++] = value;
                }

                if (!has_found_player || index < width * height)
                    throw "The given file does not fulfill the expected format";

                file.close();
                return { maze, width, height, cells, player, robots };
            } catch (const char* ex) {
                free(cells);
                throw ex;
            }
        } catch (const char* ex) {
            file.close();
            throw ex;
        } 
    }

    /**
     * @brief Writes the player's name and score in the winner's file. The entries are sorted in ascending score order.
     * If the file doesn't exist or doesn't fulfill the expected format, exceptions are thrown.
     * 
     * @param maze The number of the maze.
     * @param player_name The given player's name.
     * @param player_score The player's score.
     */
    void save_maze_score(unsigned int maze, string player_name, time_t player_score) {
        static const string HEADER1 = "Player          - Time";
        static const string HEADER2 = "----------------------";

        struct Score {
            string name; 
            time_t score;
        };

        vector<Score> scores;
        string winners_file_name = files::get_maze_winners_file_name(maze);

        // Read scores from file
        try {

            ifstream file_reader = files::open_file_reader(winners_file_name);

            try {
                string line;
                getline(file_reader, line);
                if (line != HEADER1)
                    throw "The given file does not fulfill the expected format";

                getline(file_reader, line);
                if (line != HEADER2)
                    throw "The given file does not fulfill the expected format";

                while (getline(file_reader, line)) {
                    size_t length = utf8::length(line);
                    if (length != utf8::length(HEADER1))
                        throw "The given file does not fulfill the expected format";

                    size_t start_of_score = line.length() - 4; // Score has 4 characters
                    size_t start_of_separator = start_of_score - 3;
                    
                    string sep = line.substr(start_of_separator, 3);
                    if (sep != " - ")
                        throw "The given file does not fulfill the expected format";

                    string name = utf8::rtrim(line.substr(0, start_of_separator));
                    time_t score = stol(line.substr(start_of_score, 4));

                    scores.push_back({ name, score });
                }
                
                file_reader.close();
            } catch (const char* ex) {
                file_reader.close();
                throw ex;
            }
        } catch (...) {
            scores.clear();
        }

        // Sort scores 
        scores.push_back({ player_name, player_score });
        sort(scores.begin(), scores.end(), [] (auto first, auto second) {  
            return first.score < second.score;
        });

        // Write ordered scores to file
        ofstream file_writer = files::open_file_writer(winners_file_name); 

        file_writer << HEADER1 << '\n'
                    << HEADER2 << '\n';

        for (auto score : scores) {
            file_writer << utf8::zfill(score.name, ' ', 15, false)
                        << " - "
                        << utf8::zfill(to_string(score.score), ' ', 4, true)
                        << '\n';
        }   

        file_writer << flush;
        file_writer.close();
    }
} // namespace files
