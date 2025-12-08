#include "game_logic/game.hpp"
#include "game_logic/base/board.hpp"
#include "game_logic/base/player.hpp"
#include "game_logic/base/move.hpp"
#include "game_logic/base/position.hpp"
#include "game_logic/base/game_result.hpp"
#include "game_logic/validator/move_validator.hpp"
#include "game_logic/enums.hpp"

#include <iostream>
#include <sstream>

namespace GameLogic
{
    // Construct a Game object
    Game::Game()
        : board_(),
        player_light_(Enums::Color::Light),
        player_dark_(Enums::Color::Dark),
        current_player_color_(Enums::Color::Light){};

    // Get all legal moves a piece can make at the given position
    std::vector<Move> Game::GetLegalMovesAtPosition(const Position &position)
    {
        const Move *last_move = GetLastMove();
        // Get all legal moves at the given position for the board object
        return MoveValidator::GetLegalMovesAtPosition(position, this->current_player_color_, this->board_, last_move);
    }

    // Get all legal move a player can make
    std::vector<Move> Game::GetAllLegalMovesForPlayer(Enums::Color player_color)
    {
        const Move *last_move = GetLastMove();
        return MoveValidator::GetAllLegalMovesForPlayer(player_color, this->board_, last_move);
    }

    // Returns a immutable map of key: position to value: pieces
    const std::map<Position, const Piece *> Game::GetAllPositonAndPiece() const
    {
        return this->board_.GetAllPositonAndPiece();
    }

    // Check if the game is over
    bool Game::IsGameOver() const
    {
        return !this->result_.IsOngoing();
    }

    // Execute the move that is given by the player
    bool Game::ExecuteMove(const Move& move)
    {
        // Check if the move is legal
        bool is_legal_move = MoveValidator::IsLegalMove(move, this->current_player_color_, this->board_);
        if (is_legal_move == false)
        {
            return false;
        }

        // For debugging purposes
        std::cout << Constants::GET_MOVE_TYPE_REPR(move.GetMoveType()) << std::endl;

        // Check if move captures a piece or is a pawn move
        bool is_capture_move = MoveValidator::IsCaptureMove(move, this->board_);
        bool is_pawn_move = MoveValidator::IsPawnMove(move, this->board_);

        // // Execute the move with move executor
        // MoveExecutor::ExecuteMove(move, this->current_player_color_, this->board_);
        MoveRecord record = std::move(this->board_.MakeMove(move));
        record.SetPrevFiftyMoveCounter(this->fifty_move_counter_);

        // Update 50 move rule counter
        UpdateFiftyMoveCounter(is_pawn_move, is_capture_move);

        // Switch to opponenet's turn and update move_history
        this->undo_history_.push_back(std::move(record));
        this->redo_history_.clear();

        SwitchPlayerTurn();
        if (this->current_player_color_ == Enums::Color::Light)
        {
            this->full_move_counter_++;
        }
        position_history_.push_back(GenerateFenPiecePlacement());

        UpdateGameState();
        std::cout << "FiftyMoveCounter: " << this->fifty_move_counter_ << "\n";
        this->board_.DisplayBoard();

        return true;
    }

    void Game::UnExecuteMove()
    {
        if (!this->undo_history_.empty())
        {
            MoveRecord record = std::move(this->undo_history_.back());
            this->undo_history_.pop_back();

            this->board_.UnmakeMove(record);

            this->fifty_move_counter_ = record.ReadPrevFiftyMoveCounter();

            this->redo_history_.push_back(std::move(record));

            SwitchPlayerTurn();

            if (this->current_player_color_ == Enums::Color::Dark)
            {
                this->full_move_counter_--;
            }
            // Remove the last position from history
            if (!position_history_.empty())
            {
                position_history_.pop_back();
            }

            std::cout << "Undo\n";
            std::cout << "FiftyMoveCounter: " << this->fifty_move_counter_ << "\n";
            this->board_.DisplayBoard();

            UpdateGameState();
        }
    }

    void Game::ReExecuteMove()
    {
        if (!this->redo_history_.empty())
        {
            MoveRecord old_record = std::move(this->redo_history_.back());
            this->redo_history_.pop_back();

            const Move &move_to_redo = old_record.ReadMoveMade();
            MoveRecord new_record = std::move(this->board_.MakeMove(move_to_redo));
            new_record.SetPrevFiftyMoveCounter(this->fifty_move_counter_);

            bool is_pawn_move = MoveValidator::IsPawnMove(move_to_redo, this->board_);
            bool is_capture_move = MoveValidator::IsCaptureMove(move_to_redo, this->board_);
            UpdateFiftyMoveCounter(is_pawn_move, is_capture_move);

            this->undo_history_.push_back(std::move(new_record));

            SwitchPlayerTurn();
            if (this->current_player_color_ == Enums::Color::Light)
            {
                this->full_move_counter_++;
            }
            // Add position to history
            position_history_.push_back(GenerateFenPiecePlacement());

            std::cout << "Redo\n";
            std::cout << "FiftyMoveCounter: " << this->fifty_move_counter_ << "\n";
            this->board_.DisplayBoard();

            UpdateGameState();
        }
    }

    // Return the latest move that was made
    const Move *Game::GetLastMove() const
    {
        if (this->undo_history_.empty())
        {
            return nullptr;
        }
        return &this->undo_history_.back().ReadMoveMade();
    }

    // Return the current player
    const Player& Game::GetCurrentPlayer() const
    {
        return (this->current_player_color_ == Enums::Color::Light) ? this->player_light_ : this->player_dark_;
    }

    // Return the current player's opponent's
    const Player& Game::GetOpponentPlayer() const
    {
        return (this->current_player_color_ == Enums::Color::Light) ? this->player_dark_ : this->player_light_;
    }

    void Game::UpdateGameState()
    {
        // Check fifty move rule
        if (fifty_move_counter_ >= 100)
        {
            result_.SetDraw(Enums::GameState::FiftyMoveRule);
            return;
        }

        // Check threefold repetition
        if (IsThreefoldRepetition())
        {
            result_.SetDraw(Enums::GameState::ThreeFoldRepetition);
            return;
        }

        // Check insufficient material
        if (IsInsufficientMaterial())
        {
            result_.SetDraw(Enums::GameState::InsufficientMaterial);
            return;
        }

        // Check if the current player has any legal moves
        if (GetAllLegalMovesForPlayer(this->current_player_color_).empty())
        {
            // Checkmate if current player has no legal moves and their king is in check
            if (MoveValidator::IsKingInCheck(this->current_player_color_, this->board_))
            {
                result_.SetWin(GetOpponentPlayer().GetColor());
            }
            // Stalemate if current player has no legal moves but their king is not in check
            else
            {
                result_.SetDraw(Enums::GameState::Stalemate);
            }
        }
    }

    void Game::SwitchPlayerTurn()
    {
        this->current_player_color_ = GetOpponentPlayer().GetColor();
    }

    bool Game::CanUndo() const
    {
        return undo_history_.size() >= 2;
    }

    bool Game::CanRedo() const
    {
        return redo_history_.size() >= 2;
    }

    void Game::Reset()
    {
        board_.ResetBoard();
        current_player_color_ = Enums::Color::Light;
        undo_history_.clear();
        redo_history_.clear();
        fifty_move_counter_ = 0;
        position_history_.clear();
        result_.Reset();
    }

    void Game::UpdateFiftyMoveCounter(bool is_pawn_move, bool is_capture_move)
    {
        if (is_pawn_move || is_capture_move)
        {
            this->fifty_move_counter_ = 0;
        }
        else
        {
            this->fifty_move_counter_++;
        }
    }

    void Game::DisplayBoard() const
    {
        this->board_.DisplayBoard();
    }

    std::string Game::GenerateFen() const
    {
        std::stringstream fen_ss;

        fen_ss << GenerateFenPiecePlacement() << ' ';
        fen_ss << GenerateFenActiveColor() << ' ';
        fen_ss << GenerateFenCastlingRights() << ' ';
        fen_ss << GenerateFenEnPassantSquare() << ' ';
        fen_ss << GenerateFenHalfmoveClock() << ' ';
        fen_ss << GenerateFenFullmoveNumber();

        return fen_ss.str();
    }

    std::string Game::GenerateFenPiecePlacement() const
    {
        std::string piece_placement;

        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            int empty_squares = 0;

            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                const Piece *piece = this->board_.GetPieceAt(Position{row, col});

                if (piece == nullptr)
                {
                    empty_squares++;
                }
                else
                {
                    if (empty_squares > 0)
                    {
                        piece_placement += std::to_string(empty_squares);
                        empty_squares = 0;
                    }

                    piece_placement += Constants::GET_PIECE_REPR(piece->GetColor(), piece->GetPieceType());
                }
            }

            if (empty_squares > 0)
            {
                piece_placement += std::to_string(empty_squares);
            }
            if (row < Constants::BOARD_SIZE - 1)
            {
                piece_placement += '/';
            }
        }

        return piece_placement;
    }

    std::string Game::GenerateFenActiveColor() const
    {
        return std::string(1, Constants::GET_COLOR_REPR(this->current_player_color_));
    }

    std::string Game::GenerateFenCastlingRights() const
    {
        std::string castling_rights = "";

        const Piece *white_king = this->board_.GetPieceAt(Position{7, 4});
        if (
            white_king
        &&  white_king->GetPieceType() == Enums::PieceType::King
        &&  white_king->GetColor() == Enums::Color::Light
        &&  white_king->HasMoved() == false)
        {
            const Piece *white_rook_ks = this->board_.GetPieceAt(Position{7, 7});
            if (
                white_rook_ks
            &&  white_rook_ks->GetPieceType() == Enums::PieceType::Rook
            &&  white_rook_ks->GetColor() == Enums::Color::Light
            &&  white_rook_ks->HasMoved() == false)
            {
                castling_rights += 'K';
            }
            const Piece *white_rook_qs = this->board_.GetPieceAt(Position{7, 0});
            if (
                white_rook_qs
            &&  white_rook_qs->GetPieceType() == Enums::PieceType::Rook
            &&  white_rook_qs->GetColor() == Enums::Color::Light
            &&  white_rook_qs->HasMoved() == false)
            {
                castling_rights += 'Q';
            }
        }


        const Piece *black_king = this->board_.GetPieceAt(Position{0, 4});
        if (
            black_king
        &&  black_king->GetPieceType() == Enums::PieceType::King
        &&  black_king->GetColor() == Enums::Color::Dark
        &&  black_king->HasMoved() == false)
        {
            const Piece *black_rook_ks = this->board_.GetPieceAt(Position{0, 7});
            if (
                black_rook_ks
            &&  black_rook_ks->GetPieceType() == Enums::PieceType::Rook
            &&  black_rook_ks->GetColor() == Enums::Color::Dark
            &&  black_rook_ks->HasMoved() == false)
            {
                castling_rights += 'k';
            }
            const Piece *black_rook_qs = this->board_.GetPieceAt(Position{0, 0});
            if (
                black_rook_qs
            &&  black_rook_qs->GetPieceType() == Enums::PieceType::Rook
            &&  black_rook_qs->GetColor() == Enums::Color::Dark
            &&  black_rook_qs->HasMoved() == false)
            {
                castling_rights += 'q';
            }
        }

        return castling_rights.empty() ? "-" : castling_rights;
    }

    std::string Game::GenerateFenEnPassantSquare() const
    {
        const Move *last_move = GetLastMove();

        if (last_move != nullptr && last_move->GetMoveType() == Enums::MoveType::DoublePawn)
        {
            Position two_step_position = last_move->GetToPosition();
            int one_step_row = (current_player_color_ == Enums::Color::Light)
                ? two_step_position.GetRow() + 1
                : two_step_position.GetRow() - 1;
            int one_step_col = two_step_position.GetCol();
            return  Position{one_step_row, one_step_col}.PositionToAlgebraic();
        }
        else
        {
            return "-";
        }
    }

    std::string Game::GenerateFenHalfmoveClock() const
    {
        return std::to_string(this->fifty_move_counter_);
    }

    std::string Game::GenerateFenFullmoveNumber() const
    {
        return std::to_string(this->full_move_counter_);
    }

    const GameResult &Game::GetGameResult() const
    {
        return result_;
    }

    bool Game::IsThreefoldRepetition() const
    {
        if (position_history_.empty())
        {
            return false;
        }

        const std::string &current_position = position_history_.back();
        return std::count(position_history_.begin(), position_history_.end(), current_position) >= 3;
    }

    bool Game::IsInsufficientMaterial() const
    {
        std::vector<Enums::PieceType> light_pieces;
        std::vector<Enums::PieceType> dark_pieces;
        std::vector<Enums::Color> light_bishop_colors;
        std::vector<Enums::Color> dark_bishop_colors;

        // Collect all pieces
        for (int row = 0; row < Constants::BOARD_SIZE; row++)
        {
            for (int col = 0; col < Constants::BOARD_SIZE; col++)
            {
                Position pos(row, col);
                const Piece *piece = board_.GetPieceAt(pos);
                if (piece)
                {
                    Enums::PieceType type = piece->GetPieceType();

                    // Pawns, rooks, queens can always deliver checkmate
                    if (type == Enums::PieceType::Pawn ||
                        type == Enums::PieceType::Rook ||
                        type == Enums::PieceType::Queen)
                    {
                        return false;
                    }

                    if (piece->GetColor() == Enums::Color::Light)
                    {
                        if (type != Enums::PieceType::King)
                        {
                            light_pieces.push_back(type);
                            if (type == Enums::PieceType::Bishop)
                            {
                                light_bishop_colors.push_back(pos.GetSquareColor());
                            }
                        }
                    }
                    else
                    {
                        if (type != Enums::PieceType::King)
                        {
                            dark_pieces.push_back(type);
                            if (type == Enums::PieceType::Bishop)
                            {
                                dark_bishop_colors.push_back(pos.GetSquareColor());
                            }
                        }
                    }
                }
            }
        }

        // King vs King
        if (light_pieces.empty() && dark_pieces.empty())
        {
            return true;
        }

        // King + minor piece vs King
        if ((light_pieces.empty() && dark_pieces.size() == 1
        && (dark_pieces[0] == Enums::PieceType::Bishop || dark_pieces[0] == Enums::PieceType::Knight))
        || (dark_pieces.empty() && light_pieces.size() == 1
        && (light_pieces[0] == Enums::PieceType::Bishop || light_pieces[0] == Enums::PieceType::Knight)))
        {
            return true;
        }

        // King + Bishop vs King + Bishop (same color bishops)
        if (light_pieces.size() == 1 && dark_pieces.size() == 1 &&
            light_pieces[0] == Enums::PieceType::Bishop &&
            dark_pieces[0] == Enums::PieceType::Bishop &&
            !light_bishop_colors.empty() && !dark_bishop_colors.empty() &&
            light_bishop_colors[0] == dark_bishop_colors[0])
        {
            return true;
        }

        return false;
    }

} // namespace GameLogic