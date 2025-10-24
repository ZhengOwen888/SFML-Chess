#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "enums.hpp"
#include <memory>

namespace GameLogic
{
    class Piece
    {
        public:
            // Construct a piece with their color and or has_moved, has_promoted
            Piece(Enums::Color color);
            Piece(Enums::Color color, bool has_moved, bool has_promoted);
            virtual ~Piece() = default;

            // Clone creates a new piece object with the same property and values
            virtual std::unique_ptr<Piece> clonePiece() const = 0;

            // Setters
            void setHasMoved();
            void setHasPromoted();

            // Getters
            virtual Enums::PieceType getPieceType() const = 0;
            Enums::Color getColor() const;
            bool hasMoved() const;
            bool hasPromoted() const;

        private:
            Enums::Color color_;
            bool has_moved;    // false initially
            bool has_promoted; // false initially
    };
}

#endif