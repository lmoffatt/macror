#ifndef MARKOV_REMOTE_H
#define MARKOV_REMOTE_H
#include <string>

namespace Markov_Remote
{

/**
  @brief Class to manage remote connections and executions.

  */

class Markov_Remote
{
private:

    bool connected;
    std::string server_ip;

public:

    /**
      Starts a new connection
      @pre connected = false
      @post connected = true
      */
    bool open(std::string ip, std::string username, std::string password);
    /**
      Close opened connection
      @pre connected = true
      @post connected = false
      */
    bool close();

    /**
      List all files in remote server
      @pre connected = true
      */
    std::string dir();
    /**
      Upload specified file to server
      @pre connected = true
      */
    bool upload_file(std::string file);
    /**
      Download specified file to server
      @pre connected = true
      */
    bool download_file(std::string file, std::string dest_path = "");
    /**
      Launchs a new execution from file
      @pre connected = true
      */
    bool run_script(std::string file);

};

}

#endif // MARKOV_REMOTE_H
