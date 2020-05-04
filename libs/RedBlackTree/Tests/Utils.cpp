#include "Utils.h"
#include <stack>
#include <algorithm>
#include <sstream>

ValuesWithColor::ValuesWithColor(
	const std::optional<std::string>& in_key,
	const std::string& in_value,
	const std::string& in_color,
	const std::string& in_full_string)
	: key(in_key)
	, value(in_value)
	, color(in_color)
	, full_string(in_full_string)
	{
		if (key)
		{
			key->erase(std::remove_if(key->begin(), key->end(), isspace), key->end());
			value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
			color.erase(std::remove_if(color.begin(), color.end(), isspace), color.end());
		}

	}

std::pair<std::string, size_t> GetNodeString(const std::string& str, const size_t start_pos, const size_t end_pos)
{
	if (start_pos >= end_pos || str.size() <= end_pos)
	{
		return {};
	}

	size_t start_left_tree = start_pos;
	for (; start_left_tree < end_pos; ++start_left_tree)
	{
		if (str[start_left_tree] == '(')
		{
			break;
		}
	}
	++start_left_tree;

	if (start_left_tree + 1 >= end_pos)
	{
		return {};
	}

	size_t brace_counter = 1;
	size_t pos = start_left_tree;
	for (; pos <= end_pos; ++pos)
	{
		if (str[pos] == ')')
		{
			--brace_counter;
			if (brace_counter == 0)
			{
				break;
			}
		}
		else if (str[pos] == '(')
		{
			++brace_counter;
		}
	}
	if (brace_counter != 0)
	{
		return {};
	}
	return {str.substr(start_left_tree, pos - start_left_tree), pos + 1};
}

std::pair<std::string, std::string> GetLeftRightChilds(const std::string& str, const size_t start_pos, const size_t end_pos)
{
	if (start_pos >= end_pos || str.size() <= end_pos)
	{
		return {};
	}
	auto [left_tree, index] = GetNodeString(str, start_pos, end_pos);
	if (left_tree.empty())
	{
		return {};
	}
	auto [right_tree, index2] = GetNodeString(str, index, end_pos);
	if (right_tree.empty())
	{
		return {};
	}
	return {left_tree, right_tree};
}

std::optional<ValuesWithColor> GetValuesWithColor(const std::string& str, const size_t start_pos, const size_t end_pos)
{
	if (start_pos >= end_pos || str.size() <= end_pos)
	{
		return std::nullopt;
	}

	size_t start_values = start_pos;
	for (; start_values < end_pos; ++start_values)
	{
		if (str[start_values] == '{')
		{
			break;
		}
	}
	++start_values;

	if (start_values >= end_pos)
	{
		return std::nullopt;
	}
	auto end_values = str.find('}', start_values);
	if (end_values == std::string::npos || end_values > end_pos || end_values <= start_values)
	{
		return std::nullopt;
	}
	--end_values;

	std::vector<std::string> values_with_color;
	{
		std::stringstream values_with_color_stream(str.substr(start_values, end_values - start_values + 1));
		std::string tmp_str;
		while(std::getline(values_with_color_stream, tmp_str, ','))
		{
			values_with_color.push_back(tmp_str);
		}
	}
	if (values_with_color.size() == 1)
	{
		std::string nullptr_value = values_with_color[0];
		nullptr_value.erase(remove_if(nullptr_value.begin(), nullptr_value.end(), isspace), nullptr_value.end());
		if (nullptr_value != "nullptr")
		{
			return std::nullopt;
		}
		return ValuesWithColor(std::nullopt);
	}

	if (values_with_color.size() != 3)
	{
		return std::nullopt;
	}
	return ValuesWithColor(values_with_color[0], values_with_color[1], values_with_color[2], str.substr(start_pos, end_pos - start_pos + 1));
}

std::string ConvertString(const std::string& str)
{
	if (str.size() < 2 || str.front() != '(' || str.back() != ')')
	{
		return {};
	}
	auto head_node = GetValuesWithColor(str, 1, str.size() - 2);
	if (!head_node)
	{
		return {};
	}
	std::stringstream sstream;
	std::stack<std::pair<const ValuesWithColor, std::string>> nodes;
	nodes.emplace(head_node.value(), "");
	while(!nodes.empty())
	{
		const auto [node, indent] = nodes.top();
		nodes.pop();
		sstream << indent;
		if (node.key)
		{
			sstream << "- " << "k{" << node.key.value() << "} v{" << node.value << "}(" << node.color << ")";
			auto [left_child_str, right_child_str] = GetLeftRightChilds(node.full_string, 0, node.full_string.size() - 1);
			if (left_child_str.empty() || right_child_str.empty()) 
			{
				return {};
			}
			auto left_child = GetValuesWithColor(left_child_str, 0, left_child_str.size() - 1);
			if (!left_child) 
			{
				return {};
			}
			auto right_child = GetValuesWithColor(right_child_str, 0, right_child_str.size() - 1);
			if (!right_child) 
			{
				return {};
			}
			nodes.emplace(right_child.value(), indent + "| ");
			nodes.emplace(left_child.value(), indent + "| ");
		}
		else
		{
			sstream << "- nullptr";
		}
		sstream << std::endl;
	}
	return sstream.str();
}