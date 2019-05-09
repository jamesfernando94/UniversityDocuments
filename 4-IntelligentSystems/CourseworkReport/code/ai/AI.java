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

	public AI(int difficulty, Colour colour) {
		this.difficulty = difficulty;
		this.colour = colour;
	}

	public int getDifficulty() {
		return difficulty;
	}

	public void setDifficulty(int difficulty) {
		this.difficulty = difficulty;
	}

	public Colour getColour() {
		return colour;
	}

	public Move selectMove(Game game) {
		ArrayList<Pair<Integer, Move>> evaluatedMoves = evaluateMoves(game);
		evaluatedMoves.sort((lhs, rhs) -> lhs.getKey() > rhs.getKey() ? -1 : (lhs.getKey() < rhs.getKey()) ? 1 : 0);
		return evaluatedMoves.get(0).getValue();
	}


	public ArrayList<Pair<Integer, Move>> evaluateMoves(Game game) {
		ArrayList<Pair<Integer, Move>> evaluatedMoves = new ArrayList<>();

		for (Move move : game.findAllPossibleMoves()) {
			Game futureGame = game.successor(move);
			evaluatedMoves.add(new Pair<>(minimaxAlphaBeta(futureGame, difficulty, false, Integer.MIN_VALUE, Integer.MAX_VALUE), move));
		}

		return evaluatedMoves;
	}

	private int minimaxAlphaBeta(Game gameBoard, int depth, boolean maxPlayer, int alpha, int beta) {
		if (depth == 0 || gameBoard.isGameComplete()) {
			return evaluateGameBoard(gameBoard);
		}
		if (maxPlayer) {
			int value = Integer.MIN_VALUE;
			ArrayList<Game> children = gameBoard.findAllPossibleMoves().stream().map(gameBoard::successor).collect(Collectors.toCollection(ArrayList::new));
			for (Game game : children) {
				value = Math.max(value, minimaxAlphaBeta(game, depth - 1, false, alpha, beta));
				alpha = Math.max(alpha, value);
				if (alpha >= beta) {
					break;
				}
			}
			return value;
		} else {
			int value = Integer.MAX_VALUE;
			ArrayList<Game> children = gameBoard.findAllPossibleMoves().stream().map(gameBoard::successor).collect(Collectors.toCollection(ArrayList::new));
			for (Game game : children) {
				value = Math.min(value, minimaxAlphaBeta(game, depth - 1, true, alpha, beta));
				beta = Math.min(beta, value);
				if (alpha >= beta) {
					break;
				}
			}
			return value;
		}

	}


	private int evaluateGameBoard(Game gameBoard) {
		ArrayList<Draught> draughts = gameBoard.getDraughtArrayList();
		int aiDraughts = Math.toIntExact(draughts.stream().filter(draught -> draught.getColour() == getColour()).count());
		int opponentDraughts = Math.toIntExact(draughts.stream().filter(draught -> draught.getColour() != getColour()).count());
		return aiDraughts - opponentDraughts;
	}
}
