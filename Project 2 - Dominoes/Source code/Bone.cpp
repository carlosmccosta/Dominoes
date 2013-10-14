/**\file Bone.cpp
 * \brief implementação da classe Bone que representa uma peça de um Domino com números diferentes.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "Bone.h"


//#ifdef USE_BOOST
//	BOOST_CLASS_EXPORT_GUID(Bone, "Bone")
//#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Default contructor de DoubleBone
 */
Bone::Bone() : firstNumber('0'), secondNumber('0'), positionOnBonesInUse(-1),
			xCenterPosOnBoardMatrix(0), yCenterPosOnBoardMatrix(0),
			boneConectedToFirstNumber(NULL), boneConectedToSecondNumber(NULL),
			verticalDirection(false),
			boneFirstNumberPositionOnBoard(BONE_FIRST_NUMBER_LEFT) {}



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
Bone::Bone(char _firstNumber, char _secondNumber, size_t _positionOnBonesInUse,
		size_t _xCenterPosOnBoardMatrix, size_t _yCenterPosOnBoardMatrix,
		Bone* _leftSideBone, Bone* _rigthSideBone, bool _verticalDirection) :

		firstNumber(_firstNumber), secondNumber(_secondNumber), positionOnBonesInUse(_positionOnBonesInUse),
		xCenterPosOnBoardMatrix(_xCenterPosOnBoardMatrix), yCenterPosOnBoardMatrix(_yCenterPosOnBoardMatrix),
		boneConectedToFirstNumber(_leftSideBone), boneConectedToSecondNumber(_rigthSideBone),
		verticalDirection(_verticalDirection) {

	if (_firstNumber == _secondNumber)
		boneFirstNumberPositionOnBoard = BONE_FIRST_NUMBER_UP;
	else
		boneFirstNumberPositionOnBoard = BONE_FIRST_NUMBER_LEFT;
}



/**
 * Destructor de Bone
 */
Bone::~Bone() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Bone management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que verifica se o Bone é DoubleBone (a ser usado para antes de fazer o cast da subclasse DoubleBone)
 * @return true se for DoubleBone
 */
bool Bone::isDoubleBone() {
	return (firstNumber == secondNumber);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Bone management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
char Bone::getFirstNumber() const {
	return firstNumber;
}

char Bone::getSecondNumber() const {
	return secondNumber;
}

size_t Bone::getPositionOnBonesInUse() const {
	return positionOnBonesInUse;
}

size_t Bone::getXCenterPosOnBoardMatrix() const {
	return xCenterPosOnBoardMatrix;
}

size_t Bone::getYCenterPosOnBoardMatrix() const {
	return yCenterPosOnBoardMatrix;
}

Bone *Bone::getBoneConectedToFirstNumber() const {
	return boneConectedToFirstNumber;
}

Bone *Bone::getBoneConectedToSecondNumber() const {
	return boneConectedToSecondNumber;
}


bool Bone::getVerticalDirection() const {
	return verticalDirection;
}

BoneFirstNumberPositionOnBoard Bone::getBoneFirstNumberPositionOnBoard() {
	return boneFirstNumberPositionOnBoard;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Bone::setFirstNumber(char firstNumber) {
	this->firstNumber = firstNumber;
}

void Bone::setSecondNumber(char secondNumber) {
	this->secondNumber = secondNumber;
}

void Bone::setPositionOnBonesInUse(size_t positionOnBonesInUse) {
	this->positionOnBonesInUse = positionOnBonesInUse;
}

void Bone::setXCenterPosOnBoardMatrix(size_t xCenterPosOnBoardMatrix) {
	this->xCenterPosOnBoardMatrix = xCenterPosOnBoardMatrix;
}

void Bone::setYCenterPosOnBoardMatrix(size_t yCenterPosOnBoardMatrix) {
	this->yCenterPosOnBoardMatrix = yCenterPosOnBoardMatrix;
}

void Bone::setBoneConectedToFirstNumber(Bone *boneConectedToFirstNumber) {
	this->boneConectedToFirstNumber = boneConectedToFirstNumber;
}

void Bone::setBoneConectedToSecondNumber(Bone *boneConectedToSecondNumber) {
	this->boneConectedToSecondNumber = boneConectedToSecondNumber;
}

void Bone::setVerticalDirection(bool verticalDirection) {
	this->verticalDirection = verticalDirection;
}

void Bone::setBoneFirstNumberPositionOnBoard(BoneFirstNumberPositionOnBoard boneFirstNumberPositionOnBoard) {
	this->boneFirstNumberPositionOnBoard = boneFirstNumberPositionOnBoard;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
