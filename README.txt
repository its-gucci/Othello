
I did this project on my own.

The improvements to the AI were in roughly three stages. The first stage was just to get the AI
to make legal moves. The second stage was to make decisions to maximize a heuristic, which was
determined from online research. Essentially, it highly values the corner squares, since once 
these squares are claimed, they cannot change hands and also allow the player to take the rest
of the map. We value squares next to these corner squares lowly, since if we take those squares
the opponenet has a high chance to take the corners. Squares on the side of the board are also
valued relatively highly by this heuristic, since they cannot be retaken and may provide access
to the highly valuable corner squares. The last stage was to implement a depth 2 minimax 
algorithm. This is because the "greedy" move is not necessarily the best move, so the minimax
algorithm seeks to maximize our gain taking into account the opponent's next move, where the
gain is according to our heuristic.