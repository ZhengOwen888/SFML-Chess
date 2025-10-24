#ifndef GAMELOGIC_PIECE_HPP
#define GAMELOGIC_PIECE_HPP

#include "types.hpp"

namespace GameLogic
{
    class Piece
    {
        public:
            // Constructor and destructor
            Piece(Color color, PieceType piece_type);
            virtual ~Piece();

            // Pure virtual member function to get all Pseudo-Legal Moves
            // "Pseudo-legal" means the moves that the pieces are allowed to make disregarding king safety
            // All derived classes ex. Pawn, King, ... must implement and override this function
            virtual std::vector<Position> getPseudoLegalMoves(
                Position cur_position) const = 0;

            // Check if one move is "Pseudo-Legal"
            virtual bool isPseudoLegalMove(
                Position cur_position, Position target_location) const = 0;

            // Getters
            Color getColor() const;
            PieceType getPieceType() const;
            bool hasMoved() const;
            bool hasPromoted() const;

            // Setters
            void setHasMoved(bool moved);
            void setHasPromoted(bool promoted);

        private:
            Color color_;
            PieceType piece_type_;
            bool has_moved_ = false;
            bool has_promoted_ = false;
    };
}

#endif