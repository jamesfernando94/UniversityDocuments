package game;

import moves.Move;
import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.util.ArrayList;

public class Draught implements Cloneable{
	int xPosition;
	int yPosition;
	boolean crowned;
	Colour colour;


	public int getxPosition() {
		return xPosition;
	}

	public void setxPosition(int xPosition) {
		this.xPosition = xPosition;
	}

	public int getyPosition() {
		return yPosition;
	}

	public void setyPosition(int yPosition) {
		this.yPosition = yPosition;
	}

	public boolean isCrowned() {
		return crowned;
	}

	public Colour getColour() {
		return colour;
	}


	public Draught(Draught draught) {
		xPosition = draught.xPosition;
		yPosition = draught.yPosition;
		crowned = draught.crowned;
		colour = draught.colour;
	}

	public Draught(int xPosition, int yPosition, Colour colour)
	{
		this.xPosition = xPosition;
		this.yPosition = yPosition;
		crowned = false;
		this.colour = colour;
	}

	public ArrayList<Move> listPossibleMoves() {

		ArrayList<Move> possibleMoves = new ArrayList<>();
		int yDirection;

		if (colour == Colour.LIGHT) {
			yDirection = -1;
		} else if (colour == Colour.DARK) {
			yDirection = 1;
		} else throw new NotImplementedException();

		if (crowned) {
			possibleMoves.add(new Move(this, xPosition - 1, yPosition - yDirection));
			possibleMoves.add(new Move(this, xPosition + 1, yPosition - yDirection));
		}

		possibleMoves.add(new Move(this, xPosition - 1, yPosition + yDirection));
		possibleMoves.add(new Move(this, xPosition + 1, yPosition + yDirection));

		possibleMoves.removeIf(move -> !move.moveInBounds());

		return possibleMoves;
	}

	public void crownDraughtIfPossible() {
		if (!crowned) {
			crowned = isDraughtOnKingsRow();
		}
	}


	public boolean isDraughtOnKingsRow() {
		return colour.equals(Colour.LIGHT) ? yPosition == 0 : yPosition == 7;
	}

	@Override
	protected Draught clone(){
		Draught clone = null;
		try {
			clone = (Draught) super.clone();
			clone.colour = getColour();
			clone.crowned = crowned;
			clone.xPosition = xPosition;
			clone.yPosition = yPosition;

		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}
}
