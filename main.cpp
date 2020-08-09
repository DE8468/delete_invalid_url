#include <netdb.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>
#include <vector>
#include <unistd.h>

std::string url_to_host(std::string url) {
    std::string::size_type s1 = url.find_first_of("//");
    if (s1 == std::string::npos) {
        return url;
    }
    std::string s0 = url.substr(s1 + 2);
    return s0.substr(0, s0.find_first_of('/'));
}

bool is_invalid(std::string url) {
    struct addrinfo *answer;
    return getaddrinfo(url_to_host(std::move(url)).c_str(), nullptr, nullptr, &answer) == 0;
}

int main() {
    std::ifstream input("input_url");
    std::ofstream output("output_url");
    std::ostream_iterator<std::string> output_iterator(output, "\n");
    std::string line;
    std::vector<std::string> url;
    std::vector<std::string> out_url;
    while (std::getline(input, line)) {
        url.push_back(line);
    }
    for (auto &i : url) {
        std::cout << i << std::endl;
        if (is_invalid(i)) {
            out_url.push_back(i);
        }
        usleep(100000);
    }
    std::copy(out_url.begin(), out_url.end(), output_iterator);
    input.close();
    output.close();
    return 0;
}
