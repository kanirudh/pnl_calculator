//
// Created by Anirudh Agrawal on 7/19/25.
//

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <vector>
#include <string_view>
#include <optional>

class CsvReader {
    static constexpr char kDelimiter = ',';

public:
    using Token = std::string;
    using Line = std::vector<Token>;

    explicit CsvReader(const std::string &filename, const bool header = true);

    // Return the next line from the csv file.
    std::optional<Line> GetNext();

    bool IsFinished() const;

private:
    static Line Tokenize(std::string_view input);

    Line header_;
    std::ifstream file_;
};


#endif //PARSER_H
