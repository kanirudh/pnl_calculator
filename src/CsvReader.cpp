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


CsvReader::CsvReader(const std::string &filename, const bool containsHeader) : file_(filename) {
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
    return parseCsvLine(line);
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


class CsvReader {
public:
    explicit CsvReader(const std::string &filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }

    std::optional<std::vector<std::string> > getNext() {
        std::string line;
        if (!std::getline(file, line)) {
            return std::nullopt;
        }
        return parseCsvLine(line);
    }

private:
    static std::vector<std::string> parseCsvLine(const std::string &line) {
        std::vector<std::string> fields;
        std::string field;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];
            if (ch == '"') {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                    field += '"'; // escaped quote
                    ++i;
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (ch == ',' && !inQuotes) {
                fields.push_back(field);
                field.clear();
            } else {
                field += ch;
            }
        }
        fields.push_back(field); // last field
        return fields;
    }
};


