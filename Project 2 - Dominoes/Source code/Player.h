#ifndef PLAYER_H_
#define PLAYER_H_

/**\file Player.h
 * \brief Classe que representa um dos 4 jogadores possiveis no jogo do Domino.
 *
 * @version Projecto 2 - Programação - Domino - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <string>
#include <vector>

#include "defs.h"
#include "Bone.h"
#include "Board.h"


using std::string;
using std::vector;
using std::endl;


#ifdef USE_BOOST
	#include <boost/serialization/access.hpp>
	#include <boost/serialization/vector.hpp>
	#include <boost/serialization/string.hpp>
	#include <boost/serialization/version.hpp>
//	#include <boost/serialization/export.hpp>
#endif


//##############################################################   Player   #####################################################################
/**
 * \brief Classe que representa um dos 4 jogadores possiveis no jogo do Domino.
 */
class Player {
//=============================================================   <private>   ===================================================================
private:
	string name;
	bool AIPlayer;
	unsigned score;

	vector<Bone*> playerBones;


#ifdef USE_BOOST
	friend class boost::serialization::access;

    template<class Archive> void serialize(Archive & archive, const unsigned int version) {
		archive & name;
		archive & AIPlayer;
		archive & score;
		archive & playerBones;
	}
#endif
//=============================================================   </private>   ==================================================================


//==============================================================   <public>   ===================================================================
public:
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /**
     * Default contructor de player
     */
    Player();

    /**
     * Contructor de um player
     * @param _name Nome a dar ao player
     * @param _AIPlayer flag que indica se o player deve ser controlado pela AI (se for true) ou por um utilizador (se for false)
     */
    Player(string _name, bool _AIPlayer = false);

    /**
     * Destructor de player
     */
    virtual ~Player();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Player management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que adiciona um Bone* aos Bones do player
	 * @param boneToAdd Bone* a adicionar
	 */
	void addBone(Bone* boneToAdd);

	/**
	 * Método que retorna o Bone* que está na posição index do vector <Bone*> do player
	 * @param index Posição do Bone* que se quer
	 * @return Bone* que está na posição indicada
	 */
	Bone* getBone(size_t index);

	/**
	 * Método que retira todos os bones que estavam associados ao player
	 */
	void resetPlayerBones();

	/**
	 * Método que adiciona o numero de pontos dado à pontuação do player
	 * @param points Número de pontos a adicionar
	 */
	void addPoints(unsigned points);

	/**
	 * Método que remove um dado Bone* que esteja associado ao player
	 * @param boneToRemove Bone* a remover do player
	 */
	void removeBone(Bone* boneToRemove);

	/**
	 * Método que verifica se o player tem um Bone que seja DoubleBone
	 * @return True caso o player tenha pelo menos um DoubleBone*
	 */
	bool playerHasDoubleBones();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Player management>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Player CLI interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * Método que mostra os Bones do player na consola
	 */
	void showPlayerBonesCLI();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Player CLI interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	string getName() const;
	bool getAIPlayer() const;
	unsigned getScore() const;
    vector<Bone*>& getPlayerBones();
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setName(string name);
    void setAIPlayer(bool AIPlayer);
    void setScore(unsigned  newScore);
    void setPlayerBones(const vector<Bone*>& playerBones);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//==============================================================   </public>   ==================================================================
};


#endif /* PLAYER_H_ */
