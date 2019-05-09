package moves;

import game.Draught;

public class Move {
	Draught draught;
	int newXPosition;
	int newYPosition;

	public Draught getDraught() {
		return draught;
	}

	public void setDraught(Draught draught) {
		this.draught = draught;
	}

	public int getNewXPosition() {
		return newXPosition;
	}

	public void setNewXPosition(int newXPosition) {
		this.newXPosition = newXPosition;
	}

	public int getNewYPosition() {
		return newYPosition;
	}

	public void setNewYPosition(int newYPosition) {
		this.newYPosition = newYPosition;
	}



	public Move(Draught draught, int newXPosition, int newYPosition){
		this.draught = draught;
		this.newXPosition = newXPosition;
		this.newYPosition = newYPosition;
	}

	public boolean moveInBounds() {
		return 0 <= newXPosition && newXPosition < 8 && 0 <= newYPosition && newYPosition < 8;
	}

	public int xPositionMovement(){return newXPosition - draught.getxPosition();}
	public int yPositionMovement(){return newYPosition - draught.getyPosition();}
}
