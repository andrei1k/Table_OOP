#include "MyProgram.h"

void MyProgram::open(const std::string& path)
{

    std::ifstream in(path);
    if(!in.is_open()){
        std::ofstream out(path);
        out.close();
    }
    in.close();

    bool isLoaded;
    
    try{  
        isLoaded = table.load(path);
    }
    catch(const std::exception& ex){
        std::cout << ex.what();
        return;
    }

    if(!isLoaded){
        
        // По условие прекратява изпълнението, не пише на кое, затова предполагам на цялата програма
        exit();
        return;
    }
    isOpen = true;
    std::cout << "Successfully opened " << path << '\n';
}

void MyProgram::close()
{
    isOpen = false;
    std::cout << "Successfully closed " << table.getPath() << '\n';
}

void MyProgram::exit()
{
    toExit = true;
    std::cout << "Exiting the program!" << '\n';
}

void MyProgram::save(const std::string *path) const
{
    table.save(path);

    std::cout << "Successfully saved "; 

    if(path != nullptr)
        std::cout << *path;

    std::cout << '\n';
}

bool MyProgram::getIsOpen() const
{
    if(!isOpen)
        std::cout << "Table is closed.\n";

    return isOpen;       
}

void MyProgram::running()
{
    bool invalid = false;

    while(!toExit){

        std::cout << "Enter command: ";
        char getCommand[128];
        std::cin.getline(getCommand, 128);
        std::string command = getCommand;
        std::vector<std::string> parameters;
        StringWork::separateCommand(command, parameters);

        // for(int i = 0; i < parameters.size(); i++)
        //     std::cout << '\n' << parameters[i] << '\n';

        if(parameters[0] == "open" && parameters.size() == 2){
            open(parameters[1]);
        }
        else if(parameters[0] == "save" && parameters.size() == 1){
            if(!getIsOpen()){
                continue;
            }
            save(nullptr);
        }
        else if(parameters[0] == "saveas" && parameters.size() == 2){
            if(!getIsOpen()){
                continue;
            }
            save(&parameters[1]);
        }
        else if(parameters[0] == "exit" && parameters.size() == 1){
            exit();   
        }
        else if(parameters[0] == "close" && parameters.size() == 1){
           close();      
        }
        else if(parameters[0] == "print" && parameters.size() == 1){
            if(!getIsOpen()){
                continue;
            }
            table.print();
        }
        else if(parameters[0] == "edit" && parameters.size() == 4){
            if(!getIsOpen()){
                continue;
            }
            try{
                table.edit(stoi(parameters[1]), stoi(parameters[2]), StringWork::removeWhiteSpaces(parameters[3]));
            }
            catch(const std::exception& ex){
                std::cout << ex.what();
            }
        }
        else{
            std::cout << "Invalid command! Enter again!\n";
        }

    }
}