#include <iostream>
#include <cstdlib>
#include <exception>
#include <set>
#include <RedBlackTree.h>

struct test_struct
{
	std::vector<int> a;
	test_struct()
	{
		a.resize(100000000);
		std::cout << "create struct" << std::endl;
	}
	~test_struct()
	{
		std::cout << "clear struct" << std::endl;
	}
	std::unique_ptr<test_struct> next_ptr;
};


int main(int /*arg*/, char** /*argv*/)
{
	 try
	 {
		/*const size_t size_ = 10;
		RedBlackTree::RedBlackTree<size_t, size_t> tree_;
		for (size_t i = 0; i < size_; ++i)
		{
			tree_.AddElement(i, i);
		}
		tree_.Print();
		tree_.DelElement(4);
		tree_.DelElement(5);
		tree_.DelElement(1);
		tree_.DelElement(8);
		for (const auto& pairs : tree_)
		{
			std::cout<< pairs.first << std::endl;
		}*/


		//const size_t size_ = 10;
		RedBlackTree::RedBlackTree<size_t, size_t> tree_;
		tree_.AddElement(130, 130);

		tree_.AddElement(120, 120);
		tree_.AddElement(140, 140);
		
		tree_.AddElement(110, 110);
		tree_.AddElement(125, 125);
		tree_.AddElement(135, 135);
		tree_.AddElement(150, 150);
		
		tree_.AddElement(101, 101);
		tree_.AddElement(115, 115);
		tree_.AddElement(122, 122);
		tree_.AddElement(128, 128);
		tree_.AddElement(133, 133);
		tree_.AddElement(137, 137);
		tree_.AddElement(145, 145);
		tree_.AddElement(160, 160);

		tree_.AddElement(103, 103);
		tree_.AddElement(134, 134);
		tree_.Print();

		//tree_.DelElement(130);

		const std::string mystr = 
R"(- k{130} v{130}(B)
| - k{120} v{120}(B)
| | - k{110} v{110}(R)
| | | - k{101} v{101}(B)
| | | | - nullptr
| | | | - k{103} v{103}(R)
| | | | | - nullptr
| | | | | - nullptr
| | | - k{115} v{115}(B)
| | | | - nullptr
| | | | - nullptr
| | - k{125} v{125}(B)
| | | - k{122} v{122}(R)
| | | | - nullptr
| | | | - nullptr
| | | - k{128} v{128}(R)
| | | | - nullptr
| | | | - nullptr
| - k{140} v{140}(B)
| | - k{135} v{135}(R)
| | | - k{133} v{133}(B)
| | | | - nullptr
| | | | - k{134} v{134}(R)
| | | | | - nullptr
| | | | | - nullptr
| | | - k{137} v{137}(B)
| | | | - nullptr
| | | | - nullptr
| | - k{150} v{150}(B)
| | | - k{145} v{145}(R)
| | | | - nullptr
| | | | - nullptr
| | | - k{160} v{160}(R)
| | | | - nullptr
| | | | - nullptr
)";
	//	std::cout << mystr1;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << (mystr == tree_.Print());
		std::cout << std::endl;
		std::cout << tree_.Print();

		/*RedBlackTree::RedBlackTree<size_t, size_t> tree_;
		tree_.AddElement(130, 130);

		tree_.AddElement(120, 120);
		tree_.AddElement(140, 140);

		tree_.AddElement(150, 150);
		tree_.Print();

		tree_.DelElement(130);
		tree_.Print();*/
	/*	RedBlackTree::RedBlackTree<size_t, size_t> tree_;
		tree_.AddElement(130, 130);

		tree_.AddElement(120, 120);
		tree_.AddElement(140, 140);

		tree_.AddElement(135, 135);
		tree_.AddElement(150, 150);
		tree_.Print();

		tree_.DelElement(130);
		std::cout<<tree_.Print();*/
/*
		const size_t size = 10;
		std::set<size_t> elems;
		RedBlackTree::RedBlackTree<size_t, size_t> tree;
		std::srand(33643);
		for (int i = size; i >= 0; --i)
		{
				size_t random_variable = std::rand();
				elems.insert(random_variable);
				tree.AddElement(random_variable, random_variable);
				//tree.Print();
		}
		// auto it = tree.begin();
		std::cout << elems.size() << std::endl;
		for (auto& [key, value] : tree)
		{
				//value = 78;
				std::cout << key << " " << value << std::endl;
		}
		//tree.Print();

		// while (it != tree.cend())
		// {
		//	  std::cout << *it << std::endl;
		//	  ++it;
		// }
		*/
		
		std::cout << "Hellow world denis" << std::endl;

		/*{
			auto str = std::make_unique<test_struct>();
			auto pointer = str.get();
			//pointer->next_ptr = nullptr;
			pointer->next_ptr = std::move(str);
		}*/
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