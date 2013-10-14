#ifndef DOMINO_H_
#define DOMINO_H_

/**\file Domino.h
 * \brief Classe que faz a gestão e visualização numa interface CLI de um jogo de Domino.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <vector>
#include <string>
#include <fstream>

#include "defs.h"
#include "Board.h"
#include "Player.h"
#include "Boneyard.h"
#include "utils.h"


using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
	#include <boost/archive/text_iarchive.hpp>
	#include <boost/archive/text_oarchive.hpp>
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/string.hpp>
	#include <boost/serialization/version.hpp>
//	#include <boost/serialization/export.hpp>
#endif



//###############################################################   Domino   ####################################################################
/**
 * \brief Classe que faz a gestão e visualização numa interface CLI de um jogo de Domino.
 */
class Domino {
//=============================================================   <private>   ===================================================================
private:
	unsigned scoreToCompleteGame;
	Boneyard gameBoneYard;
	Board gameBoard;
	vector<Player> gamePlayers;
	size_t currentPlayerIndex;
	size_t winnerPlayerIndex;
	unsigned numberOfConsecutivePlayersUnableToAct;


#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & scoreToCompleteGame;
		archive & gameBoneYard;
		archive & gameBoard;
		archive & gamePlayers;
		archive & currentPlayerIndex;
		archive & winnerPlayerIndex;
		archive & numberOfConsecutivePlayersUnableToAct;
	}
#endif
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Defautl contructor de Domino (explicit para evitar conversões implicitas)
	 * @param _scoreToCompleteGame score minimo que os players têm que fazer para ganhar o jogo
	 */
	explicit Domino(unsigned _scoreToCompleteGame = 100);

	/**
	 * Destructor de Domino
	 */
	virtual ~Domino();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Domino management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que inicializa o Domino (Board, Boneyard e players)
	 */
	void initDomino();

	/**
	 *  Método auxiliar que inicializa os players do Domino
	 */
	void initPlayers();


	/**
	 * Método auxiliar que faz o reset aos Bones dos players do Board
	 */
	void resetPlayersBones();

	/**
	 * Método auxiliar que faz a inicializaçao de um player do Domino
	 * @param player Player a inicializar
	 */
	void initPlayer(Player& player);

	/**
	 * Método que prepara a próxima round
	 */
	void initNextRound();


	/**
	 * Método que faz a compra de um Bone* ao Boneyard do Domino
	 * @return Bone* recebido ou NULL caso não haja mais bones para comprar
	 */
	Bone* getNewBoneFromBoneyard();

	/**
	 * Método que devolve o player que está a jogar actualmente
	 * @return Player que está a jogar
	 */
	Player& getCurrentPlayer();

	/**
	 * Método que trata da passagem da vez de um player
	 */
	void playerPassedTurn();


	/**
	 * Método que calcula qual deve ser o primeiro Player a começar uma round
	 * Ou seja primeiro começam os que têm o maior doubleBone
	 * Se nenhum player tiver doubleBones começa o que tiver a peça com maior pontos
	 */
	void calcFirstPlayerToAct();

	/**
	 * Método que actualiza o indice do player que está a jogar para o próximo player
	 */
	void updateCurrentPlayerIndexToNextPlayer();

	/**
	 * Método que actualiza o indice do player que está a jogar para o player anterior
	 */
	void updateCurrentPlayerIndexToPreviousPlayer();

	/**
	 * Método que verifica se o winnerPlayerIndex está correcto
	 * Ou seja se é mesmo o indice do player que ganhou a round
	 */
	void confirmRoundWinnerPlayerIndex();


	/**
	 * Método que verifica se um determinado player pode jogar um Bone*
	 * @param player Player a verificar
	 * @return true caso esse player tenha pelo menos um Bone* válido para jogar
	 */
	bool checkIfPlayerCanAct(Player& player);

	/**
	 * Método que verifica se dois Bones se podem conectar
	 * @param boneOnBoard Bone que está no Board
	 * @param boneToInsert Bone que se quer inserir
	 * @return true caso seja possivel conectar os dois bones
	 */
	bool checkIfNodesCanConect(Bone* boneOnBoard, Bone* boneToInsert);

	/**
	 * Método que verifica se uma round está bloqueada, ou seja ninguém terminou a round mas ninguém pode jogar, por não ter nenhum Bone* válido
	 * @return true caso a round actual esteja bloqueada
	 */
	bool checkIfRoundIsBlocked();

	/**
	 * Método que verifica se a round actual acabou, ou seja se algum player já não tem Bones para jogar
	 * @return true caso a round tenha terminado
	 */
	bool checkIfRoundIsFinish();

	/**
	 * Método que verifica se o jogo já terminou, ou seja se alguem já atingiu o número minimo de pontos para ganhar um jogo
	 * @return true caso o jogo tenha terminado
	 */
	bool checkIfGameIsFinish();

	/**
	 * Método que determina qual foi o player que ganhou o jogo (actualiza a variável winnerPlayerIndex)
	 */
	void calcWinner();

	/**
	 * Método que verifica qual é o player que tem menos pontos na sua hand de Bones
	 * @return indice do player no vector de players gamePlayers do jogador que tem o menor número de pontos na sua hand de bones
	 */
	size_t calcPlayerWithLowerPointsOnRoundBlocked();

	/**
	 * Método que calcula os pontos de bonus a dar a quem ganhou a round
	 * @param roundBlocked flag que indica se a round acabou normalmente ou se acabou por ficar bloqueada
	 * @return Pontos de bonus a atribuir ao player que ganhou a round (ainda falta fazer o arredondamento para o mais próximo multiplo de 5)
	 */
	int calcRemainScoreOnRoundCompletion(bool roundBlocked);

	/**
	 * Método auxiliar que calculo o número de pontos que um player tem na sua Bone hand
	 * @param player player que onde se vai calcular o numero de pontos
	 * @return numero de pontos que o player tem na sua bone hand
	 */
	unsigned int calcSumPlayerBonesPoints(Player& player);


	/**
	 * Método que calula o número de pontos que um player obteria se inseri-se o bone no insertion point dado (útil para a AI)
	 * @param newBoneConection Classe auxiliar que compacta o Bone* e o ponto de inserção no Board
	 * @param firstBone flag que indica se é o primeiro Bone* a inserir no Board
	 * @return pontos que se obteria se o Bone fosse inserido naquela posição
	 */
	unsigned int calcScoreOnBoneInsertion(NewBoneConection newBoneConection, bool firstBone);

	/**
	 * Método auxiliar que calcula o número de pontos que um Bone que está no Board tem (para a contagem de pontos da jogada)
	 * @param boneOnBoard Bone* que está no Board
	 * @return pontos que esse Bone* pode contribuir para uma jogada
	 */
	unsigned int calcBoneScoreOnBoard(Bone* boneOnBoard, BoardInsertPoint boardInsertionPoint);


	/**
	 * Método que verifica se a posição do bone a inserir na segunda peça jogada está correcta (para garantir a correcta inicialiação dos pointers)
	 * @param boneOnBoardToCheck bone que está no board
	 * @param boneToInsert bone que se quer inserir
	 * @param boardInsertionPoint Ponto de conecção onde se quer inserir o bone
	 * @return true caso a inserção seja valida
	 */
	bool checkIfSecondBoneInsertionIsValid(Bone *boneOnBoardToCheck, Bone *boneToInsert, BoardInsertPoint boardInsertionPoint, BoneConectionPoint boneConectionPoint);

	/**
	 * Método usado na função em baixo pra evitar repetição de código
	 */
	void updateBestBoneConectionOnBoardWingAI(
			Bone* boneOnBoardToCheck,
			Bone* boneToInsert,
			BoardInsertPoint boardInsertionPoint,
			bool firstDoubleHasPrimaryConectionPointAvailable,
			bool firstBone,
			vector <NewBoneConection>& validBones,
			NewBoneConection& bestBoneConection,
			NewBoneConection& currentBoneConection,
			unsigned& bestScoreFound,
			unsigned& currentBoneScore);

	/**
	 * Método que calcula qual o melhor Bone* a inserir no Board dado um vector de Bones (útil para a AI)
	 * @param playerBonesAI vector de Bones de um player
	 * @param firstBone flag que indica que o Bone a inserir será o primeiro no Board
	 * @return Retorna a melhor conecção que se pode ter tendo em conta a heuristica sugerida no enunciado
	 */
	NewBoneConection calcBestBoneToPlaceOnBoardAI(vector <Bone*>& playerBonesAI, bool firstBone);

	//responsabilidade de organização das peças passada para o utilizador
//	BoneConectionPoint calcBestBoneConectionPointOnBoardAI(NewBoneConection newBoneConection);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Domino management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que faz a gestão de um jogo de Domino usando a interface CLI
	 * @param roundLoaded flag que indica se o jogo que se vai fazer teve a round actual carregada de um ficheiro
	 */
	void initDominoGameCLI(bool gameLoaded);

	/**
	 * Método que trata da adição dos players ao Domino usando a interface CLI
	 */
	void addPlayersCLI();

	/// Método que mostra o tabuleiro e os bones do player actual
	void showBoardAndPlayerStatus();

	/**
	 * Método que trata da jogada do player actual
	 * @param firstBone flag que indica se o player vai inserir o primeiro bone na Board
	 */
	void currentPlayerTurnCLI(bool firstBone);

	/**
	 * Método auxiliar que seleciona o indice do Bone* que o player quer usar usando a interface CLI
	 * @return retorna o indice que o player selecionou (supoem-se que foram mostrados os bones e respectivos indices antes de pedir o indice)
	 */
	size_t selectBoneToUseFromPlayer();

	/**
	 * Método auxiliar que seleciona em que sitio do Board o player quer inserir o Bone que selecionou anteriormente
	 * @return Retorna o sitio do Board onde o player quer inserir o Bone* que tinha selecionado
	 */
	BoardInsertPoint selectBoardInsertionPointToUseFromPlayer();

	/**
	 * Método auxiliar que seleciona em que direcção o player quer inserir o Bone* que tinha selecionado antes
	 * @return Retorna a dircção que o player selecionou da tabela mostrada
	 */
	BoneConectionPoint selectBoneConectionPointToUseFromPlayer();


	/**
	 * Método auxiliar que mostra os scores quanda a round termina ou é bloqueada e actualiza a pontuação do vencedor em conformidade
	 * @param roundBlocked flag que indica se a round acabou normalmente (false), ou se acabou bloqueada (true)
	 */
	void calcAndShowScoresOnRoundEnd(bool roundBlocked);

	/**
	 * Método que mostra os scores quanda a round é bloqueada e actualiza a pontuação do vencedor em conformidade
	 */
	void showScoresOnRoundBlock();

	/**
	 * Método que mostra os scores quanda a round termina e actualiza a pontuação do vencedor em conformidade
	 */
	void showScoresOnRoundEnd();

	/**
	 * Método que mostra os scores quanda a jogo termina
	 */
	void showScoresOnGameEnd();

	/**
	 * Método que trata da interface CLI para o carregamento de um jogo de Domino
	 * @return true caso tenha sido feito o carregamento de um jogo anterir com sucesso
	 */
	bool loadDominoCLI();

	/**
	 * Método que trata da interface CLI para o backup de um jogo de Domino
	 * @return true caso tenha sido feito o backup do jogo actual com sucesso
	 */
	bool saveDominoCLI();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </CLI>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Load - save>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que trata do carregamento de um jogo a partir de um ficheiro
	 * Caso o ficheiro não exista lança uma excepção (FileDoesntExistException)
	 * @param filename Nome do ficheiro onde está o jogo a carregar
	 */
	void loadDomino(string filename) throw(FileDoesntExistException);

	/**
	 * Método que trata do backup do jogo actual para um ficheiro
	 * Caso o ficheiro para onde se ia guardar os dados já exista lança uma excepção (FileAlreadyExistException)
	 * @param filename nome do ficheiro onde se vai tentar guardar o jogo actual
	 * @param overWrite flag que indica que se o ficheiro existir, faça overwrite e não lance excepção
	 */
	void saveDomino(string filename, bool overWrite) throw(FileAlreadyExistException);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Load - save>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	size_t getCurrentPlayerIndex() const;
    Board getGameBoard() const;
    Boneyard getGameBoneYard() const;
    vector<Player>& getGamePlayers();
    unsigned getNumberOfConsecutivePlayersUnableToAct() const;
	unsigned getScoreToCompleteGame() const;
	size_t getWinnerPlayerIndex() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setCurrentPlayerIndex(size_t currentPlayerIndex);
    void setGameBoard(Board gameBoard);
    void setGameBoneYard(Boneyard gameBoneYard);
    void setGamePlayers(const vector<Player>& gamePlayers);
	void setNumberOfConsecutivePlayersUnableToAct(unsigned numberOfConsecutivePlayersUnableToAct);
	void setScoreToCompleteGame(unsigned scoreToCompleteGame);
	void setWinnerPlayerIndex(size_t winnerPlayerIndex);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ====================================================================
};


#endif /* DOMINO_H_ */
