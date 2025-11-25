#ifndef GAMELOGIC_ROOK_HPP
#define GAMELOGIC_ROOK_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Rook: public Piece
    {
        public:
            // Construct a Rook object with color
            Rook(Enums::Color color);

            /** @brief  Virtual Default Destructor*/
            ~Rook() override = default;

            /*********************************************************
             * @brief Creates a deep copy (clone) of this Rook object.
             * @return A unique_ptr to the newly created Rook clone.
             ********************************************************/
            std::unique_ptr<Piece> ClonePiece() const override;

            /***************************************************************************************************
             * @brief Calculates all potential orthogonal moves the Rook can make from a given position.
             *
             * For each orthogonal position: if on board and (empty or enemy) include.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The starting position of the Rook
             * @param board The current state of the board for validation.
             * @param last_move Optional pointer to the last move made in the game (not typically used by Rook).
             * @return A vector of potential Move objects.
             **************************************************************************************************/
            std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const override;

            /** @brief Static constant vector defining the four orthogonal directions a bishop can move in. */
            static inline const std::vector<Direction> OrthogonalDirs =
            {
                Direction::North,
                Direction::South,
                Direction::East,
                Direction::West
            };
    };
} // namespace GameLogic

#endif