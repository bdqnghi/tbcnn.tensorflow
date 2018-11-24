/*
////////////////////////////////////////////////
/// @file QuadTree.cpp
/// @author The Ballers
/// @date 2015-02-24
///
/// @ingroup QuadTree
////////////////////////////////////////////////

#include "QuadTree.h"
#include <algorithm>


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] inferieurGauche : Les limites du QuadTree
/// @param[in] superieurDroit : Les limites du QuadTree
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
{
	niveauCourant_ = 0;
	inferieurGauche_ = inferieurGauche;
	superieurDroit_ = superieurDroit;

	nordEst_ = nullptr;
	nordOuest_ = nullptr;
	sudEst_ = nullptr;
	sudOuest_ = nullptr;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::QuadTree(int level, glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
///
/// Constructeur qui initialise les variables membres de la classe.
///
/// @param[in] level : le niveau du QuadTree
/// @param[in] inferieurGauche : Les limites du QuadTree Gauche
/// @param[in] superieurDroit : Les limites du QuadTree Droite
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::QuadTree(int level, glm::dvec3 inferieurGauche, glm::dvec3 superieurDroit)
{
	inferieurGauche_ = inferieurGauche;
	superieurDroit_ = superieurDroit;
	niveauCourant_ = level;

	nordEst_ = nullptr;
	nordOuest_ = nullptr;
	sudEst_ = nullptr;
	sudOuest_ = nullptr;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree::~QuadTree()
///
/// Le destructeur desalloue l'espace attribue dynamiquement. Il appelle
///	la methode clear().
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
QuadTree::~QuadTree()
{
	clear();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::divide()
///
/// Cette methode alloue dynamiquement les sous QuadTree avec les bonnes
///	limites spaciales. 
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void QuadTree::divide()
{
	//					+------+------+  superieurDroit
	//					|	   |      |
	//					|  NO  |  NE  |
	//					+------+------+
	//					|      |      |
	//					|  SO  |  SE  |
	//					+------+------+
	//	inferieurGauche

	double centreX = ((superieurDroit_.x - inferieurGauche_.x) / 2.0) + inferieurGauche_.x;
	double centreY = ((superieurDroit_.y - inferieurGauche_.y) / 2.0) + inferieurGauche_.y;

	nordEst_ = new QuadTree(niveauCourant_ + 1, { centreX, centreY, 0 }, superieurDroit_);
	nordOuest_ = new QuadTree(niveauCourant_ + 1, { inferieurGauche_.x, centreY, 0 }, { centreX, superieurDroit_.y, 0 });
	sudEst_ = new QuadTree(niveauCourant_ + 1, { centreX, inferieurGauche_.y, 0 }, { superieurDroit_.x, centreY, 0 });
	sudOuest_ = new QuadTree(niveauCourant_ + 1, inferieurGauche_, { centreX, centreY, 0 });

}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::clear()
///
///	Cette methode vide la liste des noeuds d'un QuadTree et s'occupe de
///	la desallocation de memoire de ses sous QuadTree.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void QuadTree::clear()
{
	objets_.clear();

	if (nordEst_ != nullptr)
	{
		nordEst_->clear();
		nordOuest_->clear();
		sudEst_->clear();
		sudOuest_->clear();

		/// Desallouer la memoire
		delete nordEst_;
		delete nordOuest_;
		delete sudEst_;
		delete sudOuest_;

		/// Remettre les pointeurs a nullptr
		nordEst_ = nullptr;
		nordOuest_ = nullptr;
		sudEst_ = nullptr;
		sudOuest_ = nullptr;
	}

}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool QuadTree::estDansQuadTree(NoeudAbstrait* noeud, QuadTree* quad) const
///
/// Cette methode permet de savoir si un noeud est completement contenu dans
///	un QuadTree.
///
/// @param[in] noeud : le noeud a inserer
/// @param[in] quad : le quad dans lequel on veut inserer
///
/// @return True lorsque le noeud est dans le QuadTree passe en parametre. False autrement
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::estDansQuadTree(NoeudAbstrait* noeud, QuadTree* quad) const
{
	if (quad == nullptr)
		return false;

	std::vector<glm::dvec3> points;

	// Obtenir les 4 points de la boite englobante
	points = noeud->obtenirVecteursEnglobants();

	// Le cas ou ce n'est pas un objet qui a une forme circulaire
	if (points.size() > 1)
	{
		for (int i = 0; i < 4; i++)
			points[i] += noeud->obtenirPositionRelative();

		// Si un des points n'est pas dans le QuadTree, retourner false
		for (unsigned int i = 0; i < points.size(); i++)
		{
			if (!(estDansQuadTree(points[i], quad)))
				return false;
		}

		// Le point est dans le QuadTree
		return true;
	}

	// Le cas ou c'est un objet qui a une forme circulaire
	else if (points.size() == 1)
	{
		glm::dvec3 position = noeud->obtenirPositionRelative();
		double rayon = points[0].x;

		glm::dvec3 nord = { position.x, position.y + rayon, position.z };
		glm::dvec3 sud = { position.x, position.y - rayon, position.z };
		glm::dvec3 est = { position.x + rayon, position.y, position.z };
		glm::dvec3 ouest = { position.x - rayon, position.y, position.z };

		if (estDansQuadTree(nord, quad) && estDansQuadTree(sud, quad)
			&& estDansQuadTree(est, quad) && estDansQuadTree(ouest, quad))
			return true;

		else
			return false;
	}

	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool QuadTree::estDansQuadTree(glm::dvec3 points, QuadTree* quad) const
///
/// Cette methode permet de savoir si un point est completement contenu dans
///	un QuadTree.
///
/// @param[in] points : le point a verifier
/// @param[in] quad : le quad dans lequel on veut inserer
///
/// @return True lorsque le point est dans le QuadTree passe en parametre. False autrement
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::estDansQuadTree(glm::dvec3 points, QuadTree* quad) const
{
	if (quad == nullptr)
		return false;

	if ( (points.x > quad->inferieurGauche_.x) && (points.x < quad->superieurDroit_.x)
	  && (points.y > quad->inferieurGauche_.y) && (points.y < quad->superieurDroit_.y))
		return true;

	else
		return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn QuadTree* QuadTree::obtenirQuadrant(NoeudAbstrait* noeud)
///
/// Cette methode retourne le quadrant dans lequel il faudra inserer
/// un noeud. Retourne le parent des quadrants si le noeud est a l'intersection
///	de plusieurs quadrants
///
/// @param[in] noeud : le noeud a inserer
///
/// @return QuadTree*, le quadTree dans lequel il faudra inserer le noeud
///
////////////////////////////////////////////////////////////////////////
QuadTree* QuadTree::obtenirQuadrant(NoeudAbstrait* noeud)
{
	// Si le noeud est completement dans le quadrant Nord-Est
	if (estDansQuadTree(noeud, nordEst_))
		return nordEst_;

	// Si le noeud est completement dans le quadrant Nord-Ouest
	if (estDansQuadTree(noeud, nordOuest_))
		return nordOuest_;

	// Si le noeud est completement dans le quadrant Sud-Ouest
	if (estDansQuadTree(noeud, sudOuest_))
		return sudOuest_;

	// Si le noeud est completement dans le quadrant Sud-Est
	if (estDansQuadTree(noeud, sudEst_))
		return sudEst_;

	// Si le noeud est a l'intersection de deux quadrants et plus
	else
		return this;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void QuadTree::insert(NoeudAbstrait* noeud)
///
/// Cette methode insere un noeud dans le QuadTree
///
/// @param[in] noeud : le noeud a inserer
///
/// @return True lorsque le noeud a ete inserer, false autrement
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::insert(NoeudAbstrait* noeud)
{
	if (!noeud->estAffiche())
		return false;

	// Inserer le noeud seulement si le noeud est dans le Quadtree
	if (estDansQuadTree(noeud, this))
	{
		// Inserer l'objet dans le QuadTree courant si aucun de ses sous QuadTree ne peut l'accueuillir
		if (objets_.size() < MAX_CAPACITY && niveauCourant_ < MAX_LEVEL && obtenirQuadrant(noeud) == this)
		{
			objets_.push_back(noeud);
			return true;
		}

		// Subdiviser et reassigner les objets deja existants
		if (nordEst_ == nullptr)
		{
			divide();

			std::list<NoeudAbstrait*> copy = objets_;
			std::list<NoeudAbstrait*>::iterator iter;

			objets_.clear();

			// Reassigner les objets qui etaient precedemment inseres 
			for (iter = copy.begin(); iter != copy.end(); iter++)
				obtenirQuadrant(*iter)->insert(*iter);

			// Ajouter le nouveau noeud
			obtenirQuadrant(noeud)->insert(noeud);

			return true;
		}

		// Si le QuadTree contient deja des sous QuadTree, inserer le noeud dans le bon QuadTree
		else if (nordEst_ != nullptr && obtenirQuadrant(noeud) != this)
		{
			obtenirQuadrant(noeud)->insert(noeud);
			return true;
		}

		// Ne devrait JAMAIS se rendre jusqu'ici
		else
			return false;

	}

	// Ne pas inserer le noeud, il n'est pas dans les limites
	else
		return false;

}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
///
/// Cette methode retourne la liste des noeuds qui sont dans le meme QuadTree que
/// le noeud passe en parametre.
///
/// @param[in] noeud : le noeud pour lequel on desire ses voisins
///
/// @return l'ensemble des noeuds qui sont dans le meme QuadTree que le noeud passe
///			en parametre
///
////////////////////////////////////////////////////////////////////////
std::list<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
{
	std::list<NoeudAbstrait*> listeNoeuds;

	if (estDansQuadTree(noeud, this))
	{
		// Le quad n'a pas de sous QuadTree
		if (nordEst_ == nullptr)
			return objets_;

		// Le quad a un sous QuadTree et le parent de ce dernier ne contient aucun noeud
		else if (nordEst_ != nullptr && objets_.size() == 0)
			return obtenirQuadrant(noeud)->retrieve(noeud);

		// Le quad a un sous QuadTree et le parent de ce dernier contient des noeuds
		else if (nordEst_ != nullptr && objets_.size() != 0)
		{
			if (obtenirQuadrant(noeud) != this)
			{
				std::list<NoeudAbstrait*> sousQuad = obtenirQuadrant(noeud)->retrieve(noeud);
				std::list<NoeudAbstrait*>::iterator iter;

				// Ajouter d'abord les noeuds du parent
				listeNoeuds = objets_;

				// Ajouter les noeuds du sous QuadTree
				for (iter = sousQuad.begin(); iter != sousQuad.end(); iter++)
					listeNoeuds.push_back(*iter);

				sousQuad.clear();

				return listeNoeuds;
			}

			// Retourner tous les objets du QuadTree, incluant les objets de ses sous QuadTree
			else if (obtenirQuadrant(noeud) == this)
			{
				std::list<NoeudAbstrait*> nordEst = nordEst_->objets_;
				std::list<NoeudAbstrait*> nordOuest = nordOuest_->objets_;
				std::list<NoeudAbstrait*> sudEst = sudEst_->objets_;
				std::list<NoeudAbstrait*> sudOuest = sudOuest_->objets_;
				std::list<NoeudAbstrait*>::iterator iter;

				listeNoeuds = objets_;

				for (iter = nordEst.begin(); iter != nordEst.end(); iter++)
					listeNoeuds.push_back(*iter);

				for (iter = nordOuest.begin(); iter != nordOuest.end(); iter++)
					listeNoeuds.push_back(*iter);

				for (iter = sudEst.begin(); iter != sudEst.end(); iter++)
					listeNoeuds.push_back(*iter);

				for (iter = sudOuest.begin(); iter != sudOuest.end(); iter++)
					listeNoeuds.push_back(*iter);

				nordEst.clear();
				nordOuest.clear();
				sudEst.clear();
				sudOuest.clear();

				return listeNoeuds;
			}
			
			// Ne devrait JAMAIS se rendre ici
			else
				return listeNoeuds;
		}

		// Ne devrais JAMAIS se rendre ici
		else
			return listeNoeuds;

	}

	// Liste vide si le noeud n'est pas dans le QuadTree
	else
		return listeNoeuds;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn std::vector<NoeudAbstrait*> QuadTree::retrieve(NoeudAbstrait* noeud)
///
/// Cette methode retourne la liste des noeuds qui sont dans le meme QuadTree que
/// le noeud passe en parametre.
///
/// @param[in] noeud : le noeud pour lequel on desire ses voisins
///
/// @return l'ensemble des noeuds qui sont dans le meme QuadTree que le noeud passe
///			en parametre
///
////////////////////////////////////////////////////////////////////////
bool QuadTree::remove(NoeudAbstrait* noeud)
{
	if (noeud == nullptr)
		return false;

	if (estDansQuadTree(noeud, this))
	{
		std::list<NoeudAbstrait*>::iterator iter;

		// On verifie s'il est dans un sous QuadTree
		if (obtenirQuadrant(noeud) != this)
		{
			obtenirQuadrant(noeud)->remove(noeud);
			return true;
		}

		else
		{
			objets_.remove(noeud);
			return true;
		}
	}

	else
		return false;
}
*/