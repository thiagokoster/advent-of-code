#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "../utils/file.h"
#include "../utils/string_helper.h"


enum Type
{
    dir,
    file
};

class TreeItem
{
public:
    std::string name;
    Type type;
    TreeItem* parent;
    virtual std::string str() const = 0;
    virtual unsigned long get_size() = 0;
protected:
    unsigned long size;
};


class Directory : public TreeItem
{
public:
    std::list<TreeItem*> content;
    Directory() = default;
    Directory(const std::string& name)
    {
        this->name = name;
        type = Type::dir;
    };

    std::string str() const override
    {
        std::ostringstream strStream;
        strStream << name << " (dir)";
        return strStream.str(); 
    };

    unsigned long get_size() override
    {
        unsigned long amount = 0;

        for(auto child : this->content)
        {
            amount += child->get_size();
        }

        return amount;
    };
};

class File : public TreeItem
{
public:
    File(const std::string& name, unsigned long size)
    {
        this->name = name;
        type = Type::file;
        this->size = size;
    };
    
    std::string str() const override
    {
        std::ostringstream strStream;
        strStream << name << " (file, size=" << size << ")";
        return strStream.str();
    };

    unsigned long get_size() override
    {
        return size;
    };
};

void executeCommand(const std::vector<std::string>& args, Directory*& currentDir)
{
        if(args[1] == "cd")
        {
            if (args[2] == "..")
            {
                currentDir = dynamic_cast<Directory*>(currentDir->parent);
            }
            else
            {
                auto temp = currentDir;
                auto child = std::find_if(currentDir->content.begin(),
                        currentDir->content.end(),
                        [args](TreeItem* i){ return i->name == args[2];} 
                        );
                currentDir = dynamic_cast<Directory*>(*child);
                currentDir->parent = temp;
            }
        }
}

void createTree(const std::vector<std::string> args, Directory*& currentDir)
{
    if (args[0] == "dir")
    {
        // create directory
        currentDir->content.push_back(new Directory(args[1]));

    }
    else 
    {
        // create file
        currentDir->content.push_back(new File(args[1],std::stoul(args[0])));
    }
}

unsigned long answer(Directory*& root, unsigned long sum = 0)
{
    Directory* pointer = root;
    
    std::vector<Directory*> children;

    for(auto& item : pointer->content)
    {
        if (item->type == Type::dir)
            children.push_back(dynamic_cast<Directory*>(item));
    }
    for(auto child : children) 
    {
        auto childSize = child->get_size();
        if( childSize < 100000)
        {
            sum += childSize;
        }

        sum += answer(child);
    }

    return sum;
}


unsigned long answer2(Directory*& root, unsigned long spaceNeeded, unsigned long smallestFile)
{
    Directory* pointer = root;
    
    std::vector<Directory*> children;

    for(auto& item : pointer->content)
    {
        if (item->type == Type::dir)
            children.push_back(dynamic_cast<Directory*>(item));
    }
    for(auto child : children) 
    {
        auto childSize = child->get_size();
        if( childSize > spaceNeeded && childSize < smallestFile)
        {
            smallestFile = childSize;
        }

        smallestFile = answer2(child, spaceNeeded, smallestFile);
    }

    return smallestFile;
}


int main()
{
    std::cout << "Day 7!" << std::endl;
    Directory* root = new Directory("root");
    Directory* currentDirectory = root;
    currentDirectory->content.push_back(new Directory("/"));
    auto lines = FileHandler::read_file("../day7/input.txt");


    for(auto line : lines)
    {
        auto args = StringHandler::split(line, ' ');
       if(args[0] == "$")
       {
            executeCommand(args, currentDirectory);
       }
       else
       {
            createTree(args, currentDirectory);
       }

    }
    
    auto freeSpace = 70000000 - root->get_size();
    auto spaceToFree = 30000000 - freeSpace;    
    unsigned long temp = 0;
    std::cout << "Part 1: " << answer(root) << std::endl;
    std::cout << "Part 2: " << answer2(root, spaceToFree, ULONG_MAX) << std::endl;

}
