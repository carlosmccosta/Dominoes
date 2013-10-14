#ifndef BONE_H_
#define BONE_H_


/**\file Bone.h
 * \brief Classe que representa uma peça de um Domino com números diferentes.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <cstddef>

#include "defs.h"


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
//	#include <boost/serialization/export.hpp>
#endif


enum BoneFirstNumberPositionOnBoard { BONE_FIRST_NUMBER_UP, BONE_FIRST_NUMBER_DOWN, BONE_FIRST_NUMBER_LEFT, BONE_FIRST_NUMBER_RIGHT };


//################################################################   Bone   ######################################################################
/**
 * \brief Classe que representa uma peça de um Domino com número diferentes.
 */
class Bone {
//==============================================================   <private>   ===================================================================
private:
	char firstNumber;
	char secondNumber;
	size_t positionOnBonesInUse;
	size_t xCenterPosOnBoardMatrix;
	size_t yCenterPosOnBoardMatrix;
	Bone* boneConectedToFirstNumber;
	Bone* boneConectedToSecondNumber;

	bool verticalDirection;
	BoneFirstNumberPositionOnBoard boneFirstNumberPositionOnBoard;

#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & firstNumber;
		archive & secondNumber;
		archive & positionOnBonesInUse;
		archive & xCenterPosOnBoardMatrix;
		archive & yCenterPosOnBoardMatrix;
		archive & boneConectedToFirstNumber;
		archive & boneConectedToSecondNumber;
		archive & verticalDirection;
		archive & boneFirstNumberPositionOnBoard;
	}
#endif

//==============================================================   <private>   ==================================================================


//==============================================================   <public>   ===================================================================
public:
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Default contructor de Bone
	 */
	Bone();


	/**
     * Contructor de Bone
     * @param _firstNumber Primeiro número do Bone
     * @param _secondNumber Segundo número do Bone
     * @param positionOnBonesInUse Posição que o DoubleBone ocupa no vector <Bone*> no Boneyard
     * @param _xCenterPosOnBoardMatrix Posição no eixo dos x que ocupa na chatMatrix do Board
     * @param _yCenterPosOnBoardMatrix Posição no eixo dos y que ocupa na chatMatrix do Board
     * @param _leftSideBone Bone* para o bone que está conectado do lado esquerdo do Bone a ser criado
     * @param _rigthSideBone Bone* para o bone que está conectado do lado direito do Bone a ser criado
     * @param _verticalDirection flag que indica se o Bone ficará na vertical (true) ou horizontal (false)
     */
	Bone(char _firstNumber, char _secondNumber, size_t positionOnBonesInUse = -1, size_t _xCenterPosOnBoardMatrix = 0, size_t _yCenterPosOnBoardMatrix = 0, Bone *_leftSideBone = NULL, Bone *_rigthSideBone = NULL, bool _verticalDirection = false);

	/**
	 * Destructor de Bone
	 */
    virtual ~Bone();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Bone management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /**
     * Método que verifica se o Bone é DoubleBone (a ser usado para antes de fazer o cast da subclasse DoubleBone)
     * @return true se for DoubleBone
     */
    bool isDoubleBone();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Bone management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    char getFirstNumber() const;
    char getSecondNumber() const;
    size_t getPositionOnBonesInUse() const;
    size_t getXCenterPosOnBoardMatrix() const;
    size_t getYCenterPosOnBoardMatrix() const;
    Bone *getBoneConectedToFirstNumber() const;
    Bone *getBoneConectedToSecondNumber() const;
    bool getVerticalDirection() const;
    BoneFirstNumberPositionOnBoard getBoneFirstNumberPositionOnBoard();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setFirstNumber(char firstNumber);
    void setSecondNumber(char secondNumber);
    void setPositionOnBonesInUse(size_t positionOnBonesInUse);
    void setXCenterPosOnBoardMatrix(size_t xCenterPosOnBoardMatrix);
    void setYCenterPosOnBoardMatrix(size_t yCenterPosOnBoardMatrix);
    void setBoneConectedToFirstNumber(Bone *boneConectedToFirstNumber);
    void setBoneConectedToSecondNumber(Bone *boneConectedToSecondNumber);
    void setVerticalDirection(bool verticalDirection);
    void setBoneFirstNumberPositionOnBoard(BoneFirstNumberPositionOnBoard boneFirstNumberPositionOnBoard);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ==================================================================
};


#endif /* BONE_H_ */
