#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <bitset>
#include <algorithm>

class solution {
public:
    std::vector<std::vector<int>> grayCode(int n) {
	std::vector<std::vector<int>> gcode = getCode(n, std::vector<int>{0});
	for (auto & vec : gcode) {
	    std::transform(vec.begin(), vec.end(), std::ostream_iterator<std::bitset<4>>(std::cout, "\n"),
			   [](int i){
			       return std::bitset<4>(i);
			   });
	    std::cout << std::endl;
	}
	return gcode;
    }

private:
    std::vector<std::vector<int>> getCode(int n, const std::vector<int> & curr) {
	std::vector<std::vector<int>> result;
	if (curr.size() == int(pow(2,n)))
	    result.push_back(curr);
	else {
	    std::vector<int> next = getNext(n, curr);
	    for (auto nx : next) {
		auto curr_copy = curr;
		curr_copy.push_back(nx);
		auto temp = getCode(n, curr_copy);
		std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
	    }
	}
	return result;
    }

    std::vector<int> getNext(int n, const std::vector<int> & curr) {
	std::vector<int> next;
	std::bitset<32> bset(curr.back());
	for (int i = 0; i < n; i++) {
	    auto cpy = bset;
	    cpy.flip(i);
	    if (std::find(curr.begin(), curr.end(), int(cpy.to_ulong())) == curr.end())
		next.push_back(int(cpy.to_ulong()));
	}
	return next;
    }
};

int main() {
    int numOfBits = 4;

    solution soln;
    auto code = soln.grayCode(numOfBits);
}
