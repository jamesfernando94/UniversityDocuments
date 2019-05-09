package game;

import moves.CapturingMove;
import moves.Move;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;
import java.util.stream.Collectors;

public class Game implements Cloneable {
	private ArrayList<Draught> draughtArrayList;
	private Colour currentTurn;
	private Draught selectedDraught;
	private boolean isCurrentMultiStepMove;
	private Colour gameWinner;
	private boolean isGameComplete;

	public ArrayList<Draught> getDraughtArrayList() {
		return draughtArrayList;
	}

	public Colour getCurrentTurn() {
		return currentTurn;
	}

	public Draught getSelectedDraught() {
		return selectedDraught;
	}

	public void setSelectedDraught(Draught selectedDraught) {
		this.selectedDraught = selectedDraught;
	}

	public Colour getGameWinner() {
		return gameWinner;
	}

	public boolean isGameComplete() {
		return isGameComplete;
	}

	public Game() {
	}

	public Game(Game game) {
		draughtArrayList = new ArrayList<>();
		for (Draught draught : game.draughtArrayList) {
			draughtArrayList.add(new Draught(draught));
		}

		currentTurn = game.currentTurn;
		selectedDraught = game.selectedDraught;
		isCurrentMultiStepMove = game.isCurrentMultiStepMove;
		isGameComplete = game.isGameComplete;
	}

	public void setUpNewGame() {
		draughtArrayList = new ArrayList<>();
		for (int i = 0; i < 8; i++) {
			if (i % 2 == 1) {
				draughtArrayList.add(new Draught(i, 0, Colour.DARK));
				draughtArrayList.add(new Draught(i, 2, Colour.DARK));
				draughtArrayList.add(new Draught(i, 6, Colour.LIGHT));
			} else {
				draughtArrayList.add(new Draught(i, 1, Colour.DARK));
				draughtArrayList.add(new Draught(i, 5, Colour.LIGHT));
				draughtArrayList.add(new Draught(i, 7, Colour.LIGHT));
			}
		}
		currentTurn = Colour.DARK;
		isCurrentMultiStepMove = false;
		isGameComplete = false;
	}

	public ArrayList<Move> findAllPossibleMoves() {
		if (isCurrentMultiStepMove) {

			return findPossibleMoves(selectedDraught)
				.stream()
				.filter(move -> move instanceof CapturingMove)
				.collect(Collectors.toCollection(ArrayList::new));
		}

		ArrayList<Move> moveList = draughtArrayList
			.stream()
			.filter(draught -> draught.colour == currentTurn)
			.map(this::findPossibleMoves)
			.flatMap(Collection::stream)
			.collect(Collectors.toCollection(ArrayList::new));

		return removeNonCapturingMovesIfCapturingMoveExists(moveList);

	}

	private ArrayList<Move> removeNonCapturingMovesIfCapturingMoveExists(ArrayList<Move> moveList) {
		ArrayList<Move> captureMoveList = moveList
			.stream()
			.filter(move -> move instanceof CapturingMove)
			.collect(Collectors.toCollection(ArrayList::new));

		return !captureMoveList.isEmpty() ? captureMoveList : moveList;
	}

	public ArrayList<Move> findPossibleMoves(Draught draught) {
		ArrayList<Move> possibleMoves = new ArrayList<>();

		for (Move move : draught.listPossibleMoves()) {
			if (isMoveBlocked(move)) {
				Optional<Draught> capturedDraught = draughtArrayList.
					stream()
					.filter(draught1 -> draught1.xPosition == move.getNewXPosition()
						&& draught1.yPosition == move.getNewYPosition()
						&& draught.colour != draught1.colour)
					.findFirst();
				if (capturedDraught.isPresent()) {
					Move captureMove = new CapturingMove(
						move.getDraught(),
						move.getNewXPosition() + move.xPositionMovement(),
						move.getNewYPosition() + move.yPositionMovement(),
						capturedDraught.get()
					);
					if (!isMoveBlocked(captureMove) && captureMove.moveInBounds()) {
						possibleMoves.add(captureMove);
					}
				}
			}else{possibleMoves.add(move);}
		}

		return removeNonCapturingMovesIfCapturingMoveExists(possibleMoves);
	}

	private boolean isMoveBlocked(Move move) {
		for (Draught draught : draughtArrayList) {
			if (draught.xPosition == move.getNewXPosition() && draught.yPosition == move.getNewYPosition()) {
				return true;
			}
		}
		return false;
	}

	public ArrayList<Draught> draughtsWithPossibleMoves() {
		return findAllPossibleMoves()
			.stream()
			.map(Move::getDraught)
			.distinct()
			.collect(Collectors.toCollection(ArrayList::new));
	}

	public void selectMove(Move move){
		Draught moveDraught = getDraughtFromPosition(move.getDraught().xPosition, move.getDraught().yPosition);

		moveDraught.setxPosition(move.getNewXPosition());
		moveDraught.setyPosition(move.getNewYPosition());

		if (move instanceof CapturingMove) {

			Draught capturedDraught = getDraughtFromPosition(((CapturingMove) move).getCapturedDraught().getxPosition(), ((CapturingMove) move).getCapturedDraught().getyPosition());
			draughtArrayList.remove(capturedDraught);

			ArrayList<Move> moves = findPossibleMoves(moveDraught);
			if (moves.stream().anyMatch(move1 -> move1 instanceof CapturingMove)) {
				if (!moveDraught.isDraughtOnKingsRow() || moveDraught.isCrowned()) {
					selectedDraught = moveDraught;
					isCurrentMultiStepMove = true;
					checkForWinner();
					return;
				}
			}

		}
		moveDraught.crownDraughtIfPossible();

		if (currentTurn == Colour.DARK){
			currentTurn = Colour.LIGHT;
		}else{
			currentTurn = Colour.DARK;
		}
		selectedDraught = null;
		isCurrentMultiStepMove = false;
		checkForWinner();
	}

	private Draught getDraughtFromPosition(int x, int y) {
		return draughtArrayList.stream().filter(draught -> draught.xPosition == x && draught.yPosition == y).findAny().get();
	}

	public Game successor(Move move) {
		Game rtnGame = this.clone();

		rtnGame.selectMove(move);
		return rtnGame;
	}

	private boolean checkForWinner() {

		if (draughtArrayList.stream().noneMatch(draught -> draught.getColour() == Colour.LIGHT)) {
			isGameComplete = true;
			gameWinner = Colour.DARK;
			return true;
		}
		if (draughtArrayList.stream().noneMatch(draught -> draught.getColour() == Colour.DARK)) {
			isGameComplete = true;
			gameWinner = Colour.LIGHT;
			return true;
		}
		if (findAllPossibleMoves().isEmpty()) {
			isGameComplete = true;
			if (currentTurn == Colour.LIGHT) {
				gameWinner = Colour.DARK;
			} else if (currentTurn == Colour.DARK) {
				gameWinner = Colour.LIGHT;
			}
			return true;
		}
		return isGameComplete;
	}


	public boolean isCurrentMultiStepMove() {
		return isCurrentMultiStepMove;
	}

	@Override
	protected Game clone() {
		Game clone = null;
		try {
			clone = (Game) super.clone();
			clone.draughtArrayList = new ArrayList<>();
			for (Draught draught : draughtArrayList) {
				clone.draughtArrayList.add(draught.clone());
			}
			clone.isGameComplete = isGameComplete;
			clone.gameWinner = gameWinner;
			clone.currentTurn = currentTurn;
			clone.isCurrentMultiStepMove = isCurrentMultiStepMove;
			clone.selectedDraught = selectedDraught == null ? null : selectedDraught.clone();
		} catch (CloneNotSupportedException ignored) {}
		return clone;
	}

}
