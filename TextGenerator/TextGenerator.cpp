#include "stdafx.h"

#include "Generator.h"
#include "Trainer.h"
#include "Serialization.h"

// There is a bug that we cannot pass boost::filesystem::path directly as 
// value to boost::program_options element, so we need this stupid conversion.
// See https://svn.boost.org/trac/boost/ticket/8535
static auto stringsToPaths(const std::vector<std::string>& strings)
{
  return boost::copy_range<std::vector<fs::path>>(strings);
}

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
    ("input,i", value<std::vector<std::string>>()->multitoken(),
     "Set of space separated input text files for chain creation. Used only for training.")
    ("chain,c", value<std::string>()->required(),
     "File with Markov's chain. When training, file will be created; when generating, file will be read.")
    ;

  variables_map options;
  try
  {
    store(command_line_parser(argc, argv).options(descr).run(), options);

    // Placed before "notify" to handle missing required options
    if (options.empty())
    {
      std::cout << "Text generator based on Markov's chains." << std::endl;
      std::cout << "Created by Mikhail Matrosov, July 2016. Special for Mail.ru." << std::endl;
      std::cout << std::endl;
      std::cout << descr << std::endl;
      std::exit(0);
    }

    notify(options);
  }
  catch (error& e)
  {
    throw std::runtime_error("Cannot parse arguments! Error: " + std::string(e.what()) + ".");
  }

  bool isTraining = options.count("train") > 0;
  bool isGenerating = options.count("gen") > 0;

  if (!isTraining && !isGenerating)
  {
    throw std::runtime_error("Specify the working mode! You should be either trainig, or generating, or both.");
  }
  if (isTraining && !options.count("input"))
  {
    throw std::runtime_error("Specify input files for training!");
  }

  return options;
}

void mainImpl(int argc, char* argv[])
{
  auto options = readOptions(argc, argv);

  fs::path chainFile = options["chain"].as<std::string>();

  if (options.count("train"))
  {
    std::clog << "Creating chain..." << std::endl;
    auto order = options["train"].as<int>();
    if (order < 0) { throw std::runtime_error("Chain order should be a positive value!"); }
    auto&& inputFiles = stringsToPaths(options["input"].as<std::vector<std::string>>());
    auto chain = Trainer(order).createChainFromFiles(inputFiles);

    std::clog << "Saving chain to " << chainFile << "..." << std::endl;
    {
      fs::ofstream output(chainFile);
      boost::archive::text_oarchive archive(output);
      archive << chain.getData();
    }
  }

  if (options.count("gen"))
  {
    boost::optional<Chain> chain; 

    std::clog << "Reading chain from " << chainFile << "..." << std::endl;
    {
      Chain::Data data;
      fs::ifstream input(chainFile);
      boost::archive::text_iarchive archive(input);
      archive >> data;
      chain.emplace(std::move(data));
    }

    std::clog << "Input first " << chain->getData().order << " words: " << std::endl;
    std::clog << "> ";
    auto generator = Generator(*chain, std::cin);

    auto count = options["gen"].as<int>();
    std::clog << "Generating further " << count << " words:" << std::endl;
    for (int i = 0; i < count; ++i)
    {
      std::cout << generator.genNextWord() << ' ';
    }
    std::cout << std::endl;
  }
}

int main(int argc, char* argv[])
{
  try
  {
    mainImpl(argc, argv);
  }
  catch (const std::exception& e)
  {
    std::cerr << std::endl << e.what() << std::endl;
    return 1;
  }
  return 0;
}
