#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     Board player_board;
     this->this_side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    using namespace std;
    Side other;
    if (this_side == WHITE){
        other = BLACK;
    }
    else if (this_side == BLACK){
        other = WHITE;
    }
    //heuristic only code
    /*int the_move[2];
    int cost = -99 * 64;
    player_board.doMove(opponentsMove, other);
    if (not player_board.hasMoves(this_side)){
        return NULL;
    }
    else {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                Board * new_board = player_board.copy();
                Move * our_move = new Move(i, j);
                if (new_board->checkMove(our_move, this_side)){
                    new_board->doMove(our_move, this_side);
                    if (new_board->value(this_side) > cost){
                        cost = new_board->value(this_side);
                        the_move[0] = i;
                        the_move[1] = j;
                    }
                }
                delete our_move;
                delete new_board;
            }
        }
    }
    Move * new_move = new Move(the_move[0], the_move[1]);
    player_board.doMove(new_move, this_side);
    return new_move;*/

    //heuristic + depth 2 min - max code
    player_board.doMove(opponentsMove, other);
    int next_move[2];
    int max_of_min = -99 * 64;
    if (not player_board.hasMoves(this_side)){
        return NULL;
    }
    else {
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                Board * new_board = player_board.copy();
                Move * our_move = new Move(i, j);
                if (new_board->checkMove(our_move, this_side)){
                    new_board->doMove(our_move, this_side);
                    int min_value = 99 * 64;
                    if (not new_board->hasMoves(other)){
                        new_board->doMove(NULL, other);
                        min_value = new_board->value(this_side);
                    }
                    else {
                        for (int a = 0; a < 8; a++){
                            for (int b = 0; b < 8; b++){
                                Board * ply_2_board = new_board->copy();
                                Move * their_move = new Move(a, b);
                                if (ply_2_board->checkMove(their_move, other)){
                                    ply_2_board->doMove(their_move, other);
                                    if (ply_2_board->value(this_side) < min_value){
                                        min_value = ply_2_board->value(this_side);
                                    }
                                }
                                delete their_move;
                                delete ply_2_board;
                            }
                        }       
                    }
                    if (min_value > max_of_min){
                        max_of_min = min_value;
                        next_move[0] = i;
                        next_move[1] = j;
                    }
                }
                delete our_move;
                delete new_board;
            }
        }
    }
    Move * new_move = new Move(next_move[0], next_move[1]);
    player_board.doMove(new_move, this_side);
    return new_move;
}
