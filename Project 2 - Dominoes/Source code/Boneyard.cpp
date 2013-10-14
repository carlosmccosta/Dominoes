/**\file Boneyard.cpp
 * \brief Ficheiro com a implementação da classe Boneyard.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "Boneyard.h"


//#ifdef USE_BOOST
//	BOOST_CLASS_EXPORT_GUID(Boneyard, "Boneyard")
//#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Default constructor de Boneyard
 */
Boneyard::Boneyard() : bonePile(vector <Bone*>()), bonesInUse(vector <Bone*>()) {}


/**
 * Destructor de Boneyard que limpa de memória os Bones que foram alocados dinamicamente
 */
Boneyard::~Boneyard() {
	this->destroyBoneyard();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <BoneYard management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// random generator function:
ptrdiff_t RandomFunction (ptrdiff_t i) { return rand()%i;}

// pointer object to it:
ptrdiff_t (*PointerToRandomFunction)(ptrdiff_t) = RandomFunction;

/**
 * Método que inicializa o Boneyard, criandos os Bones do Domino
 */
void Boneyard::initBoneyard() {
	//criação dos bones do jogo
	for (char firstNumber = '0'; firstNumber < MAX_BONE_NUMBER; ++firstNumber) {
		for (char secondNumber = firstNumber; secondNumber < MAX_BONE_NUMBER; ++secondNumber) {
			if (firstNumber == secondNumber) {
				bonePile.push_back(new DoubleBone(firstNumber, secondNumber));
			} else {
				bonePile.push_back(new Bone(firstNumber, secondNumber));
			}
		}
	}


	srand((unsigned)time(NULL));
	random_shuffle(bonePile.begin(), bonePile.end(), PointerToRandomFunction);
}


/**
 * Método que reinicializa o Boneyard (apaga os Bones antigos e cria novos, colocando o Boneyard no estado inicial)
 */
void Boneyard::resetBoneyard() {
	destroyBoneyard();
	initBoneyard();
}


/**
 * Método que dealoca de memória os Bones do Boneyard (e os que estão a ser usados pelos players ou já estão no Board)
 */
void Boneyard::destroyBoneyard() {
	//dealocação da memória dos bones da bonepile
	for (size_t i = 0; i < bonePile.size(); ++i) {
		delete(bonePile[i]);
	}

	//dealocação da memória dos restantes bones que já estavam em jogo
	for (size_t i = 0; i < bonesInUse.size(); ++i) {
		delete(bonesInUse[i]);
	}

	bonePile.clear();
	bonesInUse.clear();
}


/**
 * Método que verifica se ainda à Bones para "comprar"
 * @return true caso ainda se possa comprar Bones
 */
bool Boneyard::empty() {
	return bonePile.empty();
}


/**
 * Método que trata da compra de um Bone ao Boneyard
 * @return Bone* que estava nos bones disponiveis para compra e que ainda não estava em jogo
 */
Bone* Boneyard::getLastBone() {
	if (bonePile.empty())
		return NULL;

	//obtenção do último bone da bonepile e retirada do mesmo
	Bone* lastBone = bonePile.back();
	//actualização da posição que o bone terá no bonesInUse (usado nos loads/saves)
	lastBone->setPositionOnBonesInUse(bonesInUse.size());

	bonePile.pop_back();

	//colocação do bone retirado no vector bonesInUse (vector usado para evitar memory leaks)
	bonesInUse.push_back(lastBone);

	return lastBone;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </BoneYard management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
vector<Bone*>& Boneyard::getBonePile() {
	return bonePile;
}

vector<Bone*>& Boneyard::getBonesInUse() {
	return bonesInUse;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Boneyard::setBonePile(const vector<Bone*> &bonePile) {
	this->bonePile = bonePile;
}

void Boneyard::setBonesInUse(vector<Bone*>& bonesInUse) {
	this->bonesInUse = bonesInUse;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
