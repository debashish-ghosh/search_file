import std;
import thread_pool;

namespace fs = std::filesystem;

std::mutex mtx; // Mutex for thread-safe access to shared resources
std::vector<fs::path> foundPaths; // Shared vector to store found paths

void printHelp() {
  std::cout << "Usage: search_file <path> <filename>\n"
            << "Searches for the specified file in the given path and its "
               "parent directories.\n\n"
            << "Arguments:\n"
            << "  <path>      The starting directory path to search from.\n"
            << "  <filename>  The name of the file to search for.\n\n"
            << "Example:\n"
            << "  search_file /home/user myfile.txt\n";
}

void searchFileInParent(const fs::path &currentPath,
                        const std::string &filename) {
  // Check if the file exists in the current directory
  fs::path filePath = currentPath / filename;
  if (fs::exists(filePath)) {
    std::lock_guard<std::mutex> lock(
        mtx); // Lock the mutex for thread-safe access
    foundPaths.push_back(filePath);
  }
}

void searchFileInParents(const fs::path &startPath, const std::string &filename,
                         ThreadPool &pool) {
  fs::path currentPath = startPath;

  // Traverse up the directory tree
  while (currentPath.has_parent_path()) {
    // Enqueue a task for each directory check
    pool.enqueue(
        [currentPath, filename] { searchFileInParent(currentPath, filename); });

    // Break out of loop if we are already in the root path
    if (currentPath == currentPath.root_path()) {
      break;
    }

    // Move to the parent directory
    currentPath = currentPath.parent_path();
  }
}

bool handleCommandLineArguments(int argc, char *argv[], fs::path &path,
                                std::string &filename) {
  // Check for help request
  if (argc == 2 && std::string(argv[1]) == "--help") {
    printHelp();
    return false; // Indicate that help was requested
  }

  // Check for correct number of arguments
  if (argc != 3) {
    std::cerr << "Error: Invalid number of arguments.\n";
    printHelp();
    return false; // Indicate that there was an error
  }

  path = fs::path(argv[1]);
  filename = argv[2];

  // Check if the specified path exists
  if (!fs::exists(path)) {
    std::cerr << "Error: The specified path does not exist: "
              << path.generic_string() << std::endl;
    return false; // Indicate that there was an error
  }

  // Check if the specified path is a directory
  if (!fs::is_directory(path)) {
    std::cerr << "Error: The specified path is not a directory: "
              << path.generic_string() << std::endl;
    return false; // Indicate that there was an error
  }

  return true; // Indicate that arguments were handled successfully
}

int main(int argc, char *argv[]) {
  fs::path path;
  std::string filename;

  // Call the argument handling function
  if (!handleCommandLineArguments(argc, argv, path, filename)) {
    return 1; // Exit if there was an error or help was requested
  }

  {
    // Create a thread pool with a number of threads based on the system's
    // hardware concurrency
    ThreadPool pool(std::thread::hardware_concurrency());

    // Perform the file search
    searchFileInParents(path, filename, pool);
  }

  // Output the results
  if (!foundPaths.empty()) {
    std::ranges::sort(foundPaths);
    for (const auto &p : foundPaths) {
      std::cout << p.generic_string() << std::endl;
    }
  }

  return 0;
}
