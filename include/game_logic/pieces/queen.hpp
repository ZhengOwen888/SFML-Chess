#ifndef GAMELOGIC_QUEEN_HPP
#define GAMELOGIC_QUEEN_HPP

#include "game_logic/base/direction.hpp"
#include "game_logic/base/piece.hpp"

#include "game_logic/enums.hpp"

#include <memory>
#include <vector>

namespace GameLogic
{
    class Queen: public Piece
    {
        public:
            /**********************************************************
             * @brief Constructs a Queen Object with a specific color.
             * @param color The color (Light or Dark) of the Queen.
             *********************************************************/
            Queen(Enums::Color color);

            /** @brief  Virtual Default Destructor*/
            ~Queen() override = default;

            /**********************************************************
             * @brief Creates a deep copy (clone) of this Queen object.
             * @return A unique_ptr to the newly created Queen clone.
             *********************************************************/
            std::unique_ptr<Piece> ClonePiece() const override;

            /****************************************************************************************************
             * @brief Calculates all potential cardinal moves the Queen can make from a given position.
             *
             * For each position: if on board and (empty or enemy) include.
             *
             * !!! IMPORTANT: This method does not check for king safety
             *
             * @param from_position The starting position of the Queen
             * @param board The current state of the board for validation.
             * @param last_move Optional pointer to the last move made in the game (not typically used by Queen).
             * @return A vector of potential Move objects.
             ***************************************************************************************************/
            std::vector<Move> GetPotentialMoves(
                const Position& from_position, const Board &board, const Move* last_move = nullptr) const override;

            /** @brief Static constant vector defining the eight cardinal directions a bishop can move in. */
            static inline const std::vector<Direction> AllDirs =
            {
                Direction::North,
                Direction::South,
                Direction::East,
                Direction::West,
                Direction::NorthEast,
                Direction::NorthWest,
                Direction::SouthEast,
                Direction::SouthWest
            };

    };
} // namespace GameLogic

#endif