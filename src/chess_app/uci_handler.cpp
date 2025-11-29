#include "chess_app/uci_handler.hpp"
#include <boost/process.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <string>
#include <stdexcept>


namespace ChessApp
{
    UCIHandler::UCIHandler(const std::string &engine_path)
    {
        CreateAndConnectUCIProcess(engine_path);
    }

    UCIHandler::~UCIHandler()
    {
        SendCommand("quit");
        this->pipe_is_.close();
        this->pipe_os_.close();
        this->process_child_.wait();
    }

    std::string UCIHandler::GetBestMove(const std::string fen, int depth, int search_time_ms)
    {
        std::string fen_string_cmd = "position fen " + fen;
        std::string depth_cmd = "go depth " + std::to_string(depth);

        SendCommand(fen_string_cmd);
        SendCommand(depth_cmd);

        // Ex: "bestmove e2e4 ponder c7c5"
        std::string move_line = WaitForResponse("bestmove");

        std::vector<std::string> parts;

        boost::split(parts, move_line, boost::is_any_of(" "));

        if (parts.size() <= 1)
        {
            throw std::runtime_error("Failed to parse 'bestmove' response.");
        }

        return parts.at(1);
    }

    void UCIHandler::CreateAndConnectUCIProcess(const std::string &engine_path)
    {
        try
        {
            this->process_child_ = bp::child(
                engine_path,
                bp::std_in < this->pipe_os_, // (child's input)  stdin FROM (Parent) opstream
                bp::std_out > this->pipe_is_ // (child's output) stdout TO  (Parent) ipstream
            );

            if (!UseUCI() || !IsReady())
            {
                throw std::runtime_error("UCI command failed during initialization: Can't use 'usi' or 'isready'\n");
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception caught while connecting with Stockfish Engine: " << e.what() << std::endl;
        }
    }

    void UCIHandler::SendCommand(const std::string &command)
    {
        this->pipe_os_ << command << std::endl;
    }

    std::string UCIHandler::WaitForResponse(const std::string& expected_response_substring)
    {
        std::string line;

        while (std::getline(this->pipe_is_, line))
        {
            std::cout << line << "\n";

            if (line.find(expected_response_substring) != std::string::npos)
            {
                return line;
            }
        }

        std::cerr << "Expected Response Not Found: " << expected_response_substring << std::endl;
        throw std::runtime_error("Fatal Error: Expected Reposnse Not Found");
    }


    bool UCIHandler::UseUCI()
    {
        SendCommand("uci");
        return WaitForResponse("uciok") == std::string{"uciok"};
    }

    bool UCIHandler::IsReady()
    {
        SendCommand("isready");
        return WaitForResponse("readyok") == std::string{"readyok"};
    }

    void UCIHandler::Quit()
    {
        SendCommand("quit");
    }
} // namespace ChessApp