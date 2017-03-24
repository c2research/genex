#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <boost/tokenizer.hpp>
#include <readline/readline.h>
#include <readline/history.h>

#include "Command.hpp"
#include "GenexAPI.hpp"
#include "Exception.hpp"

#include "config.hpp"

static genex::GenexAPI genexAPI;

/**************************************************************************
 * HOW TO CREATE NEW COMMAND
 *
 * Step 1: Define a new command using the MAKE_COMMAND macro
 *
 * MAKE_COMMAND(<command_name>, <code>, <help_summary>, <help>)
 *  <command_name> - name of the command
 *  <code>         - the code being executed when this command is called.
 *                   Arguments are put in a vector of string call 'args'.
 *  <help_summary> - a short text line describing the command. This is
 *                   showed next to the command name when 'help' is called
 *  <help>         - a long text describe the command in details. This is
 *                   showed when 'help <command_name>' is called
 *
 * This macro creates a class Cmd<command_name> and its object in a variable
 * called cmd<command_name>. This variable is used in step 2.
 **************************************************************************/

MAKE_COMMAND(LoadData,
  {
    if (args.size() > 5) {
      std::cout << "Error! Too many arguments" << std::endl;
      return false;
    }

    std::string filePath = args[1];
    int maxNumRow = args.size() > 2 ? std::stoi(args[2]) : 0;
    int startCol  = args.size() > 3 ? std::stoi(args[3]) : 0;
    std::string separators = args.size() > 4 ? args[4] : " ";

    int id = -1;
    try {
      id = genexAPI.loadDataset(filePath, maxNumRow, startCol, separators);
    } catch (genex::GenexException& e)
    {
      std::cout << "Error! " << e.what() << std::endl;
      return false;
    }
    std::cout << "Dataset loaded. ID: " << id << std::endl;
    return true;
  },

  "Load a dataset to the memory",

  "Dataset are text files with table-like format, such as comma-separated  \n"
  "values files.                                                           \n"
  "                                                                        \n"
  "Usage: load <filePath> [<maxNumRow> <startCol> <separators>]            \n"
  "  filePath  - Path to a text file containing the dataset                \n"
  "  maxNumRow - Maximum number of rows will be read from the file. If this\n"
  "              number is non-positive or the number of actual line is    \n"
  "              smaller than this number, all lines are read. (default: 0)\n"
  "  startCol  - Omit all columns before this column. (default: 0)         \n"
  "  seprators - A list of characters used to separate values in the file  \n"
  "              (default: <space>)                                        \n"
  )

/**************************************************************************
 * Step 2: Add the Command object into the commands map
 *
 * The key of a command is a string which is also the string that is used
 * to match with user input.
 **************************************************************************/

std::map<std::string, Command*> commands = {
  {"load", &cmdLoadData},
};

/**************************************************************************/
/**************************************************************************/

#define COUT_HELP_ALIGNMENT 15

bool processLine(const std::string& line)
{
  boost::char_separator<char> sep(" ");
  typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
  tokenizer tokens(line, sep);
  std::vector<std::string> args (tokens.begin(), tokens.end());

  if (args.size() == 0)
  {
    return false;
  }

  if (args[0] == "quit" || args[0] == "exit")
  {
    return true;
  }
  else if (args[0] == "help")
  {
    if (args.size() > 1)
    {
      if (commands.find(args[1]) == commands.end())
      {
        std::cout << "Error! Cannot find help for command: " << args[1] << std::endl;
      }
      else {
        Command* cmd = commands[args[1]];
        std::cout << cmd->getSummary() << std::endl << cmd->getHelp() << std::endl;
      }
    }
    else {
      std::cout << "Use help <command> to see help for a command" << std::endl << std::endl;
      for (const auto& cmd : commands)
      {
        std::cout << std::setw(COUT_HELP_ALIGNMENT);
        std::cout << cmd.first << cmd.second->getSummary() << std::endl;
      }
      std::cout << std::setw(COUT_HELP_ALIGNMENT);
      std::cout << "help" << "Retrieve a list of commands" << std::endl;

      std::cout << std::setw(COUT_HELP_ALIGNMENT);
      std::cout << "exit|quit " << "Terminate the program" << std::endl;
    }
  }
  else
  {
    if (commands.find(args[0]) == commands.end())
    {
      std::cout << "Error! Cannot find command: " << args[0] << std::endl;
    }
    else {
      commands[args[0]]->doCommand(args);
    }
  }

  return false;
}

int main (int argc, char *argv[])
{
  // Align left
  std::cout << std::left;
  while (true)
  {
    char* raw_line = readline(">> ");
    add_history(raw_line);
    std::string line = std::string(raw_line);
    delete raw_line;

    bool quit = processLine(line);
    std::cout << std::endl;

    if (quit) { break; }
  }
  return 0;
}
