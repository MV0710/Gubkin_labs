#include <fstream>

class CompressorStation {
private:
    int id;
    static int Nextid;
public:
    inline int getid() const { return id; };
    std::string name;
    int num_workshops;
    int num_workshops_in_operation;
    double efficiency;
    CompressorStation();
    void read();
    void display() const;
    void edit();
    void save_data(const std::unordered_map<int, CompressorStation>& stations, const std::string& file_name);
    void load_data(std::unordered_map<int, CompressorStation>& stations, const std::string& file_name);
};