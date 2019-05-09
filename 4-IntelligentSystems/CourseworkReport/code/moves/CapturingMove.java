package moves;

import game.Draught;

import java.util.ArrayList;

public class CapturingMove extends Move {

	Draught capturedDraught;
	ArrayList<Move> possibleFollowingMoves;

	public Draught getCapturedDraught() {
		return capturedDraught;
	}

	public void setCapturedDraught(Draught capturedDraught) {
		this.capturedDraught = capturedDraught;
	}

	public ArrayList<Move> getPossibleFollowingMoves() {
		return possibleFollowingMoves;
	}

	public void setPossibleFollowingMoves(ArrayList<Move> possibleFollowingMoves) {
		this.possibleFollowingMoves = possibleFollowingMoves;
	}

	public CapturingMove(Draught draught, int newXPosition, int newYPosition, Draught capturedDraught) {
		super(draught, newXPosition, newYPosition);
		this.capturedDraught = capturedDraught;
	}


}
