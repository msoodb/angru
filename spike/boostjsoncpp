#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

int main()
{
    // Short alias for this namespace
    namespace pt = boost::property_tree;

    // Create a root
    pt::ptree iroot;

    // Load the json file in this ptree
    pt::read_json("example.json", iroot);


    ////////////////////
    /// READING      ///
    ////////////////////

    std::cout << "Reading example.json :" << std::endl;

    //Read values
    int height = iroot.get<int>("height");
    std::string msg = iroot.get<std::string>("some.complex.path");
    std::cout << "height : " << height << std::endl
              << "some.complex.path : " << msg << std::endl;

    std::vector< std::pair<std::string, std::string> > animals;
    for (pt::ptree::value_type &animal : iroot.get_child("animals"))
    {
        std::string name = animal.first;
        std::string color = animal.second.data();
        animals.push_back(std::make_pair(name, color));
    }

    std::cout << "Animals :" << std::endl;
    for (auto animal : animals)
        std::cout << "\t" << animal.first
                  << " is " << animal.second
                  << std::endl;

    std::vector<std::string> fruits;
    for (pt::ptree::value_type &fruit : iroot.get_child("fruits"))
    {
        // fruit.first contain the string ""
        fruits.push_back(fruit.second.data());
    }

    std::cout << "Fruits :";
    for (auto fruit : fruits)
        std::cout << " " << fruit;
    std::cout << std::endl;

    int matrix[3][3];
    int x = 0;
    for (pt::ptree::value_type &row : iroot.get_child("matrix"))
    {
        int y = 0;
        for (pt::ptree::value_type &cell : row.second)
        {
            matrix[x][y] = cell.second.get_value<int>();
            y++;
        }
        x++;
    }

    std::cout << "Matrix :" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            std::cout << " " << matrix[i][j];
        std::cout << std::endl;
    }


    ////////////////////
    /// WRITING      ///
    ////////////////////

    pt::ptree oroot;

    // Some values
    oroot.put("height", height);
    oroot.put("some.complex.path", "bonjour");

    // Add a list of animals

    // Create a node
    pt::ptree animals_node;
    // Add animals as childs
    for (auto &animal : animals)
        animals_node.put(animal.first, animal.second);
    // Add the new node to the root
    oroot.add_child("animals", animals_node);

    // Add two objects with the same name
    pt::ptree fish1;
    fish1.put_value("blue");
    pt::ptree fish2;
    fish2.put_value("yellow");
    oroot.push_back(std::make_pair("fish", fish1));
    oroot.push_back(std::make_pair("fish", fish2));

    // Add a list
    pt::ptree fruits_node;
    for (auto &fruit : fruits)
    {
        // Create an unnamed node containing the value
        pt::ptree fruit_node;
        fruit_node.put("", fruit);

        // Add this node to the list.
        fruits_node.push_back(std::make_pair("", fruit_node));
    }
    oroot.add_child("fruits", fruits_node);

    // Add a matrix
    pt::ptree matrix_node;
    for (int i = 0; i < 3; i++)
    {
        pt::ptree row;
        for (int j = 0; j < 3; j++)
        {
            // Create an unnamed value
            pt::ptree cell;
            cell.put_value(matrix[i][j]);
            // Add the value to our row
            row.push_back(std::make_pair("", cell));
        }
        // Add the row to our matrix
        matrix_node.push_back(std::make_pair("", row));
    }
    // Add the node to the root
    oroot.add_child("matrix", matrix_node);

    pt::write_json(std::cout, oroot);

    return 0;
}
