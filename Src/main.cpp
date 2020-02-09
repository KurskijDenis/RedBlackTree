#include <iostream>
#include <cstdlib>
#include <exception>
#include <set>
#include "../Headers/RedBlackTree.h"

int main(int /*arg*/, char** /*argv*/)
{
	 try
	 {
		const size_t size = 1000;
		std::set<size_t> elems;
		RedBlackTree::RedBlackTree<size_t, size_t> tree;
		std::srand(33643);
		for (int i = size; i >= 0; --i)
		{
				size_t random_variable = std::rand();
				elems.insert(random_variable);
				tree.AddElement(random_variable, random_variable);
				tree.Print();
		}
		// auto it = tree.begin();
		for (auto& [key, value] : tree)
		{
				value = 78;
				std::cout << key << " " << value << std::endl;
		}

		// while (it != tree.cend())
		// {
		//	  std::cout << *it << std::endl;
		//	  ++it;
		// }
		
		if (!tree.CheckTree())
		{
				std::cout << "Error" << std::endl;
		}

		/* for (const auto& elem : elems)
		{
				tree.DelElement(elem);
				if (!tree.CheckTree())
				{
					std::cout << "Error" << std::endl;
					break;
				}
		}*/
		
		std::cout << "Hellow world denis" << std::endl;
	 }
	 catch (const std::exception& exc)
	 {
		std::cerr << exc.what() << std::endl;
		return 1;
	 }
	 catch (...)
	 {
		std::cerr << "Unknown error" << std::endl;
		return 1;
	 }

	return 0;
}