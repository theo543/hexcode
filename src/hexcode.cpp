#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdint>
#include <map>

const auto codes = []() {
	std::map<uint32_t, std::string> codes;
	#include "codes.inc"
	return codes;
}();

const auto official_names = []() {
	std::map<std::string, std::string> official_names;
	#include "official_names.inc"
	return official_names;
}();

int main(int args, char**argv) {
	if(args < 2) {
		std::cerr<<"Usage: hexcode <number>"<<std::endl;
		return EXIT_FAILURE;
	}

    std::string arg = argv[1];
	int32_t input;
    uint32_t data;

	try {
        if(arg.starts_with("0x") || arg.starts_with("0X")) {
            data = std::stoul(arg, nullptr, 16);
        } else {
            input = std::stoi(arg);
            std::memcpy(&data, &input, sizeof(input));
        }
	} catch(std::invalid_argument&) {
		std::cout << "failed to parse argument" << std::endl;
		return EXIT_FAILURE;
	} catch(std::out_of_range&) {
		std::cout << "argument is out of range" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << data;

	const auto iter = codes.find(data);
	if(iter != codes.end()) {
		std::cout << " (" << iter->second;
		const auto official_name = official_names.find(iter->second);
		if(official_name != official_names.end()) {
			std::cout << " aka " << official_name->second;
		}
		std::cout << ")";
	}
	std::cout << std::endl;

	return EXIT_SUCCESS;
}

