#include <string>
#include <vector>
#include <iostream>
#include <optional>

struct ValuesWithColor
{
	explicit ValuesWithColor(
		const std::optional<std::string>& in_key,
		const std::string& in_value = std::string(),
		const std::string& in_color = std::string(),
		const std::string& in_full_string = std::string());

	std::optional<std::string> key;
	std::string value;
	std::string color;
	std::string full_string;
};

std::pair<std::string, size_t> GetNodeString(const std::string& str, const size_t start_pos, const size_t end_pos);

std::optional<ValuesWithColor> GetValuesWithColor(const std::string& str, const size_t start_pos, const size_t end_pos);

std::string ConvertString(const std::string& str);