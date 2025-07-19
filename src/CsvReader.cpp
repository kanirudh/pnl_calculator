//
// Created by Anirudh Agrawal on 7/19/25.
//

#include "CsvReader.h"

std::vector<std::string> tokenizeCommaSeparated(const std::string &input) {
    std::vector<std::string> tokens;
    std::size_t start = 0;
    std::size_t end;

    while ((end = input.find(',', start)) != std::string::npos) {
        tokens.emplace_back(input.substr(start, end - start));
        start = end + 1;
    }

    // Add last token
    tokens.emplace_back(input.substr(start));

    return tokens;
}


CsvReader::CsvReader(std::string_view filename, const bool containsHeader) : file_(std::string(filename)) {

    if (not file_.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    if (auto h = GetNext(); h and containsHeader
    ) {
        header_ = *h;
    }
}

bool CsvReader::IsFinished() const {
    return file_.eof();
}

auto CsvReader::GetNext() -> std::optional<Line> {
    std::string line;
    if (!std::getline(file_, line)) {
        return std::nullopt;
    }
    return Tokenize(line);
}

auto CsvReader::Tokenize(std::string_view input) -> std::vector<std::string> {
    Line result;
    auto itr = input.find(kDelimiter);
    for (; itr != std::string::npos; itr = input.find(kDelimiter)) {
        result.emplace_back(input.substr(0, itr));
    }
    // Input the last column
    result.emplace_back(input.substr(0, itr));
    return result;
}
