package ai;

import game.Colour;
import game.Draught;
import game.Game;
import javafx.util.Pair;
import moves.Move;

import java.util.ArrayList;
import java.util.stream.Collectors;

public class AI {


	int difficulty;
	Colour colour;

	public int getDifficulty() {
		return difficulty;
	}

	public void setDifficulty(int difficulty) {
		this.difficulty = difficulty;
	}

	public Colour getColour() {
		return colour;
	}

	public AI(int difficulty, Colour colour){
		this.difficulty = difficulty;
		this.colour = colour;
	}

	public Move selectMove(Game game) {
		ArrayList<Pair<Integer, Move>> evaluatedMoves = evaluateMoves(game);
		evaluatedMoves.sort((lhs, rhs) -> lhs.getKey() > rhs.getKey() ? -1 : (lhs.getKey() < rhs.getKey()) ? 1 : 0);
		return evaluatedMoves.get(0).getValue();
	}


	public ArrayList<Pair<Integer, Move>> evaluateMoves(Game game){
		ArrayList<Pair<Integer, Move>> evaluatedMoves =  new ArrayList<>();

		for (Move move : game.findAllPossibleMoves())
		{
			Game futureGame = game.successorFunction(move);
			evaluatedMoves.add(new Pair<>(minimax(futureGame, difficulty, false), move));
		}

		return evaluatedMoves;
	}

	private int minimax(Game gameBoard,int depth,boolean maxPlayer){
		if (depth == 0 || gameBoard.isGameComplete())
		{
			return evaluateGameBoard(gameBoard);
		}
		if (maxPlayer){
			int bestVal = Integer.MIN_VALUE;
			ArrayList<Game> children = gameBoard.findAllPossibleMoves().stream().map(gameBoard::successorFunction).collect(Collectors.toCollection(ArrayList::new));
			for (Game game : children){
				int evaluation = minimax(game, depth-1, false);
				bestVal = Math.max(bestVal, evaluation);
			}
			return bestVal;
		}else{
			int bestVal = Integer.MAX_VALUE;
			ArrayList<Game> children = gameBoard.findAllPossibleMoves().stream().map(gameBoard::successorFunction).collect(Collectors.toCollection(ArrayList::new));
			for (Game game: children){
				int evaluation = minimax(game, depth-1, true);
				bestVal = Math.min(bestVal, evaluation);
			}
			return bestVal;
		}

	}


	private int evaluateGameBoard(Game gameBoard){
		ArrayList<Draught> draughts = gameBoard.getDraughtArrayList();
		int aiDraughts = Math.toIntExact(draughts.stream().filter(draught -> draught.getColour() == getColour()).count());
		int opponentDraughts = Math.toIntExact(draughts.stream().filter(draught -> draught.getColour() !=  getColour()).count());
		return aiDraughts-opponentDraughts;
	}
}
