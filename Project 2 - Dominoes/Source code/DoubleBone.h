#ifndef DOUBLEBONE_H_
#define DOUBLEBONE_H_

/**\file DoubleBone.h
 * \brief Classe que representa uma peça de um Domino com números iguais.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "defs.h"
#include "Bone.h"


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
	#include <boost/serialization/base_object.hpp>
//	#include <boost/serialization/export.hpp>
#endif


//############################################################   DoubleBone   ###################################################################
/**
 * \brief Classe que representa uma peça de um Domino com números iguais.
 */
class DoubleBone : public Bone {
//=============================================================   <private>   ===================================================================
private:
	Bone* boneConectedOnMiddleDownOrLeft;
	Bone* boneConectedOnMiddleUpOrRight;


#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & boost::serialization::base_object<Bone>(*this);
		archive & boneConectedOnMiddleDownOrLeft;
		archive & boneConectedOnMiddleUpOrRight;
	}
#endif
//=============================================================   </private>   ==================================================================


//==============================================================   <public>   ===================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Default contructor de DoubleBone
	 */
	DoubleBone();

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
	DoubleBone(char _firstNumber, char _secondNumber, size_t positionOnBonesInUse = -1,
			size_t _xCenterPosOnBoardMatrix = 0, size_t _yCenterPosOnBoardMatrix = 0,
			Bone* _leftSideBone = NULL, Bone* _rigthSideBone = NULL, Bone* _upSideBone = NULL, Bone* _downSideBone = NULL,
			bool _verticalDirection = true);

	/**
	 * Destructor de DoubleBone
	 */
	virtual ~DoubleBone();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    Bone *getBoneConectedOnMiddleDownOrLeft() const;
    Bone *getBoneConectedOnMiddleUpOrRight() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setBoneConectedOnMiddleDownOrLeft(Bone *boneConectedOnMiddleDownOrLeft);
    void setBoneConectedOnMiddleUpOrRight(Bone *boneConectedOnMiddleUpOrRight);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ==================================================================
};


#endif /* DOUBLEBONE_H_ */
