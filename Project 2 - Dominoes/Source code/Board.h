#ifndef BOARD_H_
#define BOARD_H_

/**\file Board.h
 * \brief Classe que faz a gestão do tabuleiro de jogo do Domino.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <iostream>
#include <vector>
#include <string>

#include "defs.h"
#include "Bone.h"
#include "DoubleBone.h"


using std::vector;
using std::string;
using std::cout;
using std::ostream;


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/string.hpp>
	#include <boost/serialization/version.hpp>
//	#include <boost/serialization/export.hpp>
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Enums>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
enum BoardInsertPoint { NORTH_WING, SOUTH_WING, EAST_WING, WEST_WING };
enum BoneConectionPoint { BONE_CONECTION_POINT_UP, BONE_CONECTION_POINT_DOWN, BONE_CONECTION_POINT_LEFT, BONE_CONECTION_POINT_RIGHT };


/**
 * Operador que devolve o BoneConectionPoint logicamente oposto
 * @param boneConectionPoint BoneConectionPoint que se pretende "inverter"
 * @return BoneConectionPoint que é o inverso do que foi dado
 */
BoneConectionPoint operator!(const BoneConectionPoint& boneConectionPoint);

/**
 * Método que devolve a string associada à enumeração BoardInsertPoint
 * @param boneInsertionPoint BoardInsertPoint que se pretende obter a descrição
 * @return descrição da BoardInsertPoint dada
 */
string getBoardInsertionPointDescription(BoardInsertPoint boneInsertionPoint);

/**
 * Operador que permite mostrar de forma mais legivel a enumeração BoardInsertPoint
 * @param out stream de output
 * @param boneInsertionPoint BoardInsertPoint que se pretende mostrar
 * @return o stream de output, de forma a permitir encadeamentos de streams
 */
ostream& operator<<(ostream& out, const BoardInsertPoint& boneInsertionPoint);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Enums>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class NewBoneConection {
public:
	Bone* boneToInsert;
	BoardInsertPoint wingOnBoardToInsertBone;

	NewBoneConection() : boneToInsert(NULL), wingOnBoardToInsertBone(WEST_WING) {}
	virtual ~NewBoneConection() {}

private:
#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & boneToInsert;
		archive & wingOnBoardToInsertBone;
	}
#endif
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </auxiliary structs>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//###############################################################   Board   ######################################################################
/**
 * \brief Classe que faz a gestão do tabuleiro de jogo do Domino.
 */
class Board {
//=============================================================   <private>   ====================================================================
private:
	Bone* eastWingBone;
	Bone* westWingBone;
	Bone* northWingBone;
	Bone* southWingBone;
	Bone* firstDoubleBone;

	unsigned numberOfBonesOnBoard;
	vector< vector<char> > boardMatrix;


#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & eastWingBone;
		archive & westWingBone;
		archive & northWingBone;
		archive & southWingBone;
		archive & firstDoubleBone;
		archive & boardMatrix;
		archive & numberOfBonesOnBoard;
	}
#endif
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Default contructor de Board
	 */
	Board();

	/**
	 * Destructor de Board
	 */
	~Board();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Board management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método qye inicializa a charMatrix do Board
	 */
	void initBoard();

	/**
	 * Método que reinicializa o Board
	 */
	void resetBoard();


	/**
	 * Método que retorna o Bone* correspondente ao BoardInsertPoint no Board
	 * @param insertionPoint enumeração com os 4 pontos possiveis de inserir bones
	 * @return o apontador para o Bone pretendido ou NULL se esse local de inserção ainda não tiver Bones associados
	 */
	Bone* getCorrespondentBoneToBoardInsertPoint(BoardInsertPoint insertionPoint);


	/**
	 * Método que retorna a enumerção BoneFirstNumberPositionOnBoard correspospondente à enumerção BoneConectionPoint
	 * @param boneConectionPoint Enumerção que se quer converter
	 * @return Enumerção correspondente
	 */
	BoneFirstNumberPositionOnBoard getCorrespondentBoneFirstNumberPositionOnBoard(BoneConectionPoint boneConectionPoint);


	/**
	 * Método que mostra na consola a charMatrix do Board
	 */
	void showBoardCLI();


	/**
	 * Método que trata da inserção de um Bone, num dado ponto de inserção, numa determinada direcção no Board
	 * @param newBoneConection NewConection com o Bone* a inserir e em que ponto de inserção do Board
	 * @param boneConectionPoint Direcção em que inserir o Bone*
	 * @param firstBone Flag que indica se o Bone a inserir é o primeiro bone do Board
	 * @return true caso a inserção tenha sido feita com sucesso, ou false, caso não possa desenhar no sitio pretendido
	 * 		   tenha desrespeitado alguma regra do jogo ou fosse colocar o Bone numa posição que saisse fora da charMatrix do Board
	 */
	bool insertBone(NewBoneConection newBoneConection, BoneConectionPoint boneConectionPoint, bool firstBone);

	/**
	 * Método que faz o update dos pointers que o Board tem para a gestão das inserções. Só deve ser executado depois da inserção.
	 * @param boneOnBoardToCheck Bone* onde se inseriu o novo Bone*
	 * @param newBoneConection Bone* que foi inserido e sitio de inserção no Board
	 * @param boneConectionPoint Direcção em que o Bone* foi inserido
	 * @param firstBone Flag que indica se o Bone* inserido foi o primeiro da Board
	 */
	void updateBoardWingPointers(Bone* boneOnBoardToCheck, NewBoneConection newBoneConection, BoneConectionPoint boneConectionPoint, bool firstBone);

	/**
	 * Método que verifica se é possivel "desenhar" on dado Bone* numa dada direcção, noutro que já esteja no Board
	 * @param boneOnBoardToCheck Bone* onde se quer inserir o novo Bone*
	 * @param boneToInsert Bone* que se quer inserir
	 * @param boneConectionPoint Direcção em que se quer inserir o novo Bone*
	 * @return true caso seja possivel desenhar o Bone* na Board
	 */
	bool positionValidToDrawBoneOnBoard(NewBoneConection newBoneConection, BoneConectionPoint boneConectionPoint);

	/**
	 * Método auxiliar que verifica se um dado DoubleBone* é válido para inserir no Board
	 * @param boneOnBoardToCheck Bone* onde o doubleBone seria inserido
	 * @param boneToInsert doubleBone a inserir
	 * @param boneConectionPoint Direção do doubleBone a inserir
	 * @param useFirstNumberOnBoneOnBoardToCheck flag que indica para verificar o primeiro número (true) ou o segundo número (false) do bone onde se vai inserir o doubleBone
	 * @param useFirstNumberOnBoneToInsert flag que indica para verificar o primeiro número (true) ou o segundo número (false) do doubleBone
	 * @return true caso seja possivel inserir o doubleBone que se pretendia
	 */
	bool checkIfDoubleBonePositionIsValidToDrawOnBoard(Bone* boneOnBoardToCheck, Bone* boneToInsert, BoneConectionPoint boneConectionPoint, bool useFirstNumberOnBoneOnBoardToCheck, bool useFirstNumberOnBoneToInsert);

	/**
	 * Método auxiliar que verifica se um dado Bone* é válido para inserir no Board
	 * @param boneOnBoardToCheck Bone* onde o Bone* seria inserido
	 * @param boneToInsert Bone* a inserir
	 * @param boneConectionPoint Direção do Bone* a inserir
	 * @param useFirstNumberOnBoneOnBoardToCheck flag que indica para verificar o primeiro número (true) ou o segundo número (false) do bone onde se vai inserir o Bone*
	 * @param useFirstNumberOnBoneToInsert flag que indica para verificar o primeiro número (true) ou o segundo número (false) do Bone* a inserir
	 * @param boneOnBoardToCheckIsDouble flag que indica se o bone que está no Board onde se quer inserir o Bone* é um doubleBone
	 * @return true caso seja possivel inserir o Bone* nas condições especificadas
	 */
	bool checkIfBonePositionIsValidToDrawOnBoard(Bone* boneOnBoardToCheck, Bone* boneToInsert, BoneConectionPoint boneConectionPoint, bool useFirstNumberOnBoneOnBoardToCheck, bool useFirstNumberOnBoneToInsert, bool boneOnBoardToCheckIsDouble);

	/**
	 * Método auxiliar que faz o update de um Bone* que irá ser inserido noutro Bone* do Board
	 * @param boneOnBoardToCheck bone do Board onde o Bone* será inserido
	 * @param boneToInsert Bone* que se quer inserir
	 * @param boneConectionPoint Direcção em que se quer inserir o Bone*
	 * @param useFirstNumberOnBoneOnBoardToCheck flag que indica para verificar o primeiro número (true) ou o segundo número (false) do bone onde se vai inserir o Bone*
	 * @param useFirstNumberOnBoneToInsert flag que indica para verificar o primeiro número (true) ou o segundo número (false) do Bone* a inserir
	 * @return true caso o update tenha sido feito com sucesso e o Bone* pode ser inserido, false se as condições dadas forem contra as regras ou inválidas
	 */
	bool updateBoneToInsertOnBone(Bone* boneOnBoardToCheck, Bone* boneToInsert, BoneConectionPoint boneConectionPoint, bool useFirstNumberOnBoneOnBoardToCheck, bool useFirstNumberOnBoneToInsert);

	/**
	 * Método auxiliar que faz o update de um Bone* que irá ser inserido num doubleBone do Board
	 * @param boneOnBoardToCheck doubleBOne do Board onde o Bone* será inserido
	 * @param boneToInsert Bone* que se quer inserir
	 * @param boneConectionPoint Direcção em que se quer inserir o Bone*
	 * @param useFirstNumberOnBoneToInsert flag que indica para verificar o primeiro número (true) ou o segundo número (false) do bone onde se vai inserir o Bone*
	 * @return true caso o update tenha sido feito com sucesso e o Bone* pode ser inserido, false se as condições dadas forem contra as regras ou inválidas
	 */
	bool updateBoneToInsertOnDoubleBone(Bone* boneOnBoardToCheck, Bone* boneToInsert, BoneConectionPoint boneConectionPoint, bool useFirstNumberOnBoneToInsert);

	/**
	 * Método estático que verifica se possivel desenhar um dado Bone numa dada posição de uma charMatrix
	 * (ao estar estático permite ser usado noutras classes para evitar código repetido.
	 * @param charMatrix charMatrix onde se vai verificar se é válido o desenho de um Bone*
	 * @param boneXCenter posição central do Bone* e que está no eixo dos x da charMatrix onde se quer desennhar o Bone*
	 * @param boneYCenter  posição central do Bone* e que está no eixo dos y da charMatrix onde se quer desennhar o Bone*
	 * @param verticalDirection flag que indica se se quer desenhar o Bone* na vertical (true) ou horizontal (false)
	 * @return true caso seja válido o desenho do Bone* na posição e charMatrix dada
	 */
	static bool positionValidToDrawBoneOnCharMatrix(vector <vector <char> >& charMatrix, size_t boneXCenter, size_t boneYCenter, bool verticalDirection);

	/**
	 * Método auxiliar estático que verifica se se pode desenhar um dado Bone numa dada charMatrix sem se sobrepor a outros Bones
	 * @param charMatrix charMatrix onde se vai verificar se é válido o desenho de um Bone*
	 * @param boneXCenter posição central do Bone* e que está no eixo dos x da charMatrix onde se quer desenhar o Bone*
	 * @param boneYCenter posição central do Bone* e que está no eixo dos y da charMatrix onde se quer desenhar o Bone*
	 * @param verticalDirection flag que indica se se quer desenhar o Bone* na vertical (true) ou horizontal (false)
	 * @param validBackGroundChar char que indica qual o caracter de backGround do Board e como tal válido para desenhar por cima
	 * @return true caso seja possivel desenhar um bone na charMatrix sem ter problemas de sobreposição com outros Bones
	 */
	static bool checkIfPositionIsClearAndValidToDrawBone(vector <vector <char> >& charMatrix, size_t boneXCenter, size_t boneYCenter, bool verticalDirection, char validBackGround);

	/**
	 * Método estático que desenha um Bone* numa charMatrix
	 * @param bone Bone* a desenhar
	 * @param charMatrix charMatrix onde se vai desenhar o Bone*
	 * @param boneXCenter posição central do Bone* e que está no eixo dos x da charMatrix onde se quer desenhar o Bone*
	 * @param boneYCenter posição central do Bone* e que está no eixo dos y da charMatrix onde se quer desenhar o Bone*
	 * @param verticalDirection flag que indica se se quer desenhar o Bone* na vertical (true) ou horizontal (false)
	 * @param validBackGroundChar char que indica qual o caracter de backGround do Board e como tal válido para desenhar por cima
	 * @return true caso seja possivel desenhar um bone na charMatrix sem ter problemas de sobreposição com outros Bones
	 */
	static bool drawBoneOnMatrix(Bone* bone, vector <vector <char> >& charMatrix, size_t boneXCenter, size_t boneYCenter, bool verticalDirection, char validBackGroundChar = BOARD_BACKGROUND_CHAR);

	/**
	 * Métod que desenha um dado Bone* na Board
	 * @param bone Bone* a desenhar
	 * @return true caso tenha desenhado com sucesso o Bone*, false caso alguma regra tenha sido infringida ou a para desenhar posição tenha sido inválida
	 */
	bool drawBoneOnBoard(Bone* bone);

	/// Método que incrementa o contador de número de Bones  que estão no Board
	void incrementNumberOfBonesOnBoard();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Board management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    vector<vector<char> > getBoardMatrix() const;
    Bone *getEastWingBone() const;
    DoubleBone *getFirstDoubleBone() const;
    Bone *getNorthWingBone() const;
    Bone *getSouthWingBone() const;
    Bone *getWestWingBone() const;
    unsigned getNumberOfBonesOnBoard() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setBoardMatrix(vector<vector<char> > boardMatrix);
    void setEastWingBone(Bone *eastWingBone);
    void setFirstDoubleBone(Bone *firstDoubleBone);
    void setNorthWingBone(Bone *northWingBone);
    void setSouthWingBone(Bone *southWingBone);
    void setWestWingBone(Bone *westWingBone);
    void setNumberOfBonesOnBoard(unsigned numberOfBonesOnBoard);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//===============================================================   </public>   =================================================================
};

#endif /* BOARD_H_ */
