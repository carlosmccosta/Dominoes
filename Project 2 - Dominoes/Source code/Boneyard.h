#ifndef BONEYARD_H_
#define BONEYARD_H_

/**\file Boneyard.h
 * \brief Classe que representa as peças do Domino que estão disponiveis para "compra" no Domino.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <vector>
#include <algorithm>
#include <ctime>

#include "defs.h"
#include "Bone.h"
#include "DoubleBone.h"


using std::vector;
using std::random_shuffle;


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/version.hpp>
//	#include <boost/serialization/export.hpp>
#endif


//#############################################################   Boneyard   #####################################################################
/**
 * \brief Classe que representa as peças do Domino que estão disponiveis para "compra" no Domino.
 */
class Boneyard {
//=============================================================   <private>   ====================================================================
private:
	vector <Bone*> bonePile;
	vector <Bone*> bonesInUse;


#ifdef USE_BOOST
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & bonePile;
		archive & bonesInUse;
	}
#endif
//=============================================================   </private>   ===================================================================


//==============================================================   <public>   ====================================================================
public:
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Default constructor de Boneyard
	 */
	Boneyard();


	/**
	 * Destructor de Boneyard que limpa de memória os Bones que foram alocados dinamicamente
	 */
	virtual ~Boneyard();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <BoneYard management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que inicializa o Boneyard, criandos os Bones do Domino
	 */
	void initBoneyard();

	/**
	 * Método que reinicializa o Boneyard (apaga os Bones antigos e cria novos, colocando o Boneyard no estado inicial)
	 */
	void resetBoneyard();

	/**
	 * Método que dealoca de memória os Bones do Boneyard (e os que estão a ser usados pelos players ou já estão no Board)
	 */
	void destroyBoneyard();

	/**
	 * Método que verifica se ainda à Bones para "comprar"
	 * @return true caso ainda se possa comprar Bones
	 */
	bool empty();

	/**
	 * Método que trata da compra de um Bone ao Boneyard
	 * @return Bone* que estava nos bones disponiveis para compra e que ainda não estava em jogo
	 */
	Bone* getLastBone();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </BoneYard management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    vector<Bone*>& getBonePile();
    vector<Bone*>& getBonesInUse();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setBonePile(const vector<Bone*> &bonePile);
    void setBonesInUse(vector<Bone*> &bonesInUse);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ===================================================================
};


#endif /* BONEYARD_H_ */
