#include "stdafx.h"

boost::program_options::variables_map readOptions(int argc, const char* const argv[])
{
  using namespace boost::program_options;

  options_description descr("Allowed options");
  descr.add_options()
    ("train", value<int>(),
     "Use to create the Markov's chain of the given order out of the set of input files.")
    ("gen", value<int>(), 
     "Use to generate given number of words given a Markov's chain and several starting words. "
     "Starting words are provided through standard input, generated text is written to standard output.")
    ("input,i", value<std::vector<std::string>>(), 
     "Set of input files for chain creation. Used only for training.")
    ("chain,c", value<std::string>(),
     "File with Markov's chain. When training, file will be created; when generating, file will be read.")
    ;

  variables_map options;

  try
  {
    store(command_line_parser(argc, argv).options(descr).run(), options);
    notify(options);
  }
  catch (error e)
  {
    throw std::runtime_error("Cannot parse arguments! Error: " + std::string(e.what()) + ".");
  }

  if (options.empty())
  {
    std::cout << "Text generator based on Markov's chains. Created by Mikhail Matrosov, July 2016 special for Mail.ru." << std::endl;
    std::cout << std::endl;
    std::cout << descr << std::endl;
  }

  return options;
}

int main(int argc, char* argv[])
{
  auto options = readOptions(argc, argv);
  return 0;
}
