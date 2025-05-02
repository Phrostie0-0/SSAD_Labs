#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

using namespace std;

// Shared properties (Flyweight)
class FormatType {
private:
    string font;
    int size;
    string color;

public:
    FormatType(const string& f, int s, const string& c)
            : font(f), size(s), color(c) {}

    // ← Add these getters
    const string& getFont()  const { return font; }
    int getSize()  const { return size; }
    const string& getColor() const { return color; }

    void printFormat() const {
        cout << "Format: " << font << ", " << size << "pt, " << color;
    }

    bool operator==(const FormatType& other) const {
        return font == other.font
               && size  == other.size
               && color == other.color;
    }
};

// Hash functor for FormatType, now using the getters
struct FormatTypeHash {
    size_t operator()(const FormatType& f) const {
        auto h1 = hash<string>()(f.getFont());
        auto h2 = hash<int>()   (f.getSize());
        auto h3 = hash<string>()(f.getColor());
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

// Factory to manage shared formats
class FormatFactory {
private:
    static unordered_map<FormatType, shared_ptr<FormatType>, FormatTypeHash> formatMap;

public:
    shared_ptr<FormatType> getFormat(const string& font, int size, const string& color) {
        FormatType key(font, size, color);
        auto it = formatMap.find(key);
        if (it == formatMap.end()) {
            cout << "Creating new format: ";
            key.printFormat();
            cout << endl;
            auto ptr = make_shared<FormatType>(font, size, color);
            formatMap.emplace(key, ptr);
            return ptr;
        }
        return it->second;
    }

    void showAllFormats() const {
        cout << "\nCurrently stored formats:\n";
        for (auto& kv : formatMap) {
            kv.second->printFormat();
            cout << endl;
        }
    }
};

unordered_map<FormatType, shared_ptr<FormatType>, FormatTypeHash>
        FormatFactory::formatMap;

// Individual character with shared formatting
class FormattedChar {
private:
    char symbol;
    shared_ptr<FormatType> format;

public:
    FormattedChar(char c, shared_ptr<FormatType> f)
            : symbol(c), format(f) {}

    void print() const {
        cout << symbol << " (";
        format->printFormat();
        cout << ")" << endl;
    }
};

int main() {
    FormatFactory formatFactory;
    vector<FormattedChar> document;

    document.emplace_back('H', formatFactory.getFormat("Arial", 12, "Red"));
    document.emplace_back('e', formatFactory.getFormat("Arial", 12, "Red"));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Red"));
    document.emplace_back('l', formatFactory.getFormat("Arial", 12, "Red"));
    document.emplace_back('o', formatFactory.getFormat("Arial", 12, "Red"));
    document.emplace_back(' ', formatFactory.getFormat("Times New Roman", 12, "Black"));
    document.emplace_back('W', formatFactory.getFormat("Arial", 14, "Blue"));
    document.emplace_back('o', formatFactory.getFormat("Arial", 14, "Blue"));
    document.emplace_back('r', formatFactory.getFormat("Arial", 14, "Blue"));
    document.emplace_back('l', formatFactory.getFormat("Arial", 14, "Blue"));
    document.emplace_back('d', formatFactory.getFormat("Arial", 14, "Blue"));
    document.emplace_back('!', formatFactory.getFormat("Arial", 16, "Green"));

    cout << "\nFormatted Document:\n";
    for (const auto& ch : document)
        ch.print();

    formatFactory.showAllFormats();
    return 0;
}