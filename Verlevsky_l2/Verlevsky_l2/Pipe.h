#include <fstream>

class Pipe {
private:
    int id;
    static int Nextid;

public:
    inline int getid() const { return id; };
    std::string name;
    int length;
    int diameter;
    bool under_repair;
    Pipe();
    void read();
    void display() const;
    void toggle_repair();
    void save_data(const std::unordered_map<int, Pipe>& pipes, const std::string& file_name);
    void load_data(std::unordered_map<int, Pipe>& pipes, const std::string& file_name);
};