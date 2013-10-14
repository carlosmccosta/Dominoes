/**\file DoubleBone.cpp
 * \brief Ficheiro com a implementação da classe DoubleBone.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "DoubleBone.h"


//#ifdef USE_BOOST
//	BOOST_CLASS_EXPORT_GUID(DoubleBone, "DoubleBone")
//#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Default contructor de DoubleBone
 */
DoubleBone::DoubleBone() : Bone(), boneConectedOnMiddleDownOrLeft(NULL), boneConectedOnMiddleUpOrRight(NULL) {}


/**
 * Contructor de DoubleBone - subclasse de Bone
 * @param _firstNumber Primeiro número do Bone
 * @param _secondNumber Segundo número do Bone
 * @param _positionOnBonesInUse Posição que o DoubleBone ocupa no vector <Bone*> no Boneyard
 * @param _xCenterPosOnBoardMatrix Posição no eixo dos x que ocupa na chatMatrix do Board
 * @param _yCenterPosOnBoardMatrix Posição no eixo dos y que ocupa na chatMatrix do Board
 * @param _leftSideBone Bone* para o bone que está conectado do lado esquerdo do Bone a ser criado
 * @param _rigthSideBone Bone* para o bone que está conectado do lado direito do Bone a ser criado
 * @param _upSideBone Bone* para o bone que está conectado n parte lateral de cima do Bone a ser criado
 * @param _downSideBone Bone* para o bone que está conectado n parte lateral de baixo do Bone a ser criado
 * @param _verticalDirection flag que indica se o Bone ficará na vertical (true) ou horizontal (false)
 */
DoubleBone::DoubleBone(char _firstNumber, char _secondNumber, size_t _positionOnBonesInUse,
		size_t _xCenterPosOnBoardMatrix, size_t _yCenterPosOnBoardMatrix,
		Bone* _leftSideBone, Bone* _rigthSideBone, Bone* _upSideBone, Bone* _downSideBone,
		bool _verticalDirection) :

		Bone(_firstNumber, _secondNumber, _positionOnBonesInUse,
				_xCenterPosOnBoardMatrix, _yCenterPosOnBoardMatrix, _leftSideBone, _rigthSideBone, _verticalDirection),
		boneConectedOnMiddleDownOrLeft(_upSideBone), boneConectedOnMiddleUpOrRight(_downSideBone) {}

/**
 * Destructor de DoubleBone
 */
DoubleBone::~DoubleBone() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
Bone *DoubleBone::getBoneConectedOnMiddleDownOrLeft() const {
	return boneConectedOnMiddleDownOrLeft;
}

Bone *DoubleBone::getBoneConectedOnMiddleUpOrRight() const {
	return boneConectedOnMiddleUpOrRight;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void DoubleBone::setBoneConectedOnMiddleDownOrLeft(Bone *boneConectedOnMiddleDownOrLeft) {
	this->boneConectedOnMiddleDownOrLeft = boneConectedOnMiddleDownOrLeft;
}

void DoubleBone::setBoneConectedOnMiddleUpOrRight(Bone *boneConectedOnMiddleUpOrRight) {
	this->boneConectedOnMiddleUpOrRight = boneConectedOnMiddleUpOrRight;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

