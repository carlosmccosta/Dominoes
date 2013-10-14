/**\file Domino.cpp
 * \brief Ficheiro com a implementação da classe Domino.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "Domino.h"


//#ifdef USE_BOOST
//	BOOST_CLASS_EXPORT_GUID(Domino, "Domino")
//#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Defautl contructor de Domino (explicit para evitar conversões implicitas)
 * @param _scoreToCompleteGame score minimo que os players têm que fazer para ganhar o jogo
 */
Domino::Domino(unsigned _scoreToCompleteGame):
			scoreToCompleteGame(_scoreToCompleteGame),
			gameBoneYard(Boneyard()),
			gameBoard(Board()),
			gamePlayers(vector<Player>()),
			currentPlayerIndex(0),
			winnerPlayerIndex(0),
			numberOfConsecutivePlayersUnableToAct(0) {}


/**
 * Destructor de Domino
 */
Domino::~Domino() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Domino management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que inicializa o Domino (Board, Boneyard e players)
 */
void Domino::initDomino() {
	this->gameBoard.initBoard();
	this->gameBoneYard.initBoneyard();
	this->initPlayers();
}


/**
 *  Método auxiliar que inicializa os players do Domino
 */
void Domino::initPlayers() {
	//inicializa cada um dos players
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		initPlayer(gamePlayers[i]);
	}
}


/**
 * Método auxiliar que faz o reset aos Bones dos players do Board
 */
void Domino::resetPlayersBones() {
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		gamePlayers[i].resetPlayerBones();
	}
}


/**
 * Método auxiliar que faz a inicializaçao de um player do Domino
 * @param player Player a inicializar
 */
void Domino::initPlayer(Player& player) {
	//acrescenta os 7 bones ao player caso ainda existam bones disponiveis na bonePile
	for (size_t numPlayerBones = 0; numPlayerBones < 7; ++numPlayerBones) {
		if (!gameBoneYard.empty()) {
			player.getPlayerBones().push_back(gameBoneYard.getLastBone());
		}
	}
}


/**
 * Método que prepara a próxima round
 */
void Domino::initNextRound() {
	gameBoard.resetBoard();
	gameBoneYard.resetBoneyard();
	resetPlayersBones();
	initPlayers();
	currentPlayerIndex = 0;
	numberOfConsecutivePlayersUnableToAct = 0;
	calcFirstPlayerToAct();
}


/**
 * Método que faz a compra de um Bone* ao Boneyard do Domino
 * @return Bone* recebido ou NULL caso não haja mais bones para comprar
 */
Bone* Domino::getNewBoneFromBoneyard() {

	return gameBoneYard.getLastBone();
}


/**
 * Método que devolve o player que está a jogar actualmente
 * @return Player que está a jogar
 */
Player& Domino::getCurrentPlayer() {
	return gamePlayers[currentPlayerIndex];
}


/**
 * Método que trata da passagem da vez de um player
 */
void Domino::playerPassedTurn() {
	++numberOfConsecutivePlayersUnableToAct;
}


/**
 * Método que calcula qual deve ser o primeiro Player a começar uma round
 * Ou seja primeiro começam os que têm o maior doubleBone
 * Se nenhum player tiver doubleBones começa o que tiver a peça com maior pontos
 */
void Domino::calcFirstPlayerToAct() {
	size_t candidadePlayerToStart = 0;
	char maxDoubleNumber = 0;

	//check for doublesBones
	for (size_t playerIndex = 0; playerIndex < gamePlayers.size(); ++playerIndex) {
		for (size_t boneIndex = 0; boneIndex < gamePlayers[playerIndex].getPlayerBones().size(); ++boneIndex) {
			Bone* currentBone = gamePlayers[playerIndex].getPlayerBones()[boneIndex];

			if (!currentBone->isDoubleBone())
				continue;

			char playerBoneNumber = currentBone->getFirstNumber();
			if (playerBoneNumber > maxDoubleNumber) {
				maxDoubleNumber = playerBoneNumber;
				candidadePlayerToStart = playerIndex;
			}
		}
	}


	//check for the greatest bone se não foi encontrado nenhum doubleBone (mesmo o '0' em ascii é maior do que 0)
	if (maxDoubleNumber == 0) {
		char greatestBoneSum = 0;

		for (size_t playerIndex = 0; playerIndex < gamePlayers.size(); ++playerIndex) {
			for (size_t boneIndex = 0; boneIndex < gamePlayers[playerIndex].getPlayerBones().size(); ++boneIndex) {
				char playerFirstBoneNumber = gamePlayers[playerIndex].getPlayerBones()[boneIndex]->getFirstNumber();
				char playerSecondBoneNumber = gamePlayers[playerIndex].getPlayerBones()[boneIndex]->getSecondNumber();
				char playerBoneNumbersSum = playerFirstBoneNumber + playerSecondBoneNumber;
				if (playerBoneNumbersSum > greatestBoneSum) {
					greatestBoneSum = playerBoneNumbersSum;
					candidadePlayerToStart = playerIndex;
				}
			}
		}
	}

	currentPlayerIndex = candidadePlayerToStart;
}


/**
 * Método que actualiza o indice do player que está a jogar para o próximo player
 */
void Domino::updateCurrentPlayerIndexToNextPlayer() {
	++currentPlayerIndex;

	if (currentPlayerIndex >= gamePlayers.size())
		currentPlayerIndex = 0;
}


/**
 * Método que actualiza o indice do player que está a jogar para o player anterior
 */
void Domino::updateCurrentPlayerIndexToPreviousPlayer() {
	if (currentPlayerIndex > 0) {
		--currentPlayerIndex;
	} else {
		if (currentPlayerIndex == 0)
			currentPlayerIndex = gamePlayers.size() - 1;
	}
}


/**
 * Método que verifica se o winnerPlayerIndex está correcto
 * Ou seja se é mesmo o indice do player que ganhou a round
 */
void Domino::confirmRoundWinnerPlayerIndex() {
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		if (gamePlayers[i].getPlayerBones().empty()) {
			currentPlayerIndex = i;
			winnerPlayerIndex = i;
			break;
		}
	}

}


/**
 * Método que verifica se um determinado player pode jogar um Bone*
 * @param player Player a verificar
 * @return true caso esse player tenha pelo menos um Bone* válido para jogar
 */
bool Domino::checkIfPlayerCanAct(Player& player) {
	for (size_t i = 0; i < player.getPlayerBones().size(); ++i) {
		NewBoneConection newBoneConection;
		newBoneConection.boneToInsert = player.getPlayerBones()[i];

		newBoneConection.wingOnBoardToInsertBone = NORTH_WING;
		if (gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_UP)   ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_DOWN) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_LEFT) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_RIGHT))
			return true;

		newBoneConection.wingOnBoardToInsertBone = SOUTH_WING;
		if (gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_UP)   ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_DOWN) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_LEFT) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_RIGHT))
			return true;

		newBoneConection.wingOnBoardToInsertBone = EAST_WING;
		if (gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_UP)   ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_DOWN) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_LEFT) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_RIGHT))
			return true;

		newBoneConection.wingOnBoardToInsertBone = WEST_WING;
		if (gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_UP)   ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_DOWN) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_LEFT) ||
			gameBoard.positionValidToDrawBoneOnBoard(newBoneConection, BONE_CONECTION_POINT_RIGHT))
			return true;
	}

	return false;
}


/**
 * Método que verifica se dois Bones se podem conectar
 * @param boneOnBoard Bone que está no Board
 * @param boneToInsert Bone que se quer inserir
 * @return true caso seja possivel conectar os dois bones
 */
bool Domino::checkIfNodesCanConect(Bone* boneOnBoard, Bone* boneToInsert) {
	if (boneOnBoard == NULL || boneToInsert == NULL)
		return false;


	if (boneOnBoard->getBoneConectedToFirstNumber() == NULL) {
		if (boneOnBoard->getFirstNumber()  == boneToInsert->getFirstNumber()  ||
			boneOnBoard->getFirstNumber()  == boneToInsert->getSecondNumber()) {
			return true;
		}
	}


	if (boneOnBoard->getBoneConectedToSecondNumber() == NULL) {
		if (boneOnBoard->getSecondNumber() == boneToInsert->getFirstNumber()  ||
			boneOnBoard->getSecondNumber() == boneToInsert->getSecondNumber()) {
			return true;
		}
	}

	return false;
}


/**
 * Método que verifica se uma round está bloqueada, ou seja ninguém terminou a round mas ninguém pode jogar, por não ter nenhum Bone* válido
 * @return true caso a round actual esteja bloqueada
 */
bool Domino::checkIfRoundIsBlocked() {
	if (numberOfConsecutivePlayersUnableToAct == gamePlayers.size())
		return true;
	else
		return false;
}


/**
 * Método que verifica se a round actual acabou, ou seja se algum player já não tem Bones para jogar
 * @return true caso a round tenha terminado
 */
bool Domino::checkIfRoundIsFinish() {
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		if (gamePlayers[i].getPlayerBones().size() == 0) {
			winnerPlayerIndex = i;
			return true;
		}
	}

	return false;
}


/**
 * Método que verifica se o jogo já terminou, ou seja se alguem já atingiu o número minimo de pontos para ganhar um jogo
 * @return true caso o jogo tenha terminado
 */
bool Domino::checkIfGameIsFinish() {
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		if (gamePlayers[i].getScore() >= scoreToCompleteGame) {
			winnerPlayerIndex = i;
			return true;
		}
	}

	return false;
}


/**
 * Método que determina qual foi o player que ganhou o jogo (actualiza a variável winnerPlayerIndex)
 */
void Domino::calcWinner() {
	unsigned maxPlayerPoints = 0;
	size_t candidateToWinner = 0;

	for (size_t playerIndex = 0; playerIndex < gamePlayers.size(); ++playerIndex) {
		unsigned currentPlayerScore = gamePlayers[playerIndex].getScore();
		if (currentPlayerScore >= scoreToCompleteGame) {
			if (currentPlayerScore > maxPlayerPoints) {
				maxPlayerPoints = currentPlayerScore;
				candidateToWinner = playerIndex;
			}
		}
	}

	winnerPlayerIndex = candidateToWinner;
}


/**
 * Método que verifica qual é o player que tem menos pontos na sua hand de Bones
 * @return indice do player no vector de players gamePlayers do jogador que tem o menor número de pontos na sua hand de bones
 */
size_t Domino::calcPlayerWithLowerPointsOnRoundBlocked() {
	size_t candidatePlayerIndex = 0;
	int currentMinimumPoints = INT_MAX;

	for (size_t playerIndex = 0; playerIndex < gamePlayers.size(); ++playerIndex) {
		int currentPlayerBonesSum = 0;
		for (size_t boneIndex = 0; boneIndex < gamePlayers[playerIndex].getPlayerBones().size(); ++boneIndex) {
			currentPlayerBonesSum += (int)(gamePlayers[playerIndex].getPlayerBones()[boneIndex]->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
			currentPlayerBonesSum += (int)(gamePlayers[playerIndex].getPlayerBones()[boneIndex]->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
		}

		if (currentPlayerBonesSum < currentMinimumPoints) {
			currentMinimumPoints = currentPlayerBonesSum;
			candidatePlayerIndex = playerIndex;
		}
	}

	return candidatePlayerIndex;
}


/**
 * Método que calcula os pontos de bonus a dar a quem ganhou a round
 * @param roundBlocked flag que indica se a round acabou normalmente ou se acabou por ficar bloqueada
 * @return Pontos de bonus a atribuir ao player que ganhou a round (ainda falta fazer o arredondamento para o mais próximo multiplo de 5)
 */
int Domino::calcRemainScoreOnRoundCompletion(bool roundBlocked) {

	if (roundBlocked)
		winnerPlayerIndex = calcPlayerWithLowerPointsOnRoundBlocked();

	int pointsWinnerWonFromOtherPlayers = 0;

	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		if (i != winnerPlayerIndex) {
			//acrescenta a pontuação dos adversários
			pointsWinnerWonFromOtherPlayers += calcSumPlayerBonesPoints(gamePlayers[i]);
		}
	}


	//tira a pontuação do próprio player (só acontece na roundBlock, porque se acabar normalmente irá tirar 0
	pointsWinnerWonFromOtherPlayers -= calcSumPlayerBonesPoints(gamePlayers[winnerPlayerIndex]);


	return pointsWinnerWonFromOtherPlayers;
}


/**
 * Método auxiliar que calculo o número de pontos que um player tem na sua Bone hand
 * @param player player que onde se vai calcular o numero de pontos
 * @return numero de pontos que o player tem na sua bone hand
 */
unsigned int Domino::calcSumPlayerBonesPoints(Player& player) {
	unsigned sumOfPlayerBonesPoints = 0;

	for (size_t i = 0; i < player.getPlayerBones().size(); ++i) {
		sumOfPlayerBonesPoints += (player.getPlayerBones()[i]->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET); //-48 para a conversão de ascii para unsigned
		sumOfPlayerBonesPoints += (player.getPlayerBones()[i]->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);//-48 para a conversão de ascii para unsigned
	}

	return sumOfPlayerBonesPoints;
}


/**
 * Método que calula o número de pontos que um player obteria se inseri-se o bone no insertion point dado (útil para a AI)
 * @param newBoneConection Classe auxiliar que compacta o Bone* e o ponto de inserção no Board
 * @param firstBone flag que indica se é o primeiro Bone* a inserir no Board
 * @return pontos que se obteria se o Bone fosse inserido naquela posição
 */
unsigned int Domino::calcScoreOnBoneInsertion(NewBoneConection newBoneConection, bool firstBone) {
	unsigned score = 0;

	if (firstBone) {
		score += newBoneConection.boneToInsert->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET;
		score += newBoneConection.boneToInsert->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET;
		return score;
	}

	Bone* boneOnBoardWhereBoneIsGoingToBeInserted = gameBoard.getCorrespondentBoneToBoardInsertPoint(newBoneConection.wingOnBoardToInsertBone);
	Bone* boneToInsert = newBoneConection.boneToInsert;

	// calculo dos pontos dos outros bones nas 3 outras possiveis posições de bones com pontuação sem ser o primeiro doubleBone
	if (newBoneConection.wingOnBoardToInsertBone != EAST_WING &&
		gameBoard.getEastWingBone() != NULL &&
		gameBoard.getEastWingBone() != gameBoard.getFirstDoubleBone())
		score += calcBoneScoreOnBoard(gameBoard.getEastWingBone(), newBoneConection.wingOnBoardToInsertBone);

	if (newBoneConection.wingOnBoardToInsertBone != WEST_WING &&
		gameBoard.getWestWingBone() != NULL &&
		gameBoard.getWestWingBone() != gameBoard.getFirstDoubleBone())
		score += calcBoneScoreOnBoard(gameBoard.getWestWingBone(), newBoneConection.wingOnBoardToInsertBone);

	if (newBoneConection.wingOnBoardToInsertBone != NORTH_WING &&
		gameBoard.getNorthWingBone() != NULL &&
		gameBoard.getNorthWingBone() != gameBoard.getFirstDoubleBone())
		score += calcBoneScoreOnBoard(gameBoard.getNorthWingBone(), newBoneConection.wingOnBoardToInsertBone);

	if (newBoneConection.wingOnBoardToInsertBone != SOUTH_WING &&
		gameBoard.getSouthWingBone() != NULL &&
		gameBoard.getSouthWingBone() != gameBoard.getFirstDoubleBone())
		score += calcBoneScoreOnBoard(gameBoard.getSouthWingBone(), newBoneConection.wingOnBoardToInsertBone);


	//se for o primeiro doubleBone
	if (gameBoard.getFirstDoubleBone() != NULL) {
		unsigned doubleBonePointsCount = 0;
		if (newBoneConection.wingOnBoardToInsertBone != EAST_WING &&
			gameBoard.getEastWingBone() == gameBoard.getFirstDoubleBone())
			++doubleBonePointsCount;

		if (newBoneConection.wingOnBoardToInsertBone != WEST_WING &&
			gameBoard.getWestWingBone() == gameBoard.getFirstDoubleBone())
			++doubleBonePointsCount;

		if (newBoneConection.wingOnBoardToInsertBone != NORTH_WING &&
			gameBoard.getNorthWingBone() == gameBoard.getFirstDoubleBone())
			++doubleBonePointsCount;

		if (newBoneConection.wingOnBoardToInsertBone != SOUTH_WING &&
			gameBoard.getSouthWingBone() == gameBoard.getFirstDoubleBone())
			++doubleBonePointsCount;

		if (doubleBonePointsCount < 3)
			score += ((gameBoard.getFirstDoubleBone()->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET) * doubleBonePointsCount);
		else
			score += ((gameBoard.getFirstDoubleBone()->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET) * 2 ); //no máximo só conta os 2 lados do bone (nunca pode ser os 3, quando por exemplo a primeira peça é um double...)
	}
	
	//calculo da pontuação do bone que irá ser inserido
	unsigned scoreOfBoneToBeInserted = 0;
	bool BonesCanBeConected = false;

	if (boneOnBoardWhereBoneIsGoingToBeInserted != NULL) {
		if (boneToInsert->getFirstNumber() == boneOnBoardWhereBoneIsGoingToBeInserted->getFirstNumber() || boneToInsert->getFirstNumber() == boneOnBoardWhereBoneIsGoingToBeInserted->getSecondNumber()) {
			scoreOfBoneToBeInserted += (boneToInsert->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
			BonesCanBeConected = true;
		}

		if (boneToInsert->getSecondNumber() == boneOnBoardWhereBoneIsGoingToBeInserted->getFirstNumber() || boneToInsert->getSecondNumber() == boneOnBoardWhereBoneIsGoingToBeInserted->getSecondNumber()) {
			scoreOfBoneToBeInserted += (boneToInsert->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
			BonesCanBeConected = true;
		}

		//bone não encaixa na posição que se pretendia
		if (!BonesCanBeConected)
			return 0;
	}


	score += scoreOfBoneToBeInserted;

	return score;
}


/**
 * Método auxiliar que calcula o número de pontos que um Bone que está no Board tem (para a contagem de pontos da jogada)
 * @param boneOnBoard Bone* que está no Board
 * @return pontos que esse Bone* pode contribuir para uma jogada
 */
unsigned int Domino::calcBoneScoreOnBoard(Bone* boneOnBoard, BoardInsertPoint boardInsertionPoint) {
	unsigned points = 0;

	if (gameBoard.getNumberOfBonesOnBoard() == 1) {
		if (boardInsertionPoint == EAST_WING) {
			if (boneOnBoard->getBoneConectedToFirstNumber() == NULL)
				points += (boneOnBoard->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
		} else if (boardInsertionPoint == WEST_WING) {
			if (boneOnBoard->getBoneConectedToSecondNumber() == NULL)
				points += (boneOnBoard->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
		}
	} else {
		if (boneOnBoard->getBoneConectedToFirstNumber() == NULL)
			points += (boneOnBoard->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
		else if (boneOnBoard->getBoneConectedToSecondNumber() == NULL)
			points += (boneOnBoard->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET);
	}

	if (boneOnBoard->isDoubleBone() && boneOnBoard != gameBoard.getFirstDoubleBone())
		points *=2;

	return points;
}


/**
 * Método que verifica se a posição do bone a inserir na segunda peça jogada está correcta (para garantir a correcta inicialiação dos pointers)
 * @param boneOnBoardToCheck bone que está no board
 * @param boneToInsert bone que se quer inserir
 * @param boardInsertionPoint Ponto de conecção onde se quer inserir o bone
 * @return true caso a inserção seja valida
 */
bool Domino::checkIfSecondBoneInsertionIsValid(Bone *boneOnBoardToCheck, Bone *boneToInsert, BoardInsertPoint boardInsertionPoint, BoneConectionPoint boneConectionPoint) {
	//caso especial do segundo bone a inserir num bone normal (não double), para evitar inserções na posição contrária
	//na primeira peça o fisrtNumber de uma peça não double está sempre do lado esquerdo

	if (boneOnBoardToCheck == NULL || boneToInsert == NULL)
		return false;

	bool invalid = false;
	if (gameBoard.getNumberOfBonesOnBoard() == 1) {
		//se for double
		if (boneOnBoardToCheck->isDoubleBone()) {
			if (boardInsertionPoint == EAST_WING && boneConectionPoint != BONE_CONECTION_POINT_RIGHT) {
				invalid = true;
			} else if (boardInsertionPoint == WEST_WING && boneConectionPoint != BONE_CONECTION_POINT_LEFT) {
				invalid = true;
			} /*else {
				invalid = true;
			}*/
		} else {
		//se não for double
			if (boardInsertionPoint == EAST_WING) {
				if ((boneOnBoardToCheck->getFirstNumber() == boneToInsert->getFirstNumber() || boneOnBoardToCheck->getFirstNumber() == boneToInsert->getSecondNumber())) {
					invalid = true;
				}
			} else if (boardInsertionPoint == WEST_WING) {
				if ((boneOnBoardToCheck->getSecondNumber() == boneToInsert->getFirstNumber() || boneOnBoardToCheck->getSecondNumber() == boneToInsert->getSecondNumber())) {
					invalid = true;
				}
			}
		}

	}

	return !invalid;
}


/**
 * Método usado na função em baixo pra evitar repetição de código
 */
void Domino::updateBestBoneConectionOnBoardWingAI(
		Bone* boneOnBoardToCheck,
		Bone* boneToInsert,
		BoardInsertPoint boardInsertionPoint,
		bool firstDoubleHasPrimaryConectionPointAvailable,
		bool firstBone,
		vector <NewBoneConection>& validBones,
		NewBoneConection& bestBoneConection,
		NewBoneConection& currentBoneConection,
		unsigned& bestScoreFound,
		unsigned& currentBoneScore) {

	if (boneOnBoardToCheck == NULL || boneToInsert == NULL)
		return;

	bool invalid = true;

	if (!firstBone) {
		//primeiro double tem posições disponiveis nas laterais (sem ser nas pontas)
		/*if (firstDoubleHasPrimaryConectionPointAvailable && gameBoard.getFirstDoubleBone() == boneOnBoardToCheck) {
			if (gameBoard.getFirstDoubleBone()->getVerticalDirection()) {
				if ((gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_LEFT)) ||
					(gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_RIGHT)) ) {
						invalid = false;
				} else {
//					invalid = true;
					return;
				}
			} else {
				if ((gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_UP)) ||
					(gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_DOWN)) ) {
						invalid = false;
				} else {
//					invalid = true;
					return;
				}
			}

		//inserção numa peça sem ser o primeiro double bone
		} else {*/

			if (gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_UP)   ||
				gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_DOWN) ||
				gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_LEFT) ||
				gameBoard.positionValidToDrawBoneOnBoard(currentBoneConection, BONE_CONECTION_POINT_RIGHT)) {
				invalid = false;
			} else {
				invalid = true;
				return;
			}
		//}



		//caso especial do segundo bone a inserir num bone normal (não double), para evitar inserções na posição contrária
		//na primeira peça o fisrtNumber de uma peça não double está sempre do lado esquerdo
		if (checkIfSecondBoneInsertionIsValid(boneOnBoardToCheck, boneToInsert, boardInsertionPoint, BONE_CONECTION_POINT_UP) ||
				checkIfSecondBoneInsertionIsValid(boneOnBoardToCheck, boneToInsert, boardInsertionPoint, BONE_CONECTION_POINT_DOWN) ||
				checkIfSecondBoneInsertionIsValid(boneOnBoardToCheck, boneToInsert, boardInsertionPoint, BONE_CONECTION_POINT_LEFT) ||
				checkIfSecondBoneInsertionIsValid(boneOnBoardToCheck, boneToInsert, boardInsertionPoint, BONE_CONECTION_POINT_RIGHT)) {
			invalid = false;
		} else {
//			invalid = true;
			return;
		}

		//acrescentação das conecções válidas e update à melhor
		if (!invalid) {
			currentBoneScore = calcScoreOnBoneInsertion(currentBoneConection, firstBone);

			if ((currentBoneScore >= bestScoreFound) && ((currentBoneScore % 5) == 0)) {
				bestBoneConection = currentBoneConection;
				bestScoreFound = currentBoneScore;
			}

			validBones.push_back(currentBoneConection);
		}


	//first bone
	} else {
		currentBoneScore = calcScoreOnBoneInsertion(currentBoneConection, firstBone);

		if ((currentBoneScore >= bestScoreFound) && ((currentBoneScore % 5) == 0)) {
			bestBoneConection = currentBoneConection;
			bestScoreFound = currentBoneScore;
		}

		validBones.push_back(currentBoneConection);
	}
}


/**
 * Método que calcula qual o melhor Bone* a inserir no Board dado um vector de Bones (útil para a AI)
 * @param playerBonesAI vector de Bones de um player
 * @param firstBone flag que indica que o Bone a inserir será o primeiro no Board
 * @return Retorna a melhor conecção que se pode ter tendo em conta a heuristica sugerida no enunciado
 */
NewBoneConection Domino::calcBestBoneToPlaceOnBoardAI(vector <Bone*>& playerBonesAI, bool firstBone) {
	//1º pesquisa pela peça de melhor pontuação
	//se nenhuma tiver pontuação faz uma 2ª pesquisa pelo maior double valido
	//se não houver nenhum double válido, retorna a primeira peça válida com maior pontuação

	vector <NewBoneConection> validBones;

	NewBoneConection bestBoneConection;
	NewBoneConection currentBoneConection;

	unsigned bestScoreFound = 0;
	unsigned currentBoneScore = 0;

	bool firstDoubleHasPrimaryConectionPointAvailable = false;
	if (gameBoard.getFirstDoubleBone() != NULL &&
	   (gameBoard.getFirstDoubleBone()->getBoneConectedOnMiddleDownOrLeft() == NULL ||
		gameBoard.getFirstDoubleBone()->getBoneConectedOnMiddleUpOrRight() == NULL))
		firstDoubleHasPrimaryConectionPointAvailable = true;


#ifdef FIRST_BONE_MUST_BE_A_DOUBLE
	//se for o primeiro bone tem que ser usado um double
	if (!firstBone) {
#endif
		//adição das peças válidas aos vector validBones e verificação da peça de melhor pontuação
		for (size_t bonesIndex = 0; bonesIndex < playerBonesAI.size(); ++bonesIndex) {
			Bone* boneOnBoardToCheck = NULL;
			Bone* boneToInsert = playerBonesAI[bonesIndex];
			currentBoneConection.boneToInsert = boneToInsert;


			//EAST_WING
			currentBoneConection.wingOnBoardToInsertBone = EAST_WING;
			boneOnBoardToCheck = gameBoard.getCorrespondentBoneToBoardInsertPoint(EAST_WING);
			updateBestBoneConectionOnBoardWingAI(boneOnBoardToCheck, boneToInsert, EAST_WING, firstDoubleHasPrimaryConectionPointAvailable, firstBone,
					                           validBones, bestBoneConection, currentBoneConection, bestScoreFound, currentBoneScore);


			//WEST_WING
			currentBoneConection.wingOnBoardToInsertBone = WEST_WING;
			boneOnBoardToCheck = gameBoard.getCorrespondentBoneToBoardInsertPoint(WEST_WING);
			updateBestBoneConectionOnBoardWingAI(boneOnBoardToCheck, boneToInsert, WEST_WING, firstDoubleHasPrimaryConectionPointAvailable, firstBone,
											   validBones, bestBoneConection, currentBoneConection, bestScoreFound, currentBoneScore);


			//NORTH_WING
			currentBoneConection.wingOnBoardToInsertBone = NORTH_WING;
			boneOnBoardToCheck = gameBoard.getCorrespondentBoneToBoardInsertPoint(NORTH_WING);
			updateBestBoneConectionOnBoardWingAI(boneOnBoardToCheck, boneToInsert, NORTH_WING, firstDoubleHasPrimaryConectionPointAvailable, firstBone,
											   validBones, bestBoneConection, currentBoneConection, bestScoreFound, currentBoneScore);



			//SOUTH_WING
			currentBoneConection.wingOnBoardToInsertBone = SOUTH_WING;
			boneOnBoardToCheck = gameBoard.getCorrespondentBoneToBoardInsertPoint(SOUTH_WING);
			updateBestBoneConectionOnBoardWingAI(boneOnBoardToCheck, boneToInsert, SOUTH_WING, firstDoubleHasPrimaryConectionPointAvailable, firstBone,
											   validBones, bestBoneConection, currentBoneConection, bestScoreFound, currentBoneScore);
		}


		//encontrou bones que fazem pontos
		if (bestScoreFound != 0) {
			return bestBoneConection;
		}
#ifdef FIRST_BONE_MUST_BE_A_DOUBLE
	}
#endif


	//se nenhuma das peças dá pontos tenta livrar-se dos doubleBones maiores
	char bigestDouble = 0;
	NewBoneConection bestDoubleBoneConection;
	bestDoubleBoneConection.boneToInsert = NULL;
	bestDoubleBoneConection.wingOnBoardToInsertBone = WEST_WING;

	//na primeira peça não vai haver validBones
	if (firstBone) {
		for (size_t i = 0; i < playerBonesAI.size(); ++i) {
			Bone* currentBone = playerBonesAI[i];
			if (currentBone->isDoubleBone()) {
				if (currentBone->getFirstNumber() > bigestDouble) {
					bigestDouble = currentBone->getFirstNumber();
					bestDoubleBoneConection.boneToInsert = currentBone;
				}
			}
		}

	//não é a primeira peça
	} else {
		for (size_t j = 0; j < validBones.size(); ++j) {
			Bone* currentBone = validBones[j].boneToInsert;
			if (currentBone->isDoubleBone()) {
				if (currentBone->getFirstNumber() > bigestDouble) {
					bigestDouble = currentBone->getFirstNumber();
					bestDoubleBoneConection = validBones[j];
				}
			}
		}
	}


	//encontrou um doubleBone válido
	if (bestDoubleBoneConection.boneToInsert != NULL) {
		return bestDoubleBoneConection;
	}


	//se não houver peças de pontos nem doubles seleciona a peça com maior pontos
	//(assim se perder o round, dá menos pontos ao adversário)
	char bigestBoneSum = 0;
	NewBoneConection bigestBoneConection;
	bigestBoneConection.boneToInsert = NULL;
	bigestBoneConection.wingOnBoardToInsertBone = WEST_WING;


	for (size_t i = 0; i < (firstBone ? (playerBonesAI.size()) : (validBones.size())); ++i) {
		Bone* currentBone = (firstBone ? (playerBonesAI[i]) : (validBones[i].boneToInsert));
		char currentBoneSum = currentBone->getFirstNumber() + currentBone->getSecondNumber();
		if (currentBoneSum > bigestBoneSum) {
			bigestBoneSum = currentBoneSum;
			if (firstBone)
				bigestBoneConection.boneToInsert = currentBone;
			else
				bigestBoneConection = validBones[i];
		}
	}

	return bigestBoneConection;
}


//responsabilidade de organização das peças passada para o utilizador
//BoneConectionPoint Domino::calcBestBoneConectionPointOnBoardAI(NewBoneConection newBoneConection) {
//
//	return BONE_CONECTION_POINT_DOWN;
//}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Domino management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que faz a gestão de um jogo de Domino usando a interface CLI
 * @param roundLoaded flag que indica se o jogo que se vai fazer teve a round actual carregada de um ficheiro
 */
void Domino::initDominoGameCLI(bool roundLoaded) {
	if (!roundLoaded) {
		utils::clearConsoleScreen();
		addPlayersCLI();

		utils::clearConsoleScreen();
		unsigned scoreToFinishGame = utils::getNumberCin<unsigned>("\nNumero de pontos minimo para terminar o jogo: ");
		this->scoreToCompleteGame = scoreToFinishGame;
		initDomino();
	}

	//se não estiver a usar o boost o load apenas carrega as informações dos users, por isso é preciso inicializar o domino
#ifndef USE_BOOST
	if (roundLoaded)
		initDomino();
#endif


	bool firstRound = true;
	bool roundBlocked = false;

	while (!checkIfGameIsFinish() || roundLoaded) {

		if (!firstRound && !roundLoaded) {
			initNextRound();
		}

		if (!roundLoaded)
			calcFirstPlayerToAct();

//se o load tenha sido feito sem usar o boost é preciso ver quem começa primeiro, porque a round começa do inicio
#ifndef USE_BOOST
		if (roundLoaded)
			calcFirstPlayerToAct();
#endif


		firstRound = false;
		roundLoaded = false;


		bool firstBone = (gameBoard.getNumberOfBonesOnBoard() == 0) ? true : false;

		while (!checkIfRoundIsFinish()) {
			utils::clearConsoleScreen();

			if (checkIfRoundIsBlocked()) {
				roundBlocked = true;
				utils::clearConsoleScreen();
				gameBoard.showBoardCLI();

				for (size_t i = 0; i < gamePlayers.size(); ++i) {
					gamePlayers[i].showPlayerBonesCLI();
				}

				cout << "\n  >>>  A round ficou bloqueada por mais nenhum jogador ter bones validos e nao haver mais bones no Boneyard!\n" << endl;
				utils::getUserInput();
				break;
			}

			bool playerHasValidBone = false;

			if (!firstBone) {
				while (!playerHasValidBone) {
					playerHasValidBone = checkIfPlayerCanAct(getCurrentPlayer());

					if (playerHasValidBone)
						break;

					if (gameBoneYard.empty()) {
						utils::clearConsoleScreen();
						gameBoard.showBoardCLI();
						getCurrentPlayer().showPlayerBonesCLI();
						cout << "\n" << getCurrentPlayer().getName() << " nao tem Bones possiveis para jogar e nao existem mais bones disponiveis para compra!\nPassando a vez...\n\n";
						playerPassedTurn();
						utils::getUserInput();
						break;
					}

					utils::clearConsoleScreen();
					gameBoard.showBoardCLI();
					gamePlayers[currentPlayerIndex].showPlayerBonesCLI();

					cout << "\n" << getCurrentPlayer().getName() << " nao tem bones possiveis para jogar!\nComprando bone do boneyard...\n\n";
					getCurrentPlayer().addBone(gameBoneYard.getLastBone());
					utils::getUserInput();
				}
			} else {
				playerHasValidBone = true;
			}


			if (playerHasValidBone) {
				utils::clearConsoleScreen();
				currentPlayerTurnCLI(firstBone);
				numberOfConsecutivePlayersUnableToAct = 0;
				firstBone = false;
			}

			//passagem para o próximo player
			updateCurrentPlayerIndexToNextPlayer();
		}

		//o player seguinte não chegou a jogar, porque não se entrou no anterior ciclo
		updateCurrentPlayerIndexToPreviousPlayer();
		confirmRoundWinnerPlayerIndex();


		if (roundBlocked)
			showScoresOnRoundBlock();
		else
			showScoresOnRoundEnd();

		roundBlocked = false;
		//endround
	}

	calcWinner();
	//endgame


	showScoresOnGameEnd();
	initNextRound();
	gameBoneYard.destroyBoneyard();
	gamePlayers.clear();
}


/**
 * Método que trata da adição dos players ao Domino usando a interface CLI
 */
void Domino::addPlayersCLI() {
	size_t numPlayers = utils::getNumberCin("  >>> Quantos jogadores pretende que o jogo tenha: ", 5, 2, false, "\nO jogo tem que ter entre 2 e 4 jogadores!\n\n");

	cout << endl;

	for (size_t i = 0; i < numPlayers; ++i) {
		cout << "\n  >>> Introduza o nome do jogador " << i << ": ";
		string name = utils::getlineCin();

		bool playerIsAI = utils::getYesNoCin("  >>> Pretende que o player seja controlado por AI (S/N): ", "\nIntroduza S para o player ser controlado por uma AI,\nou N se quer que um humano o controle!\n\n");
		gamePlayers.push_back(Player(name, playerIsAI));
	}
}


/// Método que mostra o tabuleiro e os bones do player actual
void Domino::showBoardAndPlayerStatus() {
	gameBoard.showBoardCLI();

	cout << endl;

	cout << "\n" << getCurrentPlayer().getName() << " tem " << getCurrentPlayer().getScore() << (getCurrentPlayer().getScore() == 1 ? " ponto" : " pontos") << ".\n";
	cout << "Numero de bones no boneyard: " << gameBoneYard.getBonePile().size() << "\n";
	cout << "Controlado por AI: " << (getCurrentPlayer().getAIPlayer() ? "sim" : "nao") << "\n" << endl;


	getCurrentPlayer().showPlayerBonesCLI();

	cout << endl;
}


/**
 * Método que trata da jogada do player actual
 * @param firstBone flag que indica se o player vai inserir o primeiro bone na Board
 */
void Domino::currentPlayerTurnCLI(bool firstBone) {
	showBoardAndPlayerStatus();

	BoardInsertPoint boardInsertionPointSelected;
	BoneConectionPoint boneConectionPointSelected;
	NewBoneConection boneConection;
	unsigned newPoints = 0;

	bool playerUseInvalidBone;
	do {			
		playerUseInvalidBone = false;

		if (!getCurrentPlayer().getAIPlayer()) {
			size_t boneIndexSelected = selectBoneToUseFromPlayer();
			Bone* boneSelected = getCurrentPlayer().getBone(boneIndexSelected);
			boneConection.boneToInsert = boneSelected;

			if (firstBone) {
#ifdef FIRST_BONE_MUST_BE_A_DOUBLE
				//primeiro bone tem que ser double (se o player tiver doubles)
				if (getCurrentPlayer().playerHasDoubleBones() && !boneSelected->isDoubleBone()) {
					cout << "\nNa primeira jogada caso tenha um DoubleBone tem que o inserir!\n\n";
					playerUseInvalidBone = true;
					continue;
				}
#endif

				boardInsertionPointSelected = WEST_WING;
				boneConectionPointSelected = BONE_CONECTION_POINT_LEFT;
			} else {
				boardInsertionPointSelected = selectBoardInsertionPointToUseFromPlayer();
				boneConectionPointSelected = selectBoneConectionPointToUseFromPlayer();	
			}
		} else {
			//player com inteligencia artificial
			NewBoneConection AIBestBoneConectionFound = calcBestBoneToPlaceOnBoardAI(getCurrentPlayer().getPlayerBones(), firstBone);
			boneConection.boneToInsert = AIBestBoneConectionFound.boneToInsert;


			boardInsertionPointSelected = AIBestBoneConectionFound.wingOnBoardToInsertBone;

			cout << "A AI selecionou o bone |" << AIBestBoneConectionFound.boneToInsert->getFirstNumber() << "|" << AIBestBoneConectionFound.boneToInsert->getSecondNumber() << "|";
			cout << " para inserir na " << getBoardInsertionPointDescription(AIBestBoneConectionFound.wingOnBoardToInsertBone) << endl;

			if (firstBone) {
				boneConectionPointSelected = BONE_CONECTION_POINT_LEFT;
			} else {
				cout << "Selecione em que posicao quer inserir esse bone..." << endl;
				boneConectionPointSelected = selectBoneConectionPointToUseFromPlayer();
			}

		}

		boneConection.wingOnBoardToInsertBone = boardInsertionPointSelected;

		newPoints = 0;
		if (!firstBone)
			newPoints = calcScoreOnBoneInsertion(boneConection, firstBone);
		else {
			newPoints += boneConection.boneToInsert->getFirstNumber() + ASCII_CHAR_TO_NUMBER_OFFSET;
			newPoints += boneConection.boneToInsert->getSecondNumber() + ASCII_CHAR_TO_NUMBER_OFFSET;
		}

		//verifica se na segunda inserção, os pointers são inicializados correctamente
		if(gameBoard.getNumberOfBonesOnBoard() == 1) {
			Bone* boneOnBoardToCheck = gameBoard.getCorrespondentBoneToBoardInsertPoint(boneConection.wingOnBoardToInsertBone);
			playerUseInvalidBone = !checkIfSecondBoneInsertionIsValid(boneOnBoardToCheck, boneConection.boneToInsert, boneConection.wingOnBoardToInsertBone, boneConectionPointSelected);
		}

		//se a verificação em cima passou ou não existiu (continuou valido), tenta inserir o bone
		if (!playerUseInvalidBone)
			playerUseInvalidBone = !(gameBoard.insertBone(boneConection, boneConectionPointSelected, firstBone));


		if (playerUseInvalidBone) {
			cout << "\n\nNao foi possivel inserir o bone que especificou na posicao indicada!\n\n";
			utils::getUserInput();
			utils::clearConsoleScreen();
			showBoardAndPlayerStatus();
		}

	} while (playerUseInvalidBone);


	cout << "\n\n\nNumero de pontos feitos nesta jogada: " << newPoints << endl;
	
	//só os multiplos de  é que contam para a pontuação
	if ((newPoints > 0) && ((newPoints % 5) == 0)) {
		getCurrentPlayer().addPoints(newPoints);
		cout << "\nForam acrescentados " << newPoints << " pontos a sua pontuacao!\n";
		cout << getCurrentPlayer().getName() << " tem agora " << getCurrentPlayer().getScore() << " pontos!\n" << endl;
	}

	utils::getUserInput();

	//retirada do bone que foi usado
	getCurrentPlayer().removeBone(boneConection.boneToInsert);
}


/**
 * Método auxiliar que seleciona o indice do Bone* que o player quer usar usando a interface CLI
 * @return retorna o indice que o player selecionou (supoem-se que foram mostrados os bones e respectivos indices antes de pedir o indice)
 */
size_t Domino::selectBoneToUseFromPlayer() {
	size_t boneIndexSelected = 0;
	bool invalidInput = false;

	cout << "\n   >>> Introduza o numero do bone que quer usar (S para sair e G para guardar e sair)\n";

	do {
		if (invalidInput)
			cout << "\nIntroduza um dos indices dos bones mostrados em cima (ou S / G)!\n\n";


		cout << "  >>> Opcao: ";
		string input = utils::getlineCin();

		if (utils::toUpper(input) == "S")
			exit(0);

		if (utils::toUpper(input) == "G") {
			utils::clearConsoleScreen();
			saveDominoCLI();
			exit(0);
		}

		if (input.empty()) {
			invalidInput = true;
			continue;
		}


		stringstream ssInput(input);

		ssInput >> boneIndexSelected;

		if (ssInput.fail()) {
			ssInput.clear();
			invalidInput = true;
			continue;
		}


		if (boneIndexSelected < 0 || boneIndexSelected >= getCurrentPlayer().getPlayerBones().size())
			invalidInput = true;
		else
			invalidInput = false;

	} while (invalidInput);



	return boneIndexSelected;
}


/**
 * Método auxiliar que seleciona em que sitio do Board o player quer inserir o Bone que selecionou anteriormente
 * @return Retorna o sitio do Board onde o player quer inserir o Bone* que tinha selecionado
 */
BoardInsertPoint Domino::selectBoardInsertionPointToUseFromPlayer() {
	BoardInsertPoint insertionPointOnBoard;

	string title("");
	vector <string> colNames;
	colNames.push_back("Pontos de insercao no board");
	vector < vector <string> > columns;
	columns.push_back(vector <string>());
	columns[0].push_back("SOUTH_WING");
	columns[0].push_back("WEST_WING");
	columns[0].push_back("NORTH_WING");
	columns[0].push_back("EAST_WING");



	size_t insertionPointIndex = 0;

	utils::printMenu(title, columns, colNames);
	insertionPointIndex = utils::getNumberCin("\n  >>> Indice do ponto de insercao: ", 5, 0, false, "\nIntroduza um dos indices da tabela!\n\n");


	switch (insertionPointIndex) {
		case 2: {
			insertionPointOnBoard = NORTH_WING;
			break;
		}

		case 0: {
			insertionPointOnBoard = SOUTH_WING;
			break;
		}

		case 3: {
			insertionPointOnBoard = EAST_WING;
			break;
		}

		case 1: {
			insertionPointOnBoard = WEST_WING;
			break;
		}

		default: {
			insertionPointOnBoard = WEST_WING;
			break;
		}
	}

	return insertionPointOnBoard;
}


/**
 * Método auxiliar que seleciona em que direcção o player quer inserir o Bone* que tinha selecionado antes
 * @return Retorna a dircção que o player selecionou da tabela mostrada
 */
BoneConectionPoint Domino::selectBoneConectionPointToUseFromPlayer() {
	BoneConectionPoint conectionPointOnBone;

	string title("");
	vector <string> colNames;
	colNames.push_back("Pontos de coneccao no bone selecionado");
	vector < vector <string> > columns;
	columns.push_back(vector <string>());
	columns[0].push_back("BONE_CONECTION_POINT_DOWN");
	columns[0].push_back("BONE_CONECTION_POINT_LEFT");
	columns[0].push_back("BONE_CONECTION_POINT_UP");
	columns[0].push_back("BONE_CONECTION_POINT_RIGHT");


	size_t insertionPointIndex = 0;

	utils::printMenu(title, columns, colNames);
	insertionPointIndex = utils::getNumberCin("\n  >>> Indice do ponto de coneccao (4 para guardar o jogo, 5 para sair): ", 6, 0, false, "\nIntroduza um dos indices da tabela!\n\n");


	switch (insertionPointIndex) {
		case 2: {
			conectionPointOnBone = BONE_CONECTION_POINT_UP;
			break;
		}

		case 0: {
			conectionPointOnBone = BONE_CONECTION_POINT_DOWN;
			break;
		}

		case 1: {
			conectionPointOnBone = BONE_CONECTION_POINT_LEFT;
			break;
		}

		case 3: {
			conectionPointOnBone = BONE_CONECTION_POINT_RIGHT;
			break;
		}

		case 4: {
			utils::clearConsoleScreen();
			saveDominoCLI();
			exit(0);
		}

		case 5: {
			exit(0);
		}

		default: {
			conectionPointOnBone = BONE_CONECTION_POINT_RIGHT;
			break;
		}
	}

	return conectionPointOnBone;
}


/**
 * Método auxiliar que mostra os scores quanda a round termina ou é bloqueada e actualiza a pontuação do vencedor em conformidade
 * @param roundBlocked flag que indica se a round acabou normalmente (false), ou se acabou bloqueada (true)
 */
void Domino::calcAndShowScoresOnRoundEnd(bool roundBlocked) {
	int bonus = calcRemainScoreOnRoundCompletion(roundBlocked);
	int offsetToRound = bonus % 5;
	int roundedBonus = bonus;

	if (offsetToRound < 3)
		roundedBonus -= offsetToRound; //arredonda para o multiplo de 5 a baixo
	else
		roundedBonus += (5 - offsetToRound);//arredonda para o multiplo de 5 a cima

	if (roundedBonus < 0)
		roundedBonus = 0;

	gamePlayers[winnerPlayerIndex].addPoints((unsigned)roundedBonus);

	cout << "---------------------------------------------------------------------------------\n";

	if (roundBlocked) {
		for (size_t i = 0; i < gamePlayers.size(); ++i) {
			cout << " * " << gamePlayers[i].getName() << " tinha na sua mao de bones" << calcSumPlayerBonesPoints(gamePlayers[i]) << " pontos no fim da round!" << endl;
		}
	}

	cout << "\nTotal de pontos dos adversarios: " << bonus;
	cout << "\nTotal de pontos dos adversarios arredondado: " << roundedBonus << endl;

	cout << "---------------------------------------------------------------------------------\n\n";

	cout << gamePlayers[winnerPlayerIndex].getName() << " ganhou esta round e obteve " << roundedBonus << " pontos de bonus dos seus adversarios!\n" << endl;

	cout << "*********************************************************************************\n";
	cout << "Pontuacoes: " << endl;
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		cout << " -> " << gamePlayers[i].getName() << " : " << (gamePlayers[i].getScore()) << ((gamePlayers[i].getScore() != 1) ? " pontos" : " ponto") << "\n";
	}
	cout << "*********************************************************************************\n";

	cout << "\n" << endl;

	utils::getUserInput();
}


/**
 * Método que mostra os scores quanda a round é bloqueada e actualiza a pontuação do vencedor em conformidade
 */
void Domino::showScoresOnRoundBlock() {
	utils::clearConsoleScreen();

	cout << "############################   DOMINO - ALL FIVES   #############################\n";
	cout << "  >>>                 PONTUACOES NO FIM DESTA ROUND BLOCKED                 <<<  \n";
	cout << "#################################################################################\n\n\n";

	calcAndShowScoresOnRoundEnd(true);
}


/**
 * Método que mostra os scores quanda a round termina e actualiza a pontuação do vencedor em conformidade
 */
void Domino::showScoresOnRoundEnd() {
	utils::clearConsoleScreen();

	cout << "############################   DOMINO - ALL FIVES   #############################\n";
	cout << "  >>>                     PONTUACOES NO FIM DESTA ROUND                     <<<  \n";
	cout << "#################################################################################\n\n\n";

	calcAndShowScoresOnRoundEnd(false);
}


/**
 * Método que mostra os scores quanda a jogo termina
 */
void Domino::showScoresOnGameEnd() {
	utils::clearConsoleScreen();

	cout << "############################   DOMINO - ALL FIVES   #############################\n";
	cout << "  >>>                          PONTUACOES FINAIS                            <<<  \n";
	cout << "#################################################################################\n\n\n";

	cout << gamePlayers[winnerPlayerIndex].getName() << " ganhou este jogo!\n" << endl;

	cout << "*********************************************************************************\n";
	cout << "Pontuacoes: " << endl;
	for (size_t i = 0; i < gamePlayers.size(); ++i) {
		cout << " -> " << gamePlayers[i].getName() << " : " << (gamePlayers[i].getScore()) << ((gamePlayers[i].getScore() != 1) ? " pontos" : " ponto") << "\n";
	}
	cout << "*********************************************************************************\n";

	cout << "\n" << endl;

	utils::getUserInput();
}


/**
 * Método que trata da interface CLI para o carregamento de um jogo de Domino
 * @return true caso tenha sido feito o carregamento de um jogo anterir com sucesso
 */
bool Domino::loadDominoCLI() {
	utils::clearConsoleScreen();
	cout << "\n  >>> Introduza o nome do ficheiro onde esta guardado o jogo que quer carregar: ";
	string filename = utils::getlineCin();

	try {
		loadDomino(filename);
	} catch (FileDoesntExistException& e) {
		cout << e.what() << endl;
		utils::getUserInput();

		if (utils::getYesNoCin("\nDeseja tentar novamente com outro nome (S/N)? ", "\nIntroduza S ou N!\n\n"))
			return loadDominoCLI();

		return false;
	}

	return true;
}


/**
 * Método que trata da interface CLI para o backup de um jogo de Domino
 * @return true caso tenha sido feito o backup do jogo actual com sucesso
 */
bool Domino::saveDominoCLI() {
	utils::clearConsoleScreen();
	cout << "\n  >>> Introduza o nome do ficheiro onde quer guardar o jogo: ";
	string filename = utils::getlineCin();

	try {
		saveDomino(filename, false);
	} catch (FileAlreadyExistException& e) {
		cout << e.what() << endl;
		utils::getUserInput();

		if (utils::getYesNoCin("\nDeseja substituir o ficheiro que ja existe (S/N)? ", "\nIntroduza S ou N!\n\n"))
			saveDomino(filename, true);
		else if (utils::getYesNoCin("\nDeseja tentar novamente com outro nome (S/N)? ", "\nIntroduza S ou N!\n\n"))
			return saveDominoCLI();

		return false;
	}

	return true;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Load - save>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef USE_BOOST
/**
 * Método que trata do carregamento de um jogo a partir de um ficheiro usando a libraria de serialização do Boost
 * Caso o ficheiro não exista lança uma excepção (FileDoesntExistException)
 * @param filename Nome do ficheiro onde está o jogo a carregar
 */
void Domino::loadDomino(string filename)  throw(FileDoesntExistException)  {
	ifstream inputFileStream(filename.c_str());

	if (inputFileStream.is_open()) {
		boost::archive::text_iarchive inputArchive(inputFileStream);
		inputArchive >> (*this);

		inputFileStream.close();
	} else {
		throw FileDoesntExistException();
		//não conseguiu abrir o ficheiro
	}

}


/**
 * Método que trata do backup do jogo actual para um ficheiro usando a libraria de serialização do Boost
 * Caso o ficheiro para onde se ia guardar os dados já exista lança uma excepção (FileAlreadyExistException)
 * @param filename nome do ficheiro onde se vai tentar guardar o jogo actual
 * @param overWrite flag que indica que se o ficheiro existir, faça overwrite e não lance excepção
 */
void Domino::saveDomino(string filename, bool overWrite) throw(FileAlreadyExistException) {
	if (!overWrite) {
		ifstream inputFileStream(filename.c_str());
		if (inputFileStream.is_open()) {
			inputFileStream.close();
			throw FileAlreadyExistException();
		} else {
			inputFileStream.close();
		}
	}

	ofstream outputFileStream(filename.c_str());

	boost::archive::text_oarchive outputArchive(outputFileStream);

	outputArchive << (*this);

	outputFileStream.close();
}

#else

/**
 * Método que trata do carregamento de um jogo a partir de um ficheiro
 * Caso o ficheiro não exista lança uma excepção (FileDoesntExistException)
 * @param filename Nome do ficheiro onde está o jogo a carregar
 */
void Domino::loadDomino(string filename) throw(FileDoesntExistException) {
	ifstream inputFileStream(filename.c_str());

	if (inputFileStream.is_open()) {
		//pontuação minima para acabar o jogo
		size_t scoreToFininhGame = 0;
		string scoreToFininhGameStr;
		getline(inputFileStream, scoreToFininhGameStr);
		stringstream scoreToFininhGameSStr(scoreToFininhGameStr);
		scoreToFininhGameSStr >> scoreToFininhGame;
		this->scoreToCompleteGame = scoreToFininhGame;

		
		//player que estava a jogar
		size_t currentPlayer = 0;
		string currentPlayerStr;
		getline(inputFileStream, currentPlayerStr);
		stringstream currentPlayerSStr(currentPlayerStr);
		currentPlayerSStr >> currentPlayer;
		this->setCurrentPlayerIndex(currentPlayer);


		//numero de players que estavam a jogar
		size_t numPlayers = 0;
		string numPlayersStr;
		getline(inputFileStream, numPlayersStr);
		stringstream numPlayersSStr(numPlayersStr);
		numPlayersSStr >> numPlayers;

		for (size_t i = 0; i < numPlayers; ++i) {
			string name;
			string AIPlayerTemp;
			bool AIPlayer = false;
			unsigned score;

			getline(inputFileStream, name);

			getline(inputFileStream, AIPlayerTemp);
			if (AIPlayerTemp == "AI")
				AIPlayer = true;


			string scoreStr;
			getline(inputFileStream, scoreStr);
			stringstream scoreSStr(scoreStr);
			scoreSStr >> score;
			

			Player newPlayer(name, AIPlayer);
			newPlayer.setScore(score);

			gamePlayers.push_back(newPlayer);
		}

		inputFileStream.close();
	} else {
		throw FileDoesntExistException();
		//não conseguiu abrir o ficheiro
	}
}


/**
 * Método que trata do backup do jogo actual para um ficheiro
 * Caso o ficheiro para onde se ia guardar os dados já exista lança uma excepção (FileAlreadyExistException)
 * @param filename nome do ficheiro onde se vai tentar guardar o jogo actual
 * @param overWrite flag que indica que se o ficheiro existir, faça overwrite e não lance excepção
 */
void Domino::saveDomino(string filename, bool overWrite) throw(FileAlreadyExistException) {
	if (!overWrite) {
		ifstream inputFileStream(filename.c_str());
		if (inputFileStream.is_open()) {
			inputFileStream.close();
			throw FileAlreadyExistException();
		} else {
			inputFileStream.close();
		}
	}


	ofstream outputFileStream(filename.c_str());

	if (outputFileStream.is_open()) {
		outputFileStream << scoreToCompleteGame << "\n";
		outputFileStream << currentPlayerIndex << "\n";
		outputFileStream << gamePlayers.size() << "\n";
		for (size_t i = 0; i < gamePlayers.size(); ++i) {
			outputFileStream << gamePlayers[i].getName() << "\n";
			outputFileStream << (gamePlayers[i].getAIPlayer() ? "AI" : "USER") << "\n";
			outputFileStream << gamePlayers[i].getScore() << "\n";
		}

		outputFileStream.close();
	}
}

#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Load - save>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
size_t Domino::getCurrentPlayerIndex() const {
	return currentPlayerIndex;
}

Board Domino::getGameBoard() const {
	return gameBoard;
}

Boneyard Domino::getGameBoneYard() const {
	return gameBoneYard;
}

vector<Player>& Domino::getGamePlayers() {
	return gamePlayers;
}

unsigned Domino::getNumberOfConsecutivePlayersUnableToAct() const {
	return numberOfConsecutivePlayersUnableToAct;
}

unsigned Domino::getScoreToCompleteGame() const {
	return scoreToCompleteGame;
}

size_t Domino::getWinnerPlayerIndex() const {
	return winnerPlayerIndex;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Domino::setCurrentPlayerIndex(size_t currentPlayerIndex) {
	this->currentPlayerIndex = currentPlayerIndex;
}

void Domino::setGameBoard(Board gameBoard) {
	this->gameBoard = gameBoard;
}

void Domino::setGameBoneYard(Boneyard gameBoneYard) {
	this->gameBoneYard = gameBoneYard;
}

void Domino::setGamePlayers(const vector<Player>& gamePlayers) {
	this->gamePlayers = gamePlayers;
}

void Domino::setNumberOfConsecutivePlayersUnableToAct(unsigned numberOfConsecutivePlayersUnableToAct) {
	this->numberOfConsecutivePlayersUnableToAct = numberOfConsecutivePlayersUnableToAct;
}

void Domino::setScoreToCompleteGame(unsigned scoreToCompleteGame) {
	this->scoreToCompleteGame = scoreToCompleteGame;
}

void Domino::setWinnerPlayerIndex(size_t winnerPlayerIndex) {
	this->winnerPlayerIndex = winnerPlayerIndex;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
